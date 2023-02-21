#pragma once
#include "CoreDefinition.h"
#include <SDL.h>
#include <SDL_ttf.h>

class Entity
{
  public:
    virtual void Init(float width_x, float height_y) = 0;

    virtual void Update(float &dt) = 0;

    virtual void Render(SDL_Renderer *render) = 0;
};
