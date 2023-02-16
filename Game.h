#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Bullet.h"
#include "Alien.h"
#include "Player.h"
#include "Buffer.h"
#include "SpriteAnimation.h"


#define GAME_MAX_BULLET 128

enum LevelScreen: int {
    MAIN_MENU = 0,
    MAIN_GAME = 1,
    HIGH_SCORE = 2
};

class Game {        
    public:
        bool gameRunning = true;
        bool firePress = false;
        int move_dir = 0;
        int fireCounter = 60;
        int screen = MAIN_MENU;

        int alienMove = 1;
        unsigned int alienMoveFrame = 0;

        unsigned int cursor = 0;

        Sprite startScreenSprite;

        size_t point = 0;
        size_t width, height;
        size_t numAliens;
        size_t numBullets = 0;
        Alien* aliens;
        Sprite* alienSprites;
        Sprite textSpriteSheet;
        Sprite numberSpriteSheet;
        SpriteAnimation* spriteAnimations;
        Player player;
        Bullet bullets[GAME_MAX_BULLET];
        uint8_t* deathCounter;

        static Game* GetInstance(size_t width, size_t height, size_t numAliens);

        Game();
        ~Game();
        Game(size_t width, size_t height, size_t numAliens);

        void Render(Buffer *buffer);
        void SetKeyCallback(GLFWwindow *window);
        static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
        void keyCallbackImplement(int key, int scancode, int action, int mods);
        void keyCallbackImplementStartScreen(int key, int scancode, int action, int mods);
        void keyCallbackImplementMaingame(int key, int scancode, int action, int mods);

    private:
        bool SpriteOverlap(const Sprite& sp_a, size_t x_a, size_t y_a,
        const Sprite& sp_b, size_t x_b, size_t y_b);
        bool OffsetCheck();
        bool GenAlienBullets();
        bool RenderTextStartScreen(Buffer* buffer);
        bool RenderTextGameScreen(Buffer* buffer);
        void RenderStartScreen(Buffer* buffer);
        void RenderGameScreen(Buffer* buffer);
        void ClearState();

};