#include "Cell.h"
#include <string>
#include <cstdlib>
#include "raylib.h"

using namespace std;

Cell::Cell() : grid(rows, vector<Cell_struct>(cols)) {}

void Cell::InitGrid()
{
    game_over = false;
    game_won = false;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            grid[r][c] = Cell_struct{ (unsigned short)r, (unsigned short)c, false, false, false, 0 };
        }
    }

    short placedMines = 0;
    while (placedMines < num_mines) {
        short r = rand() % rows;
        short c = rand() % cols;
        if (!grid[r][c].is_mine) {
            grid[r][c].is_mine = true;
            placedMines++;
        }
    }

    CountMines();
}

void Cell::CountMines()
{
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c].is_mine) continue;

            int count = 0;
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    int nr = r + dr;
                    int nc = c + dc;
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                        if (grid[nr][nc].is_mine) count++;
                    }
                }
            }
            grid[r][c].neighborMines = count;
        }
    }
}

void Cell::RevealCell(short r, short c)
{
    // Перевірка на вихід за межі масиву
    if (r < 0 || r >= rows || c < 0 || c >= cols) return;
    if (grid[r][c].is_revealed || grid[r][c].is_flagged || game_over) return;

    grid[r][c].is_revealed = true;

    if (grid[r][c].is_mine) {
        game_over = true;
        // Виправлено: j < cols замість j < j
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j].is_mine) grid[i][j].is_revealed = true;
            }
        }
        return;
    }

    if (grid[r][c].neighborMines == 0) {
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr == 0 && dc == 0) continue;
                RevealCell(r + dr, c + dc);
            }
        }
    }

    CheckWinCondition();
}

void Cell::ToggleFlag(short r, short c)
{
    if (r >= 0 && r < rows && c >= 0 && c < cols && !grid[r][c].is_revealed && !game_over) {
        grid[r][c].is_flagged = !grid[r][c].is_flagged;
    }
}

void Cell::CheckWinCondition()
{
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (!grid[r][c].is_mine && !grid[r][c].is_revealed) {
                return;
            }
        }
    }
    game_won = true;
}

Color Cell::GetNumberColor(short num)
{
    switch (num) {
    case 1: return BLUE;
    case 2: return DARKGREEN;
    case 3: return RED;
    case 4: return DARKBLUE;
    default: return PURPLE;
    }
}

void Cell::DrawGrid()
{
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int posX = c * cellSize;
            int posY = r * cellSize;
            Cell_struct cell = grid[r][c];

            if (cell.is_revealed) {
                if (cell.is_mine) {
                    DrawRectangle(posX, posY, cellSize, cellSize, RED);
                    DrawCircle(posX + cellSize / 2, posY + cellSize / 2, cellSize / 4, BLACK);
                }
                else {
                    DrawRectangle(posX, posY, cellSize, cellSize, LIGHTGRAY);
                    if (cell.neighborMines > 0) {
                        string text = to_string(cell.neighborMines);
                        DrawText(text.c_str(), posX + cellSize / 3, posY + cellSize / 4, 20, GetNumberColor(cell.neighborMines));
                    }
                }
            }
            else {
                DrawRectangle(posX, posY, cellSize, cellSize, GRAY);
                if (cell.is_flagged) {
                    DrawTriangle(
                        Vector2{ (float)posX + 10, (float)posY + 30 },
                        Vector2{ (float)posX + 30, (float)posY + 20 },
                        Vector2{ (float)posX + 10, (float)posY + 10 },
                        ORANGE
                    );
                }
            }
            DrawRectangleLines(posX, posY, cellSize, cellSize, DARKGRAY);
        }
    }
}