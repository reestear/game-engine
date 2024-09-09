#include "TextureManager.h"
#include "Engine.h"
#include "Transform.h"

TextureManager* TextureManager::instance = nullptr;

bool TextureManager::load(const std::string &id, const std::string &filename) {

    std::cout << "Loading Texture '" << id << "' : " <<  filename << std::endl;

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

    std::cout << "Texture '" << id << "' loaded successfully" << std::endl;

    return true;
}

void TextureManager::draw(const std::string &id, const SrcRect *src_rect, const DstRect *dst_rect) {
    SDL_Rect sdl_src_rect = {src_rect->x, src_rect->y, src_rect->width, src_rect->height};
    SDL_Rect sdl_dst_rect = {dst_rect->x, dst_rect->y, dst_rect->width, dst_rect->height};

    SDL_RenderCopyEx(Engine::getInstance()->getRenderer(), texture_map[id], &sdl_src_rect, &sdl_dst_rect, dst_rect->angle, dst_rect->center, dst_rect->flip);
}

void TextureManager::drop(const std::string &id) {
    SDL_DestroyTexture(texture_map[id]);
    texture_map.erase(id);
}

void TextureManager::clean() {
    for (auto &texture : texture_map) {
        SDL_DestroyTexture(texture.second);
    }
    texture_map.clear();
}