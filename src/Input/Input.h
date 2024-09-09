#pragma once

#include "pch.h"

class Input {
    public:
        static Input *getInstance() {
            if (instance == nullptr) {
                instance = new Input();
            }
            return instance;
        }

        void listen();
        bool isKeyDown(SDL_Scancode key);

    private:
        Input();
        void keyDown();
        void keyUp();

        const Uint8* keystate;
        static Input *instance;

};