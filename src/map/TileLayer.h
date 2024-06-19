#ifndef TILELAYER_H
#define TILELAYER_H

#include "Layer.h"
#include <string>
#include <vector>

struct Tileset {
    int firstId, num_tiles, lastId;
    int num_rows, num_cols;
    int tile_size;

    std::string tile_name, tile_src;
};

using ListTileset = std::vector<Tileset>;
using LayerMap = std::vector<std::vector<int> >;

class TileLayer : public Layer {
    private:
        int tile_size;
        int num_rows, num_cols;

        ListTileset tilesets;
        LayerMap layer_map;
    
    public:

        TileLayer(int tile_size, int num_rows, int num_cols, LayerMap layer_map, ListTileset tilesets);
        virtual void update() override;
        virtual void render() override;

        inline const LayerMap& getLayerMap() const {return layer_map;}

};

#endif // TILELAYER_H