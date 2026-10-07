#include "platform/system.h"
#include <stdlib.h>

namespace Platform::System
{
static bool s_SystemInitialised = false;
static bool s_ServicesStarted = false;

void Initialise()
{
    s_SystemInitialised = true;
}

void StartServices()
{
    s_ServicesStarted = true;
}

void Exit(s32 status)
{
    exit(status);
}

ConsoleLanguage Language()
{
    return LanguageEnglish;
}

DateTime LocalTime()
{
    DateTime dt;
    dt.year = 2026;
    dt.month = 1;
    dt.day = 1;
    dt.hour = 0;
    dt.minute = 0;
    dt.second = 0;
    return dt;
}
}
