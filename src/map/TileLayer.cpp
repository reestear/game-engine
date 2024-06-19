#include "TileLayer.h"

TileLayer::TileLayer(int tile_size, int num_rows, int num_cols, LayerMap layer_map, ListTileset tilesets) : 
    tile_size(tile_size),
    num_rows(num_rows),
    num_cols(num_cols),
    layer_map(layer_map),
    tilesets(tilesets)
{
}

void TileLayer::update() {

}

void TileLayer::render() {

}