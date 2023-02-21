#pragma once
#include "Paddle.h"

class Player : public Paddle
{
  public:
    Player();
    virtual ~Player();

    void Init(float width_x, float height_y) override;
    void Update(float &dt) override;
    void Render(SDL_Renderer *render) override;
};
