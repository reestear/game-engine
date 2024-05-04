#include "core/Engine.h"
#include <iostream>

int main(int argc, char* argv[]) {

    Engine *engine = Engine::getInstance();
    
    if (!engine->init()) {
        std::cerr << "Failed to initialize engine" << std::endl;
        return 1;
    }

    while(engine->isRunning()) {
        engine->events();
        engine->update();
        engine->render();
    }

    engine->clean();

    return 0;
}