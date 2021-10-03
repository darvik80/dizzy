//
// Created by Ivan Kishchenko on 13.08.2021.
//

#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "GameObjectAttributes.h"

struct TileInfo {
    SDL_Rect frame;
    SDL_Rect collision;
};

class Tile {

    std::vector<TileInfo> _frames;
    int _curFrame{0};
    uint32_t _delay{0};

    GameObjectAttributes _attr;
public:
    explicit Tile(TileInfo frame, GameObjectAttributes& attr);
    Tile(std::vector<TileInfo>& frames, uint32_t _delay, GameObjectAttributes& attr);

    const TileInfo& getTileInfo() {
        if (_delay) {
            _curFrame = (int)(SDL_GetTicks() / _delay % _frames.size());
        }

        return _frames[_curFrame];
    }

    [[nodiscard]] const GameObjectAttributes &getAttr() const {
        return _attr;
    }
};
