#pragma once

#include <stddef.h>

#if defined(__SNC__) || defined(__CELLOS_LV2__) || (defined(__cplusplus) && __cplusplus < 201103L)
#ifndef nullptr
#define nullptr NULL
#endif
#endif

#if defined(_EE) || defined(__PS2__) || defined(PS2)
#include <tamtypes.h>
#else
#include <stdint.h>
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
#endif

typedef float f32;
typedef double f64;

#if defined(__SNC__) || defined(__CELLOS_LV2__)
#define CONSTEXPR const
#elif defined(__cpp_constexpr) || (defined(__cplusplus) && __cplusplus >= 201103L) || (defined(_MSC_VER) && _MSC_VER >= 1900)
#define CONSTEXPR constexpr
#else
#define CONSTEXPR const
#endif

// GCC for the R5900 cuts decimal float literals down to single precision (it rounds towards zero, as the R5900's FPU does),
// where retail's compiler rounded them to the nearest: 0.1f comes out a bit below retail's 0.1. Rounded(0.1) is the float
// nearest to a double literal, as retail has it; literals single precision holds exactly (0.5f, 1.25f) don't need it
#if (defined(__cpp_consteval) && __cpp_consteval >= 201811L) || (defined(__cplusplus) && __cplusplus >= 202002L)
consteval f32 Rounded(double value)
{
    // A double's 52 bits of fraction rounded to a float's 23 (to even when it's halfway), its exponent biased by 127 in place
    // of 1023; the sign is the top bit of both, a carry out of the fraction goes into the exponent
    constexpr unsigned int DoubleFractionBits = 52;
    constexpr unsigned int FloatFractionBits = 23;
    constexpr unsigned int DroppedBits = DoubleFractionBits - FloatFractionBits;
    constexpr unsigned int DoubleExponentMask = 0x7FF;
    constexpr unsigned int DoubleBias = 1023;
    constexpr unsigned int FloatBias = 127;
    constexpr unsigned int SignBit = 0x80000000u;
    unsigned long long bits = __builtin_bit_cast(unsigned long long, value);
    unsigned int sign = static_cast<unsigned int>(bits >> 32) & SignBit;
    unsigned int exponent =
        static_cast<unsigned int>((bits >> DoubleFractionBits) & DoubleExponentMask) - DoubleBias + FloatBias;
    unsigned long long mantissa = bits & ((1ull << DoubleFractionBits) - 1);
    unsigned int kept = static_cast<unsigned int>(mantissa >> DroppedBits);
    unsigned long long rest = mantissa & ((1ull << DroppedBits) - 1);
    constexpr unsigned long long Half = 1ull << (DroppedBits - 1);
    if (rest > Half || (rest == Half && (kept & 1) != 0))
    {
        kept++;
    }

    return __builtin_bit_cast(f32, (sign | exponent << FloatFractionBits) + kept);
}
#elif defined(__SNC__) || defined(__CELLOS_LV2__)
inline f32 Rounded(double value)
{
    return static_cast<f32>(value);
}
#elif defined(__GNUC__) || defined(__clang__)
constexpr f32 Rounded(double value)
{
    return static_cast<f32>(value);
}
#else
inline f32 Rounded(double value)
{
    return static_cast<f32>(value);
}
#endif

// What the R5900's variable shifts (sllv, srlv, srav) take of a shift: its low 5 bits. A shift the C++ can't keep below 32 is
// masked with it, as the retail code's wrap
CONSTEXPR u32 ShiftMask = 0x1F;

// A function or variable by the name the retail executable's symbols give it (the asm's and the Ghidra project's): a function
// defined with it takes the retail one's place, a variable declared with it is the retail data the split keeps
#if (defined(__GNUC__) || defined(__clang__)) && !defined(__SNC__)
#define RETAIL(name) asm(#name)
#else
#define RETAIL(name)
#endif

// Checks a struct against the size the game's code gives it. VS Code's C/C++ extension (__INTELLISENSE__) lays structs out
// for an x86 target, where 64 bit members are only 4 byte aligned: the compiler checks them
#if defined(__INTELLISENSE__) || defined(_MSC_VER) || defined(__SNC__) || defined(__CELLOS_LV2__) || !defined(__cpp_static_assert) || (defined(__cplusplus) && __cplusplus < 201103L)
#define CHECK_SIZE(type, size)
#define CHECK_OFFSET(type, member, offset)
#else
#define CHECK_SIZE(type, size) static_assert(sizeof(type) == (size), #type " must be " #size " bytes")
#define CHECK_OFFSET(type, member, offset) static_assert(offsetof(type, member) == (offset), #type "::" #member " must be at " #offset)
#endif
