#include "snake.hpp"
#include <stddef.h>

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game!");
    SetTargetFPS(15);

    std::vector<Snake> snake = {
        {
            {
                GRID_SIZE * 5,
                GRID_SIZE * 5
            },
            {
                GRID_SIZE,
                0
            }
        }
    };

    Food food = {
        { 
            GRID_SIZE * (GetRandomValue(0, SCREEN_WIDTH / GRID_SIZE - 1)),
            GRID_SIZE * (GetRandomValue(0, SCREEN_HEIGHT / GRID_SIZE - 1))
        }
    };


    while (!WindowShouldClose()) {
        /* Movement */
        if (IsKeyPressed(KEY_RIGHT) && snake[0].dir.x == 0)
            snake[0].dir = { GRID_SIZE, 0 };
        if (IsKeyPressed(KEY_LEFT) && snake[0].dir.x == 0)
            snake[0].dir = { -GRID_SIZE, 0 };
        if (IsKeyPressed(KEY_UP) && snake[0].dir.y == 0)
            snake[0].dir = { 0, -GRID_SIZE };
        if (IsKeyPressed(KEY_DOWN) && snake[0].dir.y == 0)
            snake[0].dir = { 0, GRID_SIZE };

        Vector2 prevPos = snake[0].pos;
        snake[0].pos.x += snake[0].dir.x; 
        snake[0].pos.y += snake[0].dir.y; 

        for (size_t i = 1; i < snake.size(); ++i) {
            Vector2 temp = snake[i].pos;
            snake[i].pos = prevPos;
            prevPos = temp;
        }

        if (CheckCollision(snake[0], food)) {
            food.pos = { 
                (float)GRID_SIZE * (GetRandomValue(0, SCREEN_WIDTH / GRID_SIZE - 1)),
                (float)GRID_SIZE * (GetRandomValue(0, SCREEN_HEIGHT / GRID_SIZE - 1))
            };
            snake.push_back({
                prevPos,
                { 0, 0 }
            });
        }

        if (
            CheckSelfCollision(snake) ||
            snake[0].pos.x < 0 ||
            snake[0].pos.x >= SCREEN_WIDTH ||
            snake[0].pos.y < 0 ||
            snake[0].pos.y >= SCREEN_HEIGHT
        ) {
            snake = { { {GRID_SIZE * 5, GRID_SIZE * 5}, {GRID_SIZE, 0} } };
            food.pos = {
                (float)GRID_SIZE * (GetRandomValue(0, SCREEN_WIDTH / GRID_SIZE - 1)),
                (float)GRID_SIZE * (GetRandomValue(0, SCREEN_HEIGHT / GRID_SIZE - 1))
            };
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawSnake(snake);
            DrawFood(food);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void DrawSnake(const std::vector<Snake>& snake)
{
    for (const auto& sn : snake) {
        DrawRectangleV(sn.pos, {
            (float)GRID_SIZE,
            (float)GRID_SIZE
        }, GREEN);
    }
}

void DrawFood(const Food& food)
{
    DrawRectangleV(food.pos, {
        (float)GRID_SIZE,
        (float)GRID_SIZE
    }, RED);
}

bool CheckCollision(const Snake& snake, const Food& food)
{
    return snake.pos.x == food.pos.x &&
            snake.pos.y == food.pos.y;
};

bool CheckSelfCollision(const std::vector<Snake>& snake)
{
    for (size_t i = 1; i < snake.size(); ++i) {
        if (snake[0].pos.x == snake[i].pos.x && snake[0].pos.y == snake[i].pos.y) return true;
    }

    return false;
}