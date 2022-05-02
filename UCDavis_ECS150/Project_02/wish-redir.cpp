#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <vector>

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

void printerror();
void prompt();
vector<string> parseline(string line);
void wish_cd(vector<string> cmd);
void updatepath(vector<string> &pathvar, vector<string> &command);
void executeCommand(vector<string> &command, vector<string> &pathvar, bool hasredirection, int tracker);
void runCommands(vector<string> &command, vector<string> &pathvar, bool hasredirection, int tracker);


int main(int argc, char *argv[]) {

    string line;
    vector<string> arguments;
    vector<vector<string>> commandList;
    vector<string> command;
    vector<string> pathvar;

    // https://stackoverflow.com/questions/2407077/read-from-cin-or-a-file
    ifstream filein;
    streambuf *backup, *fbuf;

    if(argc > 2) {
        printerror();
        return 1;
    }

    if(argc == 2) {    
        filein.open(argv[1]);
        if(filein.is_open()) {
            backup = cin.rdbuf();
            fbuf = filein.rdbuf();
            cin.rdbuf(fbuf);
        }
        else {
            printerror();
            return 1;
        }
        
    }   
    
    // Prompt if needed
    if(argc == 1) prompt(); 

    pathvar.push_back("/bin/");
    pathvar.push_back("/usr/bin");

    

    // Main Loop
    while(getline(cin, line)) {

        arguments = parseline(line);  
        command = arguments; 
        if(command.size() > 0) commandList.push_back(command);
        
        
        
        for(unsigned int i = 0; i < commandList.size(); i++) {

            vector<string>::iterator point;
            point = std::find (commandList[i].begin(), commandList[i].end(), ">");


            if( point != commandList[i].end() ) {
                
                // find location
                unsigned int tracker = 0;
                bool founddirect = false;
                for(unsigned int j = 0; j < commandList[i].size(); j++) {
                    if(commandList[i][j] == ">" && !founddirect) {
                        tracker = j;
                        founddirect = true;
                    }
                }

                // additional conditions
                if( (tracker != (commandList[i].size() - 2)) || (commandList[i][tracker+1] == ">")) {
                    printerror();
                }
                else {
                    runCommands(commandList[i], pathvar, true, tracker);
                }
            }
            else {
                // cout << "skipping" << endl;
                runCommands(commandList[i], pathvar, false, 0);
            } 

        }

        while(!commandList.empty()) {
            commandList.pop_back();
        }

        // prompt for next if STDIN
        while(!command.empty()) command.pop_back(); 
        if(argc == 1) prompt();

        
    }

    // If/when getline fails, exit(0)
    cin.rdbuf(backup);
    exit(0);

}

void printerror() {
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message));     
};

void prompt() {
    char prompt[7] = "wish> ";
    write(STDOUT_FILENO, prompt, strlen(prompt));
};

vector<string> parseline(string line) {

    vector<string> arguments;
    string temp;

    for(unsigned int i = 0; i < line.length(); i++) {
        
        // if whitespace
        if(isspace(line[i])) {
            if(temp.length() > 0){
                arguments.push_back(temp);
                temp.clear();
            }       
        }
        // if command splitter
        else if ( (line[i] == '|') || (line[i] == '&') || (line[i] == '>') ) {
            
            // if temp has argument
            if(temp.length() > 0) {
                arguments.push_back(temp);
                temp.clear();  
            }
            
            temp.push_back(line[i]);
            arguments.push_back(temp);
            temp.clear();
        }
        // if last character
        else if(i == line.length()-1) {
            temp.push_back(line[i]);
            arguments.push_back(temp);
            temp.clear();
        }
        // if regular character
        else {
            temp.push_back(line[i]);
        }
        
    }

    return arguments;
};

void wish_cd(vector<string> cmd) {
    if(cmd.size() != 2) {
        printerror();
    }
    else {
        if(chdir(cmd[1].c_str()) != 0) {
            printerror();
        }
    } 
};

void updatepath(vector<string> &pathvar, vector<string> &command) {
    
    while(!pathvar.empty()){
        pathvar.pop_back();
    }    

    for(unsigned int i = 1; i < command.size(); i++){   
        string topush = command[i];
        topush += "/";                
        pathvar.push_back(topush);  
    }

    // Add arguments to the path
    char cwd[200];
    getcwd(cwd, sizeof(cwd));

    for(unsigned int i = 0; i < pathvar.size(); i++){

        if(pathvar[0][0] == '/') {
            pathvar[i] += command[1];
        }
        else {
            string temp = pathvar[i];
            pathvar[i] = cwd;
            pathvar[i] += "/";
            pathvar[i] += temp;
        }    
    }

};

void executeCommand(vector<string> &command, vector<string> &pathvar, bool hasredirection, int tracker) {
    

    // Add arguments to char array, create path
    char **myargs = new char*[command.size() + 1];
    for(unsigned int i = 0; i < command.size(); i++) {
        myargs[i] = strdup(command[i].c_str());
    }
    myargs[command.size()] = nullptr;


    string commandpath = pathvar[0];
    for(unsigned int i = 0; i < pathvar.size(); i++){
        
        if(access(pathvar[i].c_str(), X_OK) >= 0){
            commandpath = pathvar[i];
            commandpath += myargs[0];
            i = pathvar.size();
        }
    }
  

    // If path valid, allocate variables for process, run process
    if(access(commandpath.c_str(), X_OK) < 0) {
        printerror();
    }
    else{
        pid_t PID;
        int PIDstatus;
        PID = fork();

       
        if(PID == 0) {

            if(hasredirection) {

                const char* filename = command[tracker+1].c_str();
                int fd;
                // cout << "filename is: " << filename << endl;
                // cout << "command is: ";
                // for(unsigned int i = 0; i < command.size(); i++) {
                //     cout << "command[" << i << "] is " << command[i] << endl;
                // }
                        
                fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
                dup2(fd, 1);
                dup2(fd, 2);
                close(fd);
                
                command.pop_back();
                command.pop_back(); 

                // Add arguments to char array, create path
                char **myargsREDIR = new char*[command.size() + 1];
                for(unsigned int i = 0; i < command.size(); i++) {
                    myargsREDIR[i] = strdup(command[i].c_str());
                }
                myargsREDIR[command.size()] = nullptr;

                execv(commandpath.c_str(), myargsREDIR);

            }

            execv(commandpath.c_str(), myargs);
            printerror();
            cout << "error: " << errno << endl;
        }
        else if(PID < 0) {
            printerror();
        }
        else {
            waitpid(PID, &PIDstatus, 0);
        }
    }

};

void runCommands(vector<string> &command, vector<string> &pathvar, bool hasredirection, int tracker) {

    if(command[0] == "exit") {
        if(command.size() != 1) {
            printerror();
        }
        exit(0);
    }
    else if(command[0] ==  "cd") {
        wish_cd(command);
    }
    else if(command[0] == "path" && command.size() == 1) {
        while(!pathvar.empty()){
            pathvar.pop_back();
        }  
    }
    else if(command[0] == "path") {
        updatepath(pathvar, command);
    }   
    else {
        
        if(!pathvar.empty()) {
            executeCommand(command, pathvar, hasredirection, tracker);
        }
        else {
            printerror();
        }
        
    }   
};