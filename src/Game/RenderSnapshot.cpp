#include "Game/RenderSnapshot.h"

#include "Game/Drawable/DrawableNetMesh.h"
#include "Game/Render/SidelineExplodable.h"
#include "Game/BasicStadium.h"
#include "Game/Render/NPCManager.h"
#include "Game/Camera/CameraMan.h"
#include "Game/Render/NetMesh.h"
#include "Game/Physics/PhysicsNet.h"
#include "Game/Goalie.h"
#include "Game/Render/SkinAnimatedMovableNPC.h"
#include "Game/GL/GLInventory.h"
#include "Game/GL/GLTextureAnim.h"
#include "NL/gl/glState.h"

extern cCharacter* g_pCharacters[10];
extern bool g_GoalLightEnabled;
extern float g_AllActorsHidden;
extern GLInventory glInventory;

// /**
//  * Offset/Address/Size: 0x4D8 | 0x80113F20 | size: 0x3C
//  */
// void Replayable<1, LoadFrame, DrawableNetMesh>(LoadFrame&, DrawableNetMesh&)
// {
// }

// /**
//  * Offset/Address/Size: 0x49C | 0x80113EE4 | size: 0x3C
//  */
// void Replayable<3, LoadFrame, EmissionManager>(LoadFrame&, EmissionManager&)
// {
// }

// /**
//  * Offset/Address/Size: 0x460 | 0x80113EA8 | size: 0x3C
//  */
// void Replayable<1, LoadFrame, CrowdManager>(LoadFrame&, CrowdManager&)
// {
// }

// /**
//  * Offset/Address/Size: 0x3E4 | 0x80113E2C | size: 0x7C
//  */
// void Replayable<1, LoadFrame, bool>(LoadFrame&, bool&)
// {
// }

// /**
//  * Offset/Address/Size: 0x390 | 0x80113DD8 | size: 0x54
//  */
// void Replayable<1, LoadFrame, nlVector3>(LoadFrame&, nlVector3&)
// {
// }

// /**
//  * Offset/Address/Size: 0x364 | 0x80113DAC | size: 0x2C
//  */
// void Replayable<0, LoadFrame, DrawableBall>(LoadFrame&, DrawableBall&)
// {
// }

// /**
//  * Offset/Address/Size: 0x2F4 | 0x80113D3C | size: 0x70
//  */
// void Replayable<0, LoadFrame, bool>(LoadFrame&, bool&)
// {
// }

// /**
//  * Offset/Address/Size: 0x2C8 | 0x80113D10 | size: 0x2C
//  */
// void Replayable<0, LoadFrame, DrawableExplosionFragment>(LoadFrame&, DrawableExplosionFragment&)
// {
// }

// /**
//  * Offset/Address/Size: 0x29C | 0x80113CE4 | size: 0x2C
//  */
// void Replayable<0, LoadFrame, DrawablePowerup>(LoadFrame&, DrawablePowerup&)
// {
// }

// /**
//  * Offset/Address/Size: 0x270 | 0x80113CB8 | size: 0x2C
//  */
// void Replayable<0, LoadFrame, DrawableCharacter>(LoadFrame&, DrawableCharacter&)
// {
// }

// /**
//  * Offset/Address/Size: 0x234 | 0x80113C7C | size: 0x3C
//  */
// void Replayable<1, SaveFrame, DrawableNetMesh>(SaveFrame&, DrawableNetMesh&)
// {
// }

// /**
//  * Offset/Address/Size: 0x1F8 | 0x80113C40 | size: 0x3C
//  */
// void Replayable<3, SaveFrame, EmissionManager>(SaveFrame&, EmissionManager&)
// {
// }

// /**
//  * Offset/Address/Size: 0x1BC | 0x80113C04 | size: 0x3C
//  */
// void Replayable<1, SaveFrame, CrowdManager>(SaveFrame&, CrowdManager&)
// {
// }

// /**
//  * Offset/Address/Size: 0x158 | 0x80113BA0 | size: 0x64
//  */
// void Replayable<1, SaveFrame, bool>(SaveFrame&, bool&)
// {
// }

