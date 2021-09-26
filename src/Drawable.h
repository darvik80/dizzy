//
// Created by Ivan Kishchenko on 25.09.2021.
//

#pragma once

#include "GameContext.h"

class Drawable {
public:
    virtual void update(GameContext& context) { };
    virtual void draw(GameContext& context, SDL_Rect rect) = 0;
};

