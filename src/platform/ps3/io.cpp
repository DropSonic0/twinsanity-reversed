#include "platform/io.h"
#include <stdlib.h>

namespace Platform::Io
{
static bool s_IoInitialised = false;
static void* s_HeapBase = nullptr;

void Initialise()
{
    s_IoInitialised = true;
}

void Restart(const char* image)
{
    (void)image;
    s_IoInitialised = true;
}

s32 LoadDriver(const char* path)
{
    if (!path) return -1;
    return 1;
}

void InitialiseHeap()
{
    if (!s_HeapBase)
    {
        s_HeapBase = malloc(1024 * 1024);
    }
}

void* AllocateHeap(s32 size)
{
    if (!s_HeapBase)
    {
        InitialiseHeap();
    }
    return malloc(size);
}

s32 FreeHeap(void* address)
{
    if (address)
    {
        free(address);
    }
    return 0;
}
}
