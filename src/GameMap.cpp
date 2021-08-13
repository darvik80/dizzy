//
// Created by Ivan Kishchenko on 13.08.2021.
//

#include "GameMap.h"

#include <tileson/tileson.hpp>

GameMap::GameMap(SDL_Renderer* renderer, std::string_view path){
    tson::Tileson t;
    std::unique_ptr<tson::Map> map = t.parse(fs::path(path));

    const auto mapSize = map->getSize();

    if(map->getStatus() == tson::ParseStatus::OK) {
        _map.resize(mapSize.y);
        auto layer = map->getLayer("Main");

        int x = 0, y = 0;
        for (auto tile : layer->getData()) {
            _map[y].push_back((int)tile);
            if (++x >= mapSize.x) {
                x = 0;
                y++;
            }
        }

        _tileSet = std::make_unique<TileSet>(renderer, map->getTileset("dizzy_tiles"));
    } else {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Failed load map: %s", map->getStatusMessage().c_str());
    }

}

void GameMap::render(SDL_Renderer *renderer) {
    int x = 0, y = 0;
    for (const auto& col : _map) {
        for (int tileId : col) {
            if (tileId) {
                _tileSet->render(renderer, tileId-1, x, y);
            }

            x += _tileSet->getTileWidth();
        }

        x = 0;
        y += _tileSet->getTileHeight();
    }
}
