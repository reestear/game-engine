#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "pch.h"
#include "IObject.h"
#include "Transform.h"
#include "TextureManager.h"
#include "Point.h"
#include "RigidBody.h"

class Collider;

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

        Transform *getTransform() { return transform; }
        Point<float> getOrigin() { return Point<float>(transform->getX() + width / 2, transform->getY() + height / 2); }

        inline void setCollider(Collider *collider) { this->collider = collider; }

        inline int getWidth() { return width; }
        inline int getHeight() { return height; }
        inline RigidBody *getRigidBody() { return rigid_body; }

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

        RigidBody *rigid_body = nullptr;
        Collider *collider = nullptr;
        
};

#endif