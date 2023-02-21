#include "Game.h"

void Game::InitComponents()
{
    window = nullptr;
    screenSurface = nullptr;
    render = nullptr;
    gameFont = nullptr;

    isRunning = true;
    dt = 1.0f;

    sounds = new SoundsComponent;
    ball = Ball::GetInstance();
    player = new Player;
    enemy = new Enemy;
    enemy->SetTarget(*ball);

    /* Observer */
    subject = new Subject;
    scorePlayer = new GameGUI(*subject);
    scorEnemy = new GameGUI(*subject);
}

bool Game::InitWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("GAME::INITWINDOW::SDL could not initialize! % s\n", SDL_GetError());
        return false;
    }
    TTF_Init();

    window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, constantState::WINDOW_WIDTH,
                              constantState::WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        return false;
    }

    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!render)
    {
        return false;
    }

    screenSurface = SDL_GetWindowSurface(window);
    if (!screenSurface)
    {
        return false;
    }

    return true;
}

void Game::InitStates()
{
    /* GUI  Player */
    scorePlayer->InitFont(gameFont);
    scorePlayer->InitRenderer(render);
    scorePlayer->Init(constantState::WINDOW_WIDTH / 4, 20);

    /* GUI  Enemy */
    scorEnemy->InitFont(gameFont);
    scorEnemy->InitRenderer(render);
    scorEnemy->Init(3 * constantState::WINDOW_WIDTH / 4, 20);

    /* Ball */
    ball->Init(constantState::WINDOW_WIDTH / 2.0f - constantState::BALL_WIDTH / 2.0f,
               constantState::WINDOW_HEIGHT / 2.0f - constantState::BALL_HEIGHT / 2.0f);

    /* Player */
    player->Init(constantState::PADDLE_WIDTH,
                 constantState::WINDOW_HEIGHT / 2.0f - constantState::PADDLE_HEIGHT / 2.0f);

    /* Enemy */
    enemy->Init(constantState::WINDOW_WIDTH - constantState::PADDLE_WIDTH * 2,
                constantState::WINDOW_HEIGHT / 2.0f - constantState::PADDLE_HEIGHT / 2.0f);
}

void Game::InitFont()
{
    gameFont = TTF_OpenFont("Fonts/16020_FUTURAM.ttf", 40);
}

void Game::InitSounds()
{
    sounds->Init();
}

Game::Game()
{
    InitComponents();
    InitWindow();
    InitFont();
    InitSounds();
    InitStates();
}

Game::~Game()
{
    delete enemy;
    delete player;
    delete sounds;

    Cleanup();
}

void Game::OnKeyPressed(SDL_Event &event)
{
    if (event.key.keysym.sym == SDLK_ESCAPE)
    {
        isRunning = false;
    }
    else if (event.key.keysym.sym == SDLK_w)
    {
        player->movementComponent->typeOfDirection = TypeOfDirection::UP;
    }
    else if (event.key.keysym.sym == SDLK_s)
    {
        player->movementComponent->typeOfDirection = TypeOfDirection::DOWN;
    }
}
void Game::OnKeyReleased(SDL_Event &event)
{
    if (event.key.keysym.sym == SDLK_w)
    {
        player->movementComponent->typeOfDirection = TypeOfDirection::NONE;
    }
    else if (event.key.keysym.sym == SDLK_s)
    {
        player->movementComponent->typeOfDirection = TypeOfDirection::NONE;
    }
}

void Game::Cleanup()
{
    TTF_CloseFont(gameFont);
    SDL_FlushEvents(SDL_USEREVENT, SDL_LASTEVENT);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void Game::PollEvent()
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT: {
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            /*  Key pressed */
            OnKeyPressed(event);
            break;
        }
        case SDL_KEYUP: {
            /* Key released */
            OnKeyReleased(event);
            break;
        }
        default:
            break;
        }
    }
}

void Game::Update()
{
    if (isRunning == false)
    {
        Cleanup();
        return;
    }

    /* Update game component */
    player->Update(dt);

    enemy->Update(dt);

    ball->Update(dt);

    /* Sound Ball at wall */
    if (ball->CheckCollisionWall(ball))
    {
        Mix_PlayChannel(-1, sounds->soundsList[1], 0);
    }

    /* Check collision */
    if (ball->CheckCollisionObjcet(ball, enemy))
    {
        ball->movementComponent->typeOfDirection = TypeOfDirection::LEFT;

        Mix_PlayChannel(-1, sounds->soundsList[0], 0);
    }
    else if (ball->CheckCollisionObjcet(ball, player))
    {
        ball->movementComponent->typeOfDirection = TypeOfDirection::RIGHT;

        Mix_PlayChannel(-1, sounds->soundsList[0], 0);
    }

    /* Reset ball and set Score observer */
    if ((ball->posX + constantState::BALL_WIDTH < 0.0f))
    {
        ball->Init(constantState::WINDOW_WIDTH / 2.0f - constantState::BALL_WIDTH / 2.0f,
                   constantState::WINDOW_HEIGHT / 2.0f - constantState::BALL_HEIGHT / 2.0f);

        /* Nitify all object */
        scorePlayer->SetHit(true);
        subject->Notify();
    }
    else if (ball->posX > constantState::WINDOW_WIDTH)
    {
        ball->Init(constantState::WINDOW_WIDTH / 2.0f - constantState::BALL_WIDTH / 2.0f,
                   constantState::WINDOW_HEIGHT / 2.0f - constantState::BALL_HEIGHT / 2.0f);

        /* Nitify all object */
        scorEnemy->SetHit(true);
        subject->Notify();
    }
}

void Game::Render()
{
    if (isRunning == false)
    {
        return;
    }

    /* Clear the window to black */
    SDL_SetRenderDrawColor(render, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(render);

    /* Game Field */
    field.Render(render);

    /* GUI*/
    scorePlayer->Render(render);
    scorEnemy->Render(render);

    /* Ball */
    ball->Render(render);

    /* Player */
    player->Render(render);

    /* Enemy */
    enemy->Render(render);

    SDL_RenderPresent(render);
}

void Game::Run()
{
    while (isRunning)
    {
        PollEvent();
        Update();
        Render();
    }
}
