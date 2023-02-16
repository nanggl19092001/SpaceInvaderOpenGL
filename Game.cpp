#include <iostream>
#include <fstream>
#include <cstdlib>

#include <string>

#include "Game.h"
#include "Renderer.h"

Game::Game(){}

Game::Game(size_t width, size_t height, size_t numAliens) {

    this->startScreenSprite.data = new uint8_t[100]{
        1,1,0,0,0,0,0,0,0,0,
        1,1,1,1,0,0,0,0,0,0,
        1,1,1,1,1,1,0,0,0,0,
        1,1,1,1,1,1,1,0,0,0,
        1,1,1,1,1,1,1,1,1,0,
        1,1,1,1,1,1,1,1,1,0,
        1,1,1,1,1,1,1,0,0,0,
        1,1,1,1,1,1,0,0,0,0,
        1,1,1,1,0,0,0,0,0,0,
        1,1,0,0,0,0,0,0,0,0
    };
    this->startScreenSprite.width = 10;
    this->startScreenSprite.height = 10;

    this->alienSprites = new Sprite[7];

    this->alienSprites[0].width = 8;
    this->alienSprites[0].height = 8;
    this->alienSprites[0].data = new uint8_t[64]
    {
        0,0,0,1,1,0,0,0, // ...@@...
        0,0,1,1,1,1,0,0, // ..@@@@..
        0,1,1,1,1,1,1,0, // .@@@@@@.
        1,1,0,1,1,0,1,1, // @@.@@.@@
        1,1,1,1,1,1,1,1, // @@@@@@@@
        0,1,0,1,1,0,1,0, // .@.@@.@.
        1,0,0,0,0,0,0,1, // @......@
        0,1,0,0,0,0,1,0  // .@....@.
    };

    this->alienSprites[1].width = 8;
    this->alienSprites[1].height = 8;
    this->alienSprites[1].data = new uint8_t[64]
    {
        0,0,0,1,1,0,0,0, // ...@@...
        0,0,1,1,1,1,0,0, // ..@@@@..
        0,1,1,1,1,1,1,0, // .@@@@@@.
        1,1,0,1,1,0,1,1, // @@.@@.@@
        1,1,1,1,1,1,1,1, // @@@@@@@@
        0,0,1,0,0,1,0,0, // ..@..@..
        0,1,0,1,1,0,1,0, // .@.@@.@.
        1,0,1,0,0,1,0,1  // @.@..@.@
    };

    this->alienSprites[2].width = 11;
    this->alienSprites[2].height = 8;
    this->alienSprites[2].data = new uint8_t[88]
    {
        0,0,1,0,0,0,0,0,1,0,0, // ..@.....@..
        0,0,0,1,0,0,0,1,0,0,0, // ...@...@...
        0,0,1,1,1,1,1,1,1,0,0, // ..@@@@@@@..
        0,1,1,0,1,1,1,0,1,1,0, // .@@.@@@.@@.
        1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
        1,0,1,1,1,1,1,1,1,0,1, // @.@@@@@@@.@
        1,0,1,0,0,0,0,0,1,0,1, // @.@.....@.@
        0,0,0,1,1,0,1,1,0,0,0  // ...@@.@@...
    };

    this->alienSprites[3].width = 11;
    this->alienSprites[3].height = 8;
    this->alienSprites[3].data = new uint8_t[88]
    {
        0,0,1,0,0,0,0,0,1,0,0, // ..@.....@..
        1,0,0,1,0,0,0,1,0,0,1, // @..@...@..@
        1,0,1,1,1,1,1,1,1,0,1, // @.@@@@@@@.@
        1,1,1,0,1,1,1,0,1,1,1, // @@@.@@@.@@@
        1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
        0,1,1,1,1,1,1,1,1,1,0, // .@@@@@@@@@.
        0,0,1,0,0,0,0,0,1,0,0, // ..@.....@..
        0,1,0,0,0,0,0,0,0,1,0  // .@.......@.
    };

    this->alienSprites[4].width = 12;
    this->alienSprites[4].height = 8;
    this->alienSprites[4].data = new uint8_t[96]
    {
        0,0,0,0,1,1,1,1,0,0,0,0, // ....@@@@....
        0,1,1,1,1,1,1,1,1,1,1,0, // .@@@@@@@@@@.
        1,1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@@
        1,1,1,0,0,1,1,0,0,1,1,1, // @@@..@@..@@@
        1,1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@@
        0,0,0,1,1,0,0,1,1,0,0,0, // ...@@..@@...
        0,0,1,1,0,1,1,0,1,1,0,0, // ..@@.@@.@@..
        1,1,0,0,0,0,0,0,0,0,1,1  // @@........@@
    };


    this->alienSprites[5].width = 12;
    this->alienSprites[5].height = 8;
    this->alienSprites[5].data = new uint8_t[96]
    {
        0,0,0,0,1,1,1,1,0,0,0,0, // ....@@@@....
        0,1,1,1,1,1,1,1,1,1,1,0, // .@@@@@@@@@@.
        1,1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@@
        1,1,1,0,0,1,1,0,0,1,1,1, // @@@..@@..@@@
        1,1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@@
        0,0,1,1,1,0,0,1,1,1,0,0, // ..@@@..@@@..
        0,1,1,0,0,1,1,0,0,1,1,0, // .@@..@@..@@.
        0,0,1,1,0,0,0,0,1,1,0,0  // ..@@....@@..
    };

    this->alienSprites[6].width = 13;
    this->alienSprites[6].height = 7;
    this->alienSprites[6].data = new uint8_t[91]
    {
        0,1,0,0,1,0,0,0,1,0,0,1,0, // .@..@...@..@.
        0,0,1,0,0,1,0,1,0,0,1,0,0, // ..@..@.@..@..
        0,0,0,1,0,0,0,0,0,1,0,0,0, // ...@.....@...
        1,1,0,0,0,0,0,0,0,0,0,1,1, // @@.........@@
        0,0,0,1,0,0,0,0,0,1,0,0,0, // ...@.....@...
        0,0,1,0,0,1,0,1,0,0,1,0,0, // ..@..@.@..@..
        0,1,0,0,1,0,0,0,1,0,0,1,0  // .@..@...@..@.
    };

    this->width = width;
    this->height = height;
    this->numBullets = numBullets;
    this->numAliens = numAliens;
    this->aliens = new Alien[numAliens];

    //init aliens position
    for(unsigned int xi = 0; xi < 11; xi++){
        for(unsigned int yi = 0; yi < 5; yi++){
            this->aliens[xi + 11 * yi].y = 17 * yi + 128;
            if(yi == 3){
                this->aliens[xi + 11 * yi].type = ALIEN_TYPE_C;
                this->aliens[xi + 11 * yi].x = 16 * xi + 20 - 1;
            }   
            else if(yi == 4)
            {
                this->aliens[xi + 11 * yi].type = ALIEN_TYPE_A;
                this->aliens[xi + 11 * yi].x = 16 * xi + 20 + 1;
            }
            else
            {
                this->aliens[xi + 11 * yi].type = ALIEN_TYPE_B;
                this->aliens[xi + 11 * yi].x = 16 * xi + 20;
            }
        }
    }

    //init each alien type animation frames
    this->spriteAnimations = new SpriteAnimation[3];
    for(unsigned int i = 0; i < 3; i++){
        this->spriteAnimations[i].loop = true;
        this->spriteAnimations[i].frameDuration = 10;
        this->spriteAnimations[i].numFrames = 2;
        this->spriteAnimations[i].time = 0;

        this->spriteAnimations[i].frames = new Sprite*[2];
        this->spriteAnimations[i].frames[0] = &this->alienSprites[i*2];
        this->spriteAnimations[i].frames[1] = &this->alienSprites[i*2 + 1];
    }

    //dead counting for display alien death frames
    this->deathCounter = new uint8_t[this->numAliens];
    for(unsigned int i = 0; i < this->numAliens; i++){
        this->deathCounter[i] = 10;
    }

    //start pos of player
    this->player.x = this->width/2;
    this->player.y = 20;

    this->textSpriteSheet.width = 5;
    this->textSpriteSheet.height = 7;
    this->textSpriteSheet.data = new uint8_t[65 * 35]
    {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,
        0,1,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,1,0,1,0,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,0,1,0,1,0,
        0,0,1,0,0,0,1,1,1,0,1,0,1,0,0,0,1,1,1,0,0,0,1,0,1,0,1,1,1,0,0,0,1,0,0,
        1,1,0,1,0,1,1,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,1,1,0,1,0,1,1,
        0,1,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,1,0,0,0,1,0,1,1,1,1,
        0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,
        1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,
        0,0,1,0,0,1,0,1,0,1,0,1,1,1,0,0,0,1,0,0,0,1,1,1,0,1,0,1,0,1,0,0,1,0,0,
        0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,1,1,1,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
        0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,

        0,1,1,1,0,1,0,0,0,1,1,0,0,1,1,1,0,1,0,1,1,1,0,0,1,1,0,0,0,1,0,1,1,1,0,
        0,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,1,1,0,
        0,1,1,1,0,1,0,0,0,1,0,0,0,0,1,0,0,1,1,0,0,1,0,0,0,1,0,0,0,0,1,1,1,1,1,
        1,1,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,1,0,1,1,1,0,
        0,0,0,1,0,0,0,1,1,0,0,1,0,1,0,1,0,0,1,0,1,1,1,1,1,0,0,0,1,0,0,0,0,1,0,
        1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,1,0,1,1,1,0,
        0,1,1,1,0,1,0,0,0,1,1,0,0,0,0,1,1,1,1,0,1,0,0,0,1,1,0,0,0,1,0,1,1,1,0,
        1,1,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,
        0,1,1,1,0,1,0,0,0,1,1,0,0,0,1,0,1,1,1,0,1,0,0,0,1,1,0,0,0,1,0,1,1,1,0,
        0,1,1,1,0,1,0,0,0,1,1,0,0,0,1,0,1,1,1,1,0,0,0,0,1,1,0,0,0,1,0,1,1,1,0,

        0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,
        0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,
        0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
        1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,
        0,1,1,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,
        0,1,1,1,0,1,0,0,0,1,1,0,1,0,1,1,1,0,1,1,1,0,1,0,0,1,0,0,0,1,0,1,1,1,0,

        0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,
        1,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,1,1,1,0,
        0,1,1,1,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,1,1,1,0,
        1,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,0,
        1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,1,1,1,0,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1,
        1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,1,1,1,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,
        0,1,1,1,0,1,0,0,0,1,1,0,0,0,0,1,0,1,1,1,1,0,0,0,1,1,0,0,0,1,0,1,1,1,0,
        1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,
        0,1,1,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,1,1,0,
        0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,1,0,1,1,1,0,
        1,0,0,0,1,1,0,0,1,0,1,0,1,0,0,1,1,0,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,0,1,
        1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1,
        1,0,0,0,1,1,1,0,1,1,1,0,1,0,1,1,0,1,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,
        1,0,0,0,1,1,0,0,0,1,1,1,0,0,1,1,0,1,0,1,1,0,0,1,1,1,0,0,0,1,1,0,0,0,1,
        0,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,1,1,0,
        1,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,1,1,1,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,
        0,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,1,0,1,1,0,0,1,1,0,1,1,1,1,
        1,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,1,1,1,0,1,0,1,0,0,1,0,0,1,0,1,0,0,0,1,
        0,1,1,1,0,1,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,0,0,0,1,0,0,0,0,1,0,1,1,1,0,
        1,1,1,1,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,
        1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,1,1,0,
        1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,
        1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,1,0,1,1,0,1,0,1,1,1,0,1,1,1,0,0,0,1,
        1,0,0,0,1,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,1,0,0,0,1,
        1,0,0,0,1,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,
        1,1,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,1,1,1,1,

        0,0,0,1,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,1,
        0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,
        1,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1,1,0,0,0,
        0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
        0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    };

    this->numberSpriteSheet = this->textSpriteSheet;
    this->numberSpriteSheet.data += 16 * 35;
}

