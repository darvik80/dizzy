//
// Created by Ivan Kishchenko on 13.08.2021.
//

#include "Tile.h"

#include <utility>

Tile::Tile(TileInfo frame, GameObjectAttributes& attr) : _attr(attr) {
    _frames.push_back(frame);
}

Tile::Tile(std::vector<TileInfo>& frames, uint32_t delay, GameObjectAttributes& attr)
: _frames(std::move(frames)), _delay(delay), _attr(attr) {
}
