#include "GameGUI.h"

GameGUI::GameGUI(Subject &subject) : subject(subject), scoreOnScreen(0), isHit(false)
{
    this->subject.AddObserver(this);
}

GameGUI::~GameGUI()
{
    SDL_DestroyRenderer(render);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

void GameGUI::Init(float width_x, float height_y)
{
    surface = TTF_RenderText_Solid(font, "0", {0xFF, 0xFF, 0xFF, 0xFF});
    texture = SDL_CreateTextureFromSurface(render, surface);

    SDL_QueryTexture(texture, nullptr, nullptr, &entity.w, &entity.h);

    entity.x = width_x;
    entity.y = height_y;
}

void GameGUI::Render(SDL_Renderer *render)
{
    SDL_RenderCopy(render, texture, nullptr, &entity);
}

void GameGUI::InitFont(TTF_Font *font)
{
    this->font = font;
}

void GameGUI::InitRenderer(SDL_Renderer *render)
{
    this->render = render;
}

void GameGUI::Update()
{
    scoreOnScreen++;

    SetScore(scoreOnScreen);
}

void GameGUI::SetHit(bool hit)
{
    isHit = hit;
}

bool GameGUI::GetHit() const
{
    return isHit;
}

void GameGUI::SetScore(const int &score)
{
    /* Clear data */
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    surface = TTF_RenderText_Solid(font, std::to_string(score).c_str(), {0xFF, 0xFF, 0xFF, 0xFF});
    texture = SDL_CreateTextureFromSurface(render, surface);

    SDL_QueryTexture(texture, nullptr, nullptr, &entity.w, &entity.h);
}
