#include "Timer.h"

#include "pch.h"

Timer *Timer::instance = nullptr;

void Timer::tick() {
    delta_time = (SDL_GetTicks() - last_time) / 1000.0f;

    if (delta_time > MAX_DELTA_TIME) {
        delta_time = MAX_DELTA_TIME;
    }

    last_time = SDL_GetTicks();
}
