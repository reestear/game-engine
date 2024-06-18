#ifndef TIMER_H
#define TIMER_H

#define FPS 60
#define MAX_DELTA_TIME 1.5f

class Timer {
    public:
        static Timer *getInstance() {
            if(instance == nullptr) {
                instance = new Timer();
            }

            return instance;
        }

        void tick();
        inline float getDeltaTime() { return delta_time; }

    private:
        Timer() {};
        static Timer *instance;
        float delta_time;
        float last_time;
};

#endif // TIMER_H