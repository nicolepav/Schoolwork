#define RAPIDJSON_HAS_STDSTRING 1

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

#include "WwwFormEncodedDict.h"
#include "HttpClient.h"

#include "rapidjson/document.h"

using namespace std;
using namespace rapidjson;

int API_SERVER_PORT = 8080;
string API_SERVER_HOST = "localhost";
string PUBLISHABLE_KEY = "pk_test_51IyTwxHsjuEtqf846o4oT7wFnviX1sUV9625sePfskmRYZuWIF2sSuKhdptRPs1lIx4wHh2AC3p8uM9Y2nPN6vJu004iktOo0I";

string auth_token;
string user_id;

void prompt();
void printerror();
vector<string> parseline(string line);
bool isAllWhiteSpace(string line);

void cmd_auth(vector<string> arguments, string  * activetoken, string * activeid);
void cmd_balance(string activetoken, string activeid);
void cmd_deposit(vector<string> arguments, string  activetoken, string activeid);
void cmd_send(vector<string> arguments, string  activetoken, string activeid);
void cmd_logout(string * activetoken, string * activeid);

bool do_auth_post(vector<string> arguments, string *activetoken, string *activeid);
bool do_auth_put(vector<string> arguments, string activetoken, string activeid, int* balance);
bool do_stripe_post(vector<string> arguments, string * token_id);


int main(int argc, char *argv[]) {
	
	// provided setup code
	stringstream config;
	int fd = open("config.json", O_RDONLY);
	if (fd < 0) {
		cout << "could not open config.json" << endl;
		exit(1);
	}
	int ret;
	char buffer[4096];
	while ((ret = read(fd, buffer, sizeof(buffer))) > 0) {
		config << string(buffer, ret);
	}
	Document d;
	d.Parse(config.str());
	API_SERVER_PORT = d["api_server_port"].GetInt();
	API_SERVER_HOST = d["api_server_host"].GetString();
	PUBLISHABLE_KEY = d["stripe_publishable_key"].GetString();

	// initial variables
	vector<string> arguments;
	string line;
	ifstream filein;
    streambuf *backup, *fbuf;     
	
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

		// if empty command, error
		if(isAllWhiteSpace(line)) {
			printerror();
		}
		else {

			arguments = parseline(line);

			if(arguments[0] == "auth") {
				cmd_auth(arguments, &auth_token, &user_id);
			}
			else if(arguments[0] == "balance") {
				cmd_balance(auth_token, user_id);
			}
			else if(arguments[0] == "deposit") {
				cmd_deposit(arguments, auth_token, user_id);
			}
			else if(arguments[0] == "send") {
				cmd_send(arguments, auth_token, user_id);
			}
			else if(arguments[0] == "logout") {
				cmd_logout(&auth_token, &user_id);
			}
			else{
				printerror();
			}
			
		}	

		// prompt for next if STDIN
        if(argc == 1) prompt();

	}

	// If/when getline fails, exit(0)
    cin.rdbuf(backup);
    exit(0);
}

void prompt() {
    char prompt[7] = "D$> ";
    write(STDOUT_FILENO, prompt, strlen(prompt));
};

void printerror() {
    char error_message[30] = "Error\n";
    write(STDERR_FILENO, error_message, strlen(error_message));     
};

bool isAllWhiteSpace(string line) {
	for(unsigned int i =0; i < line.length(); i++) {
		if(!isspace(line[i])) {
			return false;
		}
	}
	return true;
}

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

// helper function
bool do_auth_post(vector<string> arguments, string *activetoken, string *activeid) {
	
	// Make request body
	HttpClient client(API_SERVER_HOST.c_str(), API_SERVER_PORT, false);
	WwwFormEncodedDict body;
	body.set("username", arguments[1]);
	body.set("password", arguments[2]);
	string encoded_body = body.encode();

	// send request
	HTTPClientResponse * response = client.post("/auth-tokens", encoded_body);
	bool success = response->success();

	// return request
	if (success) {
		Document *d = response->jsonBody();
		*activetoken = (*d)["auth_token"].GetString();
		*activeid = (*d)["user_id"].GetString();
		delete d;
	}
	
	return success;
}