Game::~Game(){
    delete this->aliens;
    this->aliens = nullptr;


    for(unsigned int i = 0; i < 6; i++){
        delete this->alienSprites[i].data;
        this->alienSprites[i].data = nullptr;
    }

    delete this->alienSprites;
    this->alienSprites = nullptr;

    delete this->spriteAnimations;
    this->spriteAnimations = nullptr;

    delete this->player.sprite.data;
    this->player.sprite.data = nullptr;

    delete this->numberSpriteSheet.data;
    this->numberSpriteSheet.data = nullptr;

    delete this->textSpriteSheet.data;
    this->textSpriteSheet.data = nullptr;
}

Game* Game::GetInstance(size_t width, size_t height, size_t numAliens){
    static Game* instance = new Game(width, height, numAliens);
    return instance;
}

void Game::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
    GetInstance(210, 220, 55)->keyCallbackImplement(key, scancode, action, mods);
}

void Game::keyCallbackImplement(int key, int scancode, int action, int mods){

    switch (this->screen)
    {
        case MAIN_MENU:
            keyCallbackImplementStartScreen(key, scancode, action, mods);
            break;
        case MAIN_GAME:
            keyCallbackImplementMaingame(key, scancode, action, mods);
            break;
        default:
            break;
    }
}

void Game::keyCallbackImplementStartScreen(int key, int scancode, int action, int mods){
    switch(key){
        case GLFW_KEY_ESCAPE:
            if(action == GLFW_PRESS){
                gameRunning = false;
                break;
            }
        case GLFW_KEY_UP:
            if(action == GLFW_PRESS)
                this->cursor == 0 ? this->cursor = 1 : this->cursor = 0;
            break;
        case GLFW_KEY_DOWN:
            if(action == GLFW_PRESS)
                this->cursor == 0 ? this->cursor = 1 : this->cursor = 0;
            break;
        case GLFW_KEY_SPACE:
            if(action == GLFW_PRESS)
                this->cursor == 0 ? this->screen = MAIN_GAME : this->screen = MAIN_MENU;
        default:
            break;
    }
}

