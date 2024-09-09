#include "Engine.h"
#include "Warrior.h"

// Constants and flags
#include "constants.h"
#include "flags.h"
// Externa header files
#include "TextureManager.h"
#include "Transform.h"
#include "Vector2D.h"
#include "Input.h"
#include "MapManager.h"
#include "Camera.h"
#include "AABB.h"
#include "CollisionManager.h"

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
    TextureManager::getInstance()->load("player", "../../assets/Characters/Warrior/WarriorIdle.png");
    TextureManager::getInstance()->load("player_run", "../../assets/Characters/Warrior/WarriorRun.png");

    player = new Warrior(new Properties("player", 136, 96, 100, 200, SDL_FLIP_NONE));
    Collider *player_collider = new AABB({20, 50, 20, 50}, player);
    player->setCollider(player_collider);
    CollisionManager::getInstance()->addCollider(player_collider);

    MapManager *map_manager = MapManager::getInstance();
    map_manager->load();

    map = MapManager::getInstance()->getGameMap("map1");

    Camera::getInstance()->setTarget(player);

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

void Engine::update(float dt) {
    player->update(dt);
    CollisionManager::getInstance()->checkCollisions();

    std::cout << "Player Y-velocity: " << player->getRigidBody()->getVelocity().getY() << std::endl;
    std::cout << "Player Y-position" <<  player->getTransform()->getY() << std::endl;

    Camera::getInstance()->update(dt);
}

void Engine::render() {
    SDL_SetRenderDrawColor(renderer, 60, 125, 43, 255);
    SDL_RenderClear(renderer);

    map->render();

    // TextureManager::getInstance()->draw("player", 100, 100, 347, 465);
    player->draw();

    SDL_RenderPresent(renderer);
}

void Engine::events() {
    Input::getInstance()->listen();
}