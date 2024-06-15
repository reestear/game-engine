#include "Warrior.h"
#include <iostream>
#include "TextureManager.h"
#include <SDL2/SDL.h>
#include "GameObject.h"

Warrior::Warrior(Properties *props) : Character(props) {
    character_name = "warrior";
    animation->setProperties(texture_id, 0, 0, 60, 6);
    
}

void Warrior::draw() {
    animation->draw(transform, width, height);
}

void Warrior::update(float dt) {
    animation->update();
    rigid_body->applyForceX(5.f);
    rigid_body->update(0.4f);
    transform->setPosition(rigid_body->getPosition());
}

void Warrior::clean() {
    Character::clean();
}