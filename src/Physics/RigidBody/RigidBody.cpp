#include "RigidBody.h"

RigidBody::RigidBody(float mass, float gravity) : mass(mass), gravity(gravity) {
    std::cout << "Applied Gravity: " << gravity << std::endl;

    constant_b = Vector2D<float>(0.05f, 0.001f);
}

// Hell nah I ain't gonna apply force on X-direction
/*void RigidBody::update(float dt) {
    acceleration.setX((force.getX() + friction.getX()) / mass);
    acceleration.setY((force.getY() + friction.getY()) / mass + gravity);
    velocity += acceleration * dt;

    if(velocity.getX() < 0) {
        velocity.setX(std::max(velocity.getX(), -getTerminalVelocity().getX()));
    } else {
        velocity.setX(std::min(velocity.getX(), getTerminalVelocity().getX()));
    }

    velocity.setY(std::min(velocity.getY(), getTerminalVelocity().getY()));

    position += velocity * dt;
}*/

void RigidBody::update(float dt) {

    if(grounded) {
        acceleration.setY(0);
        velocity.setY(0);
    }
    else {
        acceleration.setY((force.getY() + friction.getY()) / mass + gravity);
        velocity.setY(velocity.getY() + acceleration.getY() * dt);
    }

    velocity.setY(std::min(velocity.getY(), getTerminalVelocity().getY()));

    position.setX(position.getX() + velocity.getX() * dt);
    position.setY(position.getY() + velocity.getY() * dt + 0.5 * acceleration.getY() * dt * dt);
}

Vector2D<float> RigidBody::getTerminalVelocity() {
    return Vector2D<float>(
        (std::max(0.f, force.getX() - friction.getX())) / constant_b.getX(), 
        (force.getY() + mass * gravity) / constant_b.getY()
    );
}