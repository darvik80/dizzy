//
// Created by Ivan Kishchenko on 26.09.2021.
//

#pragma once

#include <SDL2/SDL.h>

class Game {
    SDL_Window* _window{};
    SDL_Renderer* _renderer{};
public:
    bool create();

    int run();

    void destroy();

    virtual ~Game();
};
