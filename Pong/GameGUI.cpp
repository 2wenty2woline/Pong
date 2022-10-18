#include "GameGUI.h"

GameGUI::GameGUI()
{
}

GameGUI::~GameGUI()
{
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void GameGUI::Init(float width_x, float height_y)
{
    surface = TTF_RenderText_Solid(font, "0", {0xFF, 0xFF, 0xFF, 0xFF});
	texture = SDL_CreateTextureFromSurface(render, surface);

	int width;
	int height;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

	entity.x = width_x;
	entity.y = height_y;
	entity.w = width;
	entity.h = height;
}

void GameGUI::Update(float& dt)
{
}

void GameGUI::Render(SDL_Renderer* render)
{
	SDL_RenderCopy(render, texture, nullptr, &entity);
}

void GameGUI::InitFont(TTF_Font* font)
{
	this->font = font;
}

void GameGUI::InitRenderer(SDL_Renderer* render)
{
	this->render = render;
}

void GameGUI::SetScore(int score)
{
	/* Clear data */
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);

	surface = TTF_RenderText_Solid(font, std::to_string(score).c_str(), {0xFF, 0xFF, 0xFF, 0xFF});
	texture = SDL_CreateTextureFromSurface(render, surface);

	int width, height;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	entity.w = width;
	entity.h = height;
}
