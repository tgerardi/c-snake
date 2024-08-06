#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define GRID_SIZE 20

#include "raylib.h"
#include <vector>
#include <cstddef>

struct Snake {
    Vector2 pos;
    Vector2 dir;
};

struct Food {
    Vector2 pos;
};

void DrawSnake(const std::vector<Snake>& snake);
void DrawFood(const Food& food);
bool CheckCollision(const Snake& snake, const Food& food);
bool CheckSelfCollision(const std::vector<Snake>& snake);

#endif