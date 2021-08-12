//
// Created by Ivan Kishchenko on 12.08.2021.
//

#include "AnimationSprite.h"

#include <utility>

AnimationSprite::AnimationSprite(Texture::Ptr texture, std::vector<SDL_Rect>& frames, int delay)
: _refTexture(std::move(texture)), _frames(std::move(frames)), _delay(delay) {}

void AnimationSprite::update() {
    _curFrame = SDL_GetTicks() / _delay % _frames.size();
}

void AnimationSprite::render(SDL_Renderer *renderer, int x, int y) {
    _refTexture->render(renderer, x, y, _frames[_curFrame]);
}

