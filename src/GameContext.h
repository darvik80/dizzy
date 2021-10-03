//
// Created by Ivan Kishchenko on 26.09.2021.
//

#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include "GameObject.h"

class GameContext;

class AnimationStrategy {
public:
    virtual size_t nextFrame(GameContext &ctx, uint64_t delay, size_t size) = 0;
};

class AnimationStrategyRepeat : public AnimationStrategy {
public:
    size_t nextFrame(GameContext &ctx, uint64_t delay, size_t size) override;
};

class AnimationStrategySingle : public AnimationStrategy {
    uint64_t millis{0};
    size_t _nextFrame{UINT64_MAX};
public:
    size_t nextFrame(GameContext &ctx, uint64_t delay, size_t size) override;
};

struct Control {
    bool moveLeft = false;
    bool moveRight = false;
    bool jump = false;
    bool enter = false;
    bool die = false;
};

struct GameContext {
    SDL_Renderer* renderer{};
    uint32_t millis{};
    Control control;
    AnimationStrategyRepeat strategyRepeat;
    AnimationStrategySingle strategySingle;
    std::vector<std::shared_ptr<GameObject>> objects;
};
