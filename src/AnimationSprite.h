//
// Created by Ivan Kishchenko on 26.09.2021.
//

#pragma once

#include "Drawable.h"
#include "Texture.h"
#include <vector>

class AnimationSprite: public Drawable {
    Texture::Ptr _refTexture;
protected:
    std::vector<SDL_Rect> _frames;
    uint64_t _delay;
    size_t _curFrame;
public:
    AnimationSprite(Texture::Ptr refTexture, std::vector<SDL_Rect>& frames, uint64_t delay);

    size_t frames() {
        return _frames.size();
    }

    void draw(GameContext &ctx, SDL_Rect rect) override;
};

class RepeatableAnimationSprite: public AnimationSprite {
public:
    RepeatableAnimationSprite(const Texture::Ptr &refTexture, std::vector<SDL_Rect> &frames, uint64_t delay)
            : AnimationSprite(refTexture, frames, delay) {}

    void update(GameContext& ctx) override{
        _curFrame = ctx.strategyRepeat.nextFrame(ctx, _delay, _frames.size());
    }
};

class SingleAnimationSprite: public AnimationSprite {
public:
    SingleAnimationSprite(const Texture::Ptr &refTexture, std::vector<SDL_Rect> &frames, uint64_t delay)
            : AnimationSprite(refTexture, frames, delay) {}

    void update(GameContext& ctx) override{
        _curFrame = ctx.strategySingle.nextFrame(ctx, _delay, _frames.size());
    }
};
