#include "RigidBody.h"

RigidBody::RigidBody(float mass, float gravity) : mass(mass), gravity(gravity) {}

void RigidBody::update(float dt) {
    acceleration.setX((force.getX() + friction.getX()) / mass);
    acceleration.setY((force.getY() + friction.getY()) / mass + gravity);
    velocity = acceleration * dt;
    position += velocity * dt;
}