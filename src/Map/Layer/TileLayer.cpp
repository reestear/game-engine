#include "TileLayer.h"
#include "MapManager.h"
#include "TextureManager.h"
#include "Camera.h"

TileLayer::TileLayer(const std::string &map_name, const std::string &layer_name, int tile_width, int tile_height, int row_count, int column_count, const LayerGrid &layer_grid) :
    Layer(map_name, layer_name),
    tile_width(tile_width),
    tile_height(tile_height),
    row_count(row_count),
    column_count(column_count),
    layer_grid(layer_grid)
{}

void TileLayer::update() {

}

void TileLayer::render() {
    for(int i = 0; i < row_count; ++i) {
        for(int j = 0; j < column_count; ++j) {
            const int gid = layer_grid[i][j];
            if(gid == 0) continue;

            // Render tile
            std::vector<Imageset*> imagesets = MapManager::getInstance()->getGameMap(map_name)->getImagesets();
            for(std::vector<Imageset*>::iterator it = imagesets.begin(); it != imagesets.end(); ++it) {
                if((*it)->getFirstGID() <= gid && gid < (*it)->getFirstGID() + (*it)->getCount()) {
                    Camera *camera = Camera::getInstance();

                    DstRect dst_rect(j * tile_width - camera->getViewport().position.getX(), i * tile_height -camera->getViewport().position.getY(), tile_width, tile_height);

                    (*it)->draw(gid, &dst_rect);
                    break;
                }
            }
        }
    }
}