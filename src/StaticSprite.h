//
// Created by Ivan Kishchenko on 25.09.2021.
//

#pragma once

#include "Drawable.h"
#include "Texture.h"

class StaticSprite : public Drawable {
    Texture::Ptr _refTexture;
    SDL_Rect _frame;
public:
    StaticSprite(Texture::Ptr refTexture, SDL_Rect frame);

    void draw(GameContext &ctx, SDL_Rect rect) override;
};
