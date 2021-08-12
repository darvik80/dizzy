//
// Created by Ivan Kishchenko on 10.08.2021.
//

#ifndef DIZZY_HELPER_H
#define DIZZY_HELPER_H

#include <SDL2/SDL.h>

class Helper {
public:
    static bool hasCollision(SDL_Rect& first, SDL_Rect& second);
};


#endif //DIZZY_HELPER_H
