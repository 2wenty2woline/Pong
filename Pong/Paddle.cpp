#include "Paddle.h"

Paddle::Paddle()
{
}

Paddle::~Paddle()
{
}

void Paddle::Init(float width_x, float height_y)
{
    speed = constantState::PADDLE_SPEED;
    posX = width_x;
    posY = height_y;
    rect.x = posX;
    rect.y = posY;
    rect.w = constantState::PADDLE_WIDTH;
    rect.h = constantState::PADDLE_HEIGHT;
}

void Paddle::Update(float &dt)
{
    /* Reset */
    if (posY < 0)
    {
        posY = 0;
    }
    else if (posY > (constantState::WINDOW_HEIGHT - constantState::PADDLE_HEIGHT))
    {
        posY = constantState::WINDOW_HEIGHT - constantState::PADDLE_HEIGHT;
    }
}

void Paddle::Render(SDL_Renderer *render)
{
    rect.x = posX;
    rect.y = posY;

    SDL_RenderFillRect(render, &rect);
}
