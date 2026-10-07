#include "platform/disc.h"

namespace Platform::Disc
{
static Media s_Media = Media::Dvd;
static bool s_Initialised = false;

s32 Initialise()
{
    s_Initialised = true;
    return 1;
}

s32 SetMedia(Media media)
{
    s_Media = media;
    return 1;
}

Readiness WaitReady()
{
    return Ready;
}
}
