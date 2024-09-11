#ifndef ASCII_INIT_INCLUDE
#define ASCII_INIT_INCLUDE

#include "buffer.h"

extern Buffer_t g_RenderBuffer;

void InitASCIIEngine(int width, int height);

void FreeASCIIEngine();

#endif // ASCII_INIT_INCLUDE