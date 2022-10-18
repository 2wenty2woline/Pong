#include "Player.h"

Player::Player() : movementComponent(nullptr)
{
	movementComponent = new MovementComponent;
}

Player::~Player()
{
	delete movementComponent;
}

void Player::Move(const int& direction, const float& dt)
{
	if (direction == 0)
	{
		movementComponent->Move(this, dt);

		posY -= constantState::PADDLE_SPEED * dt;
	}
	else if (direction == 1)
	{
		movementComponent->Move(this, dt);

		posY += constantState::PADDLE_SPEED * dt;
	}
	else
	{
		speed = 0.0f;
	}
}

void Player::Init(float width_x, float height_y)
{
	Paddle::Init(width_x, height_y);

	speed = constantState::PADDLE_SPEED;
}

void Player::Update(float& dt)
{
	Paddle::Update(dt);
}

void Player::Render(SDL_Renderer* render)
{
	Paddle::Render(render);
}
