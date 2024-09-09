#include "Engine.h"
#include "Timestamp.h"

int main(int argc, char* argv[]) {

    Engine *engine = Engine::getInstance();
    
    if (!engine->init()) {
        std::cerr << "Failed to initialize engine..." << std::endl;
        return 1;
    }

    Timestamp *timestamp = Timestamp::getInstance();
    timestamp->setLogTimeEnabled();

    while(engine->isRunning()) {
        timestamp->tick();
        float dt = timestamp->getDeltaTime();

        engine->events();
        engine->update(dt);
        engine->render();
    }

    engine->clean();

    return 0;
}