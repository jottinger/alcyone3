#ifndef __PEDAL_H__
#define __PEDAL_H__ 1

#include "midi.h"

class Pedal
{
private:
protected:
    int offset;
public:
    /** Default constructor */
    Pedal(int _offset):offset(_offset) {}
    virtual void down(MIDI* midi)=0;
    virtual void up(MIDI* midi)=0;
};

class MIDINote : public Pedal
{
private:
    int previousNote;
    int previousChannel;
public:
    MIDINote(int _pin):Pedal(_pin) {}
    virtual void down(MIDI* midi);
    virtual void up(MIDI* midi);
};

#endif // PEDAL_H
