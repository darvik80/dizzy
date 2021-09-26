//
// Created by Ivan Kishchenko on 13.08.2021.
//

#include "Tile.h"

#include <utility>

Tile::Tile(SDL_Rect rect, std::vector<SDL_Rect>& collisions) : _collisions(collisions) {
    _frames.push_back(rect);
}

Tile::Tile(std::vector<SDL_Rect>& frames, uint32_t delay, std::vector<SDL_Rect>& collisions) : _frames(std::move(frames)), _delay(delay), _collisions(collisions) {
}