// helper function
bool do_auth_put(vector<string> arguments, string activetoken, string activeid, int * balance) {
	
	// make request body
	HttpClient client(API_SERVER_HOST.c_str(), API_SERVER_PORT, false);
	client.set_header("x-auth-token", activetoken);

	WwwFormEncodedDict body;
	body.set("email", arguments[3]);
	string encoded_body = body.encode();

	// send request
	HTTPClientResponse * response = client.put("/users/" + activeid, encoded_body);
	bool success = response->success();

	// return request
	if(success) {
		Document *d = response->jsonBody();
		*balance = (*d)["balance"].GetInt();
		delete d;
	}

	return success;
}

// helper function
bool do_stripe_post(vector<string> arguments, string * token_id) {
	HttpClient client("api.stripe.com", 443, true);
	client.set_header("Authorization", string("Bearer ") + PUBLISHABLE_KEY);

	WwwFormEncodedDict body;
	body.set("card[number]", arguments[2]);
	body.set("card[exp_year]", arguments[3]);
	body.set("card[exp_month]", arguments[4]);
	body.set("card[cvc]", arguments[5]);
	string encoded_ebody = body.encode();

	HTTPClientResponse * rstripe = client.post("/v1/tokens", encoded_ebody);
	Document *d = rstripe->jsonBody();

	if((*d).HasMember("id")) {
		*token_id = (*d)["id"].GetString();
		delete d;
		return true;
	}
	
	delete d;
	return false;

}

// function to run the auth username password email command
void cmd_auth(vector<string> arguments, string  * activetoken, string * activeid) {

	bool success =  true;
	success = do_auth_post(arguments, activetoken, activeid);

	if(success && arguments.size() == 4) {
		int balance;
		success = do_auth_put(arguments, *activetoken, *activeid, &balance);
		if(success) {
			cmd_balance(*activetoken, *activeid);
		}
		else {
			printerror();
		}
	}
	else {
		printerror();
	}

}

// function to print balance to stream when called	
void cmd_balance(string activetoken, string activeid){
	
	// make path
	string path = "/users/" + activeid;

	// interact with gunrock
	HttpClient getclient("localhost", 8080, false);
	getclient.set_header("x-auth-token", activetoken);
	HTTPClientResponse * getresponse = getclient.get(path);

	if(getresponse->success()) {
		
		Document *d  = getresponse->jsonBody();
		int balance = (*d)["balance"].GetInt();   
		delete d;

		// convert cents to dollars print balance
		double dollars = (double)balance / 100;
		cout << fixed << setprecision(2) << "Balance: $" << dollars << endl;

	}
	else {
		printerror();
	}

}

// function to run deposit $ cardnum month year cvc command
void cmd_deposit(vector<string> arguments, string activetoken, string activeid){
	
	// check amount of arguments, if not correct, throw error
	if(arguments.size() == 6 )
	{
		// post to stripe
		string token_id;
		if(do_stripe_post(arguments, &token_id)) {
			
			// post to gunrock
			HttpClient client(API_SERVER_HOST.c_str(), API_SERVER_PORT, false);
			client.set_header("x-auth-token", activetoken);
			int cents = stod(arguments[1]) * 100;

			WwwFormEncodedDict sbody;
			sbody.set("amount", to_string(cents));
			sbody.set("stripe_token", token_id);
			string encoded_body = sbody.encode();

			HTTPClientResponse * response = client.post("/deposits", encoded_body);

			// return balance
			if(response->success()) {
				cmd_balance(activetoken, activeid);
			}
			else {
				printerror();
			}
		}
		else {
			printerror();
		}
	}
	else {
		printerror();
	}

}

// function to run send user $ command (transfer)
void cmd_send(vector<string> arguments, string activetoken, string activeid){

	// form request
	HttpClient client(API_SERVER_HOST.c_str(), API_SERVER_PORT, false);
	client.set_header("x-auth-token", activetoken);

	int cents = stod(arguments[2]) * 100;

	WwwFormEncodedDict body;
	body.set("to", arguments[1]);
	body.set("amount", cents);
	string encoded_body = body.encode();

	HTTPClientResponse * response = client.post("/transfers", encoded_body);

	// print balance
	if(response->success()) {
		cmd_balance(activetoken, activeid);
	}
	else {
		printerror();
	}

}

// function to log out the user
void cmd_logout(string * activetoken, string * activeid){

	string path = "/auth-tokens/" + *activetoken;

	// client for del request
	HttpClient delclient(API_SERVER_HOST.c_str(), API_SERVER_PORT, false);	
	delclient.set_header("x-auth-token", *activetoken);
	HTTPClientResponse * delresponse = delclient.del(path);

	if(delresponse->success()) {
		*activetoken = "";
		*activeid = "";
		exit(0);
	}
	else {
		printerror();
	}

}
