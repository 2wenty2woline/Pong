#pragma once
#include "Object.h"
#include "Paddle.h"
#include <string>
#include <iostream>
#include "MovementComponent.h"

class Ball: public Object
{
private:
    Ball();
    virtual ~Ball();

    /* Delete copy constructor/operator */
    Ball(const Ball&) = delete;
    Ball& operator=(const Ball&) = delete;

public:

    /* Singleton */
    static Ball* GetInstance();

	MovementComponent* movementComponent;

	bool CheckCollisionObjcet(Ball* ball, Paddle* entity);
	void CheckTypeOfHit(Ball* ball, Paddle* entity);
	bool CheckCollisionWall(Ball* ball);

    virtual void Move(const int& direction, const float& dt) override;
    virtual void Init(float width_x, float height_y);
    virtual void Update(float& dt);
    virtual void Render(SDL_Renderer* render);
};
