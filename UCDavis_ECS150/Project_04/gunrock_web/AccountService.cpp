#define RAPIDJSON_HAS_STDSTRING 1

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "AccountService.h"
#include "ClientError.h"

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

void acctservicejson(Database *m_db, HTTPRequest *request, HTTPResponse *response);

AccountService::AccountService() : HttpService("/users") {
  
}

void AccountService::get(HTTPRequest *request, HTTPResponse *response) {
    
    // Create variables for url data and parameters
    string url = request->getUrl();
    vector <string> spliturl = StringUtils::split(url, '/');


    // if wrong amount of vector arguments
    if(spliturl.size() != 2) {
        response->setStatus(400);
        ClientError::badRequest();
    }
    // else if auth token doesnt exist in db
    else if(m_db->auth_tokens.count(request->getAuthToken()) == 0) {
        response->setStatus(404);
        ClientError::forbidden();
    }
    // else if provided auth blank or uid blank
    else if(request->getAuthToken() == "" || spliturl[1] == "") {
        response->setStatus(400);
        ClientError::badRequest();
    }
    // else if userid doesnt match authenticated user
    else if(getAuthenticatedUser(request)->user_id != spliturl[1]) {
        response->setStatus(403);
        ClientError::forbidden();
    }
    else {
        response->setStatus(200);
    }

    // if response is good, edit body
    if(response->getStatus() == 200) {
        acctservicejson(m_db, request, response);
    }
    
}


void AccountService::put(HTTPRequest *request, HTTPResponse *response) {
    
    string url = request->getUrl();
    vector <string> spliturl = StringUtils::split(url, '/');
    string email = "";

    // if wrong amount of vector arguments
    if(spliturl.size() != 2) {
        response->setStatus(400);
        ClientError::badRequest();
    }
    // else if no auth token provided, not logged in
    else if(!request->hasAuthToken()) {
        response->setStatus(400);
        ClientError::forbidden();
    }
    // else if auth token doesnt exist in db
    else if(m_db->auth_tokens.count(request->getAuthToken()) == 0) {
        response->setStatus(404);
        ClientError::forbidden();
    }
    // else if provided auth blank or uid blank
    else if(request->getAuthToken() == "" || spliturl[1] == "") {
        response->setStatus(400);
        ClientError::badRequest();
    }
    // else if userid doesnt match authenticated user
    else if(getAuthenticatedUser(request)->user_id != spliturl[1]) {
        response->setStatus(403);
        ClientError::forbidden();
    }
    // else if missing email argument
    else if(request->formEncodedBody().get("email") == "") {
        response->setStatus(400);
        ClientError::badRequest();
    }
    else {

        email = request->formEncodedBody().get("email");
        m_db->users[m_db->auth_tokens[request->getAuthToken()]->username]->email = email;
        response->setStatus(200);
    }

    // if response is good, edit body
    if(response->getStatus() == 200 ) {
        acctservicejson(m_db, request, response);
    }

}



void acctservicejson(Database *m_db, HTTPRequest *request, HTTPResponse *response) {

    // use rapidjson to create a return object
    Document document;
    Document::AllocatorType& a = document.GetAllocator();
    Value o;
    o.SetObject();

    // Return data
    string returnEmail= m_db->users[m_db->auth_tokens[request->getAuthToken()]->username]->email;
    int returnBalance = (m_db->users[m_db->auth_tokens[request->getAuthToken()]->username]->balance);
    
    // Add to response object
    o.AddMember("balance", returnBalance, a);
    o.AddMember("email", returnEmail, a);

    // now some rapidjson boilerplate for converting the JSON object to a string
    document.Swap(o);
    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);
    document.Accept(writer);

    // send response
    response->setContentType("application/json");
    response->setBody(buffer.GetString() + string("\n"));
}