#include "platform/saves.h"
#include <string.h>
#include <stdio.h>

namespace Platform::Saves
{
static Operation s_CurrentOperation = OperationNone;
static Result s_LastResult = {1, 0, 0};
static char s_Region[16] = {0};
static char s_Product[16] = {0};

bool Initialise(const char* region, const char* product)
{
    if (region) strncpy(s_Region, region, sizeof(s_Region) - 1);
    if (product) strncpy(s_Product, product, sizeof(s_Product) - 1);
    return true;
}

Operation Update(s32 port, s32 slot, StorageInfo* info)
{
    (void)port;
    (void)slot;
    if (info)
    {
        info->type = StorageMemoryCard;
        info->freeKilobytes = 8192;
        info->formatted = 1;
    }

    if (s_CurrentOperation != OperationNone)
    {
        s_LastResult.succeeded = 1;
        s_LastResult.step = 0;
        s_LastResult.error = 0;
        Operation done = s_CurrentOperation;
        s_CurrentOperation = OperationNone;
        return done;
    }

    return OperationNone;
}

Result GetResult(Operation operation)
{
    (void)operation;
    return s_LastResult;
}

bool Format(s32 port, s32 slot)
{
    (void)port;
    (void)slot;
    s_CurrentOperation = OperationFormat;
    return true;
}

bool CreateSave(s32 port, s32 slot, const char* save)
{
    (void)port;
    (void)slot;
    (void)save;
    s_CurrentOperation = OperationCreateSave;
    return true;
}

bool MeasureSave(s32 port, s32 slot, const char* save, s32* kilobytes)
{
    (void)port;
    (void)slot;
    (void)save;
    if (kilobytes) *kilobytes = 128;
    s_CurrentOperation = OperationMeasureSave;
    return true;
}

bool FindFile(s32 port, s32 slot, const char* file, const char* save, s32* size, FileEntry* entry)
{
    (void)port;
    (void)slot;
    (void)file;
    (void)save;
    if (size) *size = 1024;
    if (entry)
    {
        memset(entry, 0, sizeof(FileEntry));
        entry->size = 1024;
        if (file) strncpy(entry->name, file, sizeof(entry->name) - 1);
    }
    s_CurrentOperation = OperationFindFile;
    return true;
}

bool Write(s32 port, s32 slot, const char* save, const char* file, const void* data, s32 size)
{
    (void)port;
    (void)slot;
    (void)save;
    (void)file;
    (void)data;
    (void)size;
    s_CurrentOperation = OperationWrite;
    return true;
}

bool Read(s32 port, s32 slot, const char* save, const char* file, void* buffer, s32 size)
{
    (void)port;
    (void)slot;
    (void)save;
    (void)file;
    (void)buffer;
    (void)size;
    s_CurrentOperation = OperationRead;
    return true;
}

u32 FileKilobytes(u32 size)
{
    return (size + 1023) / 1024;
}

u32 SaveBytes(u32 kilobytes, u32 files)
{
    return kilobytes * 1024 + files * sizeof(FileEntry);
}
}
