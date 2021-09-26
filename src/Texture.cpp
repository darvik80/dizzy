//
// Created by Ivan Kishchenko on 25.09.2021.
//

#include "Texture.h"
#include <SDL2/SDL_image.h>

std::error_code Texture::load(GameContext& ctx, std::string_view path, SDL_Color color) {
    SDL_Surface *surface = IMG_Load(path.data());
    if (!surface) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Unable to load image %s! SDL_image Error: %s", path.data(), SDL_GetError());
        return std::make_error_code(std::errc::invalid_argument);
    } else {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, color.r, color.g, color.b));
        _texture = SDL_CreateTextureFromSurface(ctx.renderer, surface);
        if (!_texture) {
            SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Unable to create texture from %s! SDL Error: %s", path.data(), SDL_GetError());
            return std::make_error_code(std::errc::invalid_argument);
        } else if (SDL_QueryTexture(_texture, nullptr, nullptr, &_width, &_height)) {
            SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "\"Failed to record metadata for a newly loaded image file %s! SDL Error: %s", path.data(), SDL_GetError());
            return std::make_error_code(std::errc::invalid_argument);
        }

        SDL_FreeSurface(surface);

        return {};
    }
}

void Texture::draw(GameContext& ctx, SDL_Rect src, SDL_Rect dst) {
    if (SDL_RenderCopy(ctx.renderer, _texture, &src, &dst)) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Unable to render image, %s", SDL_GetError());
    }
}

Texture::~Texture() {
    SDL_DestroyTexture(_texture);
}
