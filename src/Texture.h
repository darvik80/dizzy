//
// Created by Ivan Kishchenko on 25.09.2021.
//

#pragma once

#include <system_error>
#include <string_view>

#include "GameContext.h"

class Texture {
    SDL_Texture* _texture{};
    int _width{};
    int _height{};
public:
    typedef std::shared_ptr<Texture> Ptr;
public:

    std::error_code load(GameContext& ctx, std::string_view path, SDL_Color color);

    void draw(GameContext& ctx, SDL_Rect src, SDL_Rect dst);

    [[nodiscard]] int getWidth() const {
        return _width;
    }
    [[nodiscard]] int getHeight() const {
        return _height;
    }

    ~Texture();
};
