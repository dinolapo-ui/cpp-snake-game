#include "raylib.h"
#include <deque>

struct SnakeSegment {
    int x, y;
};
struct Food {
    int x, y;
};

Food GenerateRandomFood(int gridSize) {
    return {GetRandomValue(0, gridSize - 1), GetRandomValue(0, gridSize - 1)};
}

int main() {
    // 1. Initialization
    const int gridSize = 20;
    const int cellSize = 20;
    InitWindow(gridSize * cellSize, gridSize * cellSize, "Snake Game - Dyana");
    SetTargetFPS(10);

    std::deque<SnakeSegment> snake = {{10, 10}, {10, 11}, {10, 12}};
    Vector2 direction = {0, -1};
    Food food = GenerateRandomFood(gridSize);
    int score = 0;
    bool gameOver = false;

    // 2. Game Loop
    while (!WindowShouldClose()) {
        if (!gameOver) {
            // Input: Tukar arah guna arrow keys (elak undur terus ke belakang)
            if (IsKeyPressed(KEY_UP) && direction.y == 0) direction = {0, -1};
            if (IsKeyPressed(KEY_DOWN) && direction.y == 0) direction = {0, 1};
            if (IsKeyPressed(KEY_LEFT) && direction.x == 0) direction = {-1, 0};
            if (IsKeyPressed(KEY_RIGHT) && direction.x == 0) direction = {1, 0};

            // Logik Pergerakan
            SnakeSegment newHead = {snake[0].x + (int)direction.x, snake[0].y + (int)direction.y};

            // Semak perlanggaran dinding
            if (newHead.x < 0 || newHead.x >= gridSize || newHead.y < 0 || newHead.y >= gridSize) {
                gameOver = true;
            }

            // Semak perlanggaran badan sendiri
            for (size_t i = 0; i < snake.size(); i++) {
                if (newHead.x == snake[i].x && newHead.y == snake[i].y) {
                    gameOver = true;
                }
            }

            if (!gameOver) {
                if (newHead.x == food.x && newHead.y == food.y) {
                    snake.push_front(newHead);
                    food = GenerateRandomFood(gridSize);
                    score += 10; // Tambah skor
                } else {
                    snake.push_front(newHead);
                    snake.pop_back();
                }
            }
        } else {
            // Tekan R untuk mula semula jika Game Over
            if (IsKeyPressed(KEY_R)) {
                snake = {{10, 10}, {10, 11}, {10, 12}};
                direction = {0, -1};
                food = GenerateRandomFood(gridSize);
                score = 0;
                gameOver = false;
            }
        }

        // 3. Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!gameOver) {
            // Lukis Makanan
            DrawRectangle(food.x * cellSize, food.y * cellSize, cellSize - 2, cellSize - 2, RED);
            
            // Lukis Ular
            for (auto segment : snake) {
                DrawRectangle(segment.x * cellSize, segment.y * cellSize, cellSize - 2, cellSize - 2, DARKGREEN);
            }

            // Papar Skor
            DrawText(TextFormat("Score: %d", score), 10, 10, 20, DARKGRAY);
        } else {
            // Paparan Game Over
            DrawText("GAME OVER", 110, 150, 30, RED);
            DrawText("Press 'R' to Restart", 120, 200, 15, DARKGRAY);
            DrawText(TextFormat("Final Score: %d", score), 135, 230, 20, DARKGRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}