// /**
//  * Offset/Address/Size: 0x108 | 0x80113B50 | size: 0x50
//  */
// void Replayable<1, SaveFrame, nlVector3>(SaveFrame&, nlVector3&)
// {
// }

// /**
//  * Offset/Address/Size: 0xDC | 0x80113B24 | size: 0x2C
//  */
// void Replayable<0, SaveFrame, DrawableBall>(SaveFrame&, DrawableBall&)
// {
// }

// /**
//  * Offset/Address/Size: 0x84 | 0x80113ACC | size: 0x58
//  */
// void Replayable<0, SaveFrame, bool>(SaveFrame&, bool&)
// {
// }

// /**
//  * Offset/Address/Size: 0x58 | 0x80113AA0 | size: 0x2C
//  */
// void Replayable<0, SaveFrame, DrawableExplosionFragment>(SaveFrame&, DrawableExplosionFragment&)
// {
// }

// /**
//  * Offset/Address/Size: 0x2C | 0x80113A74 | size: 0x2C
//  */
// void Replayable<0, SaveFrame, DrawablePowerup>(SaveFrame&, DrawablePowerup&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80113A48 | size: 0x2C
//  */
// void Replayable<0, SaveFrame, DrawableCharacter>(SaveFrame&, DrawableCharacter&)
// {
// }

/**
 * Offset/Address/Size: 0x294 | 0x801138E8 | size: 0x160
 */
// void RenderSnapshot::Replay<SaveFrame>(SaveFrame&)
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x80113654 | size: 0x294
 */
// void RenderSnapshot::Replay<LoadFrame>(LoadFrame&)
// {
// }

/**
 * Offset/Address/Size: 0x844 | 0x80113518 | size: 0x13C
 */
void RenderSnapshot::Initialize()
{
    DrawableNetMesh* pNetMesh = new (nlMalloc(0x28, 8, false)) DrawableNetMesh(true);
    mpNetMeshPositiveX = pNetMesh;

    pNetMesh = new (nlMalloc(0x28, 8, false)) DrawableNetMesh(false);
    mpNetMeshNegativeX = pNetMesh;

    for (int i = 0; i < 20; i++)
    {
        mExplosionFragments[i].mID = i;
    }

    mNumExplodables = SidelineExplodableManager::GetNumExplodables();
    mpExplodableVisibilityRecords = (unsigned char*)nlMalloc(mNumExplodables, 8, false);

    mValid = false;
}

/**
 * Offset/Address/Size: 0x7AC | 0x80113480 | size: 0x98
 */
void RenderSnapshot::Free()
{
    for (int i = 0; i < 10; i++)
    {
        mCharacters[i].Free();
    }

    mChainChomp.Free();
    mBowser.Free();

    delete mpNetMeshPositiveX;
    delete mpNetMeshNegativeX;
    delete[] mpExplodableVisibilityRecords;

    mpNetMeshPositiveX = nullptr;
    mpNetMeshNegativeX = nullptr;
    mpExplodableVisibilityRecords = nullptr;
}

/**
 * Offset/Address/Size: 0x624 | 0x801132F8 | size: 0x188
 */
void RenderSnapshot::Grab()
{
    for (int i = 0; i < 10; i++)
    {
        mCharacters[i].Grab(*g_pCharacters[i]);
    }

    for (int i = 0; i < 150; i++)
    {
        mPowerups[i].Grab(i);
    }

    for (int i = 0; i < 20; i++)
    {
        mExplosionFragments[i].Grab();
    }

    if (mpExplodableVisibilityRecords != nullptr)
    {
        SidelineExplodableManager::GetVisibilityOfExplodableModels((bool*)mpExplodableVisibilityRecords, mNumExplodables);
    }

    {
        const BasicStadium* stadium = BasicStadium::GetCurrentStadium();
        mChainChomp.Grab(*(stadium->mpNPCManager->mpChainChomp));
    }

    {
        const BasicStadium* stadium = BasicStadium::GetCurrentStadium();
        mBowser.Grab(*(stadium->mpNPCManager->mpBowser));
    }

    mBall.Grab();

    mGoalLight = g_GoalLightEnabled;

    if (NetMesh::s_bAnimatedNetMeshEnabled)
    {
        if (mpNetMeshPositiveX != nullptr)
        {
            PhysicsNet* physNet = PhysicsNet::spPhysNetPositiveX;
            mpNetMeshPositiveX->Grab(*physNet->mpNetMesh);
        }
        if (mpNetMeshNegativeX != nullptr)
        {
            PhysicsNet* physNet = PhysicsNet::spPhysNetNegativeX;
            mpNetMeshNegativeX->Grab(*physNet->mpNetMesh);
        }

        mDoGoalieNetTestPosX = Goalie::mbPosGoalieNetCheck;
        mDoGoalieNetTestNegX = Goalie::mbNegGoalieNetCheck;
    }

    int stackSize = cCameraManager::m_UpVectorStackSize;
    mCameraUp = cCameraManager::m_UpVectorStack[stackSize];

    mValid = true;
}

