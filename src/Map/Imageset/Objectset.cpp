#include "Objectset.h"
#include "TextureManager.h"

void Objectset::draw(int gid, const DstRect* dst_rect) {
    
    int object_id = gid - firstGID;
    if(object_id < 0 || object_id >= count) {
        return;
    }

    const Object &object = objects[object_id];
    const std::string object_texture_id = name + std::to_string(object_id);

    SrcRect src_rect(0, 0, object.width, object.height);

    TextureManager::getInstance()->draw(object_texture_id, &src_rect, dst_rect);
}

bool Objectset::load() {
    int object_id = 0;
    for(const auto &object : objects) {
        if(!TextureManager::getInstance()->load(name + std::to_string(object_id++), getObjectsetDir() + "/" + object.object_src)) {
            std::cerr << "Failed to load object " << object.object_src << std::endl;
            return false;
        }
    }
    
    std::cout << "Objectset " << objectset_src << " loaded successfully" << std::endl;
    return true;
}