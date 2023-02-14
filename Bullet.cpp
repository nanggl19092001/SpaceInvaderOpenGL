#include "Bullet.h"

Bullet::Bullet(){
    Sprite bulletSprite;
    bulletSprite.width = 1;
    bulletSprite.height = 3;
    bulletSprite.data = new uint8_t[3]
    {
        1, // @
        1, // @
        1  // @
    };

    this->sprite = bulletSprite;
}

Bullet::~Bullet(){
    delete this->sprite.data;
    this->sprite.data = nullptr;
}