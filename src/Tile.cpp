//
// Created by Ivan Kishchenko on 13.08.2021.
//

#include "Tile.h"

#include <utility>

Tile::Tile(const SDL_Rect &rect) {
    _frames.push_back(rect);
}

Tile::Tile(std::vector<SDL_Rect>& frames, uint32_t delay) : _frames(std::move(frames)), _delay(delay) {
}