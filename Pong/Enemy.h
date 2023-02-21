#pragma once
#include "Paddle.h"

class Enemy : public Paddle
{
  private:
    Object *target = nullptr;

  public:
    Enemy();
    virtual ~Enemy();

    void SetTarget(Object &ball);

    virtual void Init(float width_x, float height_y) override;
    virtual void Update(float &dt) override;
    virtual void Render(SDL_Renderer *render) override;
};
