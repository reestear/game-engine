#pragma once
#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include "Vector2D.h"

#define RIGHT 1
#define LEFT -1
#define UP -1
#define DOWN 1

#define DEFAULT_GRAVITY 1000.f

class RigidBody {
    friend class DynamicCollider;

    public:
        RigidBody(float mass = 1.0f, float gravity = DEFAULT_GRAVITY);
        
        // Getters
        inline float getMass() { return mass; }
        inline float getGravity() { return gravity; }
        
        inline Vector2D<float> getForce() { return force; }
        inline Vector2D<float> getFriction() { return friction; }

        inline Vector2D<float> getVelocity() {return velocity; }
        inline Vector2D<float> getAcceleration() { return acceleration; }
        inline Vector2D<float> getPosition() { return position; }
        
        // Setters
        inline void setMass(float mass) { this->mass = mass; }
        inline void setGravity(float gravity) { this->gravity = gravity; }

        // Applied velocity
        inline void applyVelocity(Vector2D<float> velocity) { this->velocity = velocity; }
        inline void applyVelocityX(float velocityX) { this->velocity.setX(velocityX); }
        inline void applyVelocityY(float velocityY) { this->velocity.setY(velocityY); }
        inline void unsetVelocityY() { velocity.setY(0); }
        inline void reverseVelocityY() { velocity.setY(-velocity.getY()); }

        // Applied forces
        inline void applyForce(Vector2D<float> force) { this->force = force; }
        inline void applyForceX(float forceX) { force.setX(forceX); }
        inline void applyForceY(float forceY) { force.setY(forceY); }
        inline void unsetForce() { force = Vector2D<float>(0, 0); }

        // Applied gravity
        inline void applyGravity(float gravity_ = DEFAULT_GRAVITY) {gravity = gravity_;}
        inline void unsetGravity() { gravity = 0; }

        // Friction
        inline void applyFriction(Vector2D<float> friction) { this->friction = friction; }
        inline void unsetFriction() { friction = Vector2D<float>(0, 0); }

        inline Vector2D<float> getTerminalVelocity();

        inline void translate(int dx, int dy) {
            position.translate(dx, dy);
        }

        inline void setGrounded(bool grounded) { this->grounded = grounded; }

        // Update
        void update(float dt);

    private:
        // Constants defining the physics of the object
        float mass;
        float gravity;
        
        Vector2D<float> constant_b;

        // Applied forces
        Vector2D<float> force;
        Vector2D<float> friction;

        // Object's properties
        Vector2D<float> velocity;
        Vector2D<float> acceleration;
        Vector2D<float> position;

        // Grounded
        bool grounded = false;

};

#endif // RIGID_BODY_H