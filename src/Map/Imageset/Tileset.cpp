#include "Tileset.h"
#include "TextureManager.h"

void Tileset::draw(int gid, const DstRect* dst_rect) {

    int tile_id = gid - firstGID;
    
    if(tile_id < 0 || tile_id >= count) {
        return;
    }

    int tile_row = tile_id / column_count;
    int tile_column = tile_id % column_count;

    SrcRect src_rect(tile_column * tile_width, tile_row * tile_height, tile_width, tile_height);

    TextureManager::getInstance()->draw(name, &src_rect, dst_rect);
}

bool Tileset::load() {
    if(TextureManager::getInstance()->load(name, tileset_src)) {
        std::cout << "Tileset " << tileset_src << " loaded successfully" << std::endl;
        return true;
    }

    std::cerr << "Failed to load tileset: " << tileset_src << std::endl;
    return false;
}