//
// Created by Ivan Kishchenko on 08.08.2021.
//

#ifndef DIZZY_GAME_H
#define DIZZY_GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 480

class Game {
    SDL_Window* _window{};
    SDL_Renderer* _renderer{};
public:
    bool create(int argc, char *argv[]);

    int run();

    void destroy();

    virtual ~Game();
};


#endif //DIZZY_GAME_H
