#include "platform/pads.h"
#include <string.h>

namespace Platform::Pads
{
static u8 s_PadBuffers[2][BufferSize];
static bool s_PadConnected[2] = {true, false};

s32 Initialise()
{
    memset(s_PadBuffers, 0, sizeof(s_PadBuffers));
    return 1;
}

s32 Open(s32 port, s32 slot, void* buffer)
{
    (void)port;
    (void)slot;
    (void)buffer;
    return 1;
}

s32 Close(s32 port, s32 slot)
{
    (void)port;
    (void)slot;
    return 1;
}

s32 Read(s32 port, s32 slot, u8* data)
{
    (void)slot;
    if (port < 0 || port >= 2)
    {
        return 0;
    }

    u8 report[32];
    memset(report, 0, sizeof(report));
    report[ReportMode] = (ModeIdAnalog << 4) | 6;
    report[ReportButtonsHigh] = 0xFF;
    report[ReportButtonsLow] = 0xFF;
    report[StickRightX] = 128;
    report[StickRightY] = 128;
    report[StickLeftX] = 128;
    report[StickLeftY] = 128;

    memcpy(data, report, 32);
    return 32;
}

State GetState(s32 port, s32 slot)
{
    (void)slot;
    if (port == 0)
    {
        return StateStable;
    }
    return StateDisconnected;
}

RequestState GetRequestState(s32 port, s32 slot)
{
    (void)port;
    (void)slot;
    return RequestComplete;
}

s32 InfoMode(s32 port, s32 slot, ModeInfo info, s32 index)
{
    (void)port;
    (void)slot;
    (void)index;
    if (info == InfoCurrentId)
    {
        return ModeIdAnalog;
    }
    return 0;
}

s32 SetMainMode(s32 port, s32 slot, MainMode mode, ModeLock lock)
{
    (void)port;
    (void)slot;
    (void)mode;
    (void)lock;
    return 1;
}

s32 InfoActuator(s32 port, s32 slot, s32 actuator, s32 term)
{
    (void)port;
    (void)slot;
    (void)actuator;
    (void)term;
    return 2;
}

s32 SetActuatorAlign(s32 port, s32 slot, const u8 align[6])
{
    (void)port;
    (void)slot;
    (void)align;
    return 1;
}

s32 SetActuatorDirect(s32 port, s32 slot, const u8 values[6])
{
    (void)port;
    (void)slot;
    (void)values;
    return 1;
}

s32 InfoPressureMode(s32 port, s32 slot)
{
    (void)port;
    (void)slot;
    return 1;
}

s32 EnterPressureMode(s32 port, s32 slot)
{
    (void)port;
    (void)slot;
    return 1;
}
}
