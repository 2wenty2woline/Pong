#pragma once
#include <SDL.h>

class Entity
{
public:
    
    virtual void Init(float width_x, float height_y) = 0;

    virtual void Update(float& dt) = 0;

    virtual void Render(SDL_Renderer* render) = 0;
};

