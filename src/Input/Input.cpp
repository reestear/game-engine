#include "Input.h"
#include "Engine.h"

Input *Input::instance = nullptr;

Input::Input() {
    keystate = SDL_GetKeyboardState(NULL);
}

void Input::listen() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                Engine::getInstance()->quit();
                break;
            case SDL_KEYDOWN:
                keyDown();
                break;
            case SDL_KEYUP:
                keyUp();
                break;
            default:
                break;
        }
    }
}

bool Input::isKeyDown(SDL_Scancode key) {
    return keystate[key];
}

void Input::keyDown() {
    keystate = SDL_GetKeyboardState(NULL);
}

void Input::keyUp() {
    keystate = SDL_GetKeyboardState(NULL);
}