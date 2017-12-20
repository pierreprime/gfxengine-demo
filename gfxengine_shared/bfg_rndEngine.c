#include "../gfxengine_shared/bfg_rndEngine.h"

#include <stdio.h>
#include <stdlib.h>

unsigned long int next = 1;

// Positionné ici par pure fainéantise !
int rnd_random(int start,int end)
{
    return (rand() & 0x7fffffff) % (end-start+1) + start;
}

int rnd_random2(int start,int end)
{
    next = next * 1103515245UL + 12345;
    return (unsigned int)(next/65536) % (end-start+1) + start;
}

void rnd_srand2(unsigned int seed)
{
    next = seed;
}

