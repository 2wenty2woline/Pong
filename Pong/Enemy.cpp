#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::SetTarget(Object &ball)
{
    target = &ball;
}

void Enemy::Init(float width_x, float height_y)
{
    Paddle::Init(width_x, height_y);
}

void Enemy::Update(float &dt)
{
    Paddle::Update(dt);

    /* Change direction */
    if (target->posY + constantState::BALL_HEIGHT >= posY + constantState::PADDLE_HEIGHT)
    {
        movementComponent->typeOfDirection = TypeOfDirection::DOWN;

        /* Move Enemy */
        Move(dt);
    }
    else if (target->posY <= posY)
    {
        movementComponent->typeOfDirection = TypeOfDirection::UP;

        /* Move Enemy */
        Move(dt);
    }
}

void Enemy::Render(SDL_Renderer *render)
{
    Paddle::Render(render);
}
