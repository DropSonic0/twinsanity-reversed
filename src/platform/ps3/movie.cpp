#include "platform/movie.h"

namespace Platform::Movie
{
void Construct(Player* player)
{
    (void)player;
}

void BeginPresenting(Player* player, void (*present)())
{
    (void)player;
    if (present)
    {
        present();
    }
}

bool Open(Player* player, const char* file, u32 audioChannel, s32 width, void* lentMemory)
{
    (void)player;
    (void)file;
    (void)audioChannel;
    (void)width;
    (void)lentMemory;
    return true;
}

void StartSound(Player* player, f32 volume)
{
    (void)player;
    (void)volume;
}

bool Step(Player* player)
{
    (void)player;
    return false; // Movie finished
}

void WaitFrame(Player* player)
{
    (void)player;
}

void QueuePicture(Player* player)
{
    (void)player;
}
}
