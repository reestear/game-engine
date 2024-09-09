#pragma once
#ifndef TILESET_H
#define TILESET_H

#include "Imageset.h"
#include <string>

class Tileset : public Imageset {
    public:

        Tileset(int firstGID, int tile_count, int column_count, int tile_width, int tile_height, const std::string &name, const std::string &tileset_src) :
            Imageset(firstGID, tile_count),
            column_count(column_count),
            tile_width(tile_width),
            tile_height(tile_height),
            name(name),
            tileset_src(tileset_src)
        {}
        
        virtual void draw(int gid, const DstRect* dst_rect) override;
        virtual bool load() override;

    public:
        int column_count;
        int tile_width, tile_height;
        std::string name, tileset_src;

};

#endif // TILESET_H