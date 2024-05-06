#ifndef ANIMATION_H
#define ANIMATION_H

#include "SDL2/SDL.h"
#include "Transform.h"
#include <string>

class Animation {

    public:
        Animation();

        void update();
        void draw(Transform *transform, int width, int height);
        void setProperties(std::string texture_id, int sprite_row, int sprite_frame, int animation_speed, int frame_count);

    private:
        int sprite_row, sprite_frame;
        int animation_speed, frame_count;
        std::string texture_id;
};

#endif // ANIMATION_H