#include "Game/Effects/EmissionController.h"
#include "Game/Effects/ParticleSystem.h"
#include "Game/Effects/EmissionManager.h"
#include "NL/nlFile.h"
#include "NL/nlFileGC.h"
#include "NL/nlMemory.h"
#include "types.h"

extern int numLingeringSystems;

/**
 * Offset/Address/Size: 0xF2C | 0x801F881C | size: 0x104
 */
EmissionController::EmissionController(EffectsGroup* pEffectsGroup, unsigned short id, eGLView view)
{
    m_nextNode = nullptr;
    m_prevNode = nullptr;
    m_Systems.m_headNode = nullptr;
    m_Systems.m_tailNode = nullptr;
    m_Systems.m_numNodes = 0;
    mUpdateCallback.mTag = EMPTY;
    mFinishedCallback.mTag = EMPTY;

    m_GlView = view;
    m_Replaying = false;
    m_Age = 0.0f;
    m_ReplayDeltaTime = 0.0f;
    m_Id = id;
    m_bPoseErrorDisplayed = false;
    m_pGroup = pEffectsGroup;
    m_Mirror.f.x = 1.0f;
    m_Mirror.f.y = 1.0f;
    m_Mirror.f.z = 1.0f;
    m_uUserData = 0;

    InitializeSystemsFromGroup();

    m_fGround = 0.015625f;
    m_aFacing = 0;
    m_vPosition.f.x = 0.0f;
    m_vPosition.f.y = 0.0f;
    m_vPosition.f.z = 0.0f;

    m_vDirection.f.x = 0.0f;
    m_vDirection.f.y = 0.0f;
    m_vDirection.f.z = 1.0f;

    m_vVelocity.f.x = 0.0f;
    m_vVelocity.f.y = 0.0f;
    m_vVelocity.f.z = 0.0f;
    m_pPose = nullptr;
    m_pAnimController = nullptr;
    m_uJointIDOverride = 0;
    m_bVisible = true;
    m_bDisabled = false;

    if (m_pGroup->m_isLingering != 0)
    {
        numLingeringSystems++;
    }

    EmissionManager::KillOldest(numLingeringSystems - 12, true);
}

/**
 * Offset/Address/Size: 0xD84 | 0x801F8674 | size: 0x1A8
 */
void EmissionController::InitializeSystemsFromGroup()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0xB30 | 0x801F8420 | size: 0x254
 */
EmissionController::~EmissionController()
{
}

/**
 * Offset/Address/Size: 0xB14 | 0x801F8404 | size: 0x1C
 */
void EmissionController::SetPosition(const nlVector3& pos)
{
    m_vPosition = pos;
}

/**
 * Offset/Address/Size: 0xB0C | 0x801F83FC | size: 0x8
 */
const nlVector3& EmissionController::GetPosition() const
{
    return m_vPosition;
}

/**
 * Offset/Address/Size: 0xAF0 | 0x801F83E0 | size: 0x1C
 */
void EmissionController::SetDirection(const nlVector3& dir)
{
    m_vDirection = dir;
}

/**
 * Offset/Address/Size: 0xAD4 | 0x801F83C4 | size: 0x1C
 */
void EmissionController::SetVelocity(const nlVector3& velocity)
{
    m_vVelocity = velocity;
}

/**
 * Offset/Address/Size: 0xACC | 0x801F83BC | size: 0x8
 */
void EmissionController::SetPoseAccumulator(const cPoseAccumulator& pose)
{
    m_pPose = &pose;
}

/**
 * Offset/Address/Size: 0xAC4 | 0x801F83B4 | size: 0x8
 */
void EmissionController::SetAnimController(const cPN_SAnimController& animController)
{
    m_pAnimController = &animController;
}

/**
 * Offset/Address/Size: 0x988 | 0x801F8278 | size: 0x13C
 */
void EmissionController::Die()
{
}

/**
 * Offset/Address/Size: 0x924 | 0x801F8214 | size: 0x64
 */
float EmissionController::GetRemainingTime() const
{
    float maxTime = 0.0f;
    efBaseNode* node = m_Systems.m_headNode;

    while (node != nullptr)
    {
        ParticleSystem* system = (ParticleSystem*)node;
        float remainingTime = system->GetRemainingTime();
        if (remainingTime > maxTime)
        {
            maxTime = remainingTime;
        }
        node = node->m_nextNode;
    }

    return maxTime;
}

/**
 * Offset/Address/Size: 0x918 | 0x801F8208 | size: 0xC
 */
bool EmissionController::IsLingering() const
{
    return m_pGroup->m_isLingering;
}

/**
 * Offset/Address/Size: 0x32C | 0x801F7C1C | size: 0x5EC
 */
void EmissionController::Update(float)
{
}

/**
 * Offset/Address/Size: 0x288 | 0x801F7B78 | size: 0xA4
 */
void* fxLoadEntireFileHigh(const char* filename, unsigned long* fileSize)
{
    void* buffer = nullptr;
    u32 datasize = 0;

    nlFile* file = nlOpen(filename);
    if (file != nullptr)
    {
        unsigned int size;
        datasize = nlFileSize(file, &size);
        buffer = nlMalloc(size, 0x20, true);
        nlRead(file, buffer, datasize);
        nlClose(file);
    }

    if (fileSize != nullptr)
    {
        *fileSize = datasize;
    }

    return buffer;
}

/**
 * Offset/Address/Size: 0x150 | 0x801F7A40 | size: 0x138
 */
void EmissionController::Render()
{
}

/**
 * Offset/Address/Size: 0xA8 | 0x801F7998 | size: 0xA8
 */
void EmissionController::SetUpdateCallback(const Function1<void, EmissionController&>& callback)
{
    if (mUpdateCallback.mTag == FUNCTOR)
    {
        delete mUpdateCallback.mFunctor;
    }

    mUpdateCallback.mTag = EMPTY;
    mUpdateCallback.mTag = callback.mTag;

    if (mUpdateCallback.mTag == FREE_FUNCTION)
    {
        mUpdateCallback.mFreeFunction = callback.mFreeFunction;
    }
    else if (mUpdateCallback.mTag == FUNCTOR)
    {
        mUpdateCallback.mFunctor = callback.mFunctor->fnc_0x10();
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x801F78F0 | size: 0xA8
 */
void EmissionController::SetFinishedCallback(const Function1<void, EmissionController&>& callback)
{
    if (mFinishedCallback.mTag == FUNCTOR)
    {
        delete mFinishedCallback.mFunctor;
    }

    mFinishedCallback.mTag = EMPTY;
    mFinishedCallback.mTag = callback.mTag;

    if (mFinishedCallback.mTag == FREE_FUNCTION)
    {
        mFinishedCallback.mFreeFunction = callback.mFreeFunction;
    }
    else if (mFinishedCallback.mTag == FUNCTOR)
    {
        mFinishedCallback.mFunctor = callback.mFunctor->fnc_0x10();
    }
}
