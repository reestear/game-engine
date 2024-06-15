#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "pch.h"
#include "IObject.h"
#include "Transform.h"
#include "TextureManager.h"

struct Properties {
    std::string texture_id;
    int width, height;
    float x, y;
    SDL_RendererFlip flip;

    Properties(std::string texture_id, int width, int height, float x, float y, SDL_RendererFlip flip) :
        texture_id(texture_id), 
        width(width), 
        height(height),
        x(x), 
        y(y), 
        flip(flip) 
    {}
};

class GameObject : public IObject {

    public:
        GameObject(Properties *props) : 
            width(props->width), 
            height(props->height), 
            texture_id(props->texture_id)
        {
            transform = new Transform(props->x, props->y, props->flip);
        }

        virtual void draw() = 0;
        virtual void update(float dt) = 0;
        virtual void clean() {
            delete transform;
            TextureManager::getInstance()->drop(texture_id);
        };

    protected:
        Transform *transform;
        int width, height;
        std::string texture_id;
        
};

#endif