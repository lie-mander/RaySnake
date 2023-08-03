#include "GameMode.h"
#include "raylib.h"

GameMode::GameMode()
{
    Image BackgroundImage = LoadImage("../Graphics/Grass.png");
    Background = LoadTextureFromImage(BackgroundImage);
    UnloadImage(BackgroundImage);
}

GameMode::~GameMode()
{
    UnloadTexture(Background);
}

void GameMode::HandleEvents()
{
    if (IsKeyDown(KEY_SPACE))
    {
        bNeedPressKeyToStart = false;
    }

    SnakePlayer.HandleEvents();
}

void GameMode::Update()
{
    if (bNeedPressKeyToStart) return;

    if (!SnakePlayer.Update(Food))
    {
        bNeedPressKeyToStart = true;
        Restart();
    }
}

void GameMode::Draw()
{
    DrawTexture(Background, OFFSET, OFFSET, WHITE);
    SnakePlayer.Draw();
    Food.Draw();
    DrawRectangleLinesEx(Rectangle{OFFSET, OFFSET, (BOX_SIZE * BOX_COUNT), (BOX_SIZE * BOX_COUNT)}, 3, GREEN_BORDER);
    DrawText("RaySnake", OFFSET, OFFSET * 0.1, 60, ORANGE_HEAD);
    DrawText(TextFormat("Score: %i", SnakePlayer.GetScore()), OFFSET, WINDOW_SIZE - OFFSET + (OFFSET * 0.1), 60, ORANGE_HEAD);
}

void GameMode::Restart()
{
    Food.SetRandLocation(SnakePlayer.GetBody());
    SnakePlayer.Restart();
}
