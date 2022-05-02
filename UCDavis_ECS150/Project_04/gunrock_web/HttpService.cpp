#include <iostream>

#include <stdlib.h>
#include <stdio.h>

#include "HttpService.h"
#include "ClientError.h"

using namespace std;

HttpService::HttpService(string pathPrefix)
{
    this->m_pathPrefix = pathPrefix;
}

User *HttpService::getAuthenticatedUser(HTTPRequest *request)
{
    
    // variables to store map iterator and auth token
    string auth;
    map<string, User *>::iterator it;
  
    // get token and find matching user
    auth = request->getAuthToken();
    it = m_db->auth_tokens.find(auth);

    // if token not in db, throw error
    if (it == m_db->auth_tokens.end()) {
        throw ClientError::notFound();
    }
    else {     
        return m_db->auth_tokens[auth];        
    }
 
}

string HttpService::pathPrefix()
{
    return m_pathPrefix;
}

void HttpService::head(HTTPRequest *request, HTTPResponse *response)
{
    cout << "HEAD " << request->getPath() << endl;
    throw ClientError::methodNotAllowed();
}

void HttpService::get(HTTPRequest *request, HTTPResponse *response)
{
    cout << "GET " << request->getPath() << endl;
    throw ClientError::methodNotAllowed();
}

void HttpService::put(HTTPRequest *request, HTTPResponse *response)
{
    cout << "PUT " << request->getPath() << endl;
    throw ClientError::methodNotAllowed();
}

void HttpService::post(HTTPRequest *request, HTTPResponse *response)
{
    cout << "POST " << request->getPath() << endl;
    throw ClientError::methodNotAllowed();
}

void HttpService::del(HTTPRequest *request, HTTPResponse *response)
{
    cout << "DELETE " << request->getPath() << endl;
    throw ClientError::methodNotAllowed();
}
