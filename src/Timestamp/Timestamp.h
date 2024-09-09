#pragma once
#ifndef TIMER_H
#define TIMER_H

#define MAX_DELTA_TIME 1.5f

class Timestamp {
    public:
        static Timestamp *getInstance() {
            if(instance == nullptr) {
                instance = new Timestamp();
            }

            return instance;
        }

        inline void setLogTimeEnabled() { log_time = true; }
        inline void setLogTimeDisable() { log_time = false; }

        void tick();
        inline float getDeltaTime() { return delta_time; }


    private:
        Timestamp() {};
        static Timestamp *instance;
        float delta_time;
        float last_time;

        bool log_time = false;
        float cumulative_time = 0.0f;
};

#endif // TIMER_H