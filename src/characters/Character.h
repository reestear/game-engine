#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include "Animation.h"
#include <string>

class Character : public GameObject {
    
    public:
        Character(Properties *props) : GameObject(props) {
            animation = new Animation();
        }

        virtual void draw() = 0;
        virtual void update(float dt) = 0;
        virtual void clean() {
            GameObject::clean();
        };

    protected:
        Animation *animation;
        std::string character_name;

};

#endif // CHARACTER_H