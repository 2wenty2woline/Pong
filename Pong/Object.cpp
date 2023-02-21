#include "Object.h"

Object::Object() : posX(0.f), posY(0.f), speed(0.f), movementComponent(nullptr)
{
    movementComponent = new MovementComponent();
}

Object::~Object()
{
    delete movementComponent;
}

void Object::Move(const float &dt)
{
    movementComponent->Move(dt, speed, posX, posY);
}
