//
// Created by Ivan Kishchenko on 12.08.2021.
//

#ifndef DIZZY_ANIMATIONSPRITE_H
#define DIZZY_ANIMATIONSPRITE_H

#include "Sprite.h"
#include "Texture.h"
#include <vector>

class AnimationSprite : public Sprite {
    Texture::Ptr _refTexture;
    std::vector<SDL_Rect> _frames;
    int _delay;
    uint32_t _curFrame{0};
public:
    AnimationSprite(Texture::Ptr texture, std::vector<SDL_Rect>& frames, int delay);

    void update() override;

    void render(SDL_Renderer *renderer, int x, int y) override;

    uint32_t getCurFrame() {
        return _curFrame;
    }

    uint32_t getFrameCount() {
        return _frames.size();
    }
};


#endif //DIZZY_ANIMATIONSPRITE_H
