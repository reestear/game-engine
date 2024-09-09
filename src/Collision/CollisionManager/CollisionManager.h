#pragma once
#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "Collider.h"
#include <vector>

class CollisionManager {
    public:

        static CollisionManager *getInstance() {
            if(instance == nullptr) {
                instance = new CollisionManager();
            }
            return instance;
        }

        void addCollider(Collider *collider);
        void checkCollisions();

        ~CollisionManager() {
            for(auto dynamic_collider : dynamic_colliders) {
                delete dynamic_collider;
            }

            for(auto static_collider : static_colliders) {
                delete static_collider;
            }

            dynamic_colliders.clear();
            static_colliders.clear();
        }

    private:
        std::vector<Collider*> dynamic_colliders;
        std::vector<Collider*> static_colliders;


        CollisionManager() {}
        static CollisionManager *instance;
};

#endif // COLLISION_MANAGER_H