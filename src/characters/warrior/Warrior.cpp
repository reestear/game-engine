#include "Warrior.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Input.h"

Warrior::Warrior(Properties *props) : Character(props) {
    character_name = "warrior";
    animation->setProperties(texture_id, 0, 0, 60, 8);
}

void Warrior::draw() {
    animation->draw(transform, width, height);
}

void Warrior::update(float dt) {

    animation->setProperties("player", 0, 0, 60, 6);
    rigid_body->unsetForce();

    if(Input::getInstance()->isKeyDown(SDL_SCANCODE_A)) {
        animation->setProperties("player_run", 0, 0, 60, 8);
        rigid_body->applyForceX(10000.f*LEFT);
        // transform->setX(transform->getX() + 100.f * dt * LEFT);
        transform->setFlip(SDL_FLIP_HORIZONTAL);
    }

    if(Input::getInstance()->isKeyDown(SDL_SCANCODE_D)) {
        animation->setProperties("player_run", 0, 0, 60, 8);
        rigid_body->applyForceX(10000.f*RIGHT);
        // transform->setX(transform->getX() + 100.f * dt * RIGHT);
        transform->setFlip(SDL_FLIP_NONE);
    }

    animation->update();
    rigid_body->update(dt);

    // transform->setPosition(rigid_body->getPosition());
    // Moving only in X diretion without falling down
    transform->setX(rigid_body->getPosition().getX());
}

void Warrior::clean() {
    Character::clean();
}