#include "config.h"
#include "alcyone.h"
// for time delay methods
#include "wiringPi.h"
#include <iostream>
#include <cstdlib>

Alcyone::Alcyone()
{
}

int flareScores[][4][2]=
{
    {
        {36, 100},
        {48, 100},
        {60, 100},
        {72, 100},
    },
    {
        {72, 100},
        {60, 100},
        {48, 100},
        {36, 100},
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
    for(int i=0; i<notes; i++)
    {
        midi->noteOn(flareScores[score][i][0], 0, 65);
        delay(flareScores[score][i][1]);
        midi->noteOff(flareScores[score][i][1], 0, 0);
    }
}
