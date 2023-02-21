#pragma once
#include "Entity.h"
#include "MovementComponent.h"

class Object : public Entity
{
  public:
    Object();
    virtual ~Object();

    MovementComponent *movementComponent = nullptr;

    SDL_Rect rect;
    float posX;
    float posY;
    float speed;

    void Move(const float &dt);
};
