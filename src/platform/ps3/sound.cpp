#include "platform/sound.h"

namespace Platform::Sound
{
static bool s_RemoteInitialised = false;

s32 InitialiseRemote()
{
    s_RemoteInitialised = true;
    return 0;
}
}
