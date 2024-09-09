#include "MapManager.h"
#include "Tileset.h"
#include "Objectset.h"
#include "TileLayer.h"
#include "ObjectLayer.h"
#include "CollisionManager.h"
#include "StaticCollider.h"

#include <sstream>
#include <iostream>

#define ERROR false
#define OK true

MapManager* MapManager::instance = nullptr;

bool MapManager::load() {

    const std::string map_src = "../../assets/Maps/Level-1/longx600map.tmx";
    // const std::string map_src = "../../assets/Maps/legacy-fantasy/map/level-1-map.tmx";

    if(!parseMap("map1", map_src)) {
        std::cerr << "Error loading map from parseMap()" << std::endl;
        return ERROR;
    }

    std::vector<Imageset*> game_imagesets = getGameMap("map1")->getImagesets();
    for(std::vector<Imageset*>::iterator it = game_imagesets.begin(); it != game_imagesets.end(); ++it) {
        if(!(*it)->load()) {
            std::cerr << "Error loading imageset from load()" << std::endl;
            return ERROR;
        }
    }

    return OK;
}

void MapManager::clean() {
    for (auto& map : dict_game_maps) {
        delete map.second;
    }
    dict_game_maps.clear();
}

bool MapManager::parseMap(const std::string &map_name, const std::string &map_src) {

    tinyxml2::XMLDocument xml;
    xml.LoadFile(map_src.c_str());

    if(xml.ErrorID() != 0) {
        std::cerr << "Error loading " << map_src << std::endl;
        return ERROR;
    }

    tinyxml2::XMLElement* xml_map = xml.FirstChildElement("map");

    int tile_width = xml_map->IntAttribute("tilewidth");
    int tile_height = xml_map->IntAttribute("tileheight");
    int row_count = xml_map->IntAttribute("height");
    int column_count = xml_map->IntAttribute("width");

    GameMap *game_map = new GameMap(map_name, map_src, tile_width, tile_height, row_count, column_count);
    addGameMap(map_name, game_map);

    for(tinyxml2::XMLElement* xml_obj = xml_map->FirstChildElement(); xml_obj != nullptr; xml_obj = xml_obj->NextSiblingElement()) {
        if(strcmp(xml_obj->Name(), "tileset") == 0) {
            if(!parseImageset(xml_obj, map_name)) {
                std::cerr << "Error parsing imageset" << std::endl;
                return ERROR;
            }
        } else if(strcmp(xml_obj->Name(), "layer") == 0 || strcmp(xml_obj->Name(), "objectgroup") == 0) {
            if(!parseLayer(xml_obj, map_name)) {
                std::cerr << "Error parsing layer" << std::endl;
                return ERROR;
            }
        }
    }

    return OK;
}

namespace {

    Tileset* parseTilesetHelper(tinyxml2::XMLElement* xml_tileset, const std::string &map_name) {
        Tileset *tileset = new Tileset(
            xml_tileset->IntAttribute("firstgid"),
            xml_tileset->IntAttribute("tilecount"),
            xml_tileset->IntAttribute("columns"),
            xml_tileset->IntAttribute("tilewidth"),
            xml_tileset->IntAttribute("tileheight"),
            xml_tileset->Attribute("name"),
            MapManager::getInstance()->getGameMap(map_name)->getMapDir() + "/" + xml_tileset->FirstChildElement("image")->Attribute("source")
        );

        return tileset;
    }

    Objectset* parseObjectsetHelper(tinyxml2::XMLElement* xml_objectset, const std::string &rel_tileset_src, const std::string &map_name) {
        int firstGID = xml_objectset->IntAttribute("firstgid");
        std::string tileset_src = MapManager::getInstance()->getGameMap(map_name)->getMapDir() + "/" + rel_tileset_src;

        tinyxml2::XMLDocument xml;
        xml.LoadFile(tileset_src.c_str());
        
        if(xml.ErrorID() != 0) {
            std::cerr << "Error loading " << tileset_src << std::endl;
            return nullptr;
        }

        tinyxml2::XMLElement* xml_tileset = xml.FirstChildElement("tileset");

        if(!xml_tileset) {
            std::cerr << "Error parsing: Didn't find <tileset> " << tileset_src << std::endl;
            return nullptr;
        }

        std::vector<Object> objects;
        
        for(tinyxml2::XMLElement* xml_tile = xml_tileset->FirstChildElement("tile"); xml_tile != nullptr; xml_tile = xml_tile->NextSiblingElement("tile")) {
            tinyxml2::XMLElement* xml_object = xml_tile->FirstChildElement("image");

            if(!xml_object) {
                std::cerr << "Error parsing: Didn't find <image> " << tileset_src << std::endl;
                return nullptr;
            }

            Object object(
                xml_object->IntAttribute("width"),
                xml_object->IntAttribute("height"),
                xml_object->Attribute("source")
            );

            objects.push_back(object);
        }

        Objectset *objectset = new Objectset(
            firstGID,
            objects.size(),
            xml_tileset->Attribute("name"),
            tileset_src,
            objects
        );

        return objectset;
    }
}

