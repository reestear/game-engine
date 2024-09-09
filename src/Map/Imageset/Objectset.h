#pragma once
#ifndef OBJECTSET_H
#define OBJECTSET_H

#include "Imageset.h"
#include <string>
#include <vector>

struct Object {

    Object(int width, int height, const std::string &object_src) :
        width(width),
        height(height),
        object_src(object_src)
    {}

    int width, height;
    std::string object_src;
};

class Objectset : public Imageset {
    public:

        Objectset(int firstGID, int object_count, const std::string &name, const std::string &objectset_src, const std::vector<Object> &objects) :
            Imageset(firstGID, object_count),
            name(name),
            objectset_src(objectset_src),
            objects(objects)
        {}
        
        virtual void draw(int gid, const DstRect* dst_rect) override;
        virtual bool load() override;

        const std::string getObjectsetDir() const {
            std::string objectset_dir = objectset_src;
            objectset_dir.erase(objectset_dir.find_last_of("/"));
            return objectset_dir;
        }

    public:
        std::string name, objectset_src;
        std::vector<Object> objects;

};

#endif // OBJECTSET_H