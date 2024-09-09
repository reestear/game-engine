#pragma once
#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "Imageset.h"
#include "Layer.h"
#include <vector>

class GameObject;

class GameMap {
    public:

        GameMap(const std::string &map_name, const std::string &map_src, int tile_width, int tile_height, int row_count, int column_count) : 
            map_name(map_name),
            map_src(map_src),
            tile_width(tile_width),
            tile_height(tile_height),
            row_count(row_count),
            column_count(column_count)
        {}

        void update() {
            for(std::vector<Layer*>::iterator it = map_layers.begin(); it != map_layers.end(); ++it)
                (*it)->update();
        };
        void render() {
            for(std::vector<Layer*>::iterator it = map_layers.begin(); it != map_layers.end(); ++it)
                (*it)->render();
        };

        inline const std::string& getMapSrc() const { return map_src; }
        inline const std::string& getMapName() const { return map_name; }

        inline const std::vector<Imageset*>& getImagesets() const { return imagesets; }
        inline const std::vector<Layer*>& getMapLayers() const { return map_layers; }

        inline const int getTileWidth() const { return tile_width; }
        inline const int getTileHeight() const { return tile_height; }
        
        std::string const getMapDir() const {
            std::string map_dir = map_src;
            map_dir.erase(map_dir.find_last_of("/"));
            return map_dir;
        }

    private:
        friend class MapManager;
        void addImageset(Imageset* imageset) { imagesets.push_back(imageset); }
        void addLayer(Layer* layer) { map_layers.push_back(layer); }
        void addStaticColliderObject(GameObject* object) { game_map_static_collider_objects.push_back(object); }
    
    private:
        std::vector<Imageset*> imagesets;
        std::vector<Layer*> map_layers;
        std::string map_name, map_src;

        std::vector<GameObject*> game_map_static_collider_objects;

        int tile_width, tile_height;
        int row_count, column_count;
};

#endif // GAMEMAP_H