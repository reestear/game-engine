#include "Warrior.h"

Warrior::Warrior(Properties *props) : Character(props) {
    character_name = "warrior";
    row = 0;
    frame = 0;
    frameCount = 6;
    animationSpeed = 60;
}

void Warrior::draw() {
   TextureManager::getInstance()->drawFrame(texture_id, transform->getX(), transform->getY(), width, height, row, frame, flip); 
}

void Warrior::update(float dt) {
    frame = (SDL_GetTicks() / animationSpeed) % frameCount;
}

void Warrior::clean() {
    Character::clean();
}