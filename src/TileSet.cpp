//
// Created by Ivan Kishchenko on 13.08.2021.
//

#include "TileSet.h"
#include "Helper.h"

TileSet::TileSet(GameContext &ctx, tson::Tileset *tileset) {
    auto tileSize = tileset->getTileSize();
    _texture = std::make_shared<Texture>();
    _texture->load(ctx, "assets/images/tiles.png", SDL_Color{0x51, 0xa2, 0xf3});
    int tileId = tileset->getFirstgid();
    for (int y = 0; y < _texture->getHeight(); y += tileSize.y + tileset->getSpacing()) {
        for (int x = 0; x < _texture->getWidth(); x += tileSize.x + tileset->getSpacing()) {
            auto tile = tileset->getTile(tileId);
            auto rect = tile->getDrawingRect();

            auto layer = tile->getObjectgroup();
            std::vector<SDL_Rect> collisions;
            for (const auto &obj: layer.getObjects()) {
                auto s = obj.getSize();
                auto p = obj.getPosition();
                collisions.emplace_back(SDL_Rect{p.x, p.y, s.x, s.y});
            }

            if (tile->getAnimation().any()) {
                std::vector<SDL_Rect> frames;
                for (const auto &frame: tile->getAnimation().getFrames()) {
                    auto frameTile = tileset->getTile(frame.getTileId());
                    auto frameRect = frameTile->getDrawingRect();
                    frames.push_back(SDL_Rect{frameRect.x, frameRect.y, frameRect.width, frameRect.height});
                }
                _tiles.emplace_back(frames, tile->getAnimation().getCurrentFrame()->getDuration(), collisions);
            } else {
                _tiles.emplace_back(SDL_Rect{rect.x, rect.y, rect.width, rect.height}, collisions);
            }
            tileId++;
        }
    }

}

bool TileSet::collision(GameContext& ctx, SDL_Rect obj, int tileId, int x, int y) {
    for (auto &collision: _tiles.at(tileId).getCollisions()) {
        SDL_Rect rect{x + collision.x, y + collision.y, collision.w, collision.h};
        if (Helper::hasCollision(obj, rect)) {
            return true;
        }
    }

    return false;
}

void TileSet::draw(GameContext &ctx, int tileId, int x, int y) {
    SDL_Rect src = _tiles.at(tileId).getRect();
    SDL_Rect dst{x, y, src.w, src.h};
    _texture->draw(ctx, src, dst);

//    SDL_SetRenderDrawColor(ctx.renderer, 255, 0, 0, 0);
//    for (auto &collision: _tiles.at(tileId).getCollisions()) {
//        SDL_Rect rect{x + collision.x, y + collision.y, collision.w, collision.h};
//        SDL_RenderDrawRect(ctx.renderer, &rect);
//    }
}
