#pragma once
#include <SDL.h>
#include "CoreDefinition.h"

class GameField
{
private:

public:
    GameField();
	virtual ~GameField();

    void Render(SDL_Renderer* render);
};
