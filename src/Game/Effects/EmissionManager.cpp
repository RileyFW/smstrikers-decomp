#include "Game/Effects/EmissionManager.h"
#include "Dolphin/types.h"
#include "NL/nlAVLTree.h"

static class efList* controllers = nullptr;
static nlAVLTree<unsigned long, LingerMessage*, DefaultKeyCompare<unsigned long> >* lingerers = nullptr;
static int g_nNumLights = 0;
static unsigned long fx_sTerrain;

static s8 init = 0;
static EmissionManager instance;

extern eGLView defaultView;

/**
 * Offset/Address/Size: 0xE38 | 0x801F9758 | size: 0x20
 */
EmissionManager& EmissionManager::InstanceForReplayOnly()
{
    if (init == 0)
    {
        instance.m_bRecording = true;
        init = 1;
    }
    return instance;
}

/**
 * Offset/Address/Size: 0xD6C | 0x801F968C | size: 0xCC
 */
void EmissionManager::Startup(eGLView)
{
}

/**
 * Offset/Address/Size: 0xD0C | 0x801F962C | size: 0x60
 */
// void nlAVLTree<unsigned long, LingerMessage*, DefaultKeyCompare<unsigned long> >::~nlAVLTree()
// {
// }

/**
 * Offset/Address/Size: 0xC1C | 0x801F953C | size: 0xF0
 */
void EmissionManager::Shutdown()
{
}

/**
 * Offset/Address/Size: 0x930 | 0x801F9250 | size: 0x2EC
 */
void EmissionManager::Update(float)
{
}

/**
 * Offset/Address/Size: 0x928 | 0x801F9248 | size: 0x8
 */
s32 EmissionManager::GetNumLights()
{
    return g_nNumLights;
}

/**
 * Offset/Address/Size: 0x8F8 | 0x801F9218 | size: 0x30
 */
void EmissionManager::GetLight(int)
{
}

/**
 * Offset/Address/Size: 0x8A8 | 0x801F91C8 | size: 0x50
 */
void EmissionManager::AddEffectsLight(const EffectsLight&)
{
}

/**
 * Offset/Address/Size: 0x85C | 0x801F917C | size: 0x4C
 */
void EmissionManager::Render()
{
}

/**
 * Offset/Address/Size: 0x854 | 0x801F9174 | size: 0x8
 */
efList* EmissionManager::GetContainer()
{
    return controllers;
}

/**
 * Offset/Address/Size: 0x798 | 0x801F90B8 | size: 0xBC
 */
EmissionController* EmissionManager::Create(EffectsGroup* pEffectsGroup, unsigned short id)
{
    u16 _id = id;

    static u16 globalIdCounter = 1;

    if (_id == 0)
    {
        _id = globalIdCounter;
        globalIdCounter++;
    }

    if (globalIdCounter > 0x7E16)
    {
        globalIdCounter = 0;
    }

    EmissionController* pController = new (nlMalloc(sizeof(EmissionController), 8, false)) EmissionController(pEffectsGroup, id, defaultView);

    controllers->Append(pController);
    return pController;
}

/**
 * Offset/Address/Size: 0x768 | 0x801F9088 | size: 0x30
 */
bool EmissionManager::IsStillAlive(EmissionController* controller)
{
    EmissionController* current;
    current = (EmissionController*)(controllers->m_headNode);

    while (current != nullptr)
    {
        if (current == controller)
        {
            return true;
        }
        current = (EmissionController*)(current->m_nextNode);
    }

    return false;
}

/**
 * Offset/Address/Size: 0x6EC | 0x801F900C | size: 0x7C
 */
void EmissionManager::Kill(unsigned long userData, const EffectsGroup* pEffectsGroup)
{
    EmissionController* current;

    current = (EmissionController*)(controllers->m_headNode);

    while (current != nullptr)
    {
        if (pEffectsGroup == nullptr || current->m_pGroup == pEffectsGroup)
        {
            if (userData == current->m_uUserData)
            {
                current->Die();
            }
        }

        current = (EmissionController*)(current->m_nextNode);
    }
}

/**
 * Offset/Address/Size: 0x68C | 0x801F8FAC | size: 0x60
 */
bool EmissionManager::IsPlaying(unsigned long userData, const EffectsGroup* pEffectsGroup)
{
    EmissionController* current;

    if (controllers == nullptr)
    {
        return false;
    }

    current = (EmissionController*)(controllers->m_headNode);

    while (current != nullptr)
    {
        if (pEffectsGroup == nullptr || current->m_pGroup == pEffectsGroup)
        {
            if (userData == 0 || userData == current->m_uUserData)
            {
                return true;
            }
        }

        current = (EmissionController*)(current->m_nextNode);
    }

    return false;
}

/**
 * Offset/Address/Size: 0x5EC | 0x801F8F0C | size: 0xA0
 */
