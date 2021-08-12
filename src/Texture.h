//
// Created by Ivan Kishchenko on 10.08.2021.
//

#ifndef DIZZY_TEXTURE_H
#define DIZZY_TEXTURE_H

#include <string_view>
#include <SDL2/SDL_image.h>

class Texture {
    SDL_Texture* _texture{};
public:
    typedef std::shared_ptr<Texture> Ptr;
public:
    explicit Texture(SDL_Renderer* renderer, std::string_view path);
    void render(SDL_Renderer* renderer, int x, int y, const SDL_Rect& rect);
    ~Texture();
};


#endif //DIZZY_TEXTURE_H
