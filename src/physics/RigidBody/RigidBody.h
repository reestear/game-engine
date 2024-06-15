#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include "Vector2D.h"

class RigidBody {

    public:
        RigidBody(float mass = 1.0f, float gravity = 9.8f);
        
        // Getters
        inline float getMass() { return mass; }
        inline float getGravity() { return gravity; }
        
        inline Vector2D getForce() { return force; }
        inline Vector2D getFriction() { return friction; }

        inline Vector2D getVelocity() {return velocity; }
        inline Vector2D getAcceleration() { return acceleration; }
        inline Vector2D getPosition() { return position; }
        
        // Setters
        inline void setMass(float mass) { this->mass = mass; }
        inline void setGravity(float gravity) { this->gravity = gravity; }

        // Applied forces
        inline void applyForce(Vector2D force) { this->force = force; }
        inline void applyForceX(float forceX) { force.setX(forceX); }
        inline void applyForceY(float forceY) { force.setY(forceY); }
        inline void unsetForce() { force = Vector2D(0, 0); }

        inline void applyFriction(Vector2D friction) { this->friction = friction; }
        inline void unsetFriction() { friction = Vector2D(0, 0); }

        // Update
        void update(float dt);

    private:
        // Constants defining the physics of the object
        float mass;
        float gravity;

        // Applied forces
        Vector2D force;
        Vector2D friction;

        // Object's properties
        Vector2D velocity;
        Vector2D acceleration;
        Vector2D position;

};

#endif // RIGID_BODY_H