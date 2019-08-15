#include "main_head.h"

Uint32					get_ticks(t_timer timer)
{
    if (timer.status == TIMER_ON)
    {
        return (SDL_GetTicks() - timer.when_started);
    }
    else if (timer.status == TIMER_PAUSED)
    {
        return (timer.when_paused);
    }
    else
        return (0);
}

void					stop_timer(t_timer *timer)
{
    timer->when_started = 0;
    timer->when_paused = 0;
    timer->status = TIMER_OFF;
}

void					unpause_timer(t_timer *timer)
{
    if (timer->status == TIMER_PAUSED)
    {
        timer->when_started = SDL_GetTicks() - timer->when_paused;
        timer->when_paused = 0;
        timer->status = TIMER_ON;
    }
}

void					pause_timer(t_timer *timer)
{
    if (timer->status == TIMER_ON)
    {
        timer->when_paused = SDL_GetTicks() - timer->when_started;
        timer->when_started = 0;
        timer->status = TIMER_PAUSED;
    }
}

void					start_timer(t_timer *timer)
{
    timer->when_started = SDL_GetTicks();
    timer->status = TIMER_ON;
}

t_timer					init_timer(void)
{
    t_timer				timer;

    timer.when_started = 0;
    timer.when_paused = 0;
    timer.status = TIMER_OFF;
    return (timer);
} 