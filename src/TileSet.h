//
// Created by Ivan Kishchenko on 13.08.2021.
//

#pragma once

#include "Texture.h"
#include "Tile.h"
#include <vector>
#include <tileson/tileson.hpp>

class TileSet {
    Texture::Ptr _texture;
    std::vector<Tile> _tiles;
public:
    TileSet(GameContext& ctx, tson::Tileset* tileset);

    size_t getSize() {
        return _tiles.size();
    }

    int getTileWidth() {
        return _tiles[0].getTileInfo().frame.w;
    }

    int getTileHeight() {
        return _tiles[0].getTileInfo().frame.h;
    }

    const Tile& getTile(size_t tileId) {
        return _tiles[tileId];
    }


    bool collision(GameContext& ctx, SDL_Rect obj, int tileId, int x, int y);

    void draw(GameContext& ctx, size_t tileId, int x, int y);
};
