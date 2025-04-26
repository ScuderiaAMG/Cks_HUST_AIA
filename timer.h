#ifndef _TIMER_H_
#define _TIMER_H_

#define bool int
#define true 1
#define false 0


unsigned long currentTime()
void initializeTimer(Timer* timer)
void startTimer(Timer* timer)
void stopTimer(Timer* timer)
void resetTimer(Timer* timer)
int getElapsedTime(Timer* timer)

#endif