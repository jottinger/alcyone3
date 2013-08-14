#ifndef __PEDAL_H__
#define __PEDAL_H__ 1


class Pedal
{
private:
    int offset;
protected:
public:
    /** Default constructor */
    Pedal(int _offset):offset(_offset) {}
    virtual void down(MIDI* midi);
    virtual void up(MIDI* midi);
};

class MIDINote:Pedal
{
private:
    int offset;
    int previousNote;
    int previousChannel;
public:
    MIDINote(int _pin):Pedal(_pin) {}
};

#endif // PEDAL_H
