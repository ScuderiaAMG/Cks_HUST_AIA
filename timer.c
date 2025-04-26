include 'timer.h'



// 获取当前系统时间（以毫秒为单位）
unsigned long currentTime()
{
    struct time t;
    gettime(&t);
    return t.ti_hour * 3600000L + t.ti_min * 60000L + t.ti_sec * 1000L + t.ti_hund;
}

// 初始化计时器
void initializeTimer(Timer* timer)
{
    timer->running = false;
    timer->elapsed_time = 0.0;
}

// 启动计时器
void startTimer(Timer* timer)
{
    if (!timer->running)
    {
        timer->start_time = currentTime();
        timer->running = true;
    }
}

// 停止计时器
void stopTimer(Timer* timer)
{
    if (timer->running)
    {
        timer->end_time = currentTime();
        timer->elapsed_time += (int)((timer->end_time - timer->start_time) / 1000L);
        timer->running = false;
    }
}

// 重置计时器
void resetTimer(Timer* timer)
{
    initializeTimer(timer);
}

// 获取经过的时间
int getElapsedTime(Timer* timer)
{
    if (timer->running)
    {
        return timer->elapsed_time + (int)((currentTime() - timer->start_time) / 1000L);
    }
    else
    {
        return timer->elapsed_time;
    }
}

