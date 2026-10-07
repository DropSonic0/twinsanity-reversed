#include "platform/graphics.h"
#include <string.h>
#include <stdlib.h>

namespace Platform::Graphics
{
static Vector4 s_ViewPlanes[6];
static bool s_DevicesReset = false;
static bool s_PathReset = false;
static bool s_ShadowPassSetup = false;
static bool s_ShadowsActive = false;
static bool s_ScreenModelActive = false;
static u32 s_ScreenModelColour = 0xFFFFFFFF;

void ResetDevices()
{
    s_DevicesReset = true;
}

void ResetPath()
{
    s_PathReset = true;
}

void WaitVSync()
{
    static volatile u32 vCount = 0;
    vCount++;
}

bool IsPalDisplay()
{
    return true;
}

void WaitIdle()
{
    static volatile u32 idleCount = 0;
    idleCount++;
}

void StartRenderer(s32 height, bool pal)
{
    (void)height;
    (void)pal;
}

void FinishRendererStart()
{
}

void MoveDisplay(const Vector2* offset)
{
    (void)offset;
}

void StepAnimations(const TimeClock* clock)
{
    (void)clock;
}

void SetUpRenderTarget(RenderTargetDescription* target)
{
    (void)target;
}

void Present(const void* commands)
{
    (void)commands;
}

void PresentFromInterrupt(const void* commands)
{
    (void)commands;
}

void WaitSent()
{
    WaitIdle();
}

void ResetBuckets(bool movie)
{
    (void)movie;
}

void SubmitBuckets(bool fromInterrupt)
{
    (void)fromInterrupt;
}

void* AllocFrameMemory(u32 count, u32 size)
{
    return malloc(count * size);
}

void FinishFrame()
{
}

void FinishScene(bool effects)
{
    (void)effects;
}

void StartFrame(const FrameStart& frame)
{
    (void)frame;
}

void UseHelperPrograms(u32 set, bool wait)
{
    (void)set;
    (void)wait;
}

Material* MakeFlatMaterial()
{
    return nullptr;
}

Material* FlatMaterial()
{
    return nullptr;
}

void ConstructMaterial(Material* material)
{
    if (material)
    {
        memset(material, 0, MaterialStorage);
    }
}

void DestroyMaterial(Material* material)
{
    if (material)
    {
        memset(material, 0, MaterialStorage);
    }
}

void* MakeParticleMaterial(Material* material)
{
    ConstructMaterial(material);
    return material;
}

void MakeDistortionMaterial(Material* material)
{
    ConstructMaterial(material);
}

void ChainParticleBlocks(u8* const* blocks, s32 count)
{
    (void)blocks;
    (void)count;
}

void EndParticleBlock(u8* block)
{
    (void)block;
}

void InitParticleBlock(u8* block, bool hexagons)
{
    if (block)
    {
        u32 size = hexagons ? HexagonBlockBytes : ParticleBlockBytes;
        memset(block, 0, size);
    }
}

void InitParticleRenderTable(u8* table)
{
    if (table)
    {
        memset(table, 0, ParticleRenderTableBytes);
    }
}

void InitParticleGraphics()
{
}

void WriteParticleRenderTable(u8* table, const ParticleLook& look)
{
    if (table)
    {
        memcpy(table, &look, sizeof(ParticleLook) < ParticleRenderTableBytes ? sizeof(ParticleLook) : ParticleRenderTableBytes);
    }
}

void DrawParticleBlock(u8* block, u8* table, const Matrix4x4* matrix, Material* material, f32 time)
{
    (void)block;
    (void)table;
    (void)matrix;
    (void)material;
    (void)time;
}

void DrawDistortionBlock(u8* block, u8* table, const Matrix4x4* matrix, Material* material, f32 time, f32 distortionX, f32 distortionY)
{
    (void)block;
    (void)table;
    (void)matrix;
    (void)material;
    (void)time;
    (void)distortionX;
    (void)distortionY;
}

void LoadDecalView(const Matrix4x4* chunkMatrices, const Matrix4x4* fromChunk)
{
    (void)chunkMatrices;
    (void)fromChunk;
}

void LoadDecalType(DecalType* type)
{
    (void)type;
}

void DrawDecals(DecalData* decals)
{
    (void)decals;
}

void AgeDecal(const f32* place, const s32* frame, s32 variant, DecalLook* look)
{
    (void)place;
    (void)frame;
    (void)variant;
    if (look)
    {
        memset(look, 0, sizeof(DecalLook));
    }
}

void SetViewFrustum(f32 near, f32 far, f32 aspect, const s32* fieldOfView)
{
    (void)near;
    (void)far;
    (void)aspect;
    (void)fieldOfView;
}

void LoadChunkPlanes(const Matrix4x4* place)
{
    (void)place;
}

void LoadPortalPlanes(const Matrix4x4* place, const Vector4* portal)
{
    (void)place;
    (void)portal;
}

void LoadCullingView(const Matrix4x4* toClip, const Matrix4x4* toScreen, const Vector4* camera)
{
    (void)toClip;
    (void)toScreen;
    (void)camera;
}

void CullLoadLink(const Matrix4x4* chunk, const Matrix4x4* object)
{
    (void)chunk;
    (void)object;
}

void CullLoadModel(const Matrix4x4* model)
{
    (void)model;
}

void CullTestBox(const Vector4* corners)
{
    (void)corners;
}

void CullTestBoxAt(const Box* box, const Matrix4x4* model)
{
    (void)box;
    (void)model;
}

CullOutcome CullResult()
{
    CullOutcome outcome = {0, 0, 0};
    return outcome;
}

void CullMatrices(Matrix4x4* clipped, Matrix4x4* toScreen)
{
    (void)clipped;
    (void)toScreen;
}

void ClipBox(const Matrix4x4* view, const Box* box, u32* flags)
{
    (void)view;
    (void)box;
    if (flags) *flags = 0;
}

const Vector4* ViewPlanes()
{
    return s_ViewPlanes;
}

void ClipBoxAt(const Matrix4x4* view, const Box* box, u32* flags, const Matrix4x4* model)
{
    (void)view;
    (void)box;
    (void)model;
    if (flags) *flags = 0;
}

void DrawPlacedModel(RigidModel* model, ChunkView* view, const Matrix4x4* world)
{
    (void)model;
    (void)view;
    (void)world;
}

RigidModel* LodModelAt(Lod* lod, u32 distance)
{
    (void)lod;
    (void)distance;
    return nullptr;
}

s32 LoadParticleView(const Matrix4x4* matrices, s32 index)
{
    (void)matrices;
    (void)index;
    return index;
}

void SetFontPage(Material* material, u32 page)
{
    (void)material;
    (void)page;
}

void DrawSprite(Material* material, u32 colour, const Rectangle& place, const Rectangle& texture)
{
    (void)material;
    (void)colour;
    (void)place;
    (void)texture;
}

void DrawTurnedSprite(Material* material, u32 colour, const Vector2* corners, const Rectangle& texture)
{
    (void)material;
    (void)colour;
    (void)corners;
    (void)texture;
}

void DrawStrip(Material* material, u32 count, const Vector2* places, const u32* colours)
{
    (void)material;
    (void)count;
    (void)places;
    (void)colours;
}

void DrawRigidModel(RigidModel* model, const Matrix4x4* matrix, const ModelLights& lights, u32 mode)
{
    (void)model;
    (void)matrix;
    (void)lights;
    (void)mode;
}

void DrawSkin(Skin* skin, const Matrix4x4* joints, u32 jointCount, const Matrix4x4* matrix, const ModelLights& lights, u32 mode)
{
    (void)skin;
    (void)joints;
    (void)jointCount;
    (void)matrix;
    (void)lights;
    (void)mode;
}

void DrawBlendSkin(BlendSkin* skin, const Matrix4x4* joints, u32 jointCount, const Matrix4x4* matrix, const ModelLights& lights,
                   const f32* weights, const s32* shapes, s32 shapeCount, u32 mode)
{
    (void)skin;
    (void)joints;
    (void)jointCount;
    (void)matrix;
    (void)lights;
    (void)weights;
    (void)shapes;
    (void)shapeCount;
    (void)mode;
}

void SetUpShadowPass()
{
    s_ShadowPassSetup = true;
}

void BeginShadows()
{
    s_ShadowsActive = true;
}

void EndShadows()
{
    s_ShadowsActive = false;
}

void DrawShadowMesh(RigidModel* mesh, const Matrix4x4* toScreen, const Matrix4x4* toCamera, const Matrix4x4* world)
{
    (void)mesh;
    (void)toScreen;
    (void)toCamera;
    (void)world;
}

void BeginScreenModel()
{
    s_ScreenModelActive = true;
}

void SetScreenModelMaterial(Material* material)
{
    (void)material;
}

void SetScreenModelColour(u32 colour)
{
    s_ScreenModelColour = colour;
}

void AddScreenModelVertex(const Vector4* place)
{
    (void)place;
}

ScreenModel* EndScreenModel()
{
    s_ScreenModelActive = false;
    return nullptr;
}

void DeleteScreenModel(ScreenModel* model)
{
    if (model)
    {
        free(model);
    }
}

void DrawScreenModel(ScreenModel* model, const Matrix4x4* toScreen, const Matrix4x4* toClip, const Vector4* clip)
{
    (void)model;
    (void)toScreen;
    (void)toClip;
    (void)clip;
}

Material* MakeSkidMaterial(bool subtracting)
{
    (void)subtracting;
    return nullptr;
}

void RestartAnimations(RigidModel* model)
{
    (void)model;
}

void RestartAnimations(Skin* skin)
{
    (void)skin;
}

void RestartAnimations(BlendSkin* skin)
{
    (void)skin;
}

MaterialResource* FirstMaterial(const RigidModel* model)
{
    (void)model;
    return nullptr;
}

GameTexture* NewTexture(u32 id)
{
    (void)id;
    return nullptr;
}

void DeleteTexture(GameTexture* texture)
{
    (void)texture;
}

void ReadTexture(GameTexture* texture, Stream* stream)
{
    (void)texture;
    (void)stream;
}

MaterialResource* NewMaterial(u32 id)
{
    (void)id;
    return nullptr;
}

void DeleteMaterial(MaterialResource* material)
{
    (void)material;
}

void ReadMaterial(MaterialResource* material, Stream* stream)
{
    (void)material;
    (void)stream;
}

RigidModelData* NewModel(u32 id)
{
    (void)id;
    return nullptr;
}

void DeleteModel(RigidModelData* model)
{
    (void)model;
}

void ReadModel(RigidModelData* model, Stream* stream)
{
    (void)model;
    (void)stream;
}

RigidModel* NewRigidModel(u32 id)
{
    (void)id;
    return nullptr;
}

void DeleteRigidModel(RigidModel* model)
{
    (void)model;
}

void ReadRigidModel(RigidModel* model, Stream* stream)
{
    (void)model;
    (void)stream;
}

Skin* NewSkin(u32 id)
{
    (void)id;
    return nullptr;
}

void DeleteSkin(Skin* skin)
{
    (void)skin;
}

void ReadSkin(Skin* skin, Stream* stream)
{
    (void)skin;
    (void)stream;
}

BlendSkin* NewBlendSkin(u32 id)
{
    (void)id;
    return nullptr;
}

void DeleteBlendSkin(BlendSkin* skin)
{
    (void)skin;
}

void ReadBlendSkin(BlendSkin* skin, Stream* stream)
{
    (void)skin;
    (void)stream;
}

RigidModel* NewMesh(u32 id)
{
    (void)id;
    return nullptr;
}

void DeleteMesh(RigidModel* mesh)
{
    (void)mesh;
}

void ReadMesh(RigidModel* mesh, Stream* stream)
{
    (void)mesh;
    (void)stream;
}

Lod* NewLod(u32 id)
{
    (void)id;
    return nullptr;
}

void DeleteLod(Lod* lod)
{
    (void)lod;
}

void ReadLod(Lod* lod, Stream* stream)
{
    (void)lod;
    (void)stream;
}

Sky* NewSky(u32 id)
{
    (void)id;
    return nullptr;
}

void DeleteSky(Sky* sky)
{
    (void)sky;
}

void ReadSky(Sky* sky, Stream* stream)
{
    (void)sky;
    (void)stream;
}

void DrawChunkSky(Sky* sky, RenderView* view)
{
    (void)sky;
    (void)view;
}

void LoadParticlePage(ParticlePage* page, const char* path, bool decals)
{
    (void)page;
    (void)path;
    (void)decals;
}

void ReadParticlePage(ParticlePage* page, Stream* stream, bool decals)
{
    (void)page;
    (void)stream;
    (void)decals;
}
}
