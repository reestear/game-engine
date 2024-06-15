#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "pch.h"

class TextureManager {
    public:
        static TextureManager* getInstance() {
            if (instance == nullptr) {
                instance = new TextureManager();
            }
            return instance;
        }

        bool load(std::string id, std::string filename);
        void drop(std::string id);
        void clean();

        void draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void drawFrame(std::string id, int x, int y, int width, int height, int current_row, int current_frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:
        TextureManager() {}
        static TextureManager* instance;
        std::map<std::string, SDL_Texture*> texture_map;
};

#endif // TEXTURE_MANAGER_H