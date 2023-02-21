#pragma once
#include "Object.h"
#include "Paddle.h"

class Ball : public Object
{
  private:
    Ball();
    virtual ~Ball();

    Ball(const Ball &) = delete;
    Ball &operator=(const Ball &) = delete;

  public:
    static Ball *GetInstance();

    bool CheckCollisionObjcet(Ball *ball, Paddle *entity);
    void CheckTypeOfHit(Ball *ball, Paddle *entity);
    bool CheckCollisionWall(Ball *ball);

    virtual void Init(float width_x, float height_y) override;
    virtual void Update(float &dt) override;
    virtual void Render(SDL_Renderer *render) override;
};
