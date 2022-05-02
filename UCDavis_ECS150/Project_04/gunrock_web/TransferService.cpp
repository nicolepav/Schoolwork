#define RAPIDJSON_HAS_STDSTRING 1

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include <iostream>
#include <map>
#include <string>
#include <sstream>

#include "TransferService.h"
#include "ClientError.h"

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;
using namespace std;

void transferjson(Database *m_db, vector<Transfer *> thisusertransfers, int returnBalance, HTTPResponse *response);

TransferService::TransferService() : HttpService("/transfers") { }


void TransferService::post(HTTPRequest *request, HTTPResponse *response) {

    int returnBalance = 0;
    vector<Transfer *> thisusertransfers;
    
    // if missing arguments
    if(request->formEncodedBody().get("amount") == "" || request->formEncodedBody().get("to") == "") {
        response->setStatus(400);
        throw ClientError::badRequest();
    }
    // else if transfer amount is negative
    else if(stoi(request->formEncodedBody().get("amount")) < 0) {
        response->setStatus(400);
        throw ClientError::badRequest();
    }
    // else if transfer amount is greater than abalance
    else if(stoi(request->formEncodedBody().get("amount")) > getAuthenticatedUser(request)->balance) {
        response->setStatus(400);
        throw ClientError::forbidden();
    }
    else {

            // if to user doesnt exists throw error
            map<string, User *>::iterator it = m_db->users.find(request->formEncodedBody().get("to"));
            if(it == m_db->users.end()) {
                response->setStatus(404);
                throw ClientError::badRequest();
            }
            else {

                // get active user and make new transfer
                User * active = getAuthenticatedUser(request);
                Transfer * newtransfer = new Transfer;
                newtransfer->amount = stoi(request->formEncodedBody().get("amount"));
                newtransfer->from = active;
                newtransfer->to = m_db->users[request->formEncodedBody().get("to")];

                // update balances
                active->balance -= newtransfer->amount;
                m_db->users[request->formEncodedBody().get("to")]->balance += newtransfer->amount;
                m_db->transfers.push_back(newtransfer);
                returnBalance = active->balance;

                // get array of this users transfers
                for(unsigned int i = 0; i < m_db->transfers.size(); i++) {
                    if (m_db->transfers[i]->from->username == active->username) {
                        thisusertransfers.push_back(m_db->transfers[i]);
                    }
                }

            }
    }

    // if response good
    if(response->getStatus() == 200) {
        transferjson(m_db, thisusertransfers, returnBalance, response);
    }


}

void transferjson(Database *m_db, vector<Transfer *> thisusertransfers, int returnBalance, HTTPResponse *response){
    // use rapidjson to create a return object
    Document document;
    Document::AllocatorType& a = document.GetAllocator();
    Value o;
    o.SetObject();

    // add a key value pair directly to the object
    o.AddMember("balance", returnBalance, a);

    // create an array
    Value array;
    array.SetArray();

    // Loop through and add all transfers
    for(unsigned int i = 0; i < thisusertransfers.size(); i++) {
        Value transfer;
        transfer.SetObject();
        transfer.AddMember("from", thisusertransfers[i]->from->username, a);
        transfer.AddMember("to", thisusertransfers[i]->to->username, a);
        transfer.AddMember("amount", thisusertransfers[i]->amount, a);
        array.PushBack(transfer, a);
    }

    o.AddMember("transfers", array, a);

    // now some rapidjson boilerplate for converting the JSON object to a string
    document.Swap(o);
    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);
    document.Accept(writer);

    // set the return object
    response->setContentType("application/json");
    response->setBody(buffer.GetString() + string("\n"));
}