#pragma once
#ifndef AABB_H
#define AABB_H

#include "DynamicCollider.h"

class AABB : public DynamicCollider {
    public:
        AABB(Margin margin = {0, 0, 0, 0}, GameObject *game_object = nullptr) : 
            DynamicCollider(game_object, margin)
        {}

        inline int getX() { return game_object->getTransform()->getX() + margin_collider.left; }
        inline int getY() { return game_object->getTransform()->getY() + margin_collider.top; }
        inline int getWidth() { return game_object->getWidth() - margin_collider.right - margin_collider.left; }
        inline int getHeight() { return game_object->getHeight() - margin_collider.bottom - margin_collider.top; }

        virtual void checkCollision(Collider *collider) override;
        virtual void collide(int dx, int dy) override;

        virtual ~AABB() override {};


};

#endif // AABB_H