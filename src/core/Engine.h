#ifndef ENGINE_H
#define ENGINE_H

// I don't know why this is necessary, but it is.
#include <iostream>
// SDL2 and SDL2_Image
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
// Constants and flags
#include "constants.h"
#include "flags.h"

class Engine {
    
    public:
        static Engine* getInstance() {
            if (instance == nullptr) {
                instance = new Engine();
            }
            return instance;
        }

        bool init();
        bool clean();
        void quit();

        void update();
        void render();
        void events();

        inline bool isRunning() { return is_running; }
        inline SDL_Renderer* getRenderer() { return renderer; }

    private:
        Engine() {}
        static Engine* instance;
        bool is_running = false;

        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;
};

#endif // ENGINE_H