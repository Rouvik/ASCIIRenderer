#include "window.h"

Win_t CreateWindow(int x, int y, int width, int height, Win_t *withinWindow)
{
    return (Win_t){.x = x, .y = y, .dx = width, .dy = height, .type = Entity_WINDOW, .parent = withinWindow};
}

void DrawWindow(Win_t *win)
{
    int relX = 0;
    int relY = 0;

    if (win->parent)            // get relative coordinate to parent if exists
    {
        DrawWindow(win->parent);
        relX = win->parent->x;
        relY = win->parent->y;
    }

    // translate the system to relative coordinates
    int winX = win->x + relX;
    int winY = win->y + relY;
    int winDX = win->dx + relX;
    int winDY = win->dy + relY;

    if (win->hasBorder)
    {
        DrawVerticalLine(&g_RenderBuffer, '|', winX, winY, winY + winDY);
        DrawVerticalLine(&g_RenderBuffer, '|', winX + winDX, winY, winY + winDY);
        DrawHorizontalLine(&g_RenderBuffer, '-', winX, winX + winDX, winY);
        DrawHorizontalLine(&g_RenderBuffer, '-', winX, winX + winDX, winY + winDY);

        g_RenderBuffer.buf[g_RenderBuffer.width * winY + winX] = '+';
        g_RenderBuffer.buf[g_RenderBuffer.width * winY + winX + winDX] = '+';
        g_RenderBuffer.buf[g_RenderBuffer.width * (winY + winDY) + winX] = '+';
        g_RenderBuffer.buf[g_RenderBuffer.width * (winY + winDY) + winX + winDX] = '+';
    }
}

int clamp(int x, int min, int max)
{
    if (x < min)
    {
        return min;
    }
    else if (x > max)
    {
        return max;
    }
    else
    {
        return x;
    }
}

void WindowDrawLine(Win_t *win, char ch, int x0, int y0, int x1, int y1)
{
    // clamped X bounds
    int X0 = clamp(x0 + win->x, win->x, win->x + win->dx);
    int Y0 = clamp(y0 + win->y, win->y, win->y + win->dy);

    // clamped Y bounds
    int X1 = clamp(x1 + win->x, win->x, win->x + win->dx);
    int Y1 = clamp(y1 + win->y, win->y, win->y + win->dy);

    DrawLine(&g_RenderBuffer, ch, X0, Y0, X1, Y1);
}