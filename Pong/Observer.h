#pragma once
#include "CoreDefinition.h"
#include <SDL.h>
#include <SDL_ttf.h>

class Observer
{
  public:
    virtual void Update() = 0;

    virtual void Init(float width_x, float height_y) = 0;

    virtual void Render(SDL_Renderer *render) = 0;

    virtual void SetHit(bool hit) = 0;

    virtual bool GetHit() const = 0;
};
