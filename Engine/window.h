#ifndef ASCII_WINDOW_INCLUDE
#define ASCII_WINDOW_INCLUDE

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "global.h"
#include "init.h"
#include "buffer.h"

typedef struct Win
{
    uint8_t type; // the type of struct, must be contained in every container

    int x; // starting position
    int y;

    int dx; // ending position
    int dy;

    bool hasBorder; // if window should render border

    struct Win *parent;  // parent window to display relative to
} Win_t;

void DrawWindow(Win_t *win);

Win_t CreateWindow(int x, int y, int width, int height, Win_t *withinWindow);

void WindowDrawLine(Win_t *win, char ch, int x0, int y0, int x1, int y1);

#endif // ASCII_WINDOW_INCLUDE