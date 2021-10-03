//
// Created by Ivan Kishchenko on 26.09.2021.
//

#pragma once

#include <SDL2/SDL.h>
#include <system_error>
#include "Order.h"
#include "GameObjectAttributes.h"
#include <list>

class GameContext;

class GameObject : public Ordered {
public:
    int order() override {
        return 0;
    }

    virtual std::error_code load(GameContext &ctx, std::string_view path) = 0;

    virtual void update(GameContext &ctx) = 0;

    virtual std::list<GameObjectAttributes> collision(GameContext &ctx, SDL_Rect rect) { return {}; };

    virtual void draw(GameContext &ctx) = 0;
};
