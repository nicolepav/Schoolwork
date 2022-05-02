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
void checkRedir(vector<string> &command, vector<string> &pathvar);
void runCommands(vector<string> &command, vector<string> &pathvar, bool hasredirection, int tracker);
void executeCommand(vector<string> &command, vector<string> &pathvar, bool hasredirection, int tracker);



int main(int argc, char *argv[]) {

    string line;
    vector<string> arguments;
    vector<vector<string>> commandList;
    vector<string> command;
    vector<string> pathvar;
    ifstream filein;
    streambuf *backup, *fbuf;     // https://stackoverflow.com/questions/2407077/read-from-cin-or-a-file
    
    pathvar.push_back("/bin/");
    pathvar.push_back("/usr/bin");

    // Prompt if needed
    if(argc == 1) prompt(); 

    // Batch Mode
    if(argc == 2) {    
        filein.open(argv[1]);
        if(filein.is_open()) {
            backup = cin.rdbuf();
            fbuf = filein.rdbuf();
            cin.rdbuf(fbuf);
        }
        else {
            printerror();
            exit(1);
        }
        
    }  
    else if(argc > 2) {
        printerror();
        exit(1);
    } 
    

    // Main Loop
    while(getline(cin, line)) {

        arguments = parseline(line);  

        // If there is parallelism
        vector<string>::iterator pll;
        vector<string> temp;
        pll = std::find (arguments.begin(), arguments.end(), "&");
        if(pll != arguments.end()) {
            for(unsigned int i = 0; i < arguments.size(); i++) {
                
                if(arguments[i] == "&") {
                    // split
                    if(temp.size() > 0) commandList.push_back(temp);
                    temp.clear();
                }
                else if(i == arguments.size()-1) {
                    // last argument
                    temp.push_back(arguments[i]);
                    if(temp.size() > 0) commandList.push_back(temp);
                    temp.clear();
                }
                else {
                    temp.push_back(arguments[i]);
                } 
            }
        }
        else {
            command = arguments; 
            if(command.size() > 0) commandList.push_back(command);
        }

        // Cycle through all commands
        for(unsigned int i = 0; i < commandList.size(); i++) {
            checkRedir(commandList[i], pathvar);
        }
        while(wait(NULL) != -1 || errno != ECHILD);


        // Empty the command list for next line
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
    
    // empty path
    while(!pathvar.empty()){
        pathvar.pop_back();
    }    

    // Add the paths as passed from command
    for(unsigned int i = 1; i < command.size(); i++){   
        string topush = command[i];
        pathvar.push_back(topush); 
        topush.clear(); 
    }

    // Get the current directory
    char cwd[200];
    getcwd(cwd, sizeof(cwd));

    // Format the paths, Add arguments to the path
    for(unsigned int i = 0; i < pathvar.size(); i++){

        if(pathvar[0][0] == '/') {
            pathvar[i] += '/';
        }
        else {
            string temp = pathvar[i];
            pathvar[i] = cwd;
            pathvar[i] += "/";
            pathvar[i] += temp;
            pathvar[i] += '/';
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
    
    // Grab the first COMMANDPATH that works
    string commandpath;
    vector<string> commandPaths;
    string temp;
    bool foundvalidpath = false;

    // Create vector of potential commandpaths
    for(unsigned int i = 0; i < pathvar.size(); i++) {
        temp += pathvar[i];
        temp += myargs[0];
        commandPaths.push_back(temp);
        temp.clear();
    }

    // Check all command paths
    for(unsigned int i = 0; i < commandPaths.size(); i++){
        
        if(access(commandPaths[i].c_str(), X_OK) >= 0){
            commandpath = commandPaths[i];
            i = commandPaths.size();
            foundvalidpath = true;
        }
    }


    // If path valid, allocate variables for process, run process
    // error if no path found and dont fork
    if(!foundvalidpath) {
        printerror();
    }
    else{
        pid_t PID;
        PID = fork();       
        if(PID == 0) {
            if(hasredirection) {

                // Open redirection file
                const char* filename = command[tracker+1].c_str();
                int fd;                  
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
    }

};

void checkRedir(vector<string> &command, vector<string> &pathvar) {

    // Find redirection
    vector<string>::iterator point;
    point = std::find (command.begin(), command.end(), ">");

    // If Has Redirection
    if( point != command.end() ) {
        
        // find location
        unsigned int tracker = 0;
        bool founddirect = false;
        for(unsigned int j = 0; j < command.size(); j++) {
            if(command[j] == ">" && !founddirect) {
                tracker = j;
                founddirect = true;
            }
        }

        // additional conditions
        if( (tracker != (command.size() - 2)) || (command[tracker+1] == ">")) {
            printerror();
        }
        else {
            runCommands(command, pathvar, true, tracker);      
        } 
    }
    else {
        runCommands(command, pathvar, false, 0);
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
}