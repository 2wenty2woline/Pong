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
    entity.x = posX;
	entity.y = posY;
	entity.w = constantState::PADDLE_WIDTH;
	entity.h = constantState::PADDLE_HEIGHT;
}

void Paddle::Update(float& dt)
{
	if (posY < 0)
	{
		/* Reset */
		posY = 0;
	}
	else if (posY > (constantState::WINDOW_HEIGHT - constantState::PADDLE_HEIGHT))
	{
		/* Reset */
		posY = constantState::WINDOW_HEIGHT - constantState::PADDLE_HEIGHT;
	}
}

void Paddle::Render(SDL_Renderer* render)
{
	entity.x = posX;
	entity.y = posY;

	SDL_RenderFillRect(render, &entity);
}
