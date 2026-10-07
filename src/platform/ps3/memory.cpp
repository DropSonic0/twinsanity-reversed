#include "platform/memory.h"
#include <stdlib.h>

namespace
{
constexpr u32 DefaultPoolSize = 32 * 1024 * 1024;
static volatile u32 s_SyncCounter = 0;
}

namespace Platform::Memory
{
u32 PoolSpace()
{
    return DefaultPoolSize;
}

void* AllocatePool(u32 size)
{
    return malloc(size);
}

void Synchronise()
{
    s_SyncCounter++;
}

void BeforeDeviceWrite(void* memory, u32 size)
{
    if (memory && size > 0)
    {
        volatile u8* ptr = static_cast<volatile u8*>(memory);
        u8 temp = ptr[0];
        (void)temp;
    }
}

void WriteBackCache()
{
    s_SyncCounter++;
}
}
