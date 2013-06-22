#ifndef __DIGITALINPUT_H__
#define __DIGITALINPUT_H__ 1

#include <vector>
#include "mcp23008.h"
#include "debounce.h"

class DigitalInput
{
private:
    bool continueReads;
    int previousState[13];
    int presentState[13];
    Debouncer debouncer[13];
    std::vector<MCP23008> mcps;
protected:
public:
    DigitalInput();
    void endReadCycle() { continueReads=false;}
    void readCycle();
    bool pinChanged(int pin);
    int pinState(int pin);
};


#endif