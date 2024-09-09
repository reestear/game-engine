#pragma once
#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H

#include "Layer.h"
#include <string>
#include <vector>

struct ObjectLayerItem {

    ObjectLayerItem(int gid, int x, int y, int width, int height, float depth = 1.f) :
        gid(gid),
        x(x),
        y(y),
        width(width),
        height(height),
        depth(depth)
    {}

    int gid;
    int x, y;
    int width, height;
    float depth;
};

class ObjectLayer : public Layer {
    public:
        ObjectLayer(const std::string &map_name, const std::string &layer_name, const std::vector<ObjectLayerItem> &object_layer_items);

        virtual void update() override;
        virtual void render() override;

    private:
        std::vector<ObjectLayerItem> object_layer_items;
};

#endif // OBJECTLAYER_H