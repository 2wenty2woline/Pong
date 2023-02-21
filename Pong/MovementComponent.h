#pragma once

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

/** Movement component changes the object location. */
class MovementComponent
{
  public:
    MovementComponent();
    virtual ~MovementComponent();

    TypeOfHit typyOfHit = TypeOfHit::NONE;
    TypeOfDirection typeOfDirection = TypeOfDirection::NONE;
    TypeOfDirection directionUpDown = TypeOfDirection::NONE;

    void Move(const float &dt, const float &speed, float &posX, float &posY) const;
};
