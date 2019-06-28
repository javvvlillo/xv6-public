#include "rand.h"

static unsigned long int sig=1;

int rand(void)
{
    sig = sig * 1103515245 + 12345;
    return (unsigned int) (sig / 65536) % 32768;
}

void srand(unsigned int seed)
{
    sig = seed;
}