//
// Created by Ivan Kishchenko on 26.09.2021.
//

#include "AnimationSprite.h"

AnimationSprite::AnimationSprite(Texture::Ptr refTexture, std::vector<SDL_Rect>& frames, uint64_t delay)
        : _refTexture(std::move(refTexture)), _frames(frames), _curFrame(0), _delay(delay) {

}

void AnimationSprite::draw(GameContext &ctx, SDL_Rect rect) {
    _refTexture->draw(ctx, _frames[_curFrame], rect);
}

