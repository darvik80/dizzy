//
// Created by Ivan Kishchenko on 13.08.2021.
//

#ifndef DIZZY_TILESET_H
#define DIZZY_TILESET_H

#include "Texture.h"
#include "Tile.h"
#include <vector>
#include <tileson/tileson.hpp>

class TileSet {
    Texture::Ptr _texture;
    std::vector<Tile> _tiles;
public:
    TileSet(SDL_Renderer* renderer, int width, int height, int border);
    TileSet(SDL_Renderer* renderer, tson::Tileset* tileset);

    int getSize() {
        return _tiles.size();
    }

    int getTileWidth() {
        return _tiles[0].getRect().w;
    }

    int getTileHeight() {
        return _tiles[0].getRect().h;
    }

    void render(SDL_Renderer* renderer, int tileId, int x, int y);
};


#endif //DIZZY_TILESET_H
