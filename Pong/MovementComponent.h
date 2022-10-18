#pragma once
#include "Object.h"
#include "CoreDefinition.h"
#include "Entity.h"

enum class TypeOfDirection
{
	NONE,
	RIGHT,
	LEFT,
	UP,
	DOWN,
	COUNT
};

enum class TypeOfHit
{
	NONE,
	TOP,
	MIDDLE,
	BOTTOM,
	COUNT
};

class MovementComponent
{
public:
    MovementComponent();
    virtual ~MovementComponent();

	TypeOfHit typyOfHit;
	TypeOfDirection typeOfDirection;
	TypeOfDirection directionUpDown;

	void Move(Object* object, const float& dt);
};
