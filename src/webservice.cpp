#include "webservice.h"
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>

onion_connection_status AlcyoneService::nullResponse(Onion::Request &req, Onion::Response& res)
{
    return OCS_NOT_IMPLEMENTED;
}

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
                midi->resetToDefaults();
                break;
            case MSG_MIDI_RESET:
                midi->reset();
                break;
            case MSG_REQUEST_STATUS:
                /* No-op */
                break;
            case MSG_MIDI_OCTAVE_CHANGE:
                midi->changeOctave(message);
                break;
            case MSG_MIDI_CHANNEL_CHANGE:
                midi->changeChannel(message);
                break;
            case MSG_MIDI_TRANSPOSITION_CHANGE:
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
            if((message&0x0f)<13) {
                switch(message & 0xf0) {
                case 0x10:
                    /* pedal down */
                    pedals[message&0x0f]->down(midi);
                    break;
                case 0x20:
                    /* pedal up */
                    pedals[message&0x0f]->down(midi);
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
    }
    char buffer[1024];
    sprintf(buffer, "%d\n%d\n%d\n", midi->getOctave(), midi->getTransposition(), midi->getChannel()+1);
    res.write(buffer, strlen(buffer));
    return OCS_PROCESSED;
}
