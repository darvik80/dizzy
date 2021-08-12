//
// Created by Ivan Kishchenko on 08.08.2021.
//

#ifndef DIZZY_APPLICATION_H
#define DIZZY_APPLICATION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Application {
    SDL_Window* _window{};
    SDL_Renderer* _renderer{};
public:
    bool create(int argc, char *argv[]);

    int run();

    void destroy();

    virtual ~Application();
};


#endif //DIZZY_APPLICATION_H
