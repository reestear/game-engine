#pragma once
#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"

struct Properties;

class Warrior : public Character {
    
    public:
        Warrior(Properties *props);

        virtual void draw();

        virtual void update(float dt);

        virtual void clean();

};

#endif // WARRIOR_H