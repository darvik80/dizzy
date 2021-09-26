//
// Created by Ivan Kishchenko on 26.09.2021.
//

#pragma once

#include "GameObject.h"
#include "GameContext.h"
#include "AnimationSprite.h"
#include "Texture.h"

#define PLAYER_WIDTH 25
#define PLAYER_HEIGHT 22

class Player : public GameObject {
    enum Player_State {
        PS_STAY,
        PS_JUMP,
        PS_LEFT,
        PS_RIGHT,
        PS_JUMP_LEFT,
        PS_JUMP_RIGHT,
        PS_DIE,
    };

    std::vector<AnimationSprite*> _sprites;

    int _x{0};
    int _y{96};

    bool _moveControl{true};
    int _dy{2};
    int _dx{0};
    int _status = 0;
    Player_State _state{PS_STAY};
private:
    void handleControl(Control& control);

    bool collisionLeg(GameContext &ctx);
    bool collisionBody(GameContext &ctx);
public:

    int order() override {
        return 2;
    }

    std::error_code load(GameContext &ctx, std::string_view path) override;

    void update(GameContext &ctx) override;

    void draw(GameContext &ctx) override;
};
