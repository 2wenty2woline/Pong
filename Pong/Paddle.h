#pragma once
#include "Object.h"

class Paddle : public Object
{
  public:
    Paddle();
    virtual ~Paddle();

    virtual void Init(float width_x, float height_y) override;
    virtual void Update(float &dt) override;
    virtual void Render(SDL_Renderer *render) override;
};
