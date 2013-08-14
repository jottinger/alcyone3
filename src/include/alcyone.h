#ifndef __ALCYONE_H__
#define __ALCYONE_H__ 1

#include <vector>
#include "midi.h"
#include "pedal.h"
#include "debounce.h"

class DigitalInput
{
private:
    boolean continueReads=true;
    int previousState[13];
    int presentState[13];
    Debouncer debouncer[13];
    std::vector<MCP23008> mcps;
protected:
public:
    DigitalInput();
    void endReadCycle() { continueReads=false;}
    void readCycle();
    boolean pinChanged(int pin);
    int pinState(int pin);
};

class Alcyone
{
private:
    boolean continuePlaying=true;
    unsigned int hostPort;
    unsigned int verbosity;
    MIDI *midi;
    DigitalInput *inputs;
    Pedal[13] pedals;
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
