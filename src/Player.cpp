//
// Created by Ivan Kishchenko on 26.09.2021.
//

#include "Player.h"

std::error_code Player::load(GameContext &ctx, std::string_view path) {
    auto texture = std::make_shared<Texture>();
    if (auto err = texture->load(ctx, path, SDL_Color{0x51, 0xa2, 0xf3})) {
        return err;
    }

    // Stay
    auto tiles = std::vector(
            {
                    SDL_Rect{0, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{25, 0, PLAYER_WIDTH, PLAYER_HEIGHT}
            }
    );
    _sprites.emplace_back(new RepeatableAnimationSprite(texture, tiles, 150));

    // Jump
    tiles = std::vector(
            {
                    SDL_Rect{50, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{75, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{100, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{125, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{150, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{175, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{200, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
            }
    );
    _sprites.emplace_back(new RepeatableAnimationSprite(texture, tiles, 100));

    // Left
    tiles = std::vector(
            {
                    SDL_Rect{225, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{250, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{275, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{300, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{325, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{350, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{375, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{400, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
            }
    );
    _sprites.emplace_back(new RepeatableAnimationSprite(texture, tiles, 150));

    // Right
    tiles = std::vector(
            {
                    SDL_Rect{425, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{450, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{475, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{500, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{525, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{550, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{575, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{600, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
            }
    );
    _sprites.emplace_back(new RepeatableAnimationSprite(texture, tiles, 150));

    // Jump_Left
    tiles = std::vector(
            {
                    SDL_Rect{625, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{650, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{675, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{700, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{725, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{750, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{775, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
            }
    );
    _sprites.emplace_back(new RepeatableAnimationSprite(texture, tiles, 100));

    // Jump_Right
    tiles = std::vector(
            {
                    SDL_Rect{800, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{825, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{850, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{875, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{900, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{925, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{950, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
            }
    );
    _sprites.emplace_back(new RepeatableAnimationSprite(texture, tiles, 100));

    // Die
    tiles = std::vector(
            {
                    SDL_Rect{200, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{175, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{150, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
                    SDL_Rect{175, 0, PLAYER_WIDTH, PLAYER_HEIGHT},
            }
    );
    _sprites.emplace_back(new SingleAnimationSprite(texture, tiles, 150));

    return {};
}

void Player::handleControl(Control &control) {
    // DEBUG
    if (control.die) {
        _dx = _dy = 0;
        _state = PS_DIE;
        _moveControl = false;
        return;
    }

    if (!_moveControl) {
        return;
    }

    if (!(control.moveLeft ^ control.moveRight)) {
        _dx = 0;
        _state = control.jump ? PS_JUMP : PS_STAY;
    } else if (control.moveLeft) {
        _state = control.jump ? PS_JUMP_LEFT : PS_LEFT;
        _dx = -1;
    } else if (control.moveRight) {
        _state = control.jump ? PS_JUMP_RIGHT : PS_RIGHT;
        _dx = 1;
    }

    if (control.jump) {
        _moveControl = false;
        _dy = 1;
        _status = 32;
    }

}

bool Player::collisionLeg(GameContext &ctx) {
    for (auto &obj: ctx.objects) {
        if (obj->collision(ctx, SDL_Rect{_x + 8, _y + PLAYER_HEIGHT, PLAYER_WIDTH - 16, 1})) {
            return true;
        }
    }

    return false;
}

bool Player::collisionBody(GameContext &ctx) {
    for (auto &obj: ctx.objects) {
        if (obj->collision(ctx, SDL_Rect{_x, _y+4, PLAYER_WIDTH, PLAYER_HEIGHT-8})) {
            return true;
        }
    }

    return false;
}

void Player::update(GameContext &ctx) {
    handleControl(ctx.control);

    if (_state == PS_DIE) {
        _sprites[_state]->update(ctx);
        return;
    }

    int cnt = 4;
    while (collisionLeg(ctx) && --cnt) {
        _y--;
    }
    if (!_moveControl && _status) {
        _y -= _dy;
        _status--;
        if (collisionBody(ctx)) {
            _y += _dy;
        }
    } else {
        _y += _dy;
        if (collisionLeg(ctx)) {
            if (!_moveControl && !_sprites[_state]->frames() - 1) {
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

    _sprites[_state]->update(ctx);
}

void Player::draw(GameContext &ctx) {
    _sprites[_state]->draw(ctx, SDL_Rect{_x, _y, PLAYER_WIDTH, PLAYER_HEIGHT});
}
