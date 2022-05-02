#define RAPIDJSON_HAS_STDSTRING 1

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "AuthService.h"
#include "StringUtils.h"
#include "ClientError.h"

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

void sendauthresponse(Database *m_db, HTTPResponse *response, string uname, string newtoken);

AuthService::AuthService() : HttpService("/auth-tokens")
{
}

void AuthService::post(HTTPRequest *request, HTTPResponse *response)
{ 
    // Variables needed
    WwwFormEncodedDict req = request->formEncodedBody();
    string uname = req.get("username");
    string upass = req.get("password");
    string newtoken = "";

    // create iterator to search map
    map<string, User *>::iterator it = m_db->users.find(uname);

    // if username not in lowercase
    for(unsigned int i = 0; i < uname.length(); i++) {
        if(!islower(uname[i])) {
            throw ClientError::badRequest();
            response->setStatus(400);
        }
    }
    
    // if iterator returns at end user exists, else new user
    if (it != m_db->users.end()) {

        // if password correct log in
        if(m_db->users[uname]->password != upass) {
            throw ClientError::badRequest();
            response->setStatus(403);    
        }
        else {
            newtoken = StringUtils::createAuthToken();
            m_db->auth_tokens[newtoken] = m_db->users[uname];
            response->setStatus(200);
        }
    }
    else {
        
        // user not in db, create new user
        User * newuser = new User;
        newuser->username = uname;
        newuser->password = upass;
        newuser->email = "";
        newuser->balance = 0;

        // Create new id and authoken for user
        newuser->user_id = StringUtils::createUserId();
        newtoken = StringUtils::createAuthToken();

        // associate user id and token
        m_db->users[newuser->username] = newuser;
        m_db->auth_tokens[newtoken] = newuser;

        response->setStatus(201);
    }

    // if response is good, send
    if(response->getStatus() == 200 || response->getStatus() == 201) {
        sendauthresponse(m_db, response, uname,  newtoken);
    }

    
 
}

void AuthService::del(HTTPRequest *request, HTTPResponse *response) {

    // store url token and token to be deleted
    string url = request->getUrl();
    vector <string> spliturl = StringUtils::split(url, '/');
    string deltoken = "";

    // if no auth for deletion provided
    if(spliturl.size() != 2) {
        response->setStatus(400);
        ClientError::badRequest();
    }
    // if no auth token provided, not logged in
    else if(!request->hasAuthToken()) {
        response->setStatus(401);
        ClientError::forbidden();
    }
    // if provided auth blank (login or for delete)
    else if(request->getAuthToken() == "" || spliturl[1] == "") {
        response->setStatus(400);
        ClientError::badRequest();
    }
    // else if login token doesnt exist in db
    else if(m_db->auth_tokens.count(request->getAuthToken()) == 0) {
        response->setStatus(404);
        ClientError::forbidden();
    }
    // else if deltoken doesnt exist in db
    else if(m_db->auth_tokens.count(spliturl[1]) == 0 ) {
        response->setStatus(404);
        ClientError::badRequest();
    }
    else {

        // deltoken is token for deletion from url
        deltoken =  spliturl[1];

        // get current user and provided authtoken
        User * active = getAuthenticatedUser(request);
        string authToken = request->getAuthToken();

        // If deltoken and auth token map to same user ID allow deletion, else forbidden
        if(m_db->auth_tokens[deltoken]->user_id == m_db->users[active->username]->user_id) {
            m_db->auth_tokens.erase(deltoken);
            response->setStatus(200);
        }
        else {
            response->setStatus(403);
            ClientError::forbidden();
        }

    }

}

void sendauthresponse(Database *m_db, HTTPResponse *response, string uname, string newtoken) {

    // use rapidjson to create a return object
    Document document;
    Document::AllocatorType& a = document.GetAllocator();
    Value o;
    o.SetObject();

    // Return data
    string returnUID = m_db->users[uname]->user_id;
    string returnAuth = newtoken;

    // Add to response object
    o.AddMember("auth_token", returnAuth, a);
    o.AddMember("user_id", returnUID, a);

    // now some rapidjson boilerplate for converting the JSON object to a string
    document.Swap(o);
    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);
    document.Accept(writer);

    // send response
    response->setContentType("application/json");
    response->setBody(buffer.GetString() + string("\n"));

}
