#include "Snake.h"
#include "raylib.h"
#include "raymath.h"
#include "GameTypes.h"
#include "SnakeFood.h"

void Snake::Draw()
{
    // Snake`s head has another green color
    bool bHead = true;
    for (const Vector2 BodyPart : Body)
    {
        if (bHead)
        {
            DrawRectangleRounded(
                Rectangle{BodyPart.x * BOX_SIZE + OFFSET, BodyPart.y * BOX_SIZE + OFFSET, BOX_SIZE, BOX_SIZE}, 0.7f, 0, ORANGE_HEAD);
            DrawRectangleRoundedLines(
            Rectangle{BodyPart.x * BOX_SIZE + OFFSET, BodyPart.y * BOX_SIZE + OFFSET, BOX_SIZE, BOX_SIZE}, 0.7f, 0, 5.f, BLACK);
            bHead = false;
            continue;
        }

        // Draw body, not head
        DrawRectangleRounded(
            Rectangle{BodyPart.x * BOX_SIZE + OFFSET, BodyPart.y * BOX_SIZE + OFFSET, BOX_SIZE, BOX_SIZE}, 0.7f, 0, ORANGE);
        DrawRectangleRoundedLines(
            Rectangle{BodyPart.x * BOX_SIZE + OFFSET, BodyPart.y * BOX_SIZE + OFFSET, BOX_SIZE, BOX_SIZE}, 0.7f, 0, 5.f, BLACK);
    }
}

bool Snake::Update(SnakeFood& Food)
{
    if (!CanUpdate()) return true;

    MoveInDirecation();
    AddBoxIfAteFood(Food);

    if (CheckCollisionWithWalls() || CheckCollisionWithTail())
    {
        return false;
    }

    return true;
}

void Snake::Restart()
{
    Body = {
        Vector2{(BOX_COUNT / 2), BOX_COUNT / 2}, Vector2{(BOX_COUNT / 2) - 1, BOX_COUNT / 2}, Vector2{(BOX_COUNT / 2) - 2, BOX_COUNT / 2}};
    Direction = Vector2{1, 0};
    Score = 0;
}

void Snake::MoveInDirecation()
{
    Body.push_front(Vector2Add(Body[0], Direction));
    Body.pop_back();
}

void Snake::AddBoxIfAteFood(SnakeFood& Food)
{
    if (Vector2Equals(Body[0], Food.GetLocation()))
    {
        ++Score;
        Food.SetRandLocation(Body);
        Body.push_back(Vector2Add(Body.back(), Direction));
    }
}

bool Snake::CheckCollisionWithWalls()
{
    return Body[0].x >= BOX_COUNT || Body[0].x <= -1 || Body[0].y >= BOX_COUNT || Body[0].y <= -1;
}

bool Snake::CheckCollisionWithTail()
{
    std::deque<Vector2> BodyWithoutHead = Body;
    BodyWithoutHead.pop_front();

    for (const Vector2 BodyPart : BodyWithoutHead)
    {
        if (Vector2Equals(Body[0], BodyPart))
        {
            return true;
        }
    }
    return false;
}

void Snake::HandleEvents()
{
    if (!HandleControllTimer()) return;

    // Top / Down movement
    if (IsKeyDown(KEY_W) && !Vector2Equals(Direction, Vector2{0, 1}))
    {
        Direction = Vector2{0, -1};
        StartControllTimer();
    }
    else if (IsKeyDown(KEY_S) && !Vector2Equals(Direction, Vector2{0, -1}))
    {
        Direction = Vector2{0, 1};
        StartControllTimer();
    }

    // Right / Left movement
    else if (IsKeyDown(KEY_D) && !Vector2Equals(Direction, Vector2{-1, 0}))
    {
        Direction = Vector2{1, 0};
        StartControllTimer();
    }
    else if (IsKeyDown(KEY_A) && !Vector2Equals(Direction, Vector2{1, 0}))
    {
        Direction = Vector2{-1, 0};
        StartControllTimer();
    }
}

bool Snake::HandleControllTimer()
{
    if (bStartDelayControll)
    {
        if (GetTime() - LastControllTime >= -0.25f)
        {
            bStartDelayControll = false;
            return true;
        }
        return false;
    }
    return true;
}

void Snake::StartControllTimer()
{
    bStartDelayControll = true;
    LastControllTime = float(GetTime());
}

bool Snake::CanUpdate()
{
    if (GetTime() - LastUpdateTime > DELAY_SNAKE_UPDATE)
    {
        LastUpdateTime = float(GetTime());
        return true;
    }
    return false;
}
