#include "init.h"

Buffer_t g_RenderBuffer;

void InitASCIIEngine(int width, int height)
{
    g_RenderBuffer = CreateRenderBuffer(width, height);
}

void FreeASCIIEngine()
{
    FreeRenderBuffer(&g_RenderBuffer);
}