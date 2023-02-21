#pragma once
#include "Entity.h"

class GameField : public Entity
{
  private:
  public:
    GameField();
    virtual ~GameField();

    virtual void Init(float width_x, float height_y) override;

    virtual void Update(float &dt) override;

    virtual void Render(SDL_Renderer *render) override;
};
