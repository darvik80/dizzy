//
// Created by Ivan Kishchenko on 13.08.2021.
//

#ifndef DIZZY_TILE_H
#define DIZZY_TILE_H

#include <SDL2/SDL.h>
#include <vector>

class Tile {
    std::vector<SDL_Rect> _frames;
    int _curFrame{0};
    uint32_t _delay{0};
public:
    explicit Tile(const SDL_Rect &rect);
    Tile(std::vector<SDL_Rect>& frames, uint32_t _delay);

    const SDL_Rect& getRect() {
        if (_delay) {
            _curFrame = (int)(SDL_GetTicks() / _delay % _frames.size());
        }

        return _frames[_curFrame];
    }
};


#endif //DIZZY_TILE_H
