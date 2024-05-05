#include "TextureManager.h"

TextureManager* TextureManager::instance = nullptr;

bool TextureManager::load(std::string id, std::string filename) {
    SDL_Surface *temp_surface = IMG_Load(filename.c_str());
    if (temp_surface == nullptr) {
        std::cerr << "Error loading image: " << filename << std::endl;
        std::cerr << "Error Message: " << IMG_GetError() << std::endl;
        return false;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(Engine::getInstance()->getRenderer(), temp_surface);
    if (texture == nullptr) {
        std::cerr << "Error creating texture: " << filename << std::endl;
        std::cerr << "Error Message: " << SDL_GetError() << std::endl;
        return false;
    }

    texture_map[id] = texture;
    SDL_FreeSurface(temp_surface);

    return true;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip) {
    SDL_Rect src_rect = {0, 0, width, height};
    SDL_Rect dst_rect = {x, y, width, height};

    SDL_RenderCopyEx(Engine::getInstance()->getRenderer(), texture_map[id], &src_rect, &dst_rect, 0, nullptr, flip);
}

void TextureManager::drop(std::string id) {
    SDL_DestroyTexture(texture_map[id]);
    texture_map.erase(id);
}

void TextureManager::clean() {
    for (auto &texture : texture_map) {
        SDL_DestroyTexture(texture.second);
    }
    texture_map.clear();
}