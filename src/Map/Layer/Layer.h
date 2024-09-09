#pragma once
#ifndef LAYER_H
#define LAYER_H

#include <string>

class Layer {
    public:

        Layer(const std::string &map_name, const std::string layer_name) : 
            map_name(map_name),
            layer_name(layer_name)
        {}

        virtual void update() = 0;
        virtual void render() = 0;

        inline std::string getLayerName() {return layer_name;}
    
    protected:
        std::string map_name, layer_name;
};

#endif // LAYER_H