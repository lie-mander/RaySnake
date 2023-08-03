#pragma once

#include "raylib.h"
#include <deque>

class SnakeFood
{
public:
    SnakeFood();
    ~SnakeFood();

    void Draw();

    Vector2 GetLocation() const { return Location; }
    void SetRandLocation(const std::deque<Vector2>& SnakeBody);

private:
    Vector2 Location{0, 0};
    Texture2D FoodTexture;

    Vector2 GetRandLocation();
    bool CheckCollisionWithSnake(const std::deque<Vector2>& SnakeBody, const Vector2& Location);
};
