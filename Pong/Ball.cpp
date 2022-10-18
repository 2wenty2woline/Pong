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

	if ((ball->posX <= entity->posX + constantState::PADDLE_WIDTH) &&
		(ball->posX + constantState::PADDLE_WIDTH >= entity->posX) &&
		(ball->posY <= entity->posY + constantState::PADDLE_HEIGHT) &&
		(ball->posY + constantState::BALL_HEIGHT >= entity->posY))
		
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

	float paddleRangeUpper = entity->posY + ((constantState::PADDLE_HEIGHT / 3.0f));
	float paddleRangeBottom = entity->posY + constantState::PADDLE_HEIGHT - (constantState::PADDLE_HEIGHT / 3.0f);

	if ((entity->posY <= ball->posY + constantState::BALL_HEIGHT) &&
		(ball->posY + constantState::BALL_HEIGHT <= paddleRangeUpper + 10))
	{
		movementComponent->typyOfHit = TypeOfHit::TOP;
	}
	else if ((ball->posY >= paddleRangeUpper) &&
			 (ball->posY + constantState::BALL_HEIGHT <= paddleRangeBottom))
	{
		movementComponent->typyOfHit = TypeOfHit::MIDDLE;
	}
	else if ((ball->posY <= entity->posY + constantState::PADDLE_HEIGHT) &&
			 (ball->posY + constantState::BALL_HEIGHT >= paddleRangeBottom))
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
		movementComponent->directionUpDown	= TypeOfDirection::DOWN;
		movementComponent->typyOfHit		= TypeOfHit::NONE;
		return true;
	}
	else if (ball->posY + constantState::BALL_HEIGHT >= constantState::WINDOW_HEIGHT)
	{
		movementComponent->directionUpDown	= TypeOfDirection::UP;
		movementComponent->typyOfHit		= TypeOfHit::NONE;
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

	movementComponent->typeOfDirection	= TypeOfDirection::RIGHT;
	movementComponent->typyOfHit		= TypeOfHit::NONE;
	movementComponent->directionUpDown	= TypeOfDirection::NONE;

	posX		= width_x;
	posY		= height_y;
	entity.x	= posX;
	entity.y	= posY;
	entity.w	= constantState::BALL_WIDTH;
	entity.h	= constantState::BALL_HEIGHT;
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
