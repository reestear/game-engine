#pragma once
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "pch.h"
class Transform;

struct Rect {

    Rect(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

    int x, y;
    int width, height;
};

struct SrcRect : Rect {
    SrcRect(int x, int y, int width, int height) : Rect(x, y, width, height) {}
};
struct DstRect : Rect {

    DstRect(int x, int y, int width, int height, double angle = 0.f, SDL_Point *center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE) : 
        Rect(x, y, width, height)
    {
        this->angle = angle;
        this->flip = flip;
        this->center = center;
    }

    double angle;
    SDL_Point *center;
    SDL_RendererFlip flip;
};

class TextureManager {
    public:
        static TextureManager* getInstance() {
            if (instance == nullptr) {
                instance = new TextureManager();
            }
            return instance;
        }

        bool load(const std::string &id, const std::string &filename);
        void drop(const std::string &id);
        void clean();

        void draw(const std::string &id, const SrcRect *src_rect, const DstRect *dst_rect);

    private:
        TextureManager() {}
        static TextureManager* instance;
        std::map<std::string, SDL_Texture*> texture_map;
};

#endif // TEXTURE_MANAGER_H