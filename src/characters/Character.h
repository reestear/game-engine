#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include <string>

class Character : public GameObject {
    
    public:
        Character(Properties *props) : GameObject(props) {}

        virtual void draw() = 0;
        virtual void update(float dt) = 0;
        virtual void clean() {
            GameObject::clean();
        };

    protected:
        std::string character_name;
        int row, frame, frameCount;
        int animationSpeed;

};

#endif // CHARACTER_H