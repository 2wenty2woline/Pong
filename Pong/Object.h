#pragma once
#include "Entity.h"

class Object : public Entity
{
public:
    Object();
    virtual ~Object();

    SDL_Rect entity;

    float posX;
    float posY;
    float speed;

    virtual void Move(const int& direction, const float& dt);
    virtual void Init(float width_x, float height_y) override;
    virtual void Update(float& dt) override;
    virtual void Render(SDL_Renderer* render) override;
};
