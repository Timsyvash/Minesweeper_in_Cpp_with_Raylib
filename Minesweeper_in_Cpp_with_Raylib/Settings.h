#pragma once
#include <raylib.h>

inline const unsigned short cellSize = 30;
inline const unsigned short rows = 20;
inline const unsigned short cols = 20;
inline const unsigned short num_mines = 40;
inline const unsigned short window_width = cols * cellSize;
inline const unsigned short window_height = rows * cellSize;
inline const Color c = BLACK;
inline const char* title = "Minesweeper";
inline const unsigned short fps = 60;