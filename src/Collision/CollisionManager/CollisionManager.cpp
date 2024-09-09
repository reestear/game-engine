#include "CollisionManager.h"
#include "DynamicCollider.h"

CollisionManager *CollisionManager::instance = nullptr;

void CollisionManager::addCollider(Collider *collider) {
    if(DynamicCollider *ptr = dynamic_cast<DynamicCollider*>(collider)){
        std::cout << "Dynamic Collider" << std::endl;
        dynamic_colliders.push_back(collider);
    } else {
        std::cout << "Static Collider" << std::endl;
        static_colliders.push_back(collider);
    }
}

void CollisionManager::checkCollisions() {

    for(Collider *collider : dynamic_colliders) {
        DynamicCollider *dynamic_collider = static_cast<DynamicCollider*>(collider);
        dynamic_collider->game_object->getRigidBody()->setGrounded(false);
    }

    for(auto dynamic_collider : dynamic_colliders) {
        for(auto static_collider : static_colliders) {
            dynamic_collider->checkCollision(static_collider);
        }
    }
    
    // No Logic for dynamic colliders colliding with each other
    /*for(auto dynamic_collider : dynamic_colliders) {
        for(auto dynamic_collider2 : dynamic_colliders) {
            if(dynamic_collider != dynamic_collider2) {
                dynamic_collider->checkCollision(dynamic_collider2);
            }
        }
    }*/
}

