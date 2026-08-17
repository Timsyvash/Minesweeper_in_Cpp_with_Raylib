#include "raylib.h"
#include "Cell.h"
#include "Settings.h"
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
    srand(static_cast<unsigned short>(time(nullptr)));

    InitWindow(window_width, window_height, title);
    SetTargetFPS(60);

    Cell board;
    board.InitGrid();

    while (!WindowShouldClose()) {
        // --- 1. Обробка натискань миші ---
        if (!board.IsGameOver() && !board.IsGameWon()) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                Vector2 mousePos = GetMousePosition();
                int r = mousePos.y / cellSize;
                int c = mousePos.x / cellSize;

                if (r >= 0 && r < rows && c >= 0 && c < cols) {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        board.RevealCell(r, c);
                    }
                    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                        board.ToggleFlag(r, c);
                    }
                }
            }
        }

        // Перезапуск гри на кнопку 'R'
        if (IsKeyPressed(KEY_R)) {
            board.InitGrid();
        }

        // --- 2. Малювання ---
        BeginDrawing();
        ClearBackground(DARKGRAY);

        // Викликаємо готове малювання сітки з класу Cell
        board.DrawGrid();

        // Оверлей екранів програшу та виграшу
        if (board.IsGameOver()) {
            DrawRectangle(0, 0, window_width, window_height, Fade(BLACK, 0.75f));
            DrawText("YOU LOST!", window_width / 2 - 110, window_height / 2 - 30, 30, RED);
            DrawText("Press 'R' to restart", window_width / 2 - 130, window_height / 2 + 15, 16, LIGHTGRAY);
        }
        else if (board.IsGameWon()) {
            DrawRectangle(0, 0, window_width, window_height, Fade(BLACK, 0.75f));
            DrawText("YOU GUESSED IT ALL!", window_width / 2 - 140, window_height / 2 - 30, 30, GREEN);
            DrawText("Press 'R' to restart", window_width / 2 - 130, window_height / 2 + 15, 16, LIGHTGRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}