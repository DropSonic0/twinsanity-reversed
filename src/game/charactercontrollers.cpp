#include "game/characters.h"

#include "game/clock.h"
#include "game/colour.h"
#include "game/followcamera.h"
#include "game/math.h"

// The character controllers' translation unit's start-up (its static initialisation and global constructor) and two of its
// out-of-line inline functions. Its constants stay in the asm's .bss: most are the follow camera rig's (its header's copies,
// declared in game/followcamera.h), the first six a common header's (mostly unread), then the controllers' own

extern "C"
{
    // A common header's: 45 degrees, the up axis (the jump's room to take off), the UI's shadow offset and colour, and 0
    extern s32 g_ControllersAngle45 RETAIL(D_0030A528);
    extern Vector4 g_JumpUp RETAIL(D_0030BB20);
    extern f32 g_ControllersShadowX RETAIL(D_0030A530);
    extern f32 g_ControllersShadowY RETAIL(D_0030A534);
    extern u32 g_ControllersShadowColour RETAIL(D_0030A538);
    extern u32 g_ControllersZero RETAIL(D_0030A540);
    // The up axis of the crouch's checks for room to stand up
    extern Vector4 g_CrouchUp RETAIL(D_0030BB70);
}

u32 TimeReached(const TimeClock* clock, s32 time, s32 end, s32 divisor)
{
    return time >= end - static_cast<s32>(clock->advance) / divisor;
}

void InvertRotation(Vector4* rotation)
{
    f32 inverse = InverseLength4(0.0f, InverseEpsilon, rotation);
    rotation->w = rotation->w * inverse;
    rotation->x = rotation->x * -inverse;
    rotation->y = rotation->y * -inverse;
    rotation->z = rotation->z * -inverse;
}

void InitCharacterControllerGlobals(u32 initialize, u32 priority)
{
    if (priority != DefaultInitPriority || initialize == 0)
    {
        return;
    }

    AngleFrom(&g_ControllersAngle45, QuarterPi, AngleRadians);
    g_JumpUp.x = 0.0f; g_JumpUp.y = 1.0f; g_JumpUp.z = 0.0f; g_JumpUp.w = 1.0f;
    g_ControllersShadowX = UiShadowOffset;
    g_ControllersShadowY = UiShadowOffset;
    ColourSet(&g_ControllersShadowColour, 0.0f, 0.0f, 0.0f, UiShadowAlpha);
    g_ControllersZero = 0;
    AngleFrom(&g_RigPitchPushRate, 180.0f, AngleDegrees);
    AngleFrom(&g_RigYawPushRate, 180.0f, AngleDegrees);
    AngleFrom(&g_RigPitchInputSpeed, 60.0f, AngleDegrees);
    AngleFrom(&g_RigYawInputSpeed, 120.0f, AngleDegrees);
    AngleFrom(&g_RigPitchLowest, -45.0f, AngleDegrees);
    AngleFrom(&g_RigPitchHighest, 75.0f, AngleDegrees);
    g_RigTargetBoxLow.x = 0.0f; g_RigTargetBoxLow.y = 1.5f; g_RigTargetBoxLow.z = 0.0f; g_RigTargetBoxLow.w = 1.0f;
    g_RigTargetBoxHigh.x = 0.0f; g_RigTargetBoxHigh.y = 3.5f; g_RigTargetBoxHigh.z = 0.0f; g_RigTargetBoxHigh.w = 1.0f;
    AngleFrom(&g_RigStartPitch, 7.0f, AngleDegrees);
    g_UnreadRigBack.x = 0.0f; g_UnreadRigBack.y = 0.0f; g_UnreadRigBack.z = -1.0f; g_UnreadRigBack.w = 1.0f;
    AngleFrom(&g_RigYawSpeed, 180.0f, AngleDegrees);
    AngleFrom(&g_RigPitchSpeed, 90.0f, AngleDegrees);
    AngleFrom(&g_RigTiltYawSpeed, 10.0f, AngleDegrees);
    AngleFrom(&g_RigTiltPitchSpeed, 50.0f, AngleDegrees);
    AngleFrom(&g_RollerbrawlYawSpeedLeast, 25.0f, AngleDegrees);
    AngleFrom(&g_RollerbrawlYawSpeedMost, 200.0f, AngleDegrees);
    g_RollerbrawlYawSpeedRange = g_RollerbrawlYawSpeedMost - g_RollerbrawlYawSpeedLeast;
    AngleFrom(&g_HumiliskateYawSpeed, 180.0f, AngleDegrees);
    AngleFrom(&g_UnreadRigAngle75, 75.0f, AngleDegrees);
    AngleFrom(&g_MechaFieldOfView, 60.0f, AngleDegrees);
    AngleFrom(&g_MechaPitch, 40.0f, AngleDegrees);
    g_MechaTargetBox.x = 0.0f; g_MechaTargetBox.y = 11.0f; g_MechaTargetBox.z = 0.0f; g_MechaTargetBox.w = 1.0f;
    g_CrouchUp.x = 0.0f; g_CrouchUp.y = 1.0f; g_CrouchUp.z = 0.0f; g_CrouchUp.w = 1.0f;
    g_ClawLockOffset.x = 0.0f; g_ClawLockOffset.y = Rounded(0.9); g_ClawLockOffset.z = 0.0f; g_ClawLockOffset.w = 1.0f;
    g_ClawGrabOffset.x = 0.0f; g_ClawGrabOffset.y = Rounded(-4.8); g_ClawGrabOffset.z = Rounded(14.4); g_ClawGrabOffset.w = 1.0f;
    g_GunOnFootLockOffset.x = 0.0f; g_GunOnFootLockOffset.y = Rounded(0.9); g_GunOnFootLockOffset.z = 0.0f; g_GunOnFootLockOffset.w = 1.0f;
    g_GunVehicleLockOffset.x = 0.0f; g_GunVehicleLockOffset.y = Rounded(0.9); g_GunVehicleLockOffset.z = 0.0f; g_GunVehicleLockOffset.w = 1.0f;
    g_GunMechaLockOffset.x = 0.0f; g_GunMechaLockOffset.y = 5.0f; g_GunMechaLockOffset.z = 5.0f; g_GunMechaLockOffset.w = 1.0f;
    g_GunArea24LockOffset.x = 0.0f; g_GunArea24LockOffset.y = Rounded(0.9); g_GunArea24LockOffset.z = 0.0f; g_GunArea24LockOffset.w = 1.0f;
    for (u32 index = 0; index < sizeof(g_Targets) / sizeof(g_Targets[0]); index++)
    {
        g_Targets[index].instance = nullptr;
    }
}

void CharacterControllerGlobalsConstructor()
{
    InitCharacterControllerGlobals(1, DefaultInitPriority);
}
