#include "buffer.h"

#include <assert.h>

inline int clamp(int x, int min, int max)
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

inline int abs(int x)
{
    if (x < 0)
    {
        return -x;
    }
    else
    {
        return x;
    }
}

Buffer_t CreateRenderBuffer(int width, int height)
{
    Buffer_t out;
    out.buf = (char *)malloc((width + 1) * height + 1);
    out.width = width;
    out.height = height;

    // fill entire thing with spaces
    ClearBuffer(&out);

    // fill the extra last gap with '\n'
    for (int y = 1; y < height; y++)
    {
        out.buf[width * y - 1] = '\n';
    }

    out.buf[width * height] = 0;    // add ending '\0'

    return out;
}

void FreeRenderBuffer(Buffer_t *buf)
{
    free(buf->buf);
    buf->buf = NULL;
    buf->width = 0;
    buf->height = 0;
}

void ClearBuffer(Buffer_t *buf)
{
    for (int y = 0; y < buf->height; y++)
    {
        for (int x = 0; x < buf->width - 1; x++)
        {            
            buf->buf[buf->width * y + x] = ' ';
        }
    }
}

void RenderBufferToScreen(Buffer_t *buf)
{
    WINDOW_CLEAR_COMMAND;
    puts(buf->buf);
}

void DrawPoint(Buffer_t *buf, char ch, int x, int y)
{
    x = clamp(x, 0, buf->width - 1);
    y = clamp(y, 0, buf->height - 1);

    buf->buf[buf->width * y + x] = ch;
}

void DrawLineHigh(Buffer_t *buf, char ch, int x0, int y0, int x1, int y1)
{
    x0 = clamp(x0, 0, buf->width - 1);
    y0 = clamp(y0, 0, buf->height - 1);
    
    x1 = clamp(x1, 0, buf->width - 1);
    y1 = clamp(y1, 0, buf->height - 1);

    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;

    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }

    int D = (2 * dx) - dy;

    int x = x0;

    for (int y = y0; y < y1; y++)
    {
        buf->buf[buf->width * y + x] = ch;
        if (D > 0)
        {
            x += xi;
            D += 2 * (dx = dy);
        }
        else
        {
            D += 2 * dx;
        }
    }
}

void DrawLineLow(Buffer_t *buf, char ch, int x0, int y0, int x1, int y1)
{
    x0 = clamp(x0, 0, buf->width - 1);
    y0 = clamp(y0, 0, buf->height - 1);
    
    x1 = clamp(x1, 0, buf->width - 1);
    y1 = clamp(y1, 0, buf->height - 1);

    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;

    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }

    int D = (2 * dy) - dx;
    int y = y0;

    for (int x = x0; x < x1; x++)
    {
        buf->buf[buf->width * y + x] = ch;
        if (D > 0)
        {
            y += yi;
            D += 2 * (dy - dx);
        }
        else
        {
            D += 2 * dy;
        }
    }
}

void DrawVerticalLine(Buffer_t *buf, char ch, int x, int y0, int y1)
{
    x = clamp(x, 0, buf->width - 1);
    y0 = clamp(y0, 0, buf->height - 1);
    
    y1 = clamp(y1, 0, buf->height - 1);

    for (int y = y0; y < y1; y++)
    {
        buf->buf[buf->width * y + x] = ch;
    }
}

void DrawHorizontalLine(Buffer_t *buf, char ch, int x0, int x1, int y)
{
    x0 = clamp(x0, 0, buf->width - 1);
    x1 = clamp(x1, 0, buf->width - 1);
    
    y = clamp(y, 0, buf->height - 1);

    for (int x = x0; x < x1; x++)
    {
        buf->buf[buf->width * y + x] = ch;
    }
}

void DrawLine(Buffer_t *buf, char ch, int x0, int y0, int x1, int y1)
{
    x0 = clamp(x0, 0, buf->width - 1);
    y0 = clamp(y0, 0, buf->height - 1);
    
    x1 = clamp(x1, 0, buf->width - 1);
    y1 = clamp(y1, 0, buf->height - 1);

    if (x0 == x1)   // vertical lines
    {
        if (y0 > y1)
        {
            DrawVerticalLine(buf, ch, x0, y1, y0);
        }
        else
        {
            DrawVerticalLine(buf, ch, x0, y0, y1);
        }
    }
    else if (y0 == y1)  // horizintal lines
    {
        if (x0 > x1)
        {
            DrawHorizontalLine(buf, ch, x1, x0, y0);
        }
        else
        {
            DrawHorizontalLine(buf, ch, x0, x1, y0);
        }
    }    
    else if (abs(y1 - y0) < abs(x1 - x0))   // lower octant
    {
        if (x0 > x1)
        {
            DrawLineLow(buf, ch, x1, y1, x0, y0);
        }
        else
        {
            DrawLineLow(buf, ch, x0, y0, x1, y1);
        }
    }
    else    // upper octant
    {
        if (y0 > y1)
        {
            DrawLineHigh(buf, ch, x1, y1, x0, y0);
        }
        else
        {
            DrawLineHigh(buf, ch, x0, y0, x1, y1);
        }
    }
}