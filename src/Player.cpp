//
// Created by Ivan Kishchenko on 12.08.2021.
//

#include "Player.h"

Player::Player(SDL_Renderer *renderer, Player_State state) {
    _state = state;
    _texture = std::make_shared<Texture>(renderer, "assets/images/dizzy.png");

    // Stay
    auto tiles = std::vector(
            {
                    SDL_Rect{0, 0, 25, 22},
                    SDL_Rect{25, 0, 25, 22}
            }
    );
    _sprites.emplace_back(_texture, tiles, 150);

    // Jump
    tiles = std::vector(
            {
                    SDL_Rect{50, 0, 25, 22},
                    SDL_Rect{75, 0, 25, 22},
                    SDL_Rect{100, 0, 25, 22},
                    SDL_Rect{125, 0, 25, 22},
                    SDL_Rect{150, 0, 25, 22},
                    SDL_Rect{175, 0, 25, 22},
                    SDL_Rect{200, 0, 25, 22},
            }
    );
    _sprites.emplace_back(_texture, tiles, 100);

    // Left
    tiles = std::vector(
            {
                    SDL_Rect{225, 0, 25, 22},
                    SDL_Rect{250, 0, 25, 22},
                    SDL_Rect{275, 0, 25, 22},
                    SDL_Rect{300, 0, 25, 22},
                    SDL_Rect{325, 0, 25, 22},
                    SDL_Rect{350, 0, 25, 22},
                    SDL_Rect{375, 0, 25, 22},
                    SDL_Rect{400, 0, 25, 22},
            }
    );
    _sprites.emplace_back(_texture, tiles, 150);

    // Right
    tiles = std::vector(
            {
                    SDL_Rect{425, 0, 25, 22},
                    SDL_Rect{450, 0, 25, 22},
                    SDL_Rect{475, 0, 25, 22},
                    SDL_Rect{500, 0, 25, 22},
                    SDL_Rect{525, 0, 25, 22},
                    SDL_Rect{550, 0, 25, 22},
                    SDL_Rect{575, 0, 25, 22},
                    SDL_Rect{600, 0, 25, 22},
            }
    );
    _sprites.emplace_back(_texture, tiles, 150);

    // Jump_Left
    tiles = std::vector(
            {
                    SDL_Rect{625, 0, 25, 22},
                    SDL_Rect{650, 0, 25, 22},
                    SDL_Rect{675, 0, 25, 22},
                    SDL_Rect{700, 0, 25, 22},
                    SDL_Rect{725, 0, 25, 22},
                    SDL_Rect{750, 0, 25, 22},
                    SDL_Rect{775, 0, 25, 22},
            }
    );
    _sprites.emplace_back(_texture, tiles, 100);

    // Jump_Right
    tiles = std::vector(
            {
                    SDL_Rect{800, 0, 25, 22},
                    SDL_Rect{825, 0, 25, 22},
                    SDL_Rect{850, 0, 25, 22},
                    SDL_Rect{875, 0, 25, 22},
                    SDL_Rect{900, 0, 25, 22},
                    SDL_Rect{925, 0, 25, 22},
                    SDL_Rect{950, 0, 25, 22},
            }
    );
    _sprites.emplace_back(_texture, tiles, 100);
}

void Player::handle(PlayerControlContext ctx) {
    if (!_moveControl) {
        return;
    }

    if (!(ctx.moveLeft ^ ctx.moveRight)) {
        _dx = 0;
        _state = ctx.jump ? PS_JUMP : PS_STAY;
    } else if (ctx.moveLeft) {
        _state = ctx.jump ? PS_JUMP_LEFT : PS_LEFT;
        _dx = -2;
    } else if (ctx.moveRight) {
        _state = ctx.jump ? PS_JUMP_RIGHT : PS_RIGHT;
        _dx = 2;
    }

    if (ctx.jump) {
        _moveControl = false;
        _dy = 2;
        _status = 16;
    }
}


void Player::update() {
    if (!_moveControl && _status) {
        _y -= _dy;
        _status--;
    } else {
        if (_y <= 200) {
            _y += _dy;
        } else {
            if (!_moveControl && !_sprites[_state].getFrameCount() - 1) {
                _moveControl = true;
            }
        }
    }

    switch (_state) {
        case PS_LEFT:
        case PS_JUMP_LEFT:
            _x += _dx;
            if (_x < 0) {
                _x = 0;
            }
            break;
        case PS_RIGHT:
        case PS_JUMP_RIGHT:
            _x += _dx;
            if (_x > 615) {
                _x = 615;
            }
            break;
        default:
            break;
    }

    _sprites[_state].update();
}

void Player::render(SDL_Renderer *renderer) {
    _sprites[_state].render(renderer, _x, _y);
}
