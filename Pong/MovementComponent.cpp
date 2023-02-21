#include "MovementComponent.h"

MovementComponent::MovementComponent()
{
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::Move(const float &dt, const float &speed, float &posX, float &posY) const
{
    if (typeOfDirection == TypeOfDirection::UP)
    {
        posY -= speed * dt;
    }
    else if (typeOfDirection == TypeOfDirection::DOWN)
    {
        posY += speed * dt;
    }

    if (typeOfDirection == TypeOfDirection::RIGHT)
    {
        posX += speed * dt;
    }
    else if (typeOfDirection == TypeOfDirection::LEFT)
    {
        posX -= speed * dt;
    }

    switch (typyOfHit)
    {
    case TypeOfHit::NONE: {
        if (directionUpDown == TypeOfDirection::DOWN)
        {
            posY += speed * dt;
        }
        else if (directionUpDown == TypeOfDirection::UP)
        {
            posY -= speed * dt;
        }
        break;
    }
    case TypeOfHit::TOP: {
        posY -= speed * dt;
        break;
    }
    case TypeOfHit::BOTTOM: {
        posY += speed * dt;
        break;
    }
    case TypeOfHit::MIDDLE: {
        break;
    }
    default:
        break;
    }
}
