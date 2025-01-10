#include "Time1_t.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
double GetMilliseconds()
{
    static struct timeval s_tTimeVal;
    gettimeofday(&s_tTimeVal, NULL);
    double time = s_tTimeVal.tv_sec * 1000.0; // sec to ms
    time += s_tTimeVal.tv_usec * 0.001;       // us to ms
    return time;
}

long getT(Time1 *time1)
{
    return (time1->time.tv_sec * 1000) + (time1->time.tv_usec * 0.001);
}

void initT(Time1 *time1)
{
    time1->prevTime = GetMilliseconds();
    time1->currentTime = GetMilliseconds();
    time1->deltaTime = 0.0;
    time1->sleepTime = 0;
    gettimeofday(&time1->time, NULL);
    time1->nextGameTick = getT(time1);
}

void provideT(Time1 *time1)
{
    time1->currentTime = GetMilliseconds();
    time1->deltaTime = (double)(time1->currentTime - time1->prevTime) * 0.001;
    time1->prevTime = time1->currentTime;
}

void updateT(Time1 *time1)
{
    gettimeofday(&time1->time, NULL);
    time1->nextGameTick += 16.666666667;
    time1->sleepTime = time1->nextGameTick - (getT(time1));
    usleep((unsigned int)(time1->sleepTime * 0.001));
}
