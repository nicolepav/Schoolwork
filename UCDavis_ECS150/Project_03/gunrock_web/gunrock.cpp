#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <signal.h>
#include <pthread.h>

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <deque>


#include "HTTPRequest.h"
#include "HTTPResponse.h"
#include "HttpService.h"
#include "HttpUtils.h"
#include "FileService.h"
#include "MySocket.h"
#include "MyServerSocket.h"
#include "dthread.h"

using namespace std;

int PORT = 8080;
size_t THREAD_POOL_SIZE = 1;
size_t BUFFER_SIZE = 1;
string BASEDIR = "static";
string SCHEDALG = "FIFO";
string LOGFILE = "/dev/null";
std::deque<void*> BUFFER;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t EMPTY = PTHREAD_COND_INITIALIZER; 
pthread_cond_t FILL = PTHREAD_COND_INITIALIZER;

vector<HttpService *> services;

HttpService *find_service(HTTPRequest *request) {
   // find a service that is registered for this path prefix
  for (unsigned int idx = 0; idx < services.size(); idx++) {
    if (request->getPath().find(services[idx]->pathPrefix()) == 0) {
      return services[idx];
    }
  }

  return NULL;
}


void invoke_service_method(HttpService *service, HTTPRequest *request, HTTPResponse *response) {
  stringstream payload;
  
  // invoke the service if we found one
  if (service == NULL) {
    // not found status
    response->setStatus(404);
  } else if (request->isHead()) {
    payload << "HEAD " << request->getPath();
    sync_print("invoke_service_method", payload.str());
    cout << payload.str() << endl;
    service->head(request, response);
  } else if (request->isGet()) {
    payload << "GET " << request->getPath();
    sync_print("invoke_service_method", payload.str());
    cout << payload.str() << endl;
    service->get(request, response);
  } else {
    // not implemented status
    response->setStatus(405);
  }
}

void * handle_request(void *dclient) {
  MySocket * client = ((MySocket*) dclient);

  HTTPRequest *request = new HTTPRequest(client, PORT);
  HTTPResponse *response = new HTTPResponse();
  stringstream payload;
  
  // read in the request
  bool readResult = false;
  try {
    payload << "client: " << (void *) client;
    sync_print("read_request_enter", payload.str());
    readResult = request->readRequest();
    sync_print("read_request_return", payload.str());
  } catch (...) {
    // swallow it
  }    
    
  if (!readResult) {
    // there was a problem reading in the request, bail
    delete response;
    delete request;
    sync_print("read_request_error", payload.str());
    return NULL;
  }
  
  HttpService *service = find_service(request);
  invoke_service_method(service, request, response);

  // send data back to the client and clean up
  payload.str(""); payload.clear();
  payload << " RESPONSE " << response->getStatus() << " client: " << (void *) client;
  sync_print("write_response", payload.str());
  cout << payload.str() << endl;
  client->write(response->response());
    
  delete response;
  delete request;

  payload.str(""); payload.clear();
  payload << " client: " << (void *) client;
  sync_print("close_connection", payload.str());
  client->close();
  delete client;
  return NULL;
}

void * consumer(void *arg) {
  
  void *dclient;

  while(true) {

    dthread_mutex_lock(&mutex);             // lock
    while(BUFFER.size() == 0) {             // while buffer empty
      dthread_cond_wait(&FILL, &mutex);     // wait (release, sleep, reacquire)
    }
    dclient = BUFFER.front();               // get front
    BUFFER.pop_front();                     // pop front
    dthread_cond_signal(&EMPTY);            // signal
    dthread_mutex_unlock(&mutex);           // unlock

    handle_request(dclient);                // handle

  }

}




int main(int argc, char *argv[]) {

  signal(SIGPIPE, SIG_IGN);
  int option;

  while ((option = getopt(argc, argv, "d:p:t:b:s:l:")) != -1) {
    switch (option) {
    case 'd':
      BASEDIR = string(optarg);
      break;
    case 'p':
      PORT = atoi(optarg);
      break;
    case 't':
      THREAD_POOL_SIZE = atoi(optarg);
      break;
    case 'b':
      BUFFER_SIZE = atoi(optarg);
      break;
    case 's':
      SCHEDALG = string(optarg);
      break;
    case 'l':
      LOGFILE = string(optarg);
      break;
    default:
      cerr<< "usage: " << argv[0] << " [-p port] [-t threads] [-b buffers]" << endl;
      exit(1);
    }
  }

  set_log_file(LOGFILE);

  sync_print("init", "");
  MyServerSocket *server = new MyServerSocket(PORT);
  MySocket *client;

  services.push_back(new FileService(BASEDIR));
  


  // create a bunch of threads to handle connections, based on user input
  pthread_t thread_pool[THREAD_POOL_SIZE];

  for (unsigned int i = 0; i < THREAD_POOL_SIZE; i++) {
    dthread_create(&thread_pool[i], NULL, consumer, NULL);  // create thread func
    dthread_detach(thread_pool[i]);                         // allow sys to reclaim resources
  }


  while(true) {
    sync_print("waiting_to_accept", "");
    client = server->accept();
    sync_print("client_accepted", "");
    // handle_request(client);                  	// original server line


    // producer function    
    void *dclient = client;

    dthread_mutex_lock(&mutex);                     // lock
    while(BUFFER.size() == BUFFER_SIZE) {           // check invariant
      dthread_cond_wait(&EMPTY, &mutex);            // wait (release, sleep, reacquire)
    }

    BUFFER.push_back(dclient);                      // add connection to the queue
    dthread_cond_signal(&FILL);                     // signal
    dthread_mutex_unlock(&mutex);                   // unlock
  }


}