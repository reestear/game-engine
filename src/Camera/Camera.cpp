#include "Camera.h"

Camera *Camera::instance = nullptr;

void Camera::update(float dt) {
    if(target == nullptr) {
        return;
    }

    Point<int> target_origin = static_cast<Point<int>>(target->getOrigin());

    int newx = static_cast<int> (target_origin.getX()) - viewport.width / 2;
    int newy = static_cast<int> (target_origin.getY()) - viewport.height / 2;

    if(newx < 0) {
        newx = 0;
    }

    if(newy < 0) {
        newy = 0;
    }

    viewport.position = Point<int>(newx, newy);
}