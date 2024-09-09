#pragma once
#ifndef IMAGESET_H
#define IMAGESET_H

#include <string>
struct DstRect;

class Imageset {
    public:

        Imageset(int firstGID, int count) : firstGID(firstGID), count(count) {}

        virtual void draw(int gid, const DstRect* dst_rect) = 0;
        virtual bool load() = 0;

        inline int getFirstGID() {return firstGID;}
        inline int getCount() {return count;}
    
    protected:
        int firstGID, count;
};

#endif // IMAGESET_H