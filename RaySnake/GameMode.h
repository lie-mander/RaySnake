#pragma once

#include "Snake.h"
#include "SnakeFood.h"
#include "raylib.h"

class GameMode
{
public:
    GameMode();
    ~GameMode();

    void HandleEvents();
    void Update();
    void Draw();

private:
    Snake SnakePlayer;
    SnakeFood Food;

    Texture2D Background;

    bool bNeedPressKeyToStart = true;
    void Restart();
};
