#pragma once
#include "Ball.h"
#include "Enemy.h"
#include "GameField.h"
#include "GameGUI.h"
#include "Player.h"
#include "SoundsComponent.h"
#include <chrono>

class Game
{
  private:
    /* SDL components */
    SDL_Window *window;
    SDL_Surface *screenSurface;
    SDL_Renderer *render;
    SDL_Event event;
    TTF_Font *gameFont;

    /* Game components */
    Ball *ball;
    Player *player;
    Enemy *enemy;
    SoundsComponent *sounds;

    GameField field;

    Subject *subject;
    GameGUI *scorePlayer;
    GameGUI *scorEnemy;

    bool isRunning;
    float dt;

    /* Initialize */
    void InitComponents();
    bool InitWindow();
    void InitStates();
    void InitFont();
    void InitSounds();

  public:
    Game();
    virtual ~Game();

    /* Regular */
    void OnKeyPressed(SDL_Event &event);
    void OnKeyReleased(SDL_Event &event);

    void Cleanup();
    void PollEvent();
    void Update();
    void Render();
    void Run();
};
