#pragma once
#include "Entity.h"
#include "CoreDefinition.h"
#include <SDL_ttf.h>
#include <string>

class GameGUI : public Entity
{
public:
    GameGUI();
    virtual ~GameGUI();

	TTF_Font*       font;
    SDL_Renderer*   render;
	SDL_Surface*    surface;
	SDL_Texture*    texture;
    SDL_Rect        entity;
    
    float posX;
    float posY;

    void InitFont(TTF_Font* font);
    void InitRenderer(SDL_Renderer* render);

    void SetScore(int score);

    virtual void Init(float width_x, float height_y);
    virtual void Update(float& dt);
    virtual void Render(SDL_Renderer* render);
};

