#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector2D.h"
#include "pch.h"

class Transform {

    public:

        Transform(float x=0, float y = 0, SDL_RendererFlip flip = SDL_FLIP_NONE, float scale = 1) : x(x), y(y), flip(flip), scale(scale) {}

        inline float getX() { return x; }
        inline float getY() { return y; }
        inline SDL_RendererFlip getFlip() { return flip; }
        inline float getScale() { return scale; }
        
        inline void set(Transform *transform) { x = transform->getX(); y = transform->getY(); flip = transform->getFlip(); scale = transform->getScale(); }
        inline void setPosition(Vector2D<float> position) { x = position.getX(); y = position.getY(); }
        inline void setX(float x) { this->x = x; }
        inline void setY(float y) { this->y = y; }
        inline void setFlip(SDL_RendererFlip flip) { this->flip = flip; }
        inline void setScale(float scale) { this->scale = scale; }

        inline void translateX(float x) { this->x += x; }
        inline void translateY(float y) { this->y += y; }
        inline void translate(Vector2D<float> translation) { x += translation.getX(); y += translation.getY(); }

        void log(std::string msg) {
            std::cout << msg << "(x, y) : " << "(" << x << ", " << y << ")" << std::endl;
        }
    
    private:

        float x;
        float y;
        SDL_RendererFlip flip;
        float scale;

};

#endif // TRANSFORM_H