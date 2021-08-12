//
// Created by Ivan Kishchenko on 10.08.2021.
//

#ifndef DIZZY_SPRITE_H
#define DIZZY_SPRITE_H

#include <SDL2/SDL.h>

class Sprite {
public:
    virtual void update() = 0;
    virtual void render(SDL_Renderer* renderer, int x, int y) = 0;
};


#endif //DIZZY_SPRITE_H
