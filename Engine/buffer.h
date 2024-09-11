#ifndef ASCII_BUFFER_INCLUDE
#define ASCII_BUFFER_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include "global.h"

typedef struct Buffer
{
    char *buf;
    int width;
    int height;
} Buffer_t;

Buffer_t CreateRenderBuffer(int width, int height);

void FreeRenderBuffer(Buffer_t *buf);

void ClearBuffer(Buffer_t *buf);

void RenderBufferToScreen(Buffer_t *buf);

void DrawPoint(Buffer_t *buf, char ch, int x, int y);

void DrawLineHigh(Buffer_t *buf, char ch, int x0, int y0, int x1, int y1);

void DrawLineLow(Buffer_t *buf, char ch, int x0, int y0, int x1, int y1);

void DrawVerticalLine(Buffer_t *buf, char ch, int x, int y0, int y1);

void DrawHorizontalLine(Buffer_t *buf, char ch, int x0, int x1, int y);

void DrawLine(Buffer_t *buf, char ch, int x0, int y0, int x1, int y1);

#endif // ASCII_BUFFER_INCLUDE