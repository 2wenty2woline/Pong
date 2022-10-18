#include "GameField.h"

GameField::GameField()
{
}

GameField::~GameField()
{
}

void GameField::Render(SDL_Renderer* render)
{
	/* Set the draw color to be white */
	SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);

	/* Draw the line */
	for (int y = 0; y < 720; ++y)
	{
		if (y % 5)
		{
			SDL_RenderDrawPoint(render, constantState::WINDOW_WIDTH / 2, y);
		}
	}
}
