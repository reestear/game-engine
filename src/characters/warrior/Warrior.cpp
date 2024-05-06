#include "Warrior.h"

Warrior::Warrior(Properties *props) : Character(props) {
    character_name = "warrior";
    animation->setProperties(texture_id, 0, 0, 60, 6);
}

void Warrior::draw() {
    animation->draw(transform, width, height);
}

void Warrior::update(float dt) {
    animation->update();
}

void Warrior::clean() {
    Character::clean();
}