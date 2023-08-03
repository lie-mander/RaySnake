#pragma once

#include "raylib.h"
#include "GameTypes.h"
#include <deque>

class SnakeFood;

class Snake
{
public:
    void HandleEvents();
    bool Update(SnakeFood& Food);  // Returns false if snake death
    void Draw();
    void Restart();

    int GetScore() const { return Score; }
    std::deque<Vector2> GetBody() const { return Body; }

private:
    std::deque<Vector2> Body = {
        Vector2{(BOX_COUNT / 2), BOX_COUNT / 2}, Vector2{(BOX_COUNT / 2) - 1, BOX_COUNT / 2}, Vector2{(BOX_COUNT / 2) - 2, BOX_COUNT / 2}};
    Vector2 Direction = Vector2{1, 0};

    int Score = 0;

    void MoveInDirecation();
    void AddBoxIfAteFood(SnakeFood& Food);
    bool CheckCollisionWithWalls();
    bool CheckCollisionWithTail();

    // Timer for not-spamming WASD
    bool bStartDelayControll = false;
    float LastControllTime = 0.f;

    bool HandleControllTimer();
    void StartControllTimer();

    // Timer for update movement
    float LastUpdateTime = 0.0;

    bool CanUpdate();
};
