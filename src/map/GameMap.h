#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "Layer.h"
#include <vector>

class GameMap {
    public:
        void update() {
            for(std::vector<Layer*>::iterator it = map_layers.begin(); it != map_layers.end(); ++it)
                (*it)->update();
        };
        void render() {
            for(std::vector<Layer*>::iterator it = map_layers.begin(); it != map_layers.end(); ++it)
                (*it)->render();
        };

        inline const std::vector<Layer*>& getMapLayers() const { return map_layers; }
    
    private:
        std::vector<Layer*> map_layers;
};

#endif // GAMEMAP_H