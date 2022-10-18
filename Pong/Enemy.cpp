#include "Enemy.h"

Enemy::Enemy() : movementComponent(nullptr)
{
	movementComponent = new MovementComponent;
}

Enemy::~Enemy()
{
    delete movementComponent;
}

void Enemy::Move(const int& direction, const float& dt)
{
    if (direction == 0)
	{
		movementComponent->Move(this, dt);

		posY += speed * dt;
	}
	else if (direction == 1)
	{
		movementComponent->Move(this, dt);

		posY -= speed * dt;
	}
}

void Enemy::Init(float width_x, float height_y)
{
    Paddle::Init(width_x, height_y);

    speed = constantState::PADDLE_SPEED;
}

void Enemy::Update(float& dt)
{
    Paddle::Update(dt);
}

void Enemy::Render(SDL_Renderer* render)
{
    Paddle::Render(render);
}
