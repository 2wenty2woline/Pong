#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(float width_x, float height_y)
{
    Paddle::Init(width_x, height_y);
}

void Player::Update(float &dt)
{
    Paddle::Update(dt);

    /* Move Player */
    Move(dt);
}

void Player::Render(SDL_Renderer *render)
{
    Paddle::Render(render);
}
