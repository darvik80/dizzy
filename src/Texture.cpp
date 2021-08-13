//
// Created by Ivan Kishchenko on 10.08.2021.
//

#include "Texture.h"


Texture::Texture(SDL_Renderer *renderer, std::string_view path) {
    //Load image at specified path
    SDL_Surface *surface = IMG_Load(path.data());
    if (!surface) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Unable to load image %s! SDL_image Error: %s", path.data(), SDL_GetError());
    } else {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0x51, 0xa2, 0xf3));
        _texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!_texture) {
            SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Unable to create texture from %s! SDL Error: %s", path.data(), SDL_GetError());
        } else if (SDL_QueryTexture(_texture, nullptr, nullptr, &_width, &_height)) {
            SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "\"Failed to record metadata for a newly loaded image file %s! SDL Error: %s", path.data(), SDL_GetError());
        }

        SDL_FreeSurface(surface);
    }
}

void Texture::render(SDL_Renderer *renderer, int x, int y, const SDL_Rect &src) {
    SDL_Rect dst{x, y, src.w, src.h};
    if (SDL_RenderCopy(renderer, _texture, &src, &dst)) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Unable to render image, %s", SDL_GetError());
    }
}

Texture::~Texture() {
    SDL_DestroyTexture(_texture);
}

