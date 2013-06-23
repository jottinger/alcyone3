#ifndef __ALCYONE_H__
#define __ALCYONE_H__ 1

#include <boost/thread.hpp>
#include "webservice.h"
#include "digitalinput.h"
#include "midi.h"
#include "pedal.h"

class Alcyone
{
private:
    bool continuePlaying;
    unsigned int hostPort;
    unsigned int verbosity;
    MIDI *midi;
    DigitalInput *inputs;
    AlcyoneService *webService;
    Pedal *pedals[13];
    boost::thread *inputThread;
    boost::thread *webserviceThread;
    boost::thread *alcyoneThread;
protected:
public:
    Alcyone();
    void start();
    void playCycle();
    void stopPlaying() {continuePlaying=false;}
    void setMidi(MIDI *_midi)
    {
        midi=_midi;
    }
    void setHostPort(int _hostPort)
    {
        hostPort=_hostPort;
    }
    void setVerbosity(int _verbosity)
    {
        verbosity=_verbosity;
    }
    void pedalDown(const int pedal);
    void pedalUp(const int pedal);
    void playFlare();
};

#endif
