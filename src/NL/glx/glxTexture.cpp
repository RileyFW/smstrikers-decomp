#include "NL/glx/glxTexture.h"
#include "types.h"

/**
 * Offset/Address/Size: 0x0 | 0x801B72BC | size: 0x230
 */
void glplatTextureReplace(unsigned long, const void*, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x230 | 0x801B74EC | size: 0x98
 */
void glplatTextureAdd(unsigned long, const void*, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x2C8 | 0x801B7584 | size: 0x1B4
 */
void PlatTexture::Prepare()
{
}

/**
 * Offset/Address/Size: 0x47C | 0x801B7738 | size: 0x68
 */
void PlatTexture::Swizzle(bool)
{
}

/**
 * Offset/Address/Size: 0x4E4 | 0x801B77A0 | size: 0xD8
 */
void PlatTexture::Create(int, int, eGXTextureFormat, int, bool, bool)
{
}

/**
 * Offset/Address/Size: 0x5BC | 0x801B7878 | size: 0x24
 */
void PlatTexture::CreateWithMemory(int, int, eGXTextureFormat, int, const void*)
{
}

/**
 * Offset/Address/Size: 0x5E0 | 0x801B789C | size: 0x64
 */
PlatTexture::~PlatTexture()
{
}

/**
 * Offset/Address/Size: 0x644 | 0x801B7900 | size: 0xA8
 */
PlatTexture* glx_CreatePlatTexture()
{
    return new PlatTexture();
}

/**
 * Offset/Address/Size: 0x6EC | 0x801B79A8 | size: 0x104
 */
void glplatTextureGetNumBits(int)
{
}

/**
 * Offset/Address/Size: 0x7F0 | 0x801B7AAC | size: 0x10
 */
u32 glplatTextureGetHeight()
{
    return 0;
}

/**
 * Offset/Address/Size: 0x800 | 0x801B7ABC | size: 0x10
 */
u32 glplatTextureGetWidth()
{
    return 0;
}

/**
 * Offset/Address/Size: 0x810 | 0x801B7ACC | size: 0x64
 */
bool glplatTextureLoad(unsigned long)
{
    return false;
}

/**
 * Offset/Address/Size: 0x874 | 0x801B7B30 | size: 0x20
 */
void glplatEndLoadTextureBundle(void*, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x894 | 0x801B7B50 | size: 0xA8
 */
void glplatBeginLoadTextureBundle(const char*, void (*)(void*, unsigned long, void*), void*)
{
}

/**
 * Offset/Address/Size: 0x93C | 0x801B7BF8 | size: 0xB8
 */
void glxParseTextureBundle(const char*)
{
}

/**
 * Offset/Address/Size: 0x9F4 | 0x801B7CB0 | size: 0x1D0
 */
bool glplatLoadTextureBundle(const char* filename)
{
    return false;
}

/**
 * Offset/Address/Size: 0xBC4 | 0x801B7E80 | size: 0x10
 */
void BundleSortProc(const glTexBundleDict*, const glTexBundleDict*)
{
}

/**
 * Offset/Address/Size: 0xBD4 | 0x801B7E90 | size: 0x32C
 */
void glx_MakeTexture(GXTextureHeader*, unsigned long)
{
}

/**
 * Offset/Address/Size: 0xF00 | 0x801B81BC | size: 0x94
 */
bool glx_AddTex(unsigned long handle, PlatTexture* platTex)
{
    return false;
}

/**
 * Offset/Address/Size: 0xF94 | 0x801B8250 | size: 0x194
 */
PlatTexture* glx_GetTex(unsigned long handle, bool bMissingFatal, bool bAllowGrids)
{
    FORCE_DONT_INLINE;
    return nullptr;
}

/**
 * Offset/Address/Size: 0x1128 | 0x801B83E4 | size: 0x1C4
 */
void glx_GetGridTexture(int, int)
{
}

/**
 * Offset/Address/Size: 0x12EC | 0x801B85A8 | size: 0x53C
 */
void glx_MakeGridTexture(int, int)
{
}

/**
 * Offset/Address/Size: 0x1828 | 0x801B8AE4 | size: 0x10
 */
void glx_SetGridMode(bool)
{
}

/**
 * Offset/Address/Size: 0x1838 | 0x801B8AF4 | size: 0xA4
 */
void glxInitTex()
{
}

/**
 * Offset/Address/Size: 0x18DC | 0x801B8B98 | size: 0xA0
 */
void glx_BackupTexMarkerLevel(int)
{
}

/**
 * Offset/Address/Size: 0x197C | 0x801B8C38 | size: 0x48
 */
void TexDestructor::CallDestructor(const unsigned long&, PlatTexture**)
{
}

/**
 * Offset/Address/Size: 0x19C4 | 0x801B8C80 | size: 0x10
 */
void glx_AdvanceTexMarkerLevel()
{
}

/**
 * Offset/Address/Size: 0x19D4 | 0x801B8C90 | size: 0x8
 */
void glx_GetTexMarkerLevel()
{
}

/**
 * Offset/Address/Size: 0x19DC | 0x801B8C98 | size: 0x10
 */
void glx_SetLoadCallback(unsigned long (*)(unsigned long))
{
}

// /**
//  * Offset/Address/Size: 0x0 | 0x801B8CA8 | size: 0x24
//  */
// void AVLTreeBase<unsigned long, PlatTexture*, NewAdapter<AVLTreeEntry<unsigned long, PlatTexture*>>, DefaultKeyCompare<unsigned
// long>>::DeleteEntry(AVLTreeEntry<unsigned long, PlatTexture*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x24 | 0x801B8CCC | size: 0x58
//  */
// void AVLTreeBase<unsigned long, PlatTexture*, NewAdapter<AVLTreeEntry<unsigned long, PlatTexture*>>, DefaultKeyCompare<unsigned
// long>>::Clear()
// {
// }

// /**
//  * Offset/Address/Size: 0x7C | 0x801B8D24 | size: 0x64
//  */
// void AVLTreeBase<unsigned long, PlatTexture*, NewAdapter<AVLTreeEntry<unsigned long, PlatTexture*>>, DefaultKeyCompare<unsigned
// long>>::DestroyTree(void (AVLTreeBase<unsigned long, PlatTexture*, NewAdapter<AVLTreeEntry<unsigned long, PlatTexture*>>,
// DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, PlatTexture*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0xE0 | 0x801B8D88 | size: 0x758
//  */
// void AVLTreeBase<unsigned long, PlatTexture*, NewAdapter<AVLTreeEntry<unsigned long, PlatTexture*>>, DefaultKeyCompare<unsigned
// long>>::PostorderTraversal(AVLTreeEntry<unsigned long, PlatTexture*>*, void (AVLTreeBase<unsigned long, PlatTexture*,
// NewAdapter<AVLTreeEntry<unsigned long, PlatTexture*>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, PlatTexture*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x838 | 0x801B94E0 | size: 0x8
//  */
// void AVLTreeBase<unsigned long, PlatTexture*, NewAdapter<AVLTreeEntry<unsigned long, PlatTexture*>>, DefaultKeyCompare<unsigned
// long>>::CastUp(AVLTreeNode*) const
// {
// }

// /**
//  * Offset/Address/Size: 0x840 | 0x801B94E8 | size: 0x44
//  */
// void AVLTreeBase<unsigned long, PlatTexture*, NewAdapter<AVLTreeEntry<unsigned long, PlatTexture*>>, DefaultKeyCompare<unsigned
// long>>::Walk<TexDestructor>(TexDestructor*, void (TexDestructor::*)(const unsigned long&, PlatTexture**))
// {
// }

// /**
//  * Offset/Address/Size: 0x884 | 0x801B952C | size: 0x2CC
//  */
// void AVLTreeBase<unsigned long, PlatTexture*, NewAdapter<AVLTreeEntry<unsigned long, PlatTexture*>>, DefaultKeyCompare<unsigned
// long>>::InorderWalk<TexDestructor>(AVLTreeEntry<unsigned long, PlatTexture*>*, TexDestructor*, void (TexDestructor::*)(const unsigned
// long&, PlatTexture**))
// {
// }

// /**
//  * Offset/Address/Size: 0xB50 | 0x801B97F8 | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, PlatTexture*, NewAdapter<AVLTreeEntry<unsigned long, PlatTexture*>>, DefaultKeyCompare<unsigned
// long>>::CompareNodes(AVLTreeNode*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0xB7C | 0x801B9824 | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, PlatTexture*, NewAdapter<AVLTreeEntry<unsigned long, PlatTexture*>>, DefaultKeyCompare<unsigned
// long>>::CompareKey(void*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0xBA8 | 0x801B9850 | size: 0x64
//  */
// void AVLTreeBase<unsigned long, PlatTexture*, NewAdapter<AVLTreeEntry<unsigned long, PlatTexture*>>, DefaultKeyCompare<unsigned
// long>>::AllocateEntry(void*, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801B98B4 | size: 0x28
//  */
// void nlQSort<glTexBundleDict>(glTexBundleDict*, int, int (*)(const glTexBundleDict*, const glTexBundleDict*))
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801B98DC | size: 0x28
//  */
// void nlListAddStart<ListEntry<PlatTexture*>>(ListEntry<PlatTexture*>**, ListEntry<PlatTexture*>*, ListEntry<PlatTexture*>**)
// {
// }

// /**
//  * Offset/Address/Size: 0x28 | 0x801B9904 | size: 0x68
//  */
// void nlWalkList<ListEntry<PlatTexture*>, ListContainerBase<PlatTexture*, NewAdapter<ListEntry<PlatTexture*>>>>(ListEntry<PlatTexture*>*,
// ListContainerBase<PlatTexture*, NewAdapter<ListEntry<PlatTexture*>>>*, void (ListContainerBase<PlatTexture*,
// NewAdapter<ListEntry<PlatTexture*>>>::*)(ListEntry<PlatTexture*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0xE4 | 0x801B9A50 | size: 0x24
//  */
// void ListContainerBase<PlatTexture*, NewAdapter<ListEntry<PlatTexture*>>>::DeleteEntry(ListEntry<PlatTexture*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x108 | 0x801B9A74 | size: 0x8C
//  */
// void nlListContainer<PlatTexture*>::~nlListContainer()
// {
// }
