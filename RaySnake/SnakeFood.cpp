#include "SnakeFood.h"
#include "raylib.h"
#include "raymath.h"
#include "GameTypes.h"

SnakeFood::SnakeFood()
{
	Image FoodImage = LoadImage("../Graphics/PixelApple.png");
	FoodTexture = LoadTextureFromImage(FoodImage);
	UnloadImage(FoodImage);
}

SnakeFood::~SnakeFood()
{
	UnloadTexture(FoodTexture);
}

void SnakeFood::Draw() 
{
    DrawTexture(FoodTexture, OFFSET + int(Location.x) * BOX_SIZE, OFFSET + int(Location.y) * BOX_SIZE, WHITE);
}

void SnakeFood::SetRandLocation(const std::deque<Vector2>& SnakeBody)
{
    Vector2 NewLocation = GetRandLocation();

    while (CheckCollisionWithSnake(SnakeBody, NewLocation))
    {
        NewLocation = GetRandLocation();
    }

    Location = NewLocation;
}

Vector2 SnakeFood::GetRandLocation()
{
    float RandomX = float(GetRandomValue(0, BOX_COUNT - 1));
    float RandomY = float(GetRandomValue(0, BOX_COUNT - 1));
    return Vector2{RandomX, RandomY};
}

bool SnakeFood::CheckCollisionWithSnake(const std::deque<Vector2>& SnakeBody, const Vector2& Location)
{
    for (const Vector2 BodyPart : SnakeBody)
    {
        if (Vector2Equals(BodyPart, Location))
        {
            return true;
        }
    }
    return false;
}
