#ifndef __TIME1_T__
#define __TIME1_T__
#include <sys/time.h>
#define fpos 16.666666667;
struct Time1_t
{
    double prevTime;    // = GetMilliseconds();
    double currentTime; // = GetMilliseconds();
    double deltaTime;
    struct timeval time;
    long sleepTime;
    long nextGameTick;
};

typedef struct Time1_t Time1;

double GetMilliseconds();
long getT(Time1 *time1);
void initT(Time1 *time1);
void provideT(Time1 *time1);
void updateT(Time1 *time1);
#endif