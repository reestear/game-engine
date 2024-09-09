#pragma once
#ifndef DYNAMICCOLLIDER_H
#define DYNAMICCOLLIDER_H

#include "Collider.h"

struct Margin {
    int top;
    int right;
    int bottom;
    int left;
};

class DynamicCollider : public Collider {
    friend CollisionManager;

    public:
        virtual void checkCollision(Collider *collider) = 0;
        virtual void collide(int dx, int dy) = 0;

        DynamicCollider(GameObject *game_object, Margin margin = {0, 0, 0, 0}) : 
            game_object(game_object), margin_collider(margin)
        {}

        virtual ~DynamicCollider() {};

    
    protected:
        Margin margin_collider = {0, 0, 0, 0};

        GameObject *game_object;
};

#endif // DYNAMICCOLLIDER_H