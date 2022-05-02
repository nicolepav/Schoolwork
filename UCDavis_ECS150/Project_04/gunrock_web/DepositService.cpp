#define RAPIDJSON_HAS_STDSTRING 1

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include <iostream>
#include <map>
#include <string>
#include <sstream>

#include "DepositService.h"
#include "Database.h"
#include "ClientError.h"
#include "HTTPClientResponse.h"
#include "HttpClient.h"

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;
using namespace std;

void depositjson(Database *m_db, vector<Deposit*> thisuserdeposits, int returnBalance, HTTPResponse *response);

DepositService::DepositService() : HttpService("/deposits") { }

void DepositService::post(HTTPRequest *request, HTTPResponse *response) {

    int returnBalance = 0;
    vector<Deposit *> thisuserdeposits;

    // if arguments missing
    if(request->formEncodedBody().get("amount") == "" || request->formEncodedBody().get("stripe_token") == "" ) {
        throw ClientError::badRequest();
        response->setStatus(400);
    }
    // else if deposit is <50 cents or negative
    else if (stoi(request->formEncodedBody().get("amount")) < 50) {
        throw ClientError::badRequest();
        response->setStatus(400);
    }
    else { 

        // create HTTP body for request
        WwwFormEncodedDict body;
        body.set("amount", stoi(request->formEncodedBody().get("amount")));
        body.set("source", request->formEncodedBody().get("stripe_token"));
        body.set("currency", "USD");
        string encoded_body = body.encode();

        // interact with stripe
        HttpClient client("api.stripe.com", 443, true); // set false for gunrock true for stripe
        client.set_basic_auth(m_db->stripe_secret_key, "");
        HTTPClientResponse * clientresponse = client.post("/v1/charges", encoded_body);

        // read response from stripe
        Document *d = clientresponse->jsonBody();

        // if did not succeed, throw error. Otherwise, apply deposit
        if(!(*d).HasMember("status")) {
            response->setStatus(400);
            throw ClientError::unauthorized();
            delete d;
        }   
        else {

            // get charge ID
            string chargeID = (*d)["id"].GetString();   // charge ID
            delete d;

            // create new deposit object
            User * active = getAuthenticatedUser(request);
            Deposit * newdeposit = new Deposit;
            newdeposit->amount = stoi(request->formEncodedBody().get("amount"));
            newdeposit->to = active;
            newdeposit->stripe_charge_id = chargeID;

            // modify and return balance
            active->balance += newdeposit->amount;
            m_db->deposits.push_back(newdeposit);
            returnBalance = active->balance;
            
            // get array of deposits
            for(unsigned int i = 0; i < m_db->deposits.size(); i++) {
                if (m_db->deposits[i]->to->username == active->username) {
                    thisuserdeposits.push_back(m_db->deposits[i]);
                }
            }
        }     

        // if response good
        if(response->getStatus() == 200) {
            depositjson(m_db, thisuserdeposits, returnBalance, response);
        }

    }

}


void depositjson(Database *m_db, vector<Deposit*> thisuserdeposits, int returnBalance, HTTPResponse *response) {

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

    // Loop through and add all deposits
    for(unsigned int i = 0; i < thisuserdeposits.size(); i++) {
        Value deposit;
        deposit.SetObject();
        deposit.AddMember("to", thisuserdeposits[i]->to->username, a);
        deposit.AddMember("amount", thisuserdeposits[i]->amount, a);
        deposit.AddMember("stripe_charge_id", thisuserdeposits[i]->stripe_charge_id, a);
        array.PushBack(deposit, a);
    }

    o.AddMember("deposits", array, a);

    // now some rapidjson boilerplate for converting the JSON object to a string
    document.Swap(o);
    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);
    document.Accept(writer);

    // set the return object
    response->setContentType("application/json");
    response->setBody(buffer.GetString() + string("\n"));

}