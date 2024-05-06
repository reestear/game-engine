#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include "Character.h"
#include "TextureManager.h"
#include <SDL2/SDL.h>
#include "GameObject.h"

class Warrior : public Character {
    
    public:
        Warrior(Properties *props);

        virtual void draw();

        virtual void update(float dt);

        virtual void clean();

};

#endif // WARRIOR_H