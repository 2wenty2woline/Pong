#pragma once
#include <SDL_mixer.h>
#include <vector>

class SoundsComponent
{
  public:
    SoundsComponent();
    virtual ~SoundsComponent();

    void Update();
    void Init();

    std::vector<Mix_Chunk *> soundsList;
    Mix_Chunk *paddleHitSound;
    Mix_Chunk *wallHitSound;
};
