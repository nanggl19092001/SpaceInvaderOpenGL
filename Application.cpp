#include "Game.h"
#include "Renderer.h"


int main() {
    Game* game = Game::GetInstance(210, 220, 55);
    Renderer* renderer = new Renderer(210, 220);

    renderer->Render(game);
    delete game;
    delete renderer;

    return 0;
}