#pragma once
#include "Sprite.h"

enum AlienType: uint8_t {
    ALIEN_TYPE_DEAD = 0,
    ALIEN_TYPE_A = 1,
    ALIEN_TYPE_B = 2,
    ALIEN_TYPE_C = 3
};

class Alien {
    public:
        size_t x, y;
        uint8_t type;

        Alien();
        ~Alien();
};