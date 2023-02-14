#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Sprite.h"
#include "Game.h"
#include "Buffer.h"



class Renderer {
    private:
        void BufferClear(uint32_t color);

        GLuint CompileShader(const char* vertexShader, const char* fragmentShader);
        bool ValidateShader(GLuint shaderId, const char* file_name);
        bool ValidateProgram(GLuint program);
        

    public:
        Buffer *buffer;

        Renderer();
        Renderer(size_t width, size_t height);
        ~Renderer();

        void Render(Game* game);

        static void BufferSpriteDraw(Buffer* buffer, const Sprite& sprite, size_t x, size_t y, uint32_t color);
        static void BufferTextDraw(Buffer* buffer, const Sprite& textSprite, const char* text, size_t x, size_t y, uint32_t color);
        static void BufferNumberDraw(Buffer* buffer, const Sprite& numberSprite, size_t number, size_t x, size_t y, uint32_t color);
        static uint32_t RgbToUint32(uint8_t r, uint8_t g, uint8_t b);
        
};