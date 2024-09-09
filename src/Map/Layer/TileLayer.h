#pragma once
#ifndef TILELAYER_H
#define TILELAYER_H

#include "Layer.h"
#include <vector>
#include <string>

using LayerGrid = std::vector<std::vector<int> >;

class TileLayer : public Layer {
    public:
        TileLayer(const std::string &map_name, const std::string &layer_name, int tile_width, int tile_height, int row_count, int column_count, const LayerGrid &layer_grid);

        virtual void update() override;
        virtual void render() override;

        inline const LayerGrid& getLayerGrid() const {return layer_grid;}

    private:
        int tile_width, tile_height;
        int row_count, column_count;
        LayerGrid layer_grid;

};

#endif // TILELAYER_H