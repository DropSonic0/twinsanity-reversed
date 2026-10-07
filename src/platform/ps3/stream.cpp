#include "platform/stream.h"
#include <string.h>

namespace Platform::Stream
{
static State s_StreamState = State::Stopped;
static bool s_ChannelReading[16] = {false};

s32 Initialise(s32 channels, void* workMemory)
{
    (void)channels;
    (void)workMemory;
    s_StreamState = State::Running;
    return 0;
}

s32 Update()
{
    return 0;
}

State GetState()
{
    return s_StreamState;
}

void AttachBuffer(s32 channel, u32 size, u32 soundAddress, u32 soundSize)
{
    (void)channel;
    (void)size;
    (void)soundAddress;
    (void)soundSize;
}

void DetachBuffer(s32 channel)
{
    (void)channel;
}

u32 FreeBufferMemory()
{
    return 0x100000;
}

s32 OpenFile(const char* path)
{
    (void)path;
    return 1;
}

u32 FileSize()
{
    return 0x10000;
}

void CloseFile(s32 file)
{
    (void)file;
}

void Read(s32 channel, s32 file, u32 offset, u32 size, void* destination)
{
    (void)channel;
    (void)file;
    (void)offset;
    (void)size;
    (void)destination;
    if (channel >= 0 && channel < 16)
    {
        s_ChannelReading[channel] = false;
    }
}

void ReadSoundBank(s32 channel, u32 bank, s32 file, u32 offset, u32 size)
{
    (void)channel;
    (void)bank;
    (void)file;
    (void)offset;
    (void)size;
    if (channel >= 0 && channel < 16)
    {
        s_ChannelReading[channel] = false;
    }
}

bool IsReading(s32 channel)
{
    if (channel >= 0 && channel < 16)
    {
        return s_ChannelReading[channel];
    }
    return false;
}

s32 Wait(s32 channel)
{
    (void)channel;
    if (channel >= 0 && channel < 16)
    {
        s_ChannelReading[channel] = false;
    }
    return 0;
}
}
