//
// Created by Ivan Kishchenko on 10.08.2021.
//

#include "Helper.h"

bool Helper::hasCollision(SDL_Rect &first, SDL_Rect &second) {
    int leftFirst = first.x;
    int rightFirst = first.x + first.w;
    int topFirst = first.y;
    int bottomFirst = first.y + first.h;

    int leftSecond = second.x;
    int rightSecond = second.x + second.w;
    int topSecond = second.y;
    int bottomSecond = second.y + second.h;

    if (bottomFirst <= topSecond) {
        return false;
    }

    if (topFirst >= bottomSecond) {
        return false;
    }

    if (rightFirst <= leftSecond) {
        return false;
    }

    if (leftFirst >= rightSecond) {
        return false;
    }

    return true;
}
