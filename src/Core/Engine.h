#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "pch.h"
#include "GameMap.h"

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

        void update(float dt);
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
        GameMap *map = nullptr;

};

#endif // ENGINE_H