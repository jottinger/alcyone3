#include "config.h"
#include "alcyone.h"
// for time delay methods
#include "wiringPi.h"
#include <iostream>
#include <cstdlib>
#include <boost/thread.hpp>

Alcyone::Alcyone()
{
    inputs=new DigitalInput();
    for(int i=0;i<13;i++) {
        pedals[i]=new MIDINote(i);
    }
}

int flareScores[][4][2]=
{
    {
        {36, 150},
        {48, 150},
        {60, 150},
        {64, 150},
    },
    {
        {72, 150},
        {60, 150},
        {48, 150},
        {52, 150},
    },
};

void Alcyone::playFlare()
{
    if(midi==NULL)
    {
        std::cerr << "Incorrect initialization sequence: bug your coder. " << std::endl
                  << "MIDI is unset in playFlare()" << std::endl;
        exit(1);
    }
    srand (time(NULL));
    int score=rand() % (sizeof(flareScores)/sizeof(flareScores[0]));
    int notes=sizeof(flareScores[score])/sizeof(flareScores[score][0]);
    midi->reset();
    delay(100);
    for(int i=0; i<notes; i++)
    {
        midi->noteOn(flareScores[score][i][0], 0, 65);
        delay(std::max(flareScores[score][i][1],200));
        midi->noteOff(flareScores[score][i][0], 0, 0);
    }
    delay(10);
    midi->reset();
}

DigitalInput::DigitalInput()
{
    for(int i=0; i<2; i++)
    {
        MCP23008 mcp(i);
        mcp.modeAll(MODE_INPUT);
        mcps.push_back(mcp);
    }
    MCP23008 util(2);
    util.pinMode(0, MODE_OUTPUT);
    util.pinMode(1, MODE_OUTPUT);
    util.pinMode(2, MODE_OUTPUT);
    util.pinMode(3, MODE_INPUT);
    mcps.push_back(util);
    // mcps now contains three MCP23008 entries:
    // two are fully input, one has three output pins

    for(int i=0; i<13; i++)
    {
        presentState[i]=0;
        previousState[i]=0;
    }
}

void Alcyone::start() {
    inputThread=new boost::thread(inputs->readCycle());
    alcyoneThread=new boost::thread(&playCycle);
}

Alcyone::playCycle()
{
    while(continuePlaying)
    {
        for(int i=0; i<13; i++)
        {
            if(inputs->pinChanged(i))
            {
                int state=inputs->pinState(i);
                if(state)
                {
                    pedals[i].down();
                }
                else
                {
                    pedals[i].up();
                }
            }
        }
    }
}

void DigitalInput::readCycle()
{
    int data[2];
    int datum;
    int state;
    while(continueReads)
    {
        // this is where we read the digital inputs and feed the debouncers
        data[0]=mcps[0].read();
        data[1]=mcps[1].read();
        for(int pin=0; pin<13; pin++)
        {
            datum=data[pin/8];
            presentState[pin]=debouncer[pin].debounce(decode(datum, pin%8));
        }
    }
}
/** We compare the current read value to the previous value. */
boolean DigitalInput::pinChanged(int pin)
{
    return previousState(pin)!=presentState[pin];
}
/** This returns the current pin state, and sets the previous value to this state. */
int DigitalInput::pinState(int pin)
{
    return previousState[pin]=presentState[pin];
}
