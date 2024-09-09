#include "Timestamp.h"

#include "pch.h"

Timestamp *Timestamp::instance = nullptr;

void Timestamp::tick() {
    delta_time = (SDL_GetTicks() - last_time) / 1000.0f;

    if (delta_time > MAX_DELTA_TIME) {
        delta_time = MAX_DELTA_TIME;
    }

    cumulative_time += delta_time;

    if (log_time) {
        if(cumulative_time > 1.0f) {
            std::cout << "FPS: " << 1.0f / delta_time << std::endl;
            cumulative_time = 0.0f;
        }
    }

    last_time = SDL_GetTicks();
}
