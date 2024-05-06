#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector2D.h"
#include <string>
#include <iostream>

class Transform {

    public:

        Transform(float x=0, float y = 0) : x(x), y(y) {}

        inline float getX() { return x; }
        inline float getY() { return y; }
        inline float getRotation() { return rotation; }
        inline float getScale() { return scale; }
        
        inline void setX(float x) { this->x = x; }
        inline void setY(float y) { this->y = y; }
        inline void setRotation(float rotation) { this->rotation = rotation; }
        inline void setScale(float scale) { this->scale = scale; }

        inline void translateX(float x) { this->x += x; }
        inline void translateY(float y) { this->y += y; }
        inline void translate(Vector2D translation) { x += translation.getX(); y += translation.getY(); }

        void log(std::string msg) {
            std::cout << msg << "(x, y) : " << "(" << x << ", " << y << ")" << std::endl;
        }
    
    private:

        float x;
        float y;
        float rotation;
        float scale;

};

#endif // TRANSFORM_H