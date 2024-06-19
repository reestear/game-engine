#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <map>
#include <string>
#include "GameMap.h"
#include "TileLayer.h"
#include <tinyxml2.h>

class MapManager {
    public:
        static MapManager* getInstance() {
            if (instance == nullptr) {
                instance = new MapManager();
            }
            return instance;
        }

        bool load();
        void clean();

    private:
        bool parseMap(std::string map_name, std::string map_src);
        

    private:
        MapManager() {}
        static MapManager* instance;


};

#endif // MAPMANAGER_H