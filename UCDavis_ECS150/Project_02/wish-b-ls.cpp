#include <iostream>
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


int main(int argc, char *argv[]) {

    string line;
    vector<string> arguments;
    vector<string> command;
    string defaultpath = "/bin/";

    int x = 0;
    while(x < 1) {
        prompt();
        getline(cin, line);
        arguments = parseline(line);
        
        // assume no parallel commands
        command = arguments;
        // assume no builtin commands

        
        // Add arguments to char array
        char **myargs = new char*[command.size() + 1];
        for(unsigned int i = 0; i < command.size(); i++) {
            myargs[i] = strdup(command[i].c_str());
        }
        myargs[command.size()] = nullptr;

        // Allocate variables for process
        pid_t PID;
        int PIDstatus;
        

        // Create path
        char *commandpath = new char[defaultpath.size() + strlen(myargs[0]) + 1];
        strcat(commandpath, defaultpath.c_str());
        strcat(commandpath, myargs[0]);

        // Run Process
        PID = fork();
        if(PID == 0) {
            // child process
            execv(commandpath, myargs);
            cout << "error on execv" << endl;
            printerror();
        }
        else if(PID < 0) {
            // something went wrong
            printerror();
        }
        else {
            // parent process
            waitpid(PID, &PIDstatus, 0);
        }

        x++;
    }

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

