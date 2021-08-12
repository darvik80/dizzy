//
// Created by Ivan Kishchenko on 08.08.2021.
//

#include "Application.h"
#include "Player.h"

bool Application::create(int argc, char *argv[]) {
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "Couldn't initialize SDL: %s\n", SDL_GetError());
        return false;
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_SYSTEM, "SDL Init success");

    _window = SDL_CreateWindow("Dizzy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (_window == nullptr) {
        SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "Couldn't create SDL Window: %s\n", SDL_GetError());
        destroy();
        return false;
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_SYSTEM, "SDL Window created");

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

    if (!_renderer) {
        SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "Failed to create renderer: %s", SDL_GetError());
        destroy();
        return false;
    }

    SDL_LogInfo(SDL_LOG_CATEGORY_SYSTEM, "SDL Renderer created");

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "Couldn't initialize SDL_Image: %s", SDL_GetError());
        destroy();
        return false;
    }

    return true;
}

int Application::run() {
    Player player(_renderer, PS_STAY);


    PlayerControlContent playerControlContent{false, false, false};
    while (true) {
        SDL_SetRenderDrawColor(_renderer, 0x51, 0xa2, 0xf3, 255);
        SDL_RenderClear(_renderer);

        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exit(0);
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                        case SDLK_z:
                            playerControlContent.moveLeft = false;
                            break;
                        case SDLK_RIGHT:
                        case SDLK_x:
                            playerControlContent.moveRight = false;
                            break;
                        case SDLK_SPACE:
                            playerControlContent.jump = false;
                            break;
                    }
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                        case SDLK_z:
                            playerControlContent.moveLeft = true;
                            break;
                        case SDLK_RIGHT:
                        case SDLK_x:
                            playerControlContent.moveRight = true;
                            break;
                        case SDLK_SPACE:
                            playerControlContent.jump = true;
                            break;
                    }
                    break;

                default:
                    break;
            }
        }

        player.handle(playerControlContent);
        player.update();
        player.render(_renderer);

        SDL_RenderPresent(_renderer);
        SDL_Delay(16);
    }
}

void Application::destroy() {
    if (_renderer) {
        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
    }

    if (_window) {
        SDL_DestroyWindow(_window);
    }
    IMG_Quit();

    SDL_Quit();
}

Application::~Application() {
    destroy();
}
