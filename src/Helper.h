//
// Created by Ivan Kishchenko on 10.08.2021.
//

#pragma once

#include <SDL2/SDL.h>

class Helper {
public:
    static bool hasCollision(SDL_Rect& first, SDL_Rect& second);
};
