#include "Ball.h"

Ball::Ball() : movementComponent(nullptr)
{
	movementComponent = new MovementComponent;
}

Ball::~Ball()
{
	delete movementComponent;
}

Ball* Ball::GetInstance()
{
	static Ball* singletonBall;

	if(singletonBall == nullptr)
	{
        singletonBall = new Ball;
    }
    return singletonBall;
}

bool Ball::CheckCollisionObjcet(Ball* ball, Paddle* entity)
{
	if (ball == nullptr)
	{
		return false;
	}

	if (entity == nullptr)
	{
		return false;
	}

	float entityLeft = entity->posX;
	float entityRight = entityLeft + constantState::PADDLE_WIDTH;
	float entityTop = entity->posY;
	float entityBottom = entityTop + constantState::PADDLE_HEIGHT;

	float ballLeft = ball->posX;
	float ballRight = ballLeft + constantState::BALL_WIDTH;
	float ballTop = ball->posY;
	float ballBottom = ballTop + constantState::BALL_HEIGHT;

	if ((ballLeft <= entityRight) &&
		(ballRight >= entityLeft) &&
		(ballTop <= entityBottom) &&
		(ballBottom >= entityTop))
		
	{
		/* Check what type of hit */
		CheckTypeOfHit(ball, entity);
		return true;
	}

	return false;
}

void Ball::CheckTypeOfHit(Ball* ball, Paddle* entity)
{
	if (ball == nullptr)
	{
		return;
	}
	
	if (entity == nullptr)
	{
		return;
	}

	float entityLeft = entity->posX;
	float entityRight = entityLeft + constantState::PADDLE_WIDTH;
	float entityTop = entity->posY;
	float entityBottom = entityTop + constantState::PADDLE_HEIGHT;

	float ballLeft = ball->posX;
	float ballRight = ballLeft + constantState::BALL_WIDTH;
	float ballTop = ball->posY;
	float ballBottom = ballTop + constantState::BALL_HEIGHT;

	float paddleRangeUpper = entityTop + (constantState::PADDLE_HEIGHT / 2.0f);
	float paddleRangeBottom = entityBottom - (constantState::PADDLE_HEIGHT / 3.0f);

	if ((entityTop <= ballBottom) &&
		(ballBottom <= paddleRangeUpper))
	{
		movementComponent->typyOfHit = TypeOfHit::TOP;
	}
	else if ((ballTop >= paddleRangeUpper) &&
			 (ballBottom <= paddleRangeBottom))
	{
		movementComponent->typyOfHit = TypeOfHit::MIDDLE;
	}
	else if ((ballTop <= entityBottom) &&
			 (ballBottom >= paddleRangeBottom))
	{
		movementComponent->typyOfHit = TypeOfHit::BOTTOM;
	}
	else
	{
		movementComponent->typyOfHit = TypeOfHit::NONE;
	}
}

bool Ball::CheckCollisionWall(Ball* ball)
{
	if (ball == nullptr)
	{
		return false;
	}

	if (ball->posY <= 0.0f)
	{
		movementComponent->directionUpDown = TypeOfDirection::DOWN;
		movementComponent->typyOfHit = TypeOfHit::NONE;
		return true;
	}
	else if (ball->posY + constantState::BALL_HEIGHT >= constantState::WINDOW_HEIGHT)
	{
		movementComponent->directionUpDown = TypeOfDirection::UP;
		movementComponent->typyOfHit = TypeOfHit::NONE;
		return true;
	}
	return false;
}

void Ball::Move(const int& direction, const float& dt)
{
	if (movementComponent->typeOfDirection == TypeOfDirection::RIGHT)
	{
		posX += speed * dt;
	}
	else if(movementComponent->typeOfDirection == TypeOfDirection::LEFT)
	{
		posX -= speed * dt;
	}

	switch (movementComponent->typyOfHit)
	{
	case TypeOfHit::NONE:
	{
		if (movementComponent->directionUpDown == TypeOfDirection::DOWN)
		{
			posY += speed * dt;
		}
		else if (movementComponent->directionUpDown == TypeOfDirection::UP)
		{
			posY -= speed * dt;
		}
		break;
	}
	case TypeOfHit::TOP:
	{
		posY -= speed * dt;
		break;
	}
	case TypeOfHit::BOTTOM:
	{
		posY += speed * dt;
		break;
	}
	case TypeOfHit::MIDDLE:
	{
		break;
	}
	default:
		break;
	}
}

void Ball::Init(float width_x, float height_y)
{
	speed = constantState::BALL_SPEED;
	movementComponent->typeOfDirection = TypeOfDirection::RIGHT;
	movementComponent->typyOfHit = TypeOfHit::NONE;
	movementComponent->directionUpDown = TypeOfDirection::NONE;

	posX = width_x;
	posY = height_y;
	entity.x = posX;
	entity.y = posY;
	entity.w = constantState::BALL_WIDTH;
	entity.h = constantState::BALL_HEIGHT;
}

void Ball::Update(float& dt)
{
}

void Ball::Render(SDL_Renderer* render)
{
	entity.x = posX;
	entity.y = posY;

	SDL_RenderFillRect(render, &entity);
}
