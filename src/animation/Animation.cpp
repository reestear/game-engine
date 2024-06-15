#include "Animation.h"
#include "TextureManager.h"
#include "SDL2/SDL.h"
#include "Transform.h"

Animation::Animation() : sprite_row(0), sprite_frame(0), animation_speed(0), frame_count(0) {}

void Animation::update() {
    sprite_frame = (SDL_GetTicks() / animation_speed) % frame_count;
}

void Animation::draw(Transform *transform, int width, int height) {
    TextureManager::getInstance()->drawFrame(
        texture_id, 
        transform->getX(), 
        transform->getY(), 
        width, 
        height, 
        sprite_row, 
        sprite_frame, 
        transform->getFlip()
    );
}

void Animation::setProperties(std::string texture_id, int sprite_row, int sprite_frame, int animation_speed, int frame_count) {
    this->texture_id = texture_id;
    this->sprite_row = sprite_row;
    this->sprite_frame = sprite_frame;
    this->animation_speed = animation_speed;
    this->frame_count = frame_count;
}