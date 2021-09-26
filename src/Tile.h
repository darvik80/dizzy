//
// Created by Ivan Kishchenko on 13.08.2021.
//

#pragma once

#include <SDL2/SDL.h>
#include <vector>

class Tile {
    std::vector<SDL_Rect> _frames;
    std::vector<SDL_Rect> _collisions;
    int _curFrame{0};
    uint32_t _delay{0};
public:
    explicit Tile(SDL_Rect rect, std::vector<SDL_Rect>& collisions);
    Tile(std::vector<SDL_Rect>& frames, uint32_t _delay, std::vector<SDL_Rect>& collisions);

    const SDL_Rect& getRect() {
        if (_delay) {
            _curFrame = (int)(SDL_GetTicks() / _delay % _frames.size());
        }

        return _frames[_curFrame];
    }

    [[nodiscard]] const std::vector<SDL_Rect> &getCollisions() const {
        return _collisions;
    }
};
