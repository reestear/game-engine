#include "Engine.h"
#include "Warrior.h"

// Constants and flags
#include "constants.h"
#include "flags.h"
// Externa header files
#include "TextureManager.h"
#include "Transform.h"
#include "Vector2D.h"

// Define the static member variable 'instance'
Engine* Engine::instance = nullptr;
Warrior* player = nullptr;

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

    // TextureManager::getInstance()->load("tree", "assets/textures/trees/tree.png");
    TextureManager::getInstance()->load("player", "assets/lessons/Idle.png");
    player = new Warrior(new Properties("player", 136, 96, 100, 200, SDL_FLIP_NONE));

    return is_running = true;
}

bool Engine::clean() {
    TextureManager::getInstance()->clean();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    
    return true;
}

void Engine::quit() {
    is_running = false;
}

void Engine::update() {
    player->update(0.0f);
}

void Engine::render() {
    SDL_SetRenderDrawColor(renderer, 60, 125, 43, 255);
    SDL_RenderClear(renderer);

    // TextureManager::getInstance()->draw("player", 100, 100, 347, 465);
    player->draw();

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