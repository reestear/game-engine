#include "AABB.h"
#include "iostream"

#include "GameObject.h"
#include "StaticCollider.h"

void AABB::checkCollision(Collider *collider) {

    StaticCollider *static_collider = dynamic_cast<StaticCollider*>(collider);

    if(static_collider == nullptr) {
        std::cerr << "AABB::checkCollision() expects a StaticCollider" << std::endl;
        return;
    }

    Transform *game_obj_transform = game_object->getTransform();

    int x = getX();
    int y = getY();
    int width = getWidth();
    int height = getHeight();

    // No Collision Detected
    if(!(x < static_collider->x + static_collider->width
    && x + width > static_collider->x
    && y < static_collider->y + static_collider->height
    && y + height > static_collider->y)) {
        return;
    }

    bool is_dynamic_collider, aabb_is_dynamic_collider;
    
    if(DynamicCollider *ptr = dynamic_cast<DynamicCollider*>(this)) {
        is_dynamic_collider = true;
    } else {
        is_dynamic_collider = false;
    }

    if(DynamicCollider *ptr = dynamic_cast<DynamicCollider*>(static_collider)) {
        aabb_is_dynamic_collider = true;
    } else {
        aabb_is_dynamic_collider = false;
    }

    int8_t collision_mask = is_dynamic_collider | (aabb_is_dynamic_collider << 1);

    switch (collision_mask)
    {
    // Both colliders are static
    case 0:
        // Do nothing
        break;
    
    // Both colliders are dynamic
    case 3:
        std::cerr << "No logic to check collision of two Dynamic AABB's" << std::endl;
        break;
    
    // Either one of the colliders is dynamic, but not both
    default:

        float overlap_left = (getX() + getWidth()) - static_collider->x;
        float overlap_right = (static_collider->x + static_collider->width) - getX();
        float overlap_top = (getY() + getHeight()) - static_collider->y;
        float overlap_bottom = (static_collider->y + static_collider->height) - getY();

        bool from_left = overlap_left < overlap_right;
        bool from_top = overlap_top < overlap_bottom;

        float min_overlap_x = from_left ? overlap_left : overlap_right;
        float min_overlap_y = from_top ? overlap_top : overlap_bottom;

        int dx = 0, dy = 0;

        if (min_overlap_x < min_overlap_y) {
            dx = from_left ? -min_overlap_x : min_overlap_x;
        } else {
            dy = from_top ? -min_overlap_y : min_overlap_y;
        }

        collide(dx, dy);

        break;
    }

}

void AABB::collide(int dx, int dy) {
    game_object->getRigidBody()->translate(dx, dy);

    // Now this one, only handles the collision with ceiling
    if(dy > 0) {
        game_object->getRigidBody()->reverseVelocityY();
    } else if(dy < 0) {
        game_object->getRigidBody()->unsetVelocityY();
    }

    if(dy < 0) {
        game_object->getRigidBody()->setGrounded(true);
    }

    game_object->getTransform()->translate(Vector2D<float>(static_cast<float>(dx), static_cast<float>(dy)));
}