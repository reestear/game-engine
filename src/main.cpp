#include "Engine.h"
#include "Timer.h"

int main(int argc, char* argv[]) {

    Engine *engine = Engine::getInstance();
    
    if (!engine->init()) {
        std::cerr << "Failed to initialize engine..." << std::endl;
        return 1;
    }

    while(engine->isRunning()) {
        Timer::getInstance()->tick();
        engine->events();
        engine->update();
        engine->render();
    }

    engine->clean();

    return 0;
}