/**
 * Offset/Address/Size: 0x51C | 0x801131F0 | size: 0x108
 */
int RenderSnapshot::NumDrawableObjects() const
{
    int ret = 11;

    if (mChainChomp.mVisible)
        ret = 12;
    if (mBowser.mVisible)
        ret++;

    for (int i = 0; i < 150; i++)
    {
        if (mPowerups[i].mVisible)
            ret++;
    }

    return ret;
}

/**
 * Offset/Address/Size: 0x3DC | 0x801130B0 | size: 0x140
 */
const nlVector3& RenderSnapshot::GetPositionForDrawableObject(int) const
{
    return mCameraUp;
}

/**
 * Offset/Address/Size: 0x3D0 | 0x801130A4 | size: 0xC
 */
void RenderSnapshot::Invalidate()
{
    mValid = false;
}

/**
 * Offset/Address/Size: 0x21C | 0x80112EF0 | size: 0x1B4
 */
void RenderSnapshot::Render(float deltaTime) const
{
    float hideTime = 0.0f;
    bool bAllActorsHidden = false;

    if (g_AllActorsHidden > 0.0f)
    {
        g_AllActorsHidden -= deltaTime;
        bAllActorsHidden = true;
    }

    if (!mValid)
        return;

    if (!bAllActorsHidden)
    {
        {
            const BasicStadium* stadium = BasicStadium::GetCurrentStadium();
            mChainChomp.Render(*(stadium->mpNPCManager->mpChainChomp));
        }

        {
            const BasicStadium* stadium = BasicStadium::GetCurrentStadium();
            mBowser.Render(*(stadium->mpNPCManager->mpBowser));
        }

        for (int i = 0; i < 10; i++)
        {
            mCharacters[i].Render(*g_pCharacters[i]);
        }

        for (int i = 0; i < 150; i++)
        {
            mPowerups[i].Render(i);
        }

        for (int i = 0; i < 20; i++)
        {
            mExplosionFragments[i].Render();
        }

        mBall.Render();
    }

    mpNetMeshPositiveX->Render();
    mpNetMeshNegativeX->Render();
    SidelineExplodableManager::SetVisibilityOfUnexplodedModels((bool*)mpExplodableVisibilityRecords, mNumExplodables);

    int stackSize = cCameraManager::m_UpVectorStackSize;
    cCameraManager::m_UpVectorStack[stackSize] = mCameraUp;

    static u32 texAnimHandle = glGetTexture("wario_stadium/goallight.ifl");

    GLTextureAnim* pTexAnim = glInventory.GetTextureAnim(texAnimHandle);
    if (pTexAnim != nullptr)
    {
        pTexAnim->m_isStopped = !mGoalLight;
    }
}

/**
 * Offset/Address/Size: 0x218 | 0x80112EEC | size: 0x4
 */
void RenderSnapshot::RenderDebugInfo(const RenderSnapshot&, const RenderSnapshot&, float) const
{
}

/**
 * Offset/Address/Size: 0xC | 0x80112CE0 | size: 0x20C
 */
void RenderSnapshot::Blend(const float*, const RenderSnapshot&, const RenderSnapshot&)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80112CD4 | size: 0xC
 */
RenderSnapshot& RenderSnapshot::GetMutable()
{
    mValid = true;
    return *this;
}
