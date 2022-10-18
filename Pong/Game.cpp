#include "Game.h"

void Game::InitComponents()
{
	window				= nullptr;
	screenSurface		= nullptr;
	render				= nullptr;
	gameFont			= nullptr;

	running				= true;
	dt					= 0.0f;
	playerScoreOnScreen = 0;
    enemyScoreOnScreen	= 0;

	ball				= Ball::GetInstance();
	player				= new Player;
	enemy				= new Enemy;
	sounds				= new SoundsComponent;
}

void Game::InitWindow()
{
	if(SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("GAME::INITWINDOW::SDL could not initialize! % s\n", SDL_GetError());
	}
	TTF_Init();

	window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
							  constantState::WINDOW_WIDTH, constantState::WINDOW_HEIGHT,
						SDL_WINDOW_SHOWN);
	screenSurface = SDL_GetWindowSurface(window);
	render = SDL_CreateRenderer(window, -1, 0);
}

void Game::InitStates()
{
	/* GUI  Player */
	scorePlayer.InitFont(gameFont);
	scorePlayer.InitRenderer(render);
	scorePlayer.Init(constantState::WINDOW_WIDTH / 4, 20);

	/* GUI  Enemy */
	scorEnemy.InitFont(gameFont);
	scorEnemy.InitRenderer(render);
	scorEnemy.Init(3 * constantState::WINDOW_WIDTH / 4, 20);

	/* Ball */
	ball->Init(constantState::WINDOW_WIDTH / 2.0f - constantState::BALL_WIDTH / 2.0f, constantState::WINDOW_HEIGHT / 2.0f - constantState::BALL_HEIGHT / 2.0f);

	/* Player */
	player->Init(constantState::PADDLE_WIDTH, constantState::WINDOW_HEIGHT / 2.0f - constantState::PADDLE_HEIGHT / 2.0f);

	/* Enemy */
	enemy->Init(constantState::WINDOW_WIDTH - constantState::PADDLE_WIDTH * 2, constantState::WINDOW_HEIGHT / 2.0f - constantState::PADDLE_HEIGHT / 2.0f);
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
}

void Game::OnKeyPressed(SDL_Event& event)
{
	if (event.key.keysym.sym == SDLK_ESCAPE)
	{
		running = false;
	}
	else if (event.key.keysym.sym == SDLK_w)
	{
		buttons[FRKey::UP] = true;
	}
	else if (event.key.keysym.sym == SDLK_s)
	{
		buttons[FRKey::DOWN] = true;
	}
}
void Game::OnKeyReleased(SDL_Event& event)
{
	if (event.key.keysym.sym == SDLK_w)
	{
		buttons[FRKey::UP] = false;
	}
	else if (event.key.keysym.sym == SDLK_s)
	{
		buttons[FRKey::DOWN] = false;
	}
}

void Game::Cleanup()
{
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	TTF_CloseFont(gameFont);
	SDL_Quit();
}

void Game::Update()
{
	if (running == false)
	{
		Cleanup();
		return;
	}

	/* Update the Player */
	player->Update(dt);

	/* UpDate the Enemy */
	enemy->Update(dt);

	/* Update the Ball */
	if (ball != nullptr)
	{
		ball->Update(dt);
	}
	

	while (SDL_PollEvent(&event))
	{
		
		switch (event.type)
		{
		case SDL_QUIT:
		{
			running = false;
			break;
		}
		case SDL_KEYDOWN:
		{
			/*  Key pressed */
			OnKeyPressed(event);
			break;
		}
		case SDL_KEYUP:
		{
			/* Key released */
			OnKeyReleased(event);
			break;
		}
		default:
			break;
		}

		/* Move Player */
		if (buttons[FRKey::UP])
		{
			player->Move(FRKey::UP, dt);
		}
		else if (buttons[FRKey::DOWN])
		{
			player->Move(FRKey::DOWN, dt);
		}
	}

	/* Move Enemy */
	if (ball->posY + constantState::BALL_HEIGHT >= enemy->posY + constantState::PADDLE_HEIGHT)
	{
		enemy->Move(FRKey::UP, dt);
	}
	if (ball->posY <= enemy->posY)
	{
		enemy->Move(FRKey::DOWN, dt);
	}

	/* Move Ball */
	ball->Move(true, dt);

	/* Sound Ball at wall */
	if (ball->CheckCollisionWall(ball))
	{
		Mix_PlayChannel(-1, sounds->wallHitSound, 0);
	}

	if (ball->CheckCollisionObjcet(ball, enemy))
	{
		/* Set direction */
		ball->movementComponent->typeOfDirection = TypeOfDirection::LEFT;

		/* Play sounds */
		Mix_PlayChannel(-1, sounds->soundsList[0], 0);
	}
	else if(ball->CheckCollisionObjcet(ball, player))
	{
		/* Set direction */
		ball->movementComponent->typeOfDirection = TypeOfDirection::RIGHT;

		/* Play sounds */
		Mix_PlayChannel(-1, sounds->soundsList[1], 0);
	}

	/* Ball reset */
	if ((ball->posX + constantState::BALL_WIDTH < 0.0f))
	{
		ball->Init(constantState::WINDOW_WIDTH / 2.0f - constantState::BALL_WIDTH / 2.0f, constantState::WINDOW_HEIGHT / 2.0f - constantState::BALL_HEIGHT / 2.0f);

		/* Set score */
		++playerScoreOnScreen;
		scorePlayer.SetScore(playerScoreOnScreen);
	}
	else if (ball->posX > constantState::WINDOW_WIDTH)
	{
		/* Set score */
		++enemyScoreOnScreen;
		scorEnemy.SetScore(enemyScoreOnScreen);
	}
}

void Game::Render()
{
	if (running == false)
	{
		return;
	}

	/* Clear the window to black */
	SDL_SetRenderDrawColor(render, 0x0, 0x0, 0x0, 0xFF);
	SDL_RenderClear(render);
	
	/* Game Field */
	field.Render(render);

	/* GUI*/
	scorePlayer.Render(render);
	scorEnemy.Render(render);

	/* Ball */
	ball->Render(render);

	/* Player */
	player->Render(render);

	/* Enemy */
	enemy->Render(render);

	/* Present the backbuffer */
	SDL_RenderPresent(render);
}

void Game::Run()
{
	while (running)
	{
		auto startTime = std::chrono::high_resolution_clock::now();

		Update();
		Render();

		auto stopTime = std::chrono::high_resolution_clock::now();
		dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
	}
}
