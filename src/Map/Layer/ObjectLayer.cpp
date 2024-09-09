#include "ObjectLayer.h"
#include "MapManager.h"
#include "TextureManager.h"
#include "Camera.h"

ObjectLayer::ObjectLayer(const std::string &map_name, const std::string &layer_name, const std::vector<ObjectLayerItem> &object_layer_items) :
    Layer(map_name, layer_name),
    object_layer_items(object_layer_items)
{}

void ObjectLayer::update() {
    // Update object layer
}

namespace {
    void renderBackgroundHelper(const std::vector<ObjectLayerItem> &object_layer_items, const std::string &map_name) {
        for(std::vector<ObjectLayerItem>::const_iterator it = object_layer_items.begin(); it != object_layer_items.end(); ++it) {
            // Render backgrond object
            std::vector<Imageset*> imagesets = MapManager::getInstance()->getGameMap(map_name)->getImagesets();
            for(std::vector<Imageset*>::iterator imageset_it = imagesets.begin(); imageset_it != imagesets.end(); ++imageset_it) {
                if((*imageset_it)->getFirstGID() <= it->gid && it->gid < (*imageset_it)->getFirstGID() + (*imageset_it)->getCount()) {                    
                    Camera *camera = Camera::getInstance();
                    
                    int dx = static_cast<int>(camera->getViewport().position.getX() * it->depth);
                    int dy = static_cast<int>(camera->getViewport().position.getY() * it->depth);
                    DstRect dst_rect(it->x - dx, it->y - it->height - dy, it->width, it->height);

                    (*imageset_it)->draw(it->gid, &dst_rect);
                    break;
                }
            }
        }
    }

    void renderObjectHelper(const std::vector<ObjectLayerItem> &object_layer_items, const std::string &map_name) {
        for(std::vector<ObjectLayerItem>::const_iterator it = object_layer_items.begin(); it != object_layer_items.end(); ++it) {
            // Render backgrond object
            std::vector<Imageset*> imagesets = MapManager::getInstance()->getGameMap(map_name)->getImagesets();
            for(std::vector<Imageset*>::iterator imageset_it = imagesets.begin(); imageset_it != imagesets.end(); ++imageset_it) {
                if((*imageset_it)->getFirstGID() <= it->gid && it->gid < (*imageset_it)->getFirstGID() + (*imageset_it)->getCount()) {
                    Camera *camera = Camera::getInstance();
                    int dx = camera->getViewport().position.getX();
                    int dy = camera->getViewport().position.getY();
                    DstRect dst_rect(it->x - dx, it->y - it->height - dy, it->width, it->height);

                    (*imageset_it)->draw(it->gid, &dst_rect);
                    break;
                }
            }
        }
    }
}

void ObjectLayer::render() {
    if(layer_name == "Background") {
        renderBackgroundHelper(object_layer_items, map_name);
    } else {
        renderObjectHelper(object_layer_items, map_name);
    }
}