bool MapManager::parseImageset(tinyxml2::XMLElement* xml_tileset, const std::string &map_name) {
    const tinyxml2::XMLAttribute *source_attr = xml_tileset->FindAttribute("source");

    Imageset *imageset = nullptr;

    if(source_attr == nullptr) {
        imageset = parseTilesetHelper(xml_tileset, map_name);
    } else {
        std::string rel_tileset_src = source_attr->Value();
        imageset = parseObjectsetHelper(xml_tileset, rel_tileset_src, map_name);
    }

    if(!imageset) {
        std::cerr << "Error parsing imageset" << std::endl;
        return ERROR;
    }

    getGameMap(map_name)->addImageset(imageset);

    return OK;
}

namespace {
    
        TileLayer* parseTileLayerHelper(tinyxml2::XMLElement* xml_layer, const std::string &map_name, int tile_width, int tile_height) {

            const std::string layer_name = xml_layer->Attribute("name");
            const int layer_width = xml_layer->IntAttribute("width");
            const int layer_height = xml_layer->IntAttribute("height");
    
            tinyxml2::XMLElement* xml_data = xml_layer->FirstChildElement("data");
    
            if(!xml_data) {
                std::cerr << "Error parsing: Didn't find <data> " << map_name << std::endl;
                return nullptr;
            }

            LayerGrid layer_grid(layer_height, std::vector<int>(layer_width, 0));
    
            std::string data = xml_data->GetText();
            std::istringstream sin(data);
            std::string tile_gid;

            for(int row = 0; row < layer_height; ++row) {
                for(int column = 0; column < layer_width; ++column) {
                    getline(sin, tile_gid, ',');
                    std::stringstream convertor(tile_gid);

                    convertor >> layer_grid[row][column];

                    if(convertor.fail()) {
                        std::cerr << "Error parsing: Couldn't convert " << tile_gid << " to integer" << std::endl;
                        return nullptr;
                    }

                    if(!sin.good()) {
                        break;
                    }
                }
            }

            return new TileLayer(
                map_name,
                layer_name,
                tile_width,
                tile_height,
                layer_height,
                layer_width,
                layer_grid
            );
        }
    
        ObjectLayer* parseObjectLayerHelper(tinyxml2::XMLElement* xml_layer, const std::string &map_name) {
            const std::string layer_name = xml_layer->Attribute("name");

            std::vector<ObjectLayerItem> object_layer_items;
    
            for(tinyxml2::XMLElement* xml_object = xml_layer->FirstChildElement("object"); xml_object != nullptr; xml_object = xml_object->NextSiblingElement("object")) {
                
                float depth = 1.f;

                tinyxml2::XMLElement *object_properties = xml_object->FirstChildElement("properties");
                if(object_properties != nullptr) {
                    tinyxml2::XMLElement *object_property = object_properties->FirstChildElement("property");
                    if(object_property != nullptr) {
                        if(strcmp(object_property->Attribute("name"), "Depth") == 0) {
                            depth = object_property->FloatAttribute("value");
                        }
                    }
                }

                ObjectLayerItem object_layer_item(
                    xml_object->IntAttribute("gid"),
                    xml_object->IntAttribute("x"),
                    xml_object->IntAttribute("y"),
                    xml_object->IntAttribute("width"),
                    xml_object->IntAttribute("height"),
                    depth
                );
    
                object_layer_items.push_back(object_layer_item);
            }
    
            return new ObjectLayer(
                map_name,
                layer_name,
                object_layer_items
            );
        }

        void parseCollisionLayerHelper(tinyxml2::XMLElement *xml_layer, const std::string &map_name) {
            for(tinyxml2::XMLElement *xml_object = xml_layer->FirstChildElement("object"); xml_object != nullptr; xml_object = xml_object->NextSiblingElement("object")) {
                int x = xml_object->IntAttribute("x");
                int y = xml_object->IntAttribute("y");
                int width = xml_object->IntAttribute("width");
                int height = xml_object->IntAttribute("height");

                CollisionManager::getInstance()->addCollider(new StaticCollider(x, y, width, height));
            }
        }
}

bool MapManager::parseLayer(tinyxml2::XMLElement* xml_layer, const std::string &map_name) {

    Layer *layer = nullptr;
    
    if(strcmp(xml_layer->Name(), "layer") == 0) {
        layer = parseTileLayerHelper(xml_layer, map_name, getGameMap(map_name)->getTileWidth(), getGameMap(map_name)->getTileHeight());
    } else if(strcmp(xml_layer->Name(), "objectgroup") == 0){
        if(strcmp(xml_layer->Attribute("name"), "Collision") == 0) {
            parseCollisionLayerHelper(xml_layer, map_name);
            return OK;
        }
        
        layer = parseObjectLayerHelper(xml_layer, map_name);
    }

    if(layer == nullptr) {
        std::cerr << "Error parsing layer" << std::endl;
        return ERROR;
    }

    getGameMap(map_name)->addLayer(layer);

    return OK;
}