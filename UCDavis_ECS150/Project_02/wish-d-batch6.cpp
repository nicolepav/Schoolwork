#include <iostream>
#include <fstream>

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
void runcommand(vector<string> command);


int main(int argc, char *argv[]) {

    string line;
    vector<string> arguments;
    vector<string> command;

    ifstream filein;
    streambuf *backup, *fbuf;
    
    if(argc == 2) {    
        filein.open(argv[1]);
        backup = cin.rdbuf();
        fbuf = filein.rdbuf();

        cin.rdbuf(fbuf);
    }   
    
    // Prompt and begin looping
    if(argc == 1) {
        prompt();
    }
    while(getline(cin, line)) {
        
        
        arguments = parseline(line);
        
        // assume no parallel commands
        command = arguments;

        // Builtin commands
        if(command[0] == "exit") {
            if(command.size() > 1) {
                printerror();
            }
            exit(0);
        }
        else if(command[0] ==  "cd") {
            wish_cd(command);
        }
        else {
            runcommand(command);
        }   

        // prompt for next if stdin
        if(argc == 1) {
            prompt();
        }
        
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

    for(unsigned int i = 0; i < line.length()+1; i++) {
        
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
        else if(i == line.length()) {
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

void runcommand(vector<string> command) {
    
    string defaultpath = "/bin/";

    // Add arguments to char array, create path
    char **myargs = new char*[command.size() + 1];
    for(unsigned int i = 0; i < command.size(); i++) {
        myargs[i] = strdup(command[i].c_str());
    }
    myargs[command.size()] = nullptr;
    char *commandpath = new char[defaultpath.size() + strlen(myargs[0]) + 1];
    strcat(commandpath, defaultpath.c_str());
    strcat(commandpath, myargs[0]);

    // If path valid, allocate variables for process, run process
    if(access(commandpath, X_OK) < 0) {
        printerror();
    }
    else{
        pid_t PID;
        int PIDstatus;
        PID = fork();

        if(PID == 0) {
            execv(commandpath, myargs);
            printerror();
        }
        else if(PID < 0) {
            printerror();
        }
        else {
            waitpid(PID, &PIDstatus, 0);
        }
    }

}