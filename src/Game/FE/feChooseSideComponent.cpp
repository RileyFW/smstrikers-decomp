#include "Game/FE/feChooseSideComponent.h"
#include "Game/FE/feTweener.h"
#include "Game/GameInfo.h"

#include "Game/FE/feTweenFuncs.h"

/**
 * Offset/Address/Size: 0x16B0 | 0x800C4AF4 | size: 0xCC
 */
IChooseSide::IChooseSide()
{
    mContext = CONTEXT_FE;

    for (int i = 0; i < 17; i++)
    {
        mInstanceTable[i] = NULL;
    }

    for (int i = 0; i < 4; i++)
    {
        mPlayingSides[i] = -1;
        mPlayerReady[i] = false;
    }
}

/**
 * Offset/Address/Size: 0x1658 | 0x800C4A9C | size: 0x58
 */
IChooseSide::~IChooseSide()
{
}

/**
 * Offset/Address/Size: 0x15D4 | 0x800C4A18 | size: 0x84
 */
UpdateResult IChooseSide::Update(float dt, eFEINPUT_PAD* pad, int param)
{
    UpdateResult result;
    if (mContext == CONTEXT_FE)
    {
        result = UpdateForFE(dt, pad);
    }
    else
    {
        result = UpdateForPause(dt, pad);
    }
    CheckControllers(param);
    mTweenManager.Update(dt);
    return result;
}

/**
 * Offset/Address/Size: 0xFD4 | 0x800C4418 | size: 0x600
 */
UpdateResult IChooseSide::UpdateForFE(float, eFEINPUT_PAD*)
{
    FORCE_DONT_INLINE;
    return UPDATE_OK;
}

/**
 * Offset/Address/Size: 0xCDC | 0x800C4120 | size: 0x2F8
 */
UpdateResult IChooseSide::UpdateForPause(float, eFEINPUT_PAD*)
{
    FORCE_DONT_INLINE;
    return UPDATE_OK;
}

/**
 * Offset/Address/Size: 0x820 | 0x800C3C64 | size: 0x4BC
 */
void IChooseSide::CheckControllers(int)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x4C0 | 0x800C3904 | size: 0x360
 */
void IChooseSide::ResetAndPositionControllers(bool)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x3DC | 0x800C3820 | size: 0xE4
 * TODO: 97.1% match - r4/r5 register swap for allReady and readyIndicator
 */
void IChooseSide::SetReady(int controllerIdx, bool ready)
{
    mPlayerReady[controllerIdx] = ready;
    mInstanceTable[controllerIdx + 4]->m_bVisible = ready;

    TLInstance* readyIndicator = mInstanceTable[16];
    if (readyIndicator == NULL)
    {
        return;
    }

    bool allReady = false;
    for (int i = 0; i < 4; i++)
    {
        if (mPlayerReady[i])
            allReady = true;
        else if (mPlayingSides[i] != -1)
        {
            allReady = false;
            break;
        }
    }

    if ((u8)allReady == 1)
        readyIndicator->m_bVisible = true;
    else
        readyIndicator->m_bVisible = false;
}

/**
 * Offset/Address/Size: 0x2A4 | 0x800C36E8 | size: 0x138
 * TODO: 88.4% match - register allocation (stmw r24 vs r25), load interleaving order,
 *       visibility section add instruction
 */
void IChooseSide::PositionController(int padindex, bool usetween, bool setvisibilities)
{
    u32 offset = (u32)padindex << 2;
    int side = ((int*)this)[padindex];
    int destPosIndex;

    if (side == 0)
    {
        destPosIndex = 0;
    }
    else
    {
        int temp = 2;
        if (side == 1)
        {
            temp = 1;
        }
        destPosIndex = temp;
    }

    char* base = (char*)this + offset;
    TLInstance* inst = *(TLInstance**)(base + 0x14);
    const feVector3* pos = &inst->GetPosition();

    u32 px = *(u32*)&pos->e[0];
    u32 py = *(u32*)&pos->e[1];
    u32 localPos[3];
    localPos[0] = px;
    localPos[1] = py;
    localPos[2] = *(u32*)&pos->e[2];

    mTweenManager.clearTweensOnObj(inst);

    if (usetween)
    {
        FETweener* tweener = mTweenManager.createTween(
            (float*)localPos,
            &mControllerDestPos[destPosIndex],
            0.2f,
            0.0f,
            1,
            TweenFunctions::linear,
            inst,
            TweenSetPosCallback);
        mTweenManager.startTween(tweener);
    }
    else
    {
        (*(TLInstance**)(base + 0x14))->SetAssetPosition(mControllerDestPos[destPosIndex], *(float*)&localPos[1], *(float*)&localPos[2]);
    }

    if (setvisibilities)
    {
        char* base2 = (char*)this + offset;
        (*(TLInstance**)(base2 + 0x44))->m_bVisible = (side == -1);
        (*(TLInstance**)(base2 + 0x34))->m_bVisible = (side != -1);
    }
}

/**
 * Offset/Address/Size: 0x1DC | 0x800C3620 | size: 0xC8
 * TODO: 76% match - pointer iteration pattern and register allocation mismatch
 */
bool IChooseSide::AllPlayersReady() const
{
    bool anyReady = false;
    for (int i = 0; i < 4; i++)
    {
        if (mPlayerReady[i])
        {
            anyReady = true;
        }
        else if (mPlayingSides[i] != -1)
        {
            return false;
        }
    }
    return anyReady;
}

/**
 * Offset/Address/Size: 0x16C | 0x800C35B0 | size: 0x70
 */
bool IChooseSide::AllPluggedInAreReady() const
{
    for (int i = 0; i < 4; i++)
    {
        if (g_pFEInput->IsConnected((eFEINPUT_PAD)i))
        {
            if (!mPlayerReady[i])
                return false;
        }
    }
    return true;
}

/**
 * Offset/Address/Size: 0x114 | 0x800C3558 | size: 0x58
 */
bool IChooseSide::AtLeastOnePlayerReady() const
{
    for (int i = 0; i < 4; i++)
    {
        if (mPlayerReady[i])
            return true;
    }
    return false;
}

/**
 * Offset/Address/Size: 0xBC | 0x800C3500 | size: 0x58
 * TODO: lwzu instruction mismatch - original uses pointer update pattern
 */
bool IChooseSide::AllControllersAreCentred() const
{
    for (int i = 0; i < 4; i++)
    {
        if (mPlayingSides[i] != -1)
            return false;
    }
    return true;
}

/**
 * Offset/Address/Size: 0x58 | 0x800C349C | size: 0x64
 */
void IChooseSide::TweenSetPosCallback(void* obj, const float* value)
{
    TLInstance* inst = (TLInstance*)obj;
    feVector3 pos = inst->GetPosition();
    inst->SetAssetPosition(*(const float*)value, pos.f.y, pos.f.z);
}

/**
 * Offset/Address/Size: 0x0 | 0x800C3444 | size: 0x58
 */
void IChooseSide::SaveChanges()
{
    for (int i = 0; i < 4; i++)
    {
        GameInfoManager::Instance()->SetPlayingSide(i, mPlayingSides[i]);
    }
}
