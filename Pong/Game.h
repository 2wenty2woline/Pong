#pragma once
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <chrono>
#include "CoreDefinition.h"
#include "GameField.h"
#include "Ball.h"
#include "Paddle.h"
#include "Player.h"
#include "Enemy.h"
#include "GameGUI.h"
#include "SoundsComponent.h"
#include "MovementComponent.h"

enum FRKey
{
	UP,
	DOWN,
	COUNT
};

class Game
{
private:

    /* SDL components */
	SDL_Window*         window;
	SDL_Surface*        screenSurface;
    SDL_Renderer*       render;
    SDL_Event           event;
    TTF_Font*           gameFont;

    bool                running;
    bool                buttons[2];
    int                 playerScoreOnScreen;
    int                 enemyScoreOnScreen;
    float               dt;

    /* Game components */
    Ball*               ball;
    Player*             player;
    Enemy*              enemy;
    SoundsComponent*    sounds;

    GameField           field;
    GameGUI             scorePlayer;
    GameGUI             scorEnemy;
    

    /* Initialize */
    void InitComponents();
    void InitWindow();
    void InitStates();
    void InitFont();
    void InitSounds();

public:
    Game();
    virtual ~Game();

    /* Regular */
    void OnKeyPressed(SDL_Event& event);
    void OnKeyReleased(SDL_Event& event);
    
    void Cleanup();
    
    /* Update */ 
    void Update();

    /* Render */
    void Render();

    /* Core */
    void Run();
};
