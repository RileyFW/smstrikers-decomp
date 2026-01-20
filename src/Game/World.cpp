#include "Game/World.h"

#include "string.h"

#include "NL/nlString.h"
#include "NL/nlPrint.h"
#include "NL/nlDebug.h"
#include "NL/gl/gl.h"
#include "NL/gl/glModel.h"
#include "NL/gl/glState.h"
#include "NL/gl/glUserData.h"
#include "NL/glx/glxTexture.h"
#include "Game/Sys/debug.h"
#include "Game/Drawable/DrawableObj.h"
#include "types.h"

float g_fExponentScale = 128.0f;
float g_fExponentBase = 8.0f;
float g_fTransAdjustOccluded = 1.0f;
float g_fTransAdjustNotOccluded = 0.125f;

/**
 * Offset/Address/Size: 0x0 | 0x80194CC4 | size: 0x5C
 */
int World::CompareNameToGenericName(const char* str1, const char* str2)
{
    size_t sVar1 = strlen(str2);
    return nlStrNCmp<char>(str1 + *(int*)((u8*)this + 0x120), str2, sVar1);
}

/**
 * Offset/Address/Size: 0x5C | 0x80194D20 | size: 0x44
 */
void World::GetHashIdForGenericName(const char* str) const
{
    nlStrNCpy<char>((char*)this + *(int*)((u8*)this + 0x120) + 0xe0, str, (unsigned long)0x40 - *(int*)((u8*)this + 0x120));
    nlStringLowerHash((const char*)this + 0xe0);
}

/**
 * Offset/Address/Size: 0xA0 | 0x80194D64 | size: 0x1F0
 */
void World::GetShadowLight(const nlVector3&, float)
{
}

/**
 * Offset/Address/Size: 0x290 | 0x80194F54 | size: 0x8C
 */
