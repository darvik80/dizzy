//
// Created by Ivan Kishchenko on 13.08.2021.
//

#ifndef DIZZY_GAMEMAP_H
#define DIZZY_GAMEMAP_H

#include <SDL2/SDL.h>
#include <vector>
#include "TileSet.h"

class GameMap {
    std::unique_ptr<TileSet> _tileSet;
    std::vector<std::vector<int>> _map;
public:
    explicit GameMap(SDL_Renderer* renderer, std::string_view path);

    void render(SDL_Renderer* renderer);
};


#endif //DIZZY_GAMEMAP_H
