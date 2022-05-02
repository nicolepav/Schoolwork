#include <iostream>
#include <string>
#include <vector>

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
// #include <sys/wait.h>


// The shell can be invoked with either no arguments or a single argument; anything else is an error.
// no argument: interactive mode
// arguement: batch mode, read commands from file, no prompt printed
// The loop continues indefinitely, until the user types the built-in command `exit`

// fork() execv() wait() waitpid()

// To check if a particular file exists in a directory and is executable,
// consider the `access()` system call. For example, when the user types `ls`,
// and path is set to include both `/bin` and `/usr/bin`, try `access("/bin/ls",
// X_OK)`. If that fails, try "/usr/bin/ls". If that fails too, it is an error.

// Your initial shell path should contain one directory: `/bin`. Each time the
// user invokes the `path` command, it replaces the path with the arguments that
// the user passes into the command.

using namespace std;

void printerror();
void prompt();
vector<string> parseline(string command);
vector<vector<string>> splitparallelcommands(vector<string> arguments);

// int wish_cd(char **args);
// string wish_path(vector<string> args);
void wish_exit(vector<string> args);




int main(int argc, char *argv[]) {

    
    vector<string> arguments;
    vector<vector<string>> parallelcommands;
    char *myargs;
    
    pid_t PID;
    const char* path= "/bin/";
    
    // assume interactive mode
    while(true) {

        // Prompt and parse arguments
        prompt();
        string command;
        getline(cin, command);
        
        
        arguments = parseline(command);

        // Check for built in commands
        if(arguments[0] == "exit"){
            wish_exit(arguments);  
        }

        // else if(arguments[0] == "cd"){
        //     wish_cd(arguments);
        // }
        // else if(arguments[0] == "path"){
        //     wish_path(arguments);
        // }   
        // // If not a built in command
        // else {

        //     // put string arguments into char array
        //     myargs = new char[arguments.size() + 1];
        //     for(unsigned int i = 0; i < arguments.size(); i++){
        //         myargs[i] = strdup(arguments[i]);
        //     }
        //     myargs[arguments.size() + 1] = NULL;
            
        //     // Fork for new process
        //     PID = fork();
            
        //     // child process
        //     if(PID == 0){             
        //         execv(path, myargs); 
        //     }
        //     // error
        //     else if(PID < 0) {
        //         printerror();
        //     }
        //     // parent process
        //     else {
        //         // error too few arguemnts
        //         // waitpid(PID);
        //     }


        // }

    
    return 0;
}

void printerror() {
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message));     
};

void prompt() {
    char prompt[7] = "wish> ";
    write(STDOUT_FILENO, prompt, strlen(prompt));
};

vector<string> parseline(string command) {
    // redirection: | (pipe) > (redir)
    // parallel cmd: &

    vector<string> arguments;
    string temp = "";

    for(int i = 0; i < strlen(command); i++) {
        
        if(command[i] == '|') {
            arguments.push_back(temp);
            arguments.push_back("|");
            temp = "";

        }
        else if(command[i] == '&') {
            arguments.push_back(temp);
            arguments.push_back("&");
            temp = "";

        }
        else if(command[i] == '>') {
            arguments.push_back(temp);
            arguments.push_back(">");
            temp = "";

        }
        else if(command[i] == ('\n' || '\t' || ' ')) {    
            // note: currently not possible to have \n in the getline string
            if(strlen(temp) > 0) {
                arguments.push_back(temp);
            }
            temp = "";            
        }
        else{
            temp.push_back(command[i]);
        }
    }
    
    return arguments;

};

vector<vector<string>> splitparallelcommands(vector<string> arguments) {
    vector<string> temp;
    vector<vector<string>> commands;

    for (int i = 0; i < arguments.size(); i++) {
        if(arguments[i] != "&"){
            temp.push_back(arguments[i]);
        }
        else {
            commands.push_back(temp);
            for(int j = 0; j < temp.size(); j++){
                temp.pop_back();
            }
        }
    }

    return commands;
};

int wish_cd(char **args) {
    
    // 0 or >1 args should be signaled as an error
    if(args[1] == NULL || args[2] != NULL){
        printerror();
    }
    // if `chdir` fails, that is also an error
    else{
        if(chdir(args[1]) != 0){
            printerror();
        }
    }
};

void wish_exit(vector<string> args) {
    if(args.size() > 1){
        printerror();
    }
    else {
        exit(0);
        return 0;
    }  
};

string wish_path(vector<string> args){
    return;
};


/*

    int mode = 0;       // 1 is interactive 2 is batch
    int fd;
    if(argc == 1) {
        mode = 1;
    }
    else if(argc == 2){
        mode = 2;
        fd = open(argv[2], O_RDONLY);
    }
    else {
        printerror();
        exit(0);
    }


        // char **lineptr = NULL;
        // size_t *n = 0;
        // getline(lineptr, n, stdin);


        // if multiple commands, split into parallel commands
        if(std::find(arguments.begin(), arguments.end(), "&")) {
            parallelcommands = splitparallelcommands(vector<string> arguments);
            doparallel = true;
        }

        // batch mode
        else {
            // fd is not a file stream. need to actually open the file
            while(getline(fd, command)) {

                if(command == "exit"){
                    exit(0);
                }
                arguments = parseline(command);

            }
            exit(0);
        }

        
    }

*/