void Game::keyCallbackImplementMaingame(int key, int scancode, int action, int mods){
    switch(key){
        case GLFW_KEY_ESCAPE:
            if(action == GLFW_PRESS){
                this->gameRunning = false;
                break;
            }
        case GLFW_KEY_LEFT:
            if(action == GLFW_PRESS)
                this->move_dir -= 1;
            else if(action == GLFW_RELEASE)
                this->move_dir += 1;
            break;
        case GLFW_KEY_RIGHT:
            if(action == GLFW_PRESS)
                this->move_dir == 0 ? this->move_dir += 1 : this->move_dir = 0;
            else if(action == GLFW_RELEASE)
                this->move_dir -= 1;
            break;
        case GLFW_KEY_SPACE:
            if(action == GLFW_PRESS)
                this->firePress = true;
            else if(action == GLFW_RELEASE)
                this->firePress = false;
        default :
            break;
    }
}

void Game::SetKeyCallback(GLFWwindow *window){
    glfwSetKeyCallback(window, keyCallback);
}

void Game::Render(Buffer *buffer){
    switch(this->screen){
        case MAIN_MENU:
            RenderStartScreen(buffer);
            break;
        case MAIN_GAME:
            RenderGameScreen(buffer);
            break;
        default:
            break;
    }
}