void EmissionManager::DestroyAll(bool exceptPersistent)
{
    EmissionController* next;
    EmissionController* current;

    if (controllers == nullptr)
    {
        return;
    }

    current = (EmissionController*)(controllers->m_headNode);

    while (current != nullptr)
    {
        next = (EmissionController*)(current->m_nextNode);

        if ((defaultView == current->m_GlView) && ((!exceptPersistent) || (current->m_uUserData + 0x21530000 != 0x0000BEEF)))
        {
            controllers->Remove(current);
            delete current;
        }

        current = next;
    }
}

/**
 * Offset/Address/Size: 0x54C | 0x801F8E6C | size: 0xA0
 */
void EmissionManager::Destroy(unsigned long userData, const EffectsGroup* pEffectsGroup)
{
}

/**
 * Offset/Address/Size: 0x520 | 0x801F8E40 | size: 0x2C
 */
void EmissionManager::ResetLingerers()
{
    if (lingerers != nullptr)
    {
        lingerers->DeleteValues();
    }
}

/**
 * Offset/Address/Size: 0x4D0 | 0x801F8DF0 | size: 0x50
 */
void EmissionManager::AddError(const char*, ...)
{
}

/**
 * Offset/Address/Size: 0x24C | 0x801F8B6C | size: 0x284
 */
void EmissionManager::Replay(LoadFrame&)
{
}

/**
 * Offset/Address/Size: 0x11C | 0x801F8A3C | size: 0x130
 */
void EmissionManager::Replay(SaveFrame&)
{
}

/**
 * Offset/Address/Size: 0x114 | 0x801F8A34 | size: 0x8
 */
u32 fxGetTerrain()
{
    return fx_sTerrain;
}

/**
 * Offset/Address/Size: 0x10C | 0x801F8A2C | size: 0x8
 */
void fxSetTerrain(unsigned long terrainID)
{
    fx_sTerrain = terrainID;
}

/**
 * Offset/Address/Size: 0x0 | 0x801F8920 | size: 0x10C
 */
void EmissionManager::KillOldest(int, bool)
{
}

// /**
//  * Offset/Address/Size: 0x2C | 0x801FA600 | size: 0x254
//  */
//  void LoadFrame::Replayable<0, EmissionController>(EmissionController&, NotReplayablePod)
//  {
//  }

//  /**
//   * Offset/Address/Size: 0x0 | 0x801FA5D4 | size: 0x2C
//   */
//  void LoadFrame::Replayable<0, EmissionController>(EmissionController&)
//  {
//  }

//  /**
//   * Offset/Address/Size: 0x3C4 | 0x801FA558 | size: 0x7C
//   */
//  void Replayable<0, SaveFrame, FloatCompressor<-255, 255, 6>>(SaveFrame&, const FloatCompressor<-255, 255, 6>&)
//  {
//  }

//  /**
//   * Offset/Address/Size: 0x364 | 0x801FA4F8 | size: 0x60
//   */
//  void Replayable<0, LoadFrame, FloatCompressor<-255, 255, 6>>(LoadFrame&, const FloatCompressor<-255, 255, 6>&)
//  {
//  }

//  /**
//   * Offset/Address/Size: 0x324 | 0x801FA4B8 | size: 0x40
//   */
//  void Replayable<0, SaveFrame, char>(SaveFrame&, char&)
//  {
//  }

//  /**
//   * Offset/Address/Size: 0x2E0 | 0x801FA474 | size: 0x44
//   */
//  void Replayable<0, LoadFrame, char>(LoadFrame&, char&)
//  {
//  }

//  /**
//   * Offset/Address/Size: 0x128 | 0x801FA2BC | size: 0x1B8
//   */
//  void Replayable<0, SaveFrame, EmissionController>(SaveFrame&, EmissionController&)
//  {
//  }

//  /**
//   * Offset/Address/Size: 0xE8 | 0x801FA27C | size: 0x40
//   */
//  void Replayable<0, SaveFrame, unsigned long>(SaveFrame&, unsigned long&)
//  {
//  }

//  /**
//   * Offset/Address/Size: 0xA8 | 0x801FA23C | size: 0x40
//   */
//  void Replayable<0, SaveFrame, unsigned short>(SaveFrame&, unsigned short&)
//  {
//  }

//  /**
//   * Offset/Address/Size: 0x88 | 0x801FA21C | size: 0x20
//   */
//  void Replayable<0, LoadFrame, EmissionController>(LoadFrame&, EmissionController&)
//  {
//  }

//  /**
//   * Offset/Address/Size: 0x44 | 0x801FA1D8 | size: 0x44
//   */
//  void Replayable<0, LoadFrame, unsigned long>(LoadFrame&, unsigned long&)
//  {
//  }

//  /**
//   * Offset/Address/Size: 0x0 | 0x801FA194 | size: 0x44
//   */
//  void Replayable<0, LoadFrame, unsigned short>(LoadFrame&, unsigned short&)
//  {
//  }

