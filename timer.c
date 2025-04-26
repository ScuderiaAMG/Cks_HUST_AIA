include 'timer.h'



// ��ȡ��ǰϵͳʱ�䣨�Ժ���Ϊ��λ��
unsigned long currentTime()
{
    struct time t;
    gettime(&t);
    return t.ti_hour * 3600000L + t.ti_min * 60000L + t.ti_sec * 1000L + t.ti_hund;
}

// ��ʼ����ʱ��
void initializeTimer(Timer* timer)
{
    timer->running = false;
    timer->elapsed_time = 0.0;
}

// ������ʱ��
void startTimer(Timer* timer)
{
    if (!timer->running)
    {
        timer->start_time = currentTime();
        timer->running = true;
    }
}

// ֹͣ��ʱ��
void stopTimer(Timer* timer)
{
    if (timer->running)
    {
        timer->end_time = currentTime();
        timer->elapsed_time += (int)((timer->end_time - timer->start_time) / 1000L);
        timer->running = false;
    }
}

// ���ü�ʱ��
void resetTimer(Timer* timer)
{
    initializeTimer(timer);
}

// ��ȡ������ʱ��
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