bool Game::RenderTextStartScreen(Buffer* buffer){

    this->move_dir = 0;
    
    uint32_t TextRenderColor = Renderer::RgbToUint32(128, 0, 0);

    Renderer::BufferTextDraw(buffer, this->textSpriteSheet, "START", this->width/2 - textSpriteSheet.width, this->height/2 + 30, TextRenderColor);

    Renderer::BufferTextDraw(buffer, this->textSpriteSheet, "LEADERBOARD", this->width/2 - textSpriteSheet.width, this->height/2, TextRenderColor);

    return true;
}

void Game::RenderStartScreen(Buffer* buffer){
    RenderTextStartScreen(buffer);
    Renderer::BufferSpriteDraw(buffer, startScreenSprite, this->width/2 - 30, this->height/2 + 30 - 30*this->cursor, Renderer::RgbToUint32(128, 0, 0));
}

bool Game::RenderTextGameScreen(Buffer* buffer){
    
    uint32_t TextRenderColor = Renderer::RgbToUint32(128, 0, 0);

    Renderer::BufferTextDraw(buffer, this->textSpriteSheet, "SCORE: ", 10, 10, TextRenderColor);

    Renderer::BufferNumberDraw(buffer, this->numberSpriteSheet, this->point, this->numberSpriteSheet.width + 40, 10, TextRenderColor);

    return true;
}

