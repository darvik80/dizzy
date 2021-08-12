//
// Created by Ivan Kishchenko on 10.08.2021.
//

#include "Texture.h"


Texture::Texture(SDL_Renderer* renderer, std::string_view path) {
    //Load image at specified path
    SDL_Surface *surface = IMG_Load(path.data());
    if (!surface) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Unable to load image %s! SDL_image Error: %s", path.data(), SDL_GetError());
    } else {
        _texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!_texture) {
            SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Unable to create texture from %s! SDL Error: %s", path.data(), SDL_GetError());
        }

        SDL_FreeSurface(surface);
    }
}

void Texture::render(SDL_Renderer *renderer, int x, int y, const SDL_Rect& src) {
    SDL_Rect dst{x, y, src.w, src.h};
    if (SDL_RenderCopy(renderer, _texture, &src, &dst)) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Unable to render image, %s", SDL_GetError());
    }
}

Texture::~Texture() {
    //SDL_Fre(_texture);
}

