#include <stdio.h>
#include "Engine/global.h"
#include "Engine/init.h"
#include "Engine/buffer.h"
#include "Engine/window.h"

#include <time.h>

#define WIN_WIDTH 20
#define WIN_HEIGHT 20

int main()
{
    InitASCIIEngine(100, 50);
    Win_t win = CreateWindow(1, 1, WIN_WIDTH, WIN_HEIGHT, NULL);
    win.hasBorder = true;

    bool running = true;
    int dirX = 1;
    int dirY = 1;

    struct timespec tm = {.tv_sec = 0, .tv_nsec = 16 * 1000000};

    while (running)
    {
        ClearBuffer(&g_RenderBuffer);
        DrawWindow(&win);

        win.x += dirX;    
        win.y += dirY;

        if (win.x < 2 || (win.x + win.dx) > g_RenderBuffer.width - 3)
        {
            dirX = -dirX;
        }

        
        if (win.y < 2 || (win.y + win.dy) > g_RenderBuffer.height - 3)
        {
            dirY = -dirY;
        }

        RenderBufferToScreen(&g_RenderBuffer);
        nanosleep(&tm, NULL);
    }
    
    FreeASCIIEngine();

    return 0;
}