void Game::RenderGameScreen(Buffer* buffer){
    RenderTextGameScreen(buffer);
    if(OffsetCheck()){
        for(unsigned int i = 0; i < this->numAliens; i++){
            if(this->aliens[i].type == ALIEN_TYPE_DEAD) continue;

            if(this->aliens[i].y - 3 < 30) break;
            this->aliens[i].y -= 3;
        }
        this->alienMove *= -1;
    }

    for(size_t ai = 0; ai < this->numAliens; ai++){
        if(!deathCounter[ai]) continue;
        Alien& alien = this->aliens[ai];

        if(alien.type == ALIEN_TYPE_DEAD && this->deathCounter[ai]){
            Renderer::BufferSpriteDraw(buffer, this->alienSprites[6], alien.x, alien.y, Renderer::RgbToUint32(128, 0, 0));
            --this->deathCounter[ai];
        }
        else{
            alien.x += this->alienMove;

            const SpriteAnimation& animation = this->spriteAnimations[alien.type - 1];
            size_t currentFrame = animation.time / animation.frameDuration;
            const Sprite& sprite = *animation.frames[currentFrame];

            Renderer::BufferSpriteDraw(buffer, sprite ,alien.x, alien.y, Renderer::RgbToUint32(128, 0, 0));
        }
    }

    Renderer::BufferSpriteDraw(buffer, this->player.sprite, this->player.x, this->player.y, Renderer::RgbToUint32(128, 0, 0));

    
    for(int i = 0; i < 3; i++){
        ++this->spriteAnimations[i].time;
        if(this->spriteAnimations[i].time == this->spriteAnimations[i].numFrames * this->spriteAnimations[i].frameDuration){
            if(this->spriteAnimations[i].loop)  
                this->spriteAnimations[i].time = 0;
            else{
                delete this->spriteAnimations;
                this->spriteAnimations = nullptr;
            }
        }
    }

    for(size_t bi = 0; bi < this->numBullets; bi++){
        const Bullet& bullet = this->bullets[bi];
        const Sprite& sprite = bullet.sprite;
        Renderer::BufferSpriteDraw(buffer, sprite, bullet.x, bullet.y, Renderer::RgbToUint32(128, 0, 0));
    }

    for(size_t bi = 0; bi < this->numBullets; bi++){
            
            this->bullets[bi].y += this->bullets[bi].dir;
            if(this->bullets[bi].y >= this->height || this->bullets[bi].y <= 0){
                this->bullets[bi] = this->bullets[this->numBullets - 1];
                --this->numBullets;
                continue;
            }
            
            if(this->bullets[bi].dir < 0){
                if(this->bullets[bi].x >= this->player.x && this->bullets[bi].x < this->player.x + this->player.sprite.width && this->bullets[bi].y < this->player.y + this->player.sprite.height/2){
                    this->screen = MAIN_MENU;
                    ClearState();
                }
                continue;
            }

            for(size_t ai = 0; ai < this->numAliens; ai++){
                Alien& alien = this->aliens[ai];
                if(alien.type == ALIEN_TYPE_DEAD){
                    continue;
                }

                SpriteAnimation& animation = this->spriteAnimations[alien.type - 1];
                size_t currentFrame = animation.time / animation.frameDuration;
                const Sprite& alienSprite = *animation.frames[currentFrame];

                bool overlap = SpriteOverlap(alienSprite, alien.x, alien.y, this->bullets[bi].sprite, this->bullets[bi].x, this->bullets[bi].y);
                if(overlap){
                    point += alien.type * 10;

                    alien.type = 0;
                    this->aliens[ai].x -= (this->alienSprites[6].width - alienSprite.width) / 2; 
                    this->bullets[bi] = this->bullets[this->numBullets - 1];
                    
                    --this->numBullets;
                    continue;
                }
            }
    }

    

    int player_move_dir = 2 * move_dir;
    if(this->player.x + this->player.sprite.width + player_move_dir >= this->width - 1)
    {
        this->player.x = this->width - this->player.sprite.width;
    }
    else if((int)this->player.x + player_move_dir <= 0)
    {
        this->player.x = 0;
    }
    else this->player.x += player_move_dir;

    if(this->firePress && this->numBullets < GAME_MAX_BULLET) {
        this->bullets[this->numBullets].x = this->player.x + this->player.sprite.width/2;
        this->bullets[this->numBullets].y = this->player.y + this->player.sprite.height;
        this->bullets[this->numBullets].dir = 2;
        ++this->numBullets;
    }
    this->firePress = false;
    GenAlienBullets();
}

