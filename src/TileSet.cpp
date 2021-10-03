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

            GameObjectAttributes attr{};
            auto props = tile->getProperties();
            if (auto prop = props.getProperty("cloud")) {
                attr.isCloud = prop->getValue<bool>();
            }
            if (auto prop = props.getProperty("damage")) {
                attr.isDamage = prop->getValue<bool>();
            }

            TileInfo mainFrame{
                    SDL_Rect{rect.x, rect.y, rect.width, rect.height}
            };

            auto layer = tile->getObjectgroup();
            for (const auto &obj: layer.getObjects()) {
                auto s = obj.getSize();
                auto p = obj.getPosition();
                mainFrame.collision = SDL_Rect{p.x, p.y, s.x, s.y};
                break;
            }

            if (tile->getAnimation().any()) {
                std::vector<TileInfo> frames;
                for (const auto &frame: tile->getAnimation().getFrames()) {
                    auto frameTile = tileset->getTile(frame.getTileId());

                    TileInfo curFrame{};
                    layer = frameTile->getObjectgroup();
                    const auto objs = layer.getObjects();
                    if (objs.empty()) {
                        curFrame.collision = mainFrame.collision;
                    } else {
                        const auto obj = objs[0];
                        auto s = obj.getSize();
                        auto p = obj.getPosition();
                        curFrame.collision = SDL_Rect{p.x, p.y, s.x, s.y};
                    }

                    auto frameRect = frameTile->getDrawingRect();
                    curFrame.frame = SDL_Rect{frameRect.x, frameRect.y, frameRect.width, frameRect.height};
                    frames.push_back(curFrame);
                }
                _tiles.emplace_back(frames, tile->getAnimation().getCurrentFrame()->getDuration(), attr);
            } else {
                _tiles.emplace_back(mainFrame, attr);
            }
            tileId++;
        }
    }

}

bool TileSet::collision(GameContext &ctx, SDL_Rect obj, int tileId, int x, int y) {
    auto &collision = _tiles.at(tileId).getTileInfo().collision;
    if (collision.w || collision.h) {
        SDL_Rect rect{x + collision.x, y + collision.y, collision.w, collision.h};
        return Helper::hasCollision(obj, rect);
    }

    return false;
}

void TileSet::draw(GameContext &ctx, size_t tileId, int x, int y) {
    auto &tile = _tiles.at(tileId).getTileInfo();
    SDL_Rect src = tile.frame;
    SDL_Rect dst{x, y, src.w, src.h};
    _texture->draw(ctx, src, dst);

//    if (tile.collision.w || tile.collision.h) {
//        if (_tiles.at(tileId).getAttr().isCloud) {
//            SDL_SetRenderDrawColor(ctx.renderer, 0, 255, 0, 0);
//        } else {
//            SDL_SetRenderDrawColor(ctx.renderer, 255, 0, 0, 0);
//        }
//        SDL_Rect rect{x + tile.collision.x, y + tile.collision.y, tile.collision.w, tile.collision.h};
//        SDL_RenderDrawRect(ctx.renderer, &rect);
//    }
}
