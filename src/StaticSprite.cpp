//
// Created by Ivan Kishchenko on 25.09.2021.
//

#include "StaticSprite.h"

#include <utility>

StaticSprite::StaticSprite(Texture::Ptr refTexture, SDL_Rect frame)
        : _refTexture(std::move(refTexture)), _frame(frame) {

}

void StaticSprite::draw(GameContext &ctx, SDL_Rect rect) {
    _refTexture->draw(ctx, _frame, rect);
}
