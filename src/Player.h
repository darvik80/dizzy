//
// Created by Ivan Kishchenko on 12.08.2021.
//

#ifndef DIZZY_PLAYER_H
#define DIZZY_PLAYER_H

#include "AnimationSprite.h"
#include "Texture.h"
#include "GameObject.h"

enum Player_State {
    PS_STAY,
    PS_JUMP,
    PS_LEFT,
    PS_RIGHT,
    PS_JUMP_LEFT,
    PS_JUMP_RIGHT,
    PS_COUNT
};

struct PlayerControlContent {
    bool moveLeft = false;
    bool moveRight = false;
    bool jump;
};

class Player {
    int _x{0};
    int _y{96};

    bool _moveControl{true};
    int _dy{2};
    int _dx{0};
    int _status = 0;
    Player_State _state{PS_STAY};
    Texture::Ptr _texture{};
    std::vector<AnimationSprite> _sprites;
public:
    explicit Player(SDL_Renderer *renderer, Player_State state = PS_STAY);

    void handle(PlayerControlContent content);
    void update();

    void render(SDL_Renderer *renderer);
};


#endif //DIZZY_PLAYER_H
