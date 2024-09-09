#pragma once
#ifndef COLLIDER_H
#define COLLIDER_H

#include "GameObject.h"

class CollisionManager;

class Collider {
    friend CollisionManager;

    public:
        virtual void checkCollision(Collider *collider) = 0;

        virtual ~Collider() {};

};

#endif // COLLIDER_H