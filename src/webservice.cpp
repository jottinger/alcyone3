#include "webservice.h"
#include <cstdio>
#include <cstring>
#include <iostream>

onion_connection_status AlcyoneService::root(Onion::Request &req, Onion::Response& res)
{
    res.setHeader("Access-Control-Allow-Origin","*");
    res.setHeader("Content-Type", "text/plain");

    if(req.query().has("message"))
    {
        const char *messageString=req.query()["message"].c_str();
        // needs safer strlen!
        if(strlen(messageString)<6)
        {
            int message=atoi(messageString);
            switch(message & 0xf0)
            {
            case MSG_RESET:
                if(verbose>1)
                {
                    std::cout << "(MSG_RESET)" << std::endl;
                }
                midi->resetToDefaults();
                break;
            case MSG_MIDI_RESET:
                if(verbose>1)
                {
                    std::cout << "(MSG_MIDI_RESET)" << std::endl;
                }
                midi->reset();
                break;
            case MSG_REQUEST_STATUS:
                if(verbose>1)
                {
                    std::cout << "(MSG_REQUEST_STATUS)" << std::endl;
                }
                break;
            case MSG_MIDI_OCTAVE_CHANGE:
                if(verbose>1)
                {
                    std::cout << "(MSG_MIDI_OCTAVE_CHANGE)" << message << std::endl;
                }
                midi->changeOctave(message);
                break;
            case MSG_MIDI_CHANNEL_CHANGE:
                if(verbose>1)
                {
                    std::cout << "(MSG_MIDI_CHANNEL_CHANGE)" << message << std::endl;
                }
                midi->changeChannel(message);
                break;
            case MSG_MIDI_TRANSPOSITION_CHANGE:
                if(verbose>1)
                {
                    std::cout << "(MSG_MIDI_TRANSPOSITION_CHANGE) " << message << std::endl;
                }
                midi->changeTransposition(message);
                break;
            default:
                /* unknown message type, say so */
                std::cout << "Unknown message received from controller: "
                          << std::setbase(1) << message << std::setbase(10)
                          << std::endl;
                break;
            }
        }
    }
    char buffer[1024];
    sprintf(buffer, "%d\n%d\n%d\n", midi->getOctave(), midi->getTransposition(), midi->getChannel()+1);
    res.write(buffer, strlen(buffer));
    return OCS_PROCESSED;
}

onion_connection_status AlcyoneService::pedal(Onion::Request &req, Onion::Response& res)
{
    std::cout << "pedal message received!" << std::endl;
    res.setHeader("Access-Control-Allow-Origin","*");
    res.setHeader("Content-Type", "text/plain");
    if(req.query().has("message"))
    {
        const char *messageString=req.query()["message"].c_str();
        // needs safer strlen!
        if(strlen(messageString)<6)
        {
            int message=atoi(messageString);
        }
    }
    char buffer[1024];
    sprintf(buffer, "%d\n%d\n%d\n", midi->getOctave(), midi->getTransposition(), midi->getChannel()+1);
    res.write(buffer, strlen(buffer));
    return OCS_PROCESSED;
}