bool Game::SpriteOverlap(
    const Sprite& sp_a, size_t x_a, size_t y_a,
    const Sprite& sp_b, size_t x_b, size_t y_b
)
{
    if(x_a < x_b + sp_b.width && x_a + sp_a.width > x_b &&
       y_a < y_b + sp_b.height && y_a + sp_a.height > y_b)
    {
        return true;
    }

    return false;
}

bool Game::GenAlienBullets(){
    if(this->fireCounter > 0){
        --this->fireCounter;
    }
    else{
        int randNum = rand() % this->numAliens;
        if(this->aliens[randNum].type == ALIEN_TYPE_DEAD){
            for(int i = 0; i < this->numAliens; i++){
                if(this->aliens[i].type != ALIEN_TYPE_DEAD){
                    randNum = i;
                    break;
                }
                if(i == this->numAliens - 1 && this->aliens[i].type == ALIEN_TYPE_DEAD){
                    return false;
                }
            }
        }
        if(this->numBullets < GAME_MAX_BULLET){
            this->bullets[this->numBullets].x = this->aliens[randNum].x;
            this->bullets[this->numBullets].y = this->aliens[randNum].y;
            this->bullets[this->numBullets].dir = -2;
            ++this->numBullets;
        }

        this->fireCounter = 60;
    }

    return true;
}

bool Game::OffsetCheck(){
    for(unsigned int i = 0; i < this->numAliens; i++){
        if(this->aliens[i].type == ALIEN_TYPE_DEAD)
            continue;
        
        if(this->aliens[i].x <= 0 || this->aliens[i].x + 11 >= this->width)
            return true;
    }
    return false;
}

void Game::ClearState(){
    this->point = 0;
    this->numBullets = 0;
    //init aliens position
    for(unsigned int xi = 0; xi < 11; xi++){
        for(unsigned int yi = 0; yi < 5; yi++){
            this->aliens[xi + 11 * yi].y = 17 * yi + 128;
            if(yi == 3){
                this->aliens[xi + 11 * yi].type = ALIEN_TYPE_C;
                this->aliens[xi + 11 * yi].x = 16 * xi + 20 - 1;
            }   
            else if(yi == 4)
            {
                this->aliens[xi + 11 * yi].type = ALIEN_TYPE_A;
                this->aliens[xi + 11 * yi].x = 16 * xi + 20 + 1;
            }
            else
            {
                this->aliens[xi + 11 * yi].type = ALIEN_TYPE_B;
                this->aliens[xi + 11 * yi].x = 16 * xi + 20;
            }
        }
    }

    for(unsigned int i = 0; i < this->numAliens; i++){
        this->deathCounter[i] = 10;
    }

    //start pos of player
    this->player.x = this->width/2;
    this->player.y = 20;
}