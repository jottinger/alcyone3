#include "digitalinput.h"
#include <mlog/mlog.hpp>

DigitalInput::DigitalInput():continueReads(true)
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

void DigitalInput::readCycle()
{
    int data[2];
    int datum;
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
bool DigitalInput::pinChanged(int pin)
{
    return previousState[pin]!=presentState[pin];
}
/** This returns the current pin state, and sets the previous value to this state. */
int DigitalInput::pinState(int pin)
{
    return previousState[pin]=presentState[pin];
}