bool World::AddDrawableObject(unsigned long uHashID, DrawableObject* pDrawableObject)
{
    AVLTreeNode* pExistingNode;
    AVLTreeNode** ppRoot = (AVLTreeNode**)&m_drawableMap.m_Root;

    m_drawableMap.AddAVLNode(ppRoot, &uHashID, &pDrawableObject, &pExistingNode, m_drawableMap.m_NumElements);

    DrawableObject** ppValue = nullptr;
    if (pExistingNode == nullptr)
    {
        m_drawableMap.m_NumElements++;
        ppValue = nullptr;
    }
    else
    {
        ppValue = (DrawableObject**)((u8*)pExistingNode + 0x10);
    }

    if (ppValue == nullptr)
    {
        pDrawableObject->m_pWorldContext = this;
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Offset/Address/Size: 0x31C | 0x80194FE0 | size: 0x8C
 */
HelperObject* World::FindHelperObject(unsigned long uHashID)
{
    AVLTreeEntry<unsigned long, HelperObject*>* pEntry = m_helperMap.Find(uHashID);
    if (pEntry != nullptr)
    {
        return pEntry->value;
    }
    return nullptr;
}

/**
 * Offset/Address/Size: 0x3A8 | 0x8019506C | size: 0x8C
 */
DrawableObject* World::FindDrawableObject(unsigned long uHashID)
{
    AVLTreeEntry<unsigned long, DrawableObject*>* pEntry = m_drawableMap.Find(uHashID);
    if (pEntry != nullptr)
    {
        return pEntry->value;
    }
    return nullptr;
}

/**
 * Offset/Address/Size: 0x434 | 0x801950F8 | size: 0xB20
 */
void World::Render()
{
}

/**
 * Offset/Address/Size: 0xF54 | 0x80195C18 | size: 0x1A0
 */
void World::HandleCameraSwitch()
{
}

/**
 * Offset/Address/Size: 0x10F4 | 0x80195DB8 | size: 0x24C
 */
void DoTranslucency(DrawableObject*)
{
}

/**
 * Offset/Address/Size: 0x1340 | 0x80196004 | size: 0xE8
 */
void World::IsSphereInFrustum(const nlMatrix4&, float)
{
}

/**
 * Offset/Address/Size: 0x1428 | 0x801960EC | size: 0x458
 */
void World::ExtractFrustumPlanes()
{
}

/**
 * Offset/Address/Size: 0x1880 | 0x80196544 | size: 0x4
 */
void World::UpdateInReplay(float)
{
}

/**
 * Offset/Address/Size: 0x1884 | 0x80196548 | size: 0x98
 */
void World::Update(float)
{
}

/**
 * Offset/Address/Size: 0x191C | 0x801965E0 | size: 0x260
 */
void World::CreateHelperObjFromChunk(nlChunk* chunk)
{
    const char* str = "hello world";
    char* found = nlStrChr<char>(str, 'w');
    if (found)
    {
        nlBreak();
    }
}

/**
 * Offset/Address/Size: 0x1B7C | 0x80196840 | size: 0x12C
 */
void* World::GetCustomSpecularData(glModelPacket* pPacket, bool bPerm)
{
    return nullptr;
}

/**
 * Offset/Address/Size: 0x1CA8 | 0x8019696C | size: 0x9A4
 */
void World::CreateLightUserData()
{
}

/**
 * Offset/Address/Size: 0x264C | 0x80197310 | size: 0x9D4
 */
bool World::LoadObjectData(const char*)
{
    return false;
}

/**
 * Offset/Address/Size: 0x3020 | 0x80197CE4 | size: 0x64
 */
void World::AddToHyperSTSDrawables(unsigned long key, DrawableModel* pDrawableModel)
{
    AVLTreeNode* pExistingNode;
    AVLTreeNode** ppRoot = (AVLTreeNode**)&m_hyperSTSDrawableMap.m_Root;

    m_hyperSTSDrawableMap.AddAVLNode(ppRoot, &key, &pDrawableModel, &pExistingNode, m_hyperSTSDrawableMap.m_NumElements);

    if (pExistingNode == nullptr)
    {
        m_hyperSTSDrawableMap.m_NumElements++;
    }
}

/**
 * Offset/Address/Size: 0x3084 | 0x80197D48 | size: 0x39C
 */
void World::HandleObjectCreation(WorldObjectData*)
{
}

/**
 * Offset/Address/Size: 0x3420 | 0x801980E4 | size: 0x274
 */
bool World::LoadGeometry(glModel*, unsigned long, bool, bool, unsigned long*, int*, bool)
{
    FORCE_DONT_INLINE;
    return false;
}

/**
 * Offset/Address/Size: 0x3694 | 0x80198358 | size: 0xD8
 */
bool World::LoadGeometry(const char* szWorldName, bool bMakeDrawables, bool keepTransform, unsigned long* pDrawableObjectHashes, int* pNumObjectsLoaded)
{
    char buffer[256];

    nlSNPrintf(buffer, 0xFF, "%s.glt", szWorldName);
    tDebugPrintManager::Print(DC_RENDER, "Loading world texture file: %s\n", buffer);
    glLoadTextureBundle(buffer);

    nlSNPrintf(buffer, 0xFF, "%s.glg", szWorldName);
    tDebugPrintManager::Print(DC_RENDER, "Loading world geometry file: %s\n", buffer);

    m_pModels = glLoadModel(buffer, &m_uNumModels);

    return LoadGeometry(m_pModels, m_uNumModels, bMakeDrawables, keepTransform, pDrawableObjectHashes, pNumObjectsLoaded, false);
}

/**
 * Offset/Address/Size: 0x376C | 0x80198430 | size: 0x68
 */
bool World::Load(bool forfe)
{
    bool ret = DoLoad();
    if (forfe == 0)
    {
        ret = DoInitialize();
    }
    m_Locked = 1;
    return ret;
}

/**
 * Offset/Address/Size: 0x37D4 | 0x80198498 | size: 0x580
 */
World::~World()
{
}

/**
 * Offset/Address/Size: 0x3DB4 | 0x80198A78 | size: 0x19C
 */
World::World(const char*)
{
}

// /**
//  * Offset/Address/Size: 0x0 | 0x80198C14 | size: 0x4
//  */
// void World::FixedUpdate(float)
// {
// }

// /**
//  * Offset/Address/Size: 0x4 | 0x80198C18 | size: 0x4
//  */
// void World::HandleEvent(Event*, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80198C1C | size: 0x24
//  */
// void AVLTreeBase<unsigned long, DrawableObject*, NewAdapter<AVLTreeEntry<unsigned long, DrawableObject*>>, DefaultKeyCompare<unsigned
// long>>::DeleteEntry(AVLTreeEntry<unsigned long, DrawableObject*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x24 | 0x80198C40 | size: 0x5C
//  */
// void AVLTreeBase<unsigned long, LightObject*, NewAdapter<AVLTreeEntry<unsigned long, LightObject*>>, DefaultKeyCompare<unsigned
// long>>::~AVLTreeBase()
// {
// }

// /**
//  * Offset/Address/Size: 0x80 | 0x80198C9C | size: 0x60
//  */
// void nlAVLTree<unsigned long, DrawableObject*, DefaultKeyCompare<unsigned long>>::~nlAVLTree()
// {
// }

// /**
//  * Offset/Address/Size: 0xE0 | 0x80198CFC | size: 0x5C
//  */
// void AVLTreeBase<unsigned long, DrawableObject*, NewAdapter<AVLTreeEntry<unsigned long, DrawableObject*>>, DefaultKeyCompare<unsigned
// long>>::~AVLTreeBase()
// {
// }

// /**
//  * Offset/Address/Size: 0x13C | 0x80198D58 | size: 0x60
//  */
// void nlAVLTree<unsigned long, HelperObject*, DefaultKeyCompare<unsigned long>>::~nlAVLTree()
// {
// }

// /**
//  * Offset/Address/Size: 0x19C | 0x80198DB8 | size: 0x5C
//  */
// void AVLTreeBase<unsigned long, HelperObject*, NewAdapter<AVLTreeEntry<unsigned long, HelperObject*>>, DefaultKeyCompare<unsigned
// long>>::~AVLTreeBase()
// {
// }

// /**
//  * Offset/Address/Size: 0x1F8 | 0x80198E14 | size: 0x58
//  */
// void AVLTreeBase<unsigned long, HelperObject*, NewAdapter<AVLTreeEntry<unsigned long, HelperObject*>>, DefaultKeyCompare<unsigned
// long>>::Clear()
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x80198E6C | size: 0x64
//  */
// void AVLTreeBase<unsigned long, HelperObject*, NewAdapter<AVLTreeEntry<unsigned long, HelperObject*>>, DefaultKeyCompare<unsigned
// long>>::DestroyTree(void (AVLTreeBase<unsigned long, HelperObject*, NewAdapter<AVLTreeEntry<unsigned long, HelperObject*>>,
// DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, HelperObject*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x2B4 | 0x80198ED0 | size: 0x758
//  */
// void AVLTreeBase<unsigned long, HelperObject*, NewAdapter<AVLTreeEntry<unsigned long, HelperObject*>>, DefaultKeyCompare<unsigned
// long>>::PostorderTraversal(AVLTreeEntry<unsigned long, HelperObject*>*, void (AVLTreeBase<unsigned long, HelperObject*,
// NewAdapter<AVLTreeEntry<unsigned long, HelperObject*>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long,
// HelperObject*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0xA0C | 0x80199628 | size: 0x8
//  */
// void AVLTreeBase<unsigned long, HelperObject*, NewAdapter<AVLTreeEntry<unsigned long, HelperObject*>>, DefaultKeyCompare<unsigned
// long>>::CastUp(AVLTreeNode*) const
// {
// }

// /**
//  * Offset/Address/Size: 0xA14 | 0x80199630 | size: 0x58
//  */
// void AVLTreeBase<unsigned long, LightObject*, NewAdapter<AVLTreeEntry<unsigned long, LightObject*>>, DefaultKeyCompare<unsigned
// long>>::Clear()
// {
// }

// /**
//  * Offset/Address/Size: 0xA6C | 0x80199688 | size: 0x64
//  */
// void AVLTreeBase<unsigned long, LightObject*, NewAdapter<AVLTreeEntry<unsigned long, LightObject*>>, DefaultKeyCompare<unsigned
// long>>::DestroyTree(void (AVLTreeBase<unsigned long, LightObject*, NewAdapter<AVLTreeEntry<unsigned long, LightObject*>>,
// DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, LightObject*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0xAD0 | 0x801996EC | size: 0x758
//  */
// void AVLTreeBase<unsigned long, LightObject*, NewAdapter<AVLTreeEntry<unsigned long, LightObject*>>, DefaultKeyCompare<unsigned
// long>>::PostorderTraversal(AVLTreeEntry<unsigned long, LightObject*>*, void (AVLTreeBase<unsigned long, LightObject*,
// NewAdapter<AVLTreeEntry<unsigned long, LightObject*>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, LightObject*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x1228 | 0x80199E44 | size: 0x8
//  */
// void AVLTreeBase<unsigned long, LightObject*, NewAdapter<AVLTreeEntry<unsigned long, LightObject*>>, DefaultKeyCompare<unsigned
// long>>::CastUp(AVLTreeNode*) const
// {
// }

// /**
//  * Offset/Address/Size: 0x1230 | 0x80199E4C | size: 0x58
//  */
// void AVLTreeBase<unsigned long, DrawableObject*, NewAdapter<AVLTreeEntry<unsigned long, DrawableObject*>>, DefaultKeyCompare<unsigned
// long>>::Clear()
// {
// }

// /**
//  * Offset/Address/Size: 0x1288 | 0x80199EA4 | size: 0x64
//  */
// void AVLTreeBase<unsigned long, DrawableObject*, NewAdapter<AVLTreeEntry<unsigned long, DrawableObject*>>, DefaultKeyCompare<unsigned
// long>>::DestroyTree(void (AVLTreeBase<unsigned long, DrawableObject*, NewAdapter<AVLTreeEntry<unsigned long, DrawableObject*>>,
// DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, DrawableObject*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x12EC | 0x80199F08 | size: 0x758
//  */
// void AVLTreeBase<unsigned long, DrawableObject*, NewAdapter<AVLTreeEntry<unsigned long, DrawableObject*>>, DefaultKeyCompare<unsigned
// long>>::PostorderTraversal(AVLTreeEntry<unsigned long, DrawableObject*>*, void (AVLTreeBase<unsigned long, DrawableObject*,
// NewAdapter<AVLTreeEntry<unsigned long, DrawableObject*>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long,
// DrawableObject*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x1A44 | 0x8019A660 | size: 0x8
//  */
// void AVLTreeBase<unsigned long, DrawableObject*, NewAdapter<AVLTreeEntry<unsigned long, DrawableObject*>>, DefaultKeyCompare<unsigned
// long>>::CastUp(AVLTreeNode*) const
// {
// }

// /**
//  * Offset/Address/Size: 0x1A4C | 0x8019A668 | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, HelperObject*, NewAdapter<AVLTreeEntry<unsigned long, HelperObject*>>, DefaultKeyCompare<unsigned
// long>>::CompareNodes(AVLTreeNode*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1A78 | 0x8019A694 | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, HelperObject*, NewAdapter<AVLTreeEntry<unsigned long, HelperObject*>>, DefaultKeyCompare<unsigned
// long>>::CompareKey(void*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1AA4 | 0x8019A6C0 | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, DrawableObject*, NewAdapter<AVLTreeEntry<unsigned long, DrawableObject*>>, DefaultKeyCompare<unsigned
// long>>::CompareNodes(AVLTreeNode*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1AD0 | 0x8019A6EC | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, DrawableObject*, NewAdapter<AVLTreeEntry<unsigned long, DrawableObject*>>, DefaultKeyCompare<unsigned
// long>>::CompareKey(void*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1AFC | 0x8019A718 | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, LightObject*, NewAdapter<AVLTreeEntry<unsigned long, LightObject*>>, DefaultKeyCompare<unsigned
// long>>::CompareNodes(AVLTreeNode*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1B28 | 0x8019A744 | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, LightObject*, NewAdapter<AVLTreeEntry<unsigned long, LightObject*>>, DefaultKeyCompare<unsigned
// long>>::CompareKey(void*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1B54 | 0x8019A770 | size: 0x64
//  */
// void AVLTreeBase<unsigned long, LightObject*, NewAdapter<AVLTreeEntry<unsigned long, LightObject*>>, DefaultKeyCompare<unsigned
// long>>::AllocateEntry(void*, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1BB8 | 0x8019A7D4 | size: 0x24
//  */
// void AVLTreeBase<unsigned long, LightObject*, NewAdapter<AVLTreeEntry<unsigned long, LightObject*>>, DefaultKeyCompare<unsigned
// long>>::DeleteEntry(AVLTreeEntry<unsigned long, LightObject*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1BDC | 0x8019A7F8 | size: 0x64
//  */
// void AVLTreeBase<unsigned long, DrawableObject*, NewAdapter<AVLTreeEntry<unsigned long, DrawableObject*>>, DefaultKeyCompare<unsigned
// long>>::AllocateEntry(void*, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1C40 | 0x8019A85C | size: 0x64
//  */
// void AVLTreeBase<unsigned long, HelperObject*, NewAdapter<AVLTreeEntry<unsigned long, HelperObject*>>, DefaultKeyCompare<unsigned
// long>>::AllocateEntry(void*, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1CA4 | 0x8019A8C0 | size: 0x24
//  */
// void AVLTreeBase<unsigned long, HelperObject*, NewAdapter<AVLTreeEntry<unsigned long, HelperObject*>>, DefaultKeyCompare<unsigned
// long>>::DeleteEntry(AVLTreeEntry<unsigned long, HelperObject*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8019A8E4 | size: 0x24
//  */
// void ListContainerBase<LightObject*, NewAdapter<ListEntry<LightObject*>>>::DeleteEntry(ListEntry<LightObject*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8019A908 | size: 0x24
//  */
// void DLListContainerBase<WorldAnimController*,
// NewAdapter<DLListEntry<WorldAnimController*>>>::DeleteEntry(DLListEntry<WorldAnimController*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8019A92C | size: 0x68
//  */
// void nlWalkList<ListEntry<LightObject*>, ListContainerBase<LightObject*, NewAdapter<ListEntry<LightObject*>>>>(ListEntry<LightObject*>*,
// ListContainerBase<LightObject*, NewAdapter<ListEntry<LightObject*>>>*, void (ListContainerBase<LightObject*,
// NewAdapter<ListEntry<LightObject*>>>::*)(ListEntry<LightObject*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x68 | 0x8019A994 | size: 0x28
//  */
// void nlListAddStart<ListEntry<LightObject*>>(ListEntry<LightObject*>**, ListEntry<LightObject*>*, ListEntry<LightObject*>**)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8019A9BC | size: 0x3C
//  */
// void nlWalkDLRing<DLListEntry<WorldAnimController*>, DLListContainerBase<WorldAnimController*,
// NewAdapter<DLListEntry<WorldAnimController*>>>>(DLListEntry<WorldAnimController*>*, DLListContainerBase<WorldAnimController*,
// NewAdapter<DLListEntry<WorldAnimController*>>>*, void (DLListContainerBase<WorldAnimController*,
// NewAdapter<DLListEntry<WorldAnimController*>>>::*)(DLListEntry<WorldAnimController*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x3C | 0x8019A9F8 | size: 0x20
//  */
// void nlDLRingIsEnd<DLListEntry<WorldAnimController*>>(DLListEntry<WorldAnimController*>*, DLListEntry<WorldAnimController*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x5C | 0x8019AA18 | size: 0x18
//  */
// void nlDLRingGetStart<DLListEntry<WorldAnimController*>>(DLListEntry<WorldAnimController*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8019AA30 | size: 0x60
//  */
// void nlWalkRing<DLListEntry<WorldAnimController*>, DLListContainerBase<WorldAnimController*,
// NewAdapter<DLListEntry<WorldAnimController*>>>>(DLListEntry<WorldAnimController*>*, DLListContainerBase<WorldAnimController*,
// NewAdapter<DLListEntry<WorldAnimController*>>>*, void (DLListContainerBase<WorldAnimController*,
// NewAdapter<DLListEntry<WorldAnimController*>>>::*)(DLListEntry<WorldAnimController*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8019AA90 | size: 0x2C
//  */
// void nlStrChr<char>(const char*, char)
// {
// }

// /**
//  * Offset/Address/Size: 0x2C | 0x8019AABC | size: 0x5C
//  */
// void 0x8028D34C..0x8028D350 | size: 0x4
// {
// }
