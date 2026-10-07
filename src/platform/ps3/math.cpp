#include "platform/math.h"
#include "game/math.h"
#include <math.h>

namespace Platform::Math
{
void SinCos(f32 first, f32 second, f32* out)
{
    if (!out) return;
    out[0] = sinf(first);
    out[1] = cosf(first);
    out[2] = sinf(second);
    out[3] = cosf(second);
}

f32 Max(f32 first, f32 second)
{
    return first > second ? first : second;
}

f32 Min(f32 first, f32 second)
{
    return first < second ? first : second;
}

void SlerpRotations(const Vector4* from, const Vector4* to, f32 share, Vector4* out)
{
    if (!from || !to || !out) return;
    ::SlerpRotations(share, out, from, to);
}

void EulerRotation(const Vector4* anglesNow, const Vector4* anglesNext, const Vector4* moveNow, const Vector4* moveNext,
                   Vector4* rotation, Vector4* move)
{
    f32 share = anglesNext ? anglesNext->w : 0.0f;
    if (rotation && anglesNow && anglesNext)
    {
        Lerp(anglesNow, anglesNext, share, rotation);
    }
    if (move && moveNow && moveNext)
    {
        Lerp(moveNow, moveNext, share, move);
    }
}

void TurnRotation(const Vector4* by, Vector4* rotation)
{
    if (!by || !rotation) return;
    Vector4 temp = *rotation;
    ::MultiplyRotations(rotation, &temp, by);
}

void Lerp(const Vector4* from, const Vector4* to, f32 share, Vector4* out)
{
    if (!from || !to || !out) return;
    out->x = from->x + (to->x - from->x) * share;
    out->y = from->y + (to->y - from->y) * share;
    out->z = from->z + (to->z - from->z) * share;
    out->w = 1.0f;
}

void JointMatrix(const Vector4* rotation, const Vector4* parentScale, const Vector4* scale, const Vector4* translation,
                 const Matrix4x4* parent, Matrix4x4* out)
{
    if (!out) return;
    (void)parentScale;
    Matrix4x4 mat;
    if (rotation != nullptr)
    {
        MatrixFromRotation(&mat, rotation);
        if (scale != nullptr)
        {
            MatrixScaleRows(&mat, scale);
        }
    }
    else
    {
        MatrixIdentity(&mat);
    }

    if (translation != nullptr)
    {
        mat.m[3][0] = translation->x;
        mat.m[3][1] = translation->y;
        mat.m[3][2] = translation->z;
        mat.m[3][3] = translation->w;
    }
    else
    {
        mat.m[3][0] = 0.0f;
        mat.m[3][1] = 0.0f;
        mat.m[3][2] = 0.0f;
        mat.m[3][3] = 1.0f;
    }

    if (parent != nullptr)
    {
        MultiplyByParent(&mat, parent, out);
    }
    else
    {
        *out = mat;
    }
}

void MultiplyByParent(const Matrix4x4* matrix, const Matrix4x4* parent, Matrix4x4* out)
{
    if (!matrix || !parent || !out) return;
    Matrix4x4 res;
    for (int r = 0; r < 4; ++r)
    {
        for (int c = 0; c < 4; ++c)
        {
            res.m[r][c] = matrix->m[r][0] * parent->m[0][c]
                        + matrix->m[r][1] * parent->m[1][c]
                        + matrix->m[r][2] * parent->m[2][c]
                        + matrix->m[r][3] * parent->m[3][c];
        }
    }
    *out = res;
}

f32 ViewDistance(s32 view, const f32* point)
{
    (void)view;
    if (!point) return 0.0f;
    return sqrtf(point[0] * point[0] + point[1] * point[1] + point[2] * point[2]);
}

bool ParticleBlockView(s32 view, bool keepsTranslation, const f32* extents, const Matrix4x4* gravity, const f32* place, f32 scale,
                       Matrix4x4* matrix, f32* distance)
{
    (void)view;
    (void)keepsTranslation;
    (void)extents;
    if (gravity && matrix)
    {
        *matrix = *gravity;
    }
    if (place && matrix)
    {
        matrix->m[3][0] = place[0] * scale;
        matrix->m[3][1] = place[1] * scale;
        matrix->m[3][2] = place[2] * scale;
    }
    if (distance)
    {
        *distance = place ? sqrtf(place[0] * place[0] + place[1] * place[1] + place[2] * place[2]) : 0.0f;
    }
    return false;
}

f32 DivideBySquareRoot(f32 value, f32 square)
{
    if (square <= 0.0f) return 0.0f;
    return value / sqrtf(square);
}

static const Vector4* s_RayStart = nullptr;
static const Vector4* s_RayEnd = nullptr;

void SetRay(const Vector4* start, const Vector4* end)
{
    s_RayStart = start;
    s_RayEnd = end;
}

void StartRayTriangle(const Vector4* vertices, const Vector4* nearest)
{
    (void)vertices;
    (void)nearest;
}

bool FinishRayTriangle(Vector4* hit)
{
    if (hit)
    {
        hit->x = 0.0f;
        hit->y = 0.0f;
        hit->z = 0.0f;
        hit->w = 0.0f;
    }
    return false;
}
}
