#include "webservice.h"
#include <cstdio>
#include <cstring>
#include <iostream>

onion_connection_status AlcyoneService::root(Onion::Request &req, Onion::Response& res) {
  res.setHeader("Access-Control-Allow-Origin","*");
  res.setHeader("Content-Type", "text/plain");
  
  if(req.query().has("message")) {
    const char *messageString=req.query()["message"].c_str();
    // needs safer strlen!
    if(strlen(messageString)<6) {
      int message=atoi(messageString);
      std::cout << "Message: " << message << std::endl;
    }
  }
  char buffer[1024];
  sprintf(buffer, "%d\n%d\n%d\n", midi->getOctave(), midi->getTransposition(), midi->getChannel()+1);
  res.write(buffer, strlen(buffer));
  return OCS_PROCESSED;
}

