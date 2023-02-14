#pragma once 
#include <GLFW/glfw3.h>

struct Buffer {
    size_t width, height;
    uint32_t* data;
};