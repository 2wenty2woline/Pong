#include "GameField.h"

GameField::GameField()
{
}

GameField::~GameField()
{
}

void GameField::Init(float width_x, float height_y)
{
}

void GameField::Update(float &dt)
{
}

void GameField::Render(SDL_Renderer *render)
{
    SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);

    /* Draw the line */
    for (int y = 0; y < constantState::WINDOW_HEIGHT; ++y)
    {
        if (y % 5)
        {
            SDL_RenderDrawPoint(render, constantState::WINDOW_WIDTH / 2, y);
        }
    }
}
