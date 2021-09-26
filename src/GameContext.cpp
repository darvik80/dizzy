//
// Created by Ivan Kishchenko on 26.09.2021.
//

#include "GameContext.h"
#include <iostream>

size_t AnimationStrategyRepeat::nextFrame(GameContext &ctx, uint64_t delay, size_t size) {
    return ctx.millis / delay % size;
}

size_t AnimationStrategySingle::nextFrame(GameContext &ctx, uint64_t delay, size_t size) {
    if (_nextFrame == UINT64_MAX) {
        millis = ctx.millis;
        _nextFrame = 0;
    }

    _nextFrame = (ctx.millis - millis) / delay;
    if (_nextFrame >= size) {
        _nextFrame = size - 1;
    }

    return _nextFrame;
}
