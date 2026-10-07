#include "platform/audio.h"
#include <string.h>

namespace Platform::Audio
{
static bool s_Paused = false;
static u32 s_ReservedMemory = 0;
static u32 s_GroupVolumes[4][2] = {{FullGroupVolume, FullGroupVolume}, {FullGroupVolume, FullGroupVolume}, {FullGroupVolume, FullGroupVolume}, {FullGroupVolume, FullGroupVolume}};
static u32 s_ReverbCoreMode[Cores] = {0, 0};

void Reset()
{
    s_Paused = false;
    s_ReservedMemory = 0;
}

void PauseAll()
{
    s_Paused = true;
}

void ResumeAll()
{
    s_Paused = false;
}

s32 LendToMovie()
{
    return 0;
}

s32 ReclaimFromMovie()
{
    return 0;
}

void CompactSoundMemory()
{
    if (s_ReservedMemory > 0)
    {
        s_ReservedMemory = (s_ReservedMemory + 15) & ~15u;
    }
}

void SetGroupVolume(s32 group, u32 left, u32 right)
{
    s32 idx = (group >> GroupShift) - 1;
    if (idx >= 0 && idx < 4)
    {
        s_GroupVolumes[idx][0] = left;
        s_GroupVolumes[idx][1] = right;
    }
}

s32 SetVoiceVolume(s32 voice, s16 left, s16 right)
{
    if (voice < 0 || voice >= Voices) return -1;
    (void)left;
    (void)right;
    return 0;
}

s32 SetVoicePitch(s32 voice, u16 pitch)
{
    if (voice < 0 || voice >= Voices) return -1;
    (void)pitch;
    return 0;
}

void SetVoiceReverb(s32 voice, bool on)
{
    (void)voice;
    (void)on;
}

void ReleaseVoice(s32 voice, u32 rate)
{
    (void)voice;
    (void)rate;
}

s32 IsVoiceFree(s32 voice)
{
    if (voice < 0 || voice >= Voices) return -1;
    return 1;
}

void SetReverb(s32 core, s32 mode, u16 depthLeft, u16 depthRight, u16 delay, u16 feedback)
{
    if (core >= 0 && core < Cores)
    {
        s_ReverbCoreMode[core] = mode;
    }
    (void)depthLeft;
    (void)depthRight;
    (void)delay;
    (void)feedback;
}

void ClearReverb(s32 core)
{
    if (core >= 0 && core < Cores)
    {
        s_ReverbCoreMode[core] = 0;
    }
}

void SetReverbVolume(s32 core, s16 left, s16 right)
{
    (void)core;
    (void)left;
    (void)right;
}

u32 ReserveSoundMemory(u32 size)
{
    u32 addr = s_ReservedMemory;
    s_ReservedMemory += (size + 15) & ~15u;
    return addr;
}

void SoundBankLoaded(u16 bank)
{
    (void)bank;
}

void ReserveSounds(u16 count)
{
    (void)count;
}

void ReleaseSound(u32 sound)
{
    (void)sound;
}

s32 PlaySound(u32 sound, u32 voiceAndGroup, s16 left, s16 right, u16 pitch, u32 attack, u32 release, u32 loops)
{
    (void)sound;
    (void)voiceAndGroup;
    (void)left;
    (void)right;
    (void)pitch;
    (void)attack;
    (void)release;
    (void)loops;
    return 0;
}

s32 PitchOfRate(s32 rate)
{
    return (rate * 0x1000) / 44100;
}

u32 ChannelBufferAddress(s32 channel)
{
    return static_cast<u32>(channel * 0x1000);
}

void ReadMusic(s32 file, u32 offset, u32 size)
{
    (void)file;
    (void)offset;
    (void)size;
}

s32 StreamMusic(s32 file, s32 channel, u32 voiceAndGroup, u16 pitch, bool once)
{
    (void)file;
    (void)channel;
    (void)voiceAndGroup;
    (void)pitch;
    (void)once;
    return 0;
}

void InterleaveMusic(s32 channel, u32 blockSize)
{
    (void)channel;
    (void)blockSize;
}

void AddMusicChannel(s32 child, s32 parent, u32 voiceAndGroup, u32 soundAddress)
{
    (void)child;
    (void)parent;
    (void)voiceAndGroup;
    (void)soundAddress;
}

void SetMusicEnd(s32 channel, u32 end)
{
    (void)channel;
    (void)end;
}

void PrepareMusic(s32 channel)
{
    (void)channel;
}

bool IsMusicReady(s32 channel)
{
    (void)channel;
    return true;
}

s32 PlayMusic(s32 channel)
{
    (void)channel;
    return 0;
}

bool IsMusicPlaying(s32 channel)
{
    (void)channel;
    return true;
}

void StopMusic(s32 channel)
{
    (void)channel;
}
}
