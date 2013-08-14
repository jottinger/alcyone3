#include "pedal.h"

void MIDINote::down(MIDI* midi) {
    if(previousNote!=0) {
        up(midi);
    }
    previousChannel=midi->getChannel()
    previousNote=midi->getNote(offset);
    midi->noteOn(previousNote, previousChannel, midi->getVelocity());
}

void MIDINote::up(MIDI* midi) {
    midi->noteOff(previousNote, previousChannel, 0);
    previousNote=0;
}
