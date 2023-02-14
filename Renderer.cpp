#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Renderer.h"
#include "Sprite.h"
#include "Game.h"

const char* vertexShader =
        "\n"
        "#version 330\n"
        "\n"
        "noperspective out vec2 TexCoord;\n"
        "\n"
        "void main(void){\n"
        "\n"
        "    TexCoord.x = (gl_VertexID == 2)? 2.0: 0.0;\n"
        "    TexCoord.y = (gl_VertexID == 1)? 2.0: 0.0;\n"
        "    \n"
        "    gl_Position = vec4(2.0 * TexCoord - 1.0, 0.0, 1.0);\n"
        "}\n";

const char* fragmentShader =
        "\n"
        "#version 330\n"
        "\n"
        "uniform sampler2D buffer;\n"
        "noperspective in vec2 TexCoord;\n"
        "\n"
        "out vec3 outColor;\n"
        "\n"
        "void main(void){\n"
        "    outColor = texture(buffer, TexCoord).rgb;\n"
        "}\n";

Renderer::Renderer(){}

Renderer::Renderer(size_t width, size_t height){
    this->buffer = new Buffer;
    this->buffer->width = width;
    this->buffer->height = height;
}

Renderer::~Renderer(){
    delete this->buffer;
    this->buffer = nullptr;
}

void Renderer::Render(Game* game){
    GLFWwindow* window;

    

    /* Initialize the library */
    if (!glfwInit())
        std::cout << "GLFW INIT FAILED ERROR" << std::endl;
    
    glewExperimental = GL_TRUE;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Space Invader", NULL, NULL);
    if (!window)
    {
        std::cout << "ERROR" << std::endl;
        glfwTerminate();
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK){
        std::cout << "GLEW INIT FAILED" << std::endl;
    }else{
        printf("OK");
    };

    //GLuint vertextShader = CompileShader(vertexShader, fragmentShader);

    glClearColor(1.0, 0.0, 0.0, 1.0);

    this->buffer->height = game->width;
    this->buffer->height = game->height;
    this->buffer->data = new uint32_t[game->width * game->height];

    uint32_t clearColor = RgbToUint32(0, 128, 0);
    BufferClear(clearColor);

    GLuint bufferTexture;
    glGenTextures(1, &bufferTexture);
    glBindTexture(GL_TEXTURE_2D, bufferTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->buffer->width, this->buffer->height, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, this->buffer->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint shaderId = CompileShader(vertexShader, fragmentShader);

    glLinkProgram(shaderId);

    if(!ValidateProgram(shaderId)){
        printf("Shader validate failed");
        glfwTerminate();
        glDeleteVertexArrays(1, &vao);
        delete this->buffer->data;
    }

    glUseProgram(shaderId);

    


    GLint location = glGetUniformLocation(shaderId, "buffer");
    glUniform1i(location, 0);


    glDisable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);

    Sprite lineSprite;
    lineSprite.width = game->width;
    lineSprite.height = 1;
    lineSprite.data = new uint8_t[game->width];
    for(int i = 0; i < game->width; i++){
        lineSprite.data[i] = 1;
    }

    int count = 0;
   
    glfwSwapInterval(1);
    game->SetKeyCallback(window);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window) && game->gameRunning)
    {
        /* Render here */
        BufferClear(clearColor);
        game->Render(this->buffer);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, this->buffer->width, this->buffer->height,GL_RGBA, GL_UNSIGNED_INT_8_8_8_8,this->buffer->data);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    delete this->buffer->data;
    this->buffer->data = nullptr;
}

uint32_t Renderer::RgbToUint32(uint8_t r, uint8_t g, uint8_t b){
    return (r << 24) | (g << 16) | (b << 8) | 255;
}

void Renderer::BufferClear(uint32_t color){
    for(int i = 0; i < this->buffer->width * this->buffer->height; ++i){
        this->buffer->data[i] = color;
    }
}

void Renderer::BufferSpriteDraw(Buffer* buffer, const Sprite& sprite, size_t x, size_t y, uint32_t color){
    for(size_t xi = 0; xi < sprite.width; ++xi)
    {
        for(size_t yi = 0; yi < sprite.height; ++yi)
        {
            size_t sy = sprite.height - 1 + y - yi;
            size_t sx = x + xi;
            if(sprite.data[yi * sprite.width + xi] && sy < buffer->height && sx < buffer->width) {
                buffer->data[sy * buffer->width + sx] = color;
            }
        }
    }
}

void Renderer::BufferNumberDraw(Buffer *buffer, const Sprite &numberSprite, size_t number, size_t x, size_t y, uint32_t color){
    uint8_t digits[64];
    size_t num_digits = 0;

    size_t current_number = number;
    do
    {
        digits[num_digits++] = current_number % 10;
        current_number = current_number / 10;
    }
    while(current_number > 0);

    size_t xp = x;
    size_t stride = numberSprite.width * numberSprite.height;
    Sprite sprite = numberSprite;
    for(size_t i = 0; i < num_digits; ++i)
    {
        uint8_t digit = digits[num_digits - i - 1];
        sprite.data = numberSprite.data + digit * stride;
        Renderer::BufferSpriteDraw(buffer, sprite, xp, y, color);
        xp += sprite.width + 1;
    }
}

void Renderer::BufferTextDraw(Buffer *buffer, const Sprite &textSprite, const char *text, size_t x, size_t y, uint32_t color){
    size_t xp = x;
    size_t stride = textSprite.width * textSprite.height;
    Sprite sprite = textSprite;
    for(const char* charp = text; *charp != '\0'; ++charp)
    {
        char character = *charp - 32;
        if(character < 0 || character >= 65) continue;

        sprite.data = textSprite.data + character * stride;
        Renderer::BufferSpriteDraw(buffer, sprite, xp, y, color);
        xp += sprite.width + 1;
    }
}

GLuint Renderer::CompileShader(const char* vertexShader, const char* fragmentShader){
    GLuint shaderId = glCreateProgram();

    //vertex shader
    {
        GLuint shader_vp = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(shader_vp, 1, &vertexShader, 0);
        glCompileShader(shader_vp);
        ValidateShader(shader_vp, vertexShader);
        glAttachShader(shaderId, shader_vp);

        glDeleteShader(shader_vp);
    }

    //fragment shader
    {
        GLuint shader_fp = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(shader_fp, 1, &fragmentShader, 0);
        glCompileShader(shader_fp);
        ValidateShader(shader_fp, fragmentShader);
        glAttachShader(shaderId, shader_fp);

        glDeleteShader(shader_fp);
    }

    return shaderId;
}

bool Renderer::ValidateShader(GLuint shader, const char* file){
    static const unsigned int BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];
    GLsizei length = 0;

    glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);

    if(length > 0)
    {
        printf("Shader %d(%s) compile error: %s\n",
            shader, (file ? file: ""), buffer);

        return false;
    }

    return true;
}

bool Renderer::ValidateProgram(GLuint program)
{
    static const GLsizei BUFFER_SIZE = 512;
    GLchar buffer[BUFFER_SIZE];
    GLsizei length = 0;

    glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer);

    if(length > 0)
    {
        printf("Program %d link error: %s\n", program, buffer);
        return false;
    }

    return true;
}

