#pragma once
#include "Sprite.h"

#include <GLFW/glfw3.h>

class Bullet {
    public:
        size_t x, y;
        int dir;
        Sprite sprite;

        Bullet();
        ~Bullet();
};