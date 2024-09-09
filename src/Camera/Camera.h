#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Point.h"
#include "GameObject.h"
#include "constants.h"

struct Viewport {
    Point<int> position;
    int width, height;
};

class Camera {
    public:
        static Camera *getInstance() {
            if (instance == nullptr) {
                instance = new Camera();
            }
            return instance;
        };

        void update(float dt);
        inline Viewport getViewport() { return viewport; }
        inline void setTarget(GameObject *target) { this->target = target; }

    private:
        Camera() {
            viewport.position = Point<int>(0, 0);
            viewport.width = SCREEN_WIDTH;
            viewport.height = SCREEN_HEIGHT;
        };
        GameObject *target = nullptr;
        Viewport viewport;

        static Camera *instance;

};

#endif // CAMERA_H