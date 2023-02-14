#pragma once
#include <GLFW/glfw3.h>

struct Sprite {
    size_t width, height, x, y;
    uint8_t* data;
};