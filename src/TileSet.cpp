//
// Created by Ivan Kishchenko on 13.08.2021.
//

#include "TileSet.h"

TileSet::TileSet(SDL_Renderer *renderer, int width, int height, int border) {
    int doubleBorder = border * 2;
    _texture = std::make_shared<Texture>(renderer, "assets/images/tiles.png");
    for (int y = 0; y < _texture->getHeight(); y += height + doubleBorder) {
        for (int x = 0; x < _texture->getWidth(); x += width + doubleBorder) {
            _tiles.emplace_back(SDL_Rect{x + border, y + border, width, height});
        }
    }
}


TileSet::TileSet(SDL_Renderer* renderer, tson::Tileset* tileset) {
    auto tileSize = tileset->getTileSize();
    _texture = std::make_shared<Texture>(renderer, "assets/images/tiles.png");
    int tileId = tileset->getFirstgid();
    for (int y = 0; y < _texture->getHeight(); y += tileSize.y + tileset->getSpacing()) {
        for (int x = 0; x < _texture->getWidth(); x += tileSize.x + tileset->getSpacing()) {
            auto tile = tileset->getTile(tileId);
            auto rect = tile->getDrawingRect();
            if (tile->getAnimation().any()) {
                std::vector<SDL_Rect> frames;
                for (const auto& frame : tile->getAnimation().getFrames()) {
                    auto frameTile = tileset->getTile(frame.getTileId());
                    auto frameRect = frameTile->getDrawingRect();
                    frames.push_back(SDL_Rect{frameRect.x, frameRect.y, frameRect.width, frameRect.height});
                }
                _tiles.emplace_back(frames, tile->getAnimation().getCurrentFrame()->getDuration());
            } else {
                _tiles.emplace_back(SDL_Rect{rect.x, rect.y, rect.width, rect.height});
            }
            tileId++;
        }
    }

}

void TileSet::render(SDL_Renderer *renderer, int tileId, int x, int y) {
    _texture->render(renderer, x, y, _tiles.at(tileId).getRect());
}
