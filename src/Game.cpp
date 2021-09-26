//
// Created by Ivan Kishchenko on 26.09.2021.
//

#include "Game.h"
#include "GameContext.h"
#include "Player.h"
#include "GameMap.h"

#include <queue>
#include <memory>

#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 480

bool Game::create() {
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "Couldn't initialize SDL: %s", SDL_GetError());
        return false;
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_SYSTEM, "SDL Init success");

    _window = SDL_CreateWindow("Dizzy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (_window == nullptr) {
        SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "Couldn't create SDL Window: %s", SDL_GetError());
        destroy();
        return false;
    }


    SDL_LogInfo(SDL_LOG_CATEGORY_SYSTEM, "SDL Window created");

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

    if (!_renderer) {
        SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "Failed to create renderer: %s", SDL_GetError());
        destroy();
        return false;
    }

    SDL_RenderSetLogicalSize(_renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

    SDL_LogInfo(SDL_LOG_CATEGORY_SYSTEM, "SDL Renderer created");

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "Couldn't initialize SDL_Image: %s", SDL_GetError());
        destroy();
        return false;
    }

    return true;
}

int Game::run() {
    GameContext ctx{_renderer};

    ctx.objects.emplace_back(std::make_shared<GameMap>())->load(ctx, "assets/dizzy_map.json");
    ctx.objects.emplace_back(std::make_shared<Player>())->load(ctx, "assets/images/dizzy.png");
    std::sort(ctx.objects.begin(), ctx.objects.end(), OrderedLess<GameObject>());

    uint32_t MS_PER_UPDATE = 1000 / 60, lastTime = SDL_GetTicks(), lag = 0;
    while (true) {
        uint32_t now = SDL_GetTicks();
        lag += (now - lastTime);
        lastTime = now;

        SDL_SetRenderDrawColor(_renderer, 0x51, 0xa2, 0xf3, 255);
        SDL_RenderClear(_renderer);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return 0;
            }
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                case SDLK_z:
                    ctx.control.moveLeft = event.type == SDL_KEYDOWN;
                    break;
                case SDLK_RIGHT:
                case SDLK_x:
                    ctx.control.moveRight = event.type == SDL_KEYDOWN;;
                    break;
                case SDLK_SPACE:
                    ctx.control.jump = event.type == SDL_KEYDOWN;;
                    break;
                case SDLK_RETURN:
                    ctx.control.enter = event.type == SDL_KEYDOWN;;
                    break;
                case SDLK_d:
                    ctx.control.die = event.type == SDL_KEYDOWN;;
                    break;
            }
            break;

        }

        ctx.millis = SDL_GetTicks();
        while (lag >= MS_PER_UPDATE) {
            for (auto& obj : ctx.objects) {
                obj->update(ctx);
            }
            lag -= MS_PER_UPDATE;
            ctx.millis = SDL_GetTicks();
        }
        for (auto& obj : ctx.objects) {
            obj->draw(ctx);
        }

        //gameMap.render(_renderer);
        //player.render(_renderer);
        SDL_RenderPresent(_renderer);

        long delta = (long) MS_PER_UPDATE - (long) (SDL_GetTicks() - now);
        if (delta > 0) {
            SDL_Delay(delta);
        } else {
            SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "Skip frame!");
        }
    }
}

void Game::destroy() {
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

Game::~Game() {
    destroy();
}
