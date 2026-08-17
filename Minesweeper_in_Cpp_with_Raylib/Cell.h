#pragma once
#include <vector>
#include "Settings.h"
#include "raylib.h"

struct Cell_struct {
    unsigned short r = 0, c = 0;
    bool is_mine = false;
    bool is_revealed = false;
    bool is_flagged = false;
    short neighborMines = 0;
};

class Cell {
private:
    std::vector<std::vector<Cell_struct>> grid;
    bool game_over = false;
    bool game_won = false;

    void CountMines(); // Оголошення приватного методу підрахунку

public:
    Cell();
    void InitGrid();
    void RevealCell(short r, short c);
    void ToggleFlag(short r, short c);
    void CheckWinCondition();
    void DrawGrid();

    Color GetNumberColor(short num); // Оголошення кольорів цифр

    bool IsGameOver() const { return game_over; }
    bool IsGameWon() const { return game_won; }
};