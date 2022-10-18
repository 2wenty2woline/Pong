#pragma once
#include "Paddle.h"

class Enemy : public Paddle 
{
public:

    Enemy();
    virtual ~Enemy();

    MovementComponent* movementComponent;

    virtual void Move(const int& direction, const float& dt) override;

    virtual void Init(float width_x, float height_y) override;
    virtual void Update(float& dt) override;
    virtual void Render(SDL_Renderer* render) override;
};
