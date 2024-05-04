#include "Engine.h"

// Define the static member variable 'instance'
Engine* Engine::instance = nullptr;

bool Engine::init() {

    if(SDL_Init(SDL_INIT_VIDEO) != 0 || ((IMG_Init(IMG_INIT_FLAGS) & IMG_INIT_FLAGS) != IMG_INIT_FLAGS) ){
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(window == nullptr){
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == nullptr){
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    return is_running = true;
}

bool Engine::clean() {
}

void Engine::quit() {
    is_running = false;
}

void Engine::update() {
    // std::cout << "Updating" << std::endl;
}

void Engine::render() {
    SDL_SetRenderDrawColor(renderer, 60, 125, 43, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Engine::events() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type){
        case SDL_QUIT:
            quit();
            break;
        default:
            break;
    }
}