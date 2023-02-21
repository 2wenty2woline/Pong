#pragma once
#include "Observer.h"
#include "Subject.h"
#include <string>

class GameGUI : public Observer
{
  private:
    Subject &subject;

    bool isHit;
    int32_t scoreOnScreen;

  public:
    GameGUI(Subject &subject);
    virtual ~GameGUI();

    TTF_Font *font;
    SDL_Renderer *render;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect entity;

    void InitFont(TTF_Font *font);
    void InitRenderer(SDL_Renderer *render);

    void SetScore(const int &score);

    void Init(float width_x, float height_y) override;
    void Render(SDL_Renderer *render) override;
    void SetHit(bool hit) override;
    bool GetHit() const override;
    void Update() override;
};
