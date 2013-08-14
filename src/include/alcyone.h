#ifndef __ALCYONE_H__
#define __ALCYONE_H__ 1

#include "midi.h"

class Alcyone
{
private:
    unsigned int hostPort;
    unsigned int verbosity;
    MIDI *midi;
protected:
public:
    Alcyone();
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
