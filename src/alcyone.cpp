#include "config.h"
#include "alcyone.h"
// for time delay methods
#include "wiringPi.h"
#include <boost/bind.hpp>
#include <iostream>
#include <cstdlib>
#include <onion/handler.hpp>
#include <onion/url.hpp>

Alcyone::Alcyone():continuePlaying(true),hostPort(8090),verbosity(0)
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


void Alcyone::start() {
    webService=new AlcyoneService(midi, pedals);
    
    char buffer[10];
    sprintf(buffer, "%d", hostPort);
    
    Onion::Onion o(O_DETACH_LISTEN);
    // ugh, why is this a string
    o.setPort(buffer);
    Onion::Url root(o);
    root.add("", webService, &AlcyoneService::root);
    
    o.listen();
    inputThread=new boost::thread(&DigitalInput::readCycle, inputs);
    alcyoneThread=new boost::thread(&Alcyone::playCycle, this);
    alcyoneThread->join();
}

void Alcyone::playCycle()
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
                    pedals[12-i]->down(midi);
                }
                else
                {
                    pedals[12-i]->up(midi);
                }
            }
        }
    }
}

