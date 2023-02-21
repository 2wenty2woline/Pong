#include "SoundsComponent.h"

SoundsComponent::SoundsComponent() : paddleHitSound(nullptr), wallHitSound(nullptr)
{
    paddleHitSound = new Mix_Chunk;
    wallHitSound = new Mix_Chunk;
}

SoundsComponent::~SoundsComponent()
{
    Mix_FreeChunk(paddleHitSound);
    Mix_FreeChunk(wallHitSound);

    soundsList.clear();
}

void SoundsComponent::Update()
{
}

void SoundsComponent::Init()
{
    if (paddleHitSound == nullptr)
    {
        return;
    }

    if (wallHitSound == nullptr)
    {
        return;
    }

    /* Add Sounds */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    /* Initialize sound effects */
    paddleHitSound = Mix_LoadWAV("Sounds/pong.wav");
    wallHitSound = Mix_LoadWAV("Sounds/wall_hit.wav");

    soundsList.push_back(paddleHitSound);
    soundsList.push_back(wallHitSound);
}
