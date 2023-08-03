#pragma once

#include "raylib.h"

const int BOX_SIZE = 40;
const int BOX_COUNT = 25;
const int OFFSET = 80;
const int WINDOW_SIZE = (2 * OFFSET) + (BOX_SIZE * BOX_COUNT);
const float DELAY_SNAKE_UPDATE = 0.15f;
const Color GREEN_BORDER = Color{112, 164, 66, 255};
const Color GREEN_BACKGROUND = Color{54, 141, 99, 255};
const Color GREEN_MAIN = Color{0, 204, 0, 255};
const Color ORANGE_HEAD = Color{255, 108, 0, 255};
