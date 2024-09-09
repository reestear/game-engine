#pragma once
#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <map>
#include <string>
#include "GameMap.h"
#include <tinyxml2.h>

class MapManager {
    public:
        static MapManager* getInstance() {
            if (instance == nullptr) {
                instance = new MapManager();
            }
            return instance;
        }

        // Impelement later
        /*bool loadGameMap(const std::string &map_name) {};
        void dropGameMap(std::string map_name) {};*/

        bool load();
        void clean();

        GameMap* getGameMap(const std::string &map_name) {
            return dict_game_maps[map_name];
        }

    private:
        bool parseMap(const std::string &map_name, const std::string &map_src);
        bool parseImageset(tinyxml2::XMLElement* xml_tileset, const std::string &map_name);
        bool parseLayer(tinyxml2::XMLElement* xml_layer, const std::string &map_name);

        inline void addGameMap(const std::string &map_name, GameMap* game_map) {
            dict_game_maps[map_name] = game_map;
        }

    private:
        MapManager() {}
        static MapManager* instance;
        std::map<std::string, GameMap*> dict_game_maps;

};

#endif // MAPMANAGER_H