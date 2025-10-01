#ifndef _GLXTEXTURE_H_
#define _GLXTEXTURE_H_

#include "Dolphin/gx/GXEnum.h"
#include "Dolphin/gx/GXStruct.h"

enum eGXTextureFormat
{
    GXTex_RGB565 = 0,
    GXTex_RGB5A3 = 1,
    GXTex_CMPR = 2,
    GXTex_RGBA8 = 3,
    GXTex_I8 = 4,
    GXTex_I4 = 5,
    GXTex_A8 = 6,
    GXTex_IA8 = 7,
    GXTex_CI8 = 8,
    GXTex_Num = 9,
};

enum eGLTextureType
{
    GLTT_Diffuse = 0,
    GLTT_Detail = 1,
    GLTT_Shadow = 2,
    GLTT_SelfIllum = 3,
    GLTT_Gloss = 4,
    GLTT_BumpLocal = 5,
    GLTT_Num = 6,
};

enum eGLTextureState
{
    GLTS_DiffuseWrap = 0,
    GLTS_DetailWrap = 1,
    GLTS_ShadowWrap = 2,
    GLTS_SelfIllumWrap = 3,
    GLTS_GlossWrap = 4,
    GLTS_BumpLocalWrap = 5,
    GLTS_DiffuseFilter = 6,
    GLTS_DetailFilter = 7,
    GLTS_ShadowFilter = 8,
    GLTS_SelfIllumFilter = 9,
    GLTS_GlossFilter = 10,
    GLTS_BumpLocalFilter = 11,
    GLTS_DiffuseLevel = 12,
    GLTS_DetailLevel = 13,
    GLTS_ShadowLevel = 14,
    GLTS_SelfIllumLevel = 15,
    GLTS_GlossLevel = 16,
    GLTS_BumpLocalLevel = 17,
    GLTS_Num = 18,
};

enum eGLTextureFormatType
{
    eGLTextureFormatType_0,
};

class glTexBundleDict;
class GXTextureHeader;
class PlatTexture;

void glplatTextureReplace(unsigned long, const void*, unsigned long);
void glplatTextureAdd(unsigned long, const void*, unsigned long);
void glx_CreatePlatTexture();
void glplatTextureGetNumBits(int);
u32 glplatTextureGetHeight();
u32 glplatTextureGetWidth();
bool glplatTextureLoad(unsigned long);
void glplatEndLoadTextureBundle(void*, unsigned long);
void glplatBeginLoadTextureBundle(const char*, void (*)(void*, unsigned long, void*), void*);
void glxParseTextureBundle(const char*);
bool glplatLoadTextureBundle(const char* filename);
void BundleSortProc(const glTexBundleDict*, const glTexBundleDict*);
void glx_MakeTexture(GXTextureHeader*, unsigned long);
void glx_AddTex(unsigned long, PlatTexture*);
PlatTexture* glx_GetTex(unsigned long, bool, bool);
void glx_GetGridTexture(int, int);
void glx_MakeGridTexture(int, int);
void glx_SetGridMode(bool);
void glxInitTex();
void glx_BackupTexMarkerLevel(int);
void glx_AdvanceTexMarkerLevel();
void glx_GetTexMarkerLevel();
void glx_SetLoadCallback(unsigned long (*)(unsigned long));
// void nlQSort<glTexBundleDict>(glTexBundleDict*, int, int (*)(const glTexBundleDict*, const glTexBundleDict*));
// void nlListAddStart<ListEntry<PlatTexture*>>(ListEntry<PlatTexture*>**, ListEntry<PlatTexture*>*, ListEntry<PlatTexture*>**);

class PlatTexture
{
public:
    ~PlatTexture();

    void Prepare();
    void Swizzle(bool);
    void Create(int, int, eGXTextureFormat, int, bool, bool);
    void CreateWithMemory(int, int, eGXTextureFormat, int, const void*);

    /* 0x00 */ u16 m_Width;    // offset 0x0, size 0x2
    /* 0x02 */ u16 m_Height;   // offset 0x2, size 0x2
    /* 0x04 */ u16 m_Levels;   // offset 0x4, size 0x2
    /* 0x06 */ u16 m_MaxLevel; // offset 0x6, size 0x2

    /* --- DWARF seens to be different here --- */
    /* 0x8 */ u8 m_unk8;
    /* 0x9 */ s8 m_unk9;

    /* 0x08 */ eGXTextureFormat m_Format; // offset 0x8, size 0x4
    /* 0x0C */ int m_nPaletteEntries;     // offset 0xC, size 0x4
    /* 0x10 */ bool m_bMissingTexture;    // offset 0x10, size 0x1
    /* 0x14 */ char* m_SwizzledData;      // offset 0x14, size 0x4
    /* 0x18 */ char* m_LinearData;        // offset 0x18, size 0x4
    /* 0x1C */ u16* m_PaletteData;        // offset 0x1C, size 0x4
    /* 0x20 */ u8 m_Bits[4];              // offset 0x20, size 0x4
    /* 0x24 */ _GXTexObj m_TexObj;        // offset 0x24, size 0x20
    /* 0x44 */ _GXTlutObj m_TlutObj;      // offset 0x44, size 0xC
}; // total size: 0x50

class TexDestructor
{
public:
    void CallDestructor(const unsigned long&, PlatTexture**);
};

// class AVLTreeBase<unsigned long, PlatTexture*, NewAdapter<AVLTreeEntry<unsigned long, PlatTexture*>>, DefaultKeyCompare<unsigned long>>
// {
// public:
//     void DeleteEntry(AVLTreeEntry<unsigned long, PlatTexture*>*);
//     void Clear();
//     void DestroyTree(void (AVLTreeBase<unsigned long, PlatTexture*, NewAdapter<AVLTreeEntry<unsigned long, PlatTexture*>>,
//     DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, PlatTexture*>*)); void PostorderTraversal(AVLTreeEntry<unsigned
//     long, PlatTexture*>*, void (AVLTreeBase<unsigned long, PlatTexture*, NewAdapter<AVLTreeEntry<unsigned long, PlatTexture*>>,
//     DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, PlatTexture*>*)); void CastUp(AVLTreeNode*) const; void
//     Walk<TexDestructor>(TexDestructor*, void (TexDestructor::*)(const unsigned long&, PlatTexture**)); void
//     InorderWalk<TexDestructor>(AVLTreeEntry<unsigned long, PlatTexture*>*, TexDestructor*, void (TexDestructor::*)(const unsigned long&,
//     PlatTexture**)); void CompareNodes(AVLTreeNode*, AVLTreeNode*); void CompareKey(void*, AVLTreeNode*); void AllocateEntry(void*,
//     void*);
// };

// class nlWalkList<ListEntry<PlatTexture*>, ListContainerBase<PlatTexture*, NewAdapter<ListEntry<PlatTexture*>>>>(ListEntry<PlatTexture*>*,
// ListContainerBase<PlatTexture*, NewAdapter<ListEntry<PlatTexture*>>>*, void (ListContainerBase<PlatTexture*,
// NewAdapter<ListEntry<PlatTexture*>>>
// {
// public:
//     void *)(ListEntry<PlatTexture*>*));
// };

// class ListContainerBase<PlatTexture*, NewAdapter<ListEntry<PlatTexture*>>>
// {
// public:
//     void DeleteEntry(ListEntry<PlatTexture*>*);
// };

// class nlListContainer<PlatTexture*>
// {
// public:
//     void ~nlListContainer();
// };

#endif // _GLXTEXTURE_H_
