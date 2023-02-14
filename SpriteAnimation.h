#pragma once
#include "Sprite.h"

struct SpriteAnimation
{
    bool loop;
    size_t frameDuration;
    size_t time;
    size_t numFrames;
    Sprite** frames;

    /* data */
};
