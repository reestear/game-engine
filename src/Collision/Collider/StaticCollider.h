#pragma once
#ifndef STATICCOLLIDER_H
#define STATICCOLLIDER_H

#include "Collider.h"

class StaticCollider : public Collider {
    public:
        StaticCollider(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}
        virtual void checkCollision(Collider *collider) override {}
        
        virtual ~StaticCollider() override {};

    public:
        int x, y;
        int width, height;
};


#endif // STATICCOLLIDER_H