#include "platform/files.h"
#include <stdio.h>
#include <string.h>

namespace Platform::Files
{
static FILE* s_Files[32] = {nullptr};

void Reset()
{
    for (int i = 0; i < 32; i++)
    {
        if (s_Files[i] != nullptr)
        {
            fclose(s_Files[i]);
            s_Files[i] = nullptr;
        }
    }
}

s32 Open(const char* path, s32 flags)
{
    const char* mode = "rb";
    if ((flags & OpenWrite) != 0)
    {
        mode = (flags & OpenRead) != 0 ? "r+b" : "wb";
    }

    FILE* f = fopen(path, mode);
    if (!f)
    {
        return -1;
    }

    for (int i = 0; i < 32; i++)
    {
        if (s_Files[i] == nullptr)
        {
            s_Files[i] = f;
            return i;
        }
    }

    fclose(f);
    return -1;
}

s32 Close(s32 file)
{
    if (file < 0 || file >= 32 || s_Files[file] == nullptr)
    {
        return -1;
    }

    fclose(s_Files[file]);
    s_Files[file] = nullptr;
    return 0;
}

s32 Read(s32 file, void* buffer, s32 size)
{
    if (file < 0 || file >= 32 || s_Files[file] == nullptr)
    {
        return -1;
    }

    return static_cast<s32>(fread(buffer, 1, size, s_Files[file]));
}

s32 Write(s32 file, const void* buffer, s32 size)
{
    if (file < 0 || file >= 32 || s_Files[file] == nullptr)
    {
        return -1;
    }

    return static_cast<s32>(fwrite(buffer, 1, size, s_Files[file]));
}

s32 Seek(s32 file, s32 offset, Whence whence)
{
    if (file < 0 || file >= 32 || s_Files[file] == nullptr)
    {
        return -1;
    }

    int origin = SEEK_SET;
    if (whence == SeekCurrent)
    {
        origin = SEEK_CUR;
    }
    else if (whence == SeekEnd)
    {
        origin = SEEK_END;
    }

    fseek(s_Files[file], offset, origin);
    return static_cast<s32>(ftell(s_Files[file]));
}
}
