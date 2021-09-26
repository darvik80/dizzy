//
// Created by Ivan Kishchenko on 13.08.2021.
//

#pragma once

#include <vector>
#include <memory>
#include "TileSet.h"
#include "GameObject.h"

class GameMap : public GameObject {
    std::unique_ptr<TileSet> _tileSet;
    std::vector<std::vector<int>> _map;
public:
    GameMap() = default;

    std::error_code load(GameContext &ctx, std::string_view path) override;

    void update(GameContext &ctx) override;

    bool collision(GameContext& ctx, SDL_Rect rect) override;

    void draw(GameContext &ctx) override;
};
