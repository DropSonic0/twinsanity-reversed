#include "platform/time.h"

namespace Platform::Time
{
static u64 s_Ticks = 0;

void Initialise()
{
    s_Ticks = 0;
}

u64 Ticks()
{
    s_Ticks += 9600; // Simulating frame ticks (576000 ticks/sec / 60 fps = 9600 ticks/frame)
    return s_Ticks;
}
}
