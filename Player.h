#pragma once
#include "Sprite.h"

class Player {
    public:
        size_t x, y;
        Sprite sprite;
        uint8_t life;

        Player();
        ~Player();
};