//  /**
//   * Offset/Address/Size: 0x0 | 0x801FA170 | size: 0x24
//   */
//  void NewAdapter<AVLTreeEntry<unsigned long, LingerMessage*>>::Delete(AVLTreeEntry<unsigned long, LingerMessage*>*)
//  {
//  }

//  /**
//   * Offset/Address/Size: 0x9CC | 0x801FA144 | size: 0x2C
//   */
//  void AVLTreeBase<unsigned long, LingerMessage*, NewAdapter<AVLTreeEntry<unsigned long, LingerMessage*>>, DefaultKeyCompare<unsigned long>>::CompareNodes(AVLTreeNode*, AVLTreeNode*)
//  {
//  }

//  /**
//   * Offset/Address/Size: 0x9A0 | 0x801FA118 | size: 0x2C
//   */
//  void AVLTreeBase<unsigned long, LingerMessage*, NewAdapter<AVLTreeEntry<unsigned long, LingerMessage*>>, DefaultKeyCompare<unsigned long>>::CompareKey(void*, AVLTreeNode*)
//  {
//  }

//  /**
//   * Offset/Address/Size: 0x93C | 0x801FA0B4 | size: 0x64
//   */
//  void AVLTreeBase<unsigned long, LingerMessage*, NewAdapter<AVLTreeEntry<unsigned long, LingerMessage*>>, DefaultKeyCompare<unsigned long>>::AllocateEntry(void*, void*)
//  {
//  }

//  /**
//   * Offset/Address/Size: 0x8E4 | 0x801FA05C | size: 0x58
//   */
//  void AVLTreeBase<unsigned long, LingerMessage*, NewAdapter<AVLTreeEntry<unsigned long, LingerMessage*>>, DefaultKeyCompare<unsigned long>>::Clear()
//  {
//  }

//  /**
//   * Offset/Address/Size: 0x888 | 0x801FA000 | size: 0x5C
//   */
//  void AVLTreeBase<unsigned long, LingerMessage*, NewAdapter<AVLTreeEntry<unsigned long, LingerMessage*>>, DefaultKeyCompare<unsigned long>>::~AVLTreeBase()
//  {
//  }

//  /**
//   * Offset/Address/Size: 0x880 | 0x801F9FF8 | size: 0x8
//   */
//  void AVLTreeBase<unsigned long, LingerMessage*, NewAdapter<AVLTreeEntry<unsigned long, LingerMessage*>>, DefaultKeyCompare<unsigned long>>::CastUp(AVLTreeNode*) const
//  {
//  }

//  /**
//   * Offset/Address/Size: 0x128 | 0x801F98A0 | size: 0x758
//   */
//  void AVLTreeBase<unsigned long, LingerMessage*, NewAdapter<AVLTreeEntry<unsigned long, LingerMessage*>>, DefaultKeyCompare<unsigned long>>::PostorderTraversal(AVLTreeEntry<unsigned long, LingerMessage*>*, void (AVLTreeBase<unsigned long, LingerMessage*, NewAdapter<AVLTreeEntry<unsigned long, LingerMessage*>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, LingerMessage*>*))
//  {
//  }

//  /**
//   * Offset/Address/Size: 0xC4 | 0x801F983C | size: 0x64
//   */
//  void AVLTreeBase<unsigned long, LingerMessage*, NewAdapter<AVLTreeEntry<unsigned long, LingerMessage*>>, DefaultKeyCompare<unsigned long>>::DestroyTree(void (AVLTreeBase<unsigned long, LingerMessage*, NewAdapter<AVLTreeEntry<unsigned long, LingerMessage*>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, LingerMessage*>*))
//  {
//  }

//  /**
//   * Offset/Address/Size: 0x6C | 0x801F97E4 | size: 0x58
//   */
//  void AVLTreeBase<unsigned long, LingerMessage*, NewAdapter<AVLTreeEntry<unsigned long, LingerMessage*>>, DefaultKeyCompare<unsigned long>>::DeleteValues()
//  {
//  }

//  /**
//   * Offset/Address/Size: 0x48 | 0x801F97C0 | size: 0x24
//   */
//  void AVLTreeBase<unsigned long, LingerMessage*, NewAdapter<AVLTreeEntry<unsigned long, LingerMessage*>>, DefaultKeyCompare<unsigned long>>::DeleteEntry(AVLTreeEntry<unsigned long, LingerMessage*>*)
//  {
//  }

//  /**
//   * Offset/Address/Size: 0x0 | 0x801F9778 | size: 0x48
//   */
//  void AVLTreeBase<unsigned long, LingerMessage*, NewAdapter<AVLTreeEntry<unsigned long, LingerMessage*>>, DefaultKeyCompare<unsigned long>>::DeleteValue(AVLTreeEntry<unsigned long, LingerMessage*>*)
//  {
//  }

//  /**
//   * Offset/Address/Size: 0xD0C | 0x801F962C | size: 0x60
//   */
//  void nlAVLTree<unsigned long, LingerMessage*, DefaultKeyCompare<unsigned long>>::~nlAVLTree()
//  {
//  }
