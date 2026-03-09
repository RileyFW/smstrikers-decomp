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
 * TODO: 98.25% match - extra `li r4, 0` dead store on first loop break path;
 * -inline deferred eliminates it (allReady already false from init), decomp.me -inline auto does not
 */
void IChooseSide::SetReady(int controllerIdx, bool ready)
{
    mPlayerReady[controllerIdx] = ready;
    mInstanceTable[controllerIdx + 4]->m_bVisible = ready;

    bool allReady;
    TLInstance* readyIndicator = mInstanceTable[16];
    if (readyIndicator == NULL)
    {
        return;
    }

    allReady = false;
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
 * TODO: 99.7% match - r4/r5 swap in setvisibilities block when loading +0x44/+0x34
 */
void IChooseSide::PositionController(int padindex, bool usetween, bool setvisibilities)
{
    int side = mPlayingSides[padindex];
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

    TLInstance* inst = mInstanceTable[padindex];
    feVector3 localPos = inst->GetPosition();

    mTweenManager.clearTweensOnObj(inst);

    if (usetween)
    {
        FETweener* tweener = mTweenManager.createTween(
            localPos.e,
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
        mInstanceTable[padindex]->SetAssetPosition(mControllerDestPos[destPosIndex], localPos.e[1], localPos.e[2]);
    }

    if (setvisibilities)
    {
        mInstanceTable[padindex + 12]->m_bVisible = (side == -1);
        mInstanceTable[padindex + 8]->m_bVisible = (side != -1);
    }
}

/**
 * Offset/Address/Size: 0x1DC | 0x800C3620 | size: 0xC8
 * TODO: 92.6% match - MWCC strength-reduces ready pointer (r4=&mPlayerReady[1]) instead of
 * side pointer (r4=&mPlayingSides[1]). Exhaustively tested: pointer decl order, increment order,
 * single pointer, pure indexing, while/do-while, pragmas, types. Same MWCC quirk as AllControllersAreCentred.
 */
bool IChooseSide::AllPlayersReady() const
{
    const bool* ready = mPlayerReady;
    const int* side = mPlayingSides;
    u8 allReady = 0;

    for (int i = 0; i < 4; i++, ready++, side++)
    {
        if (*ready)
        {
            allReady = 1;
        }
        else if (*side != -1)
        {
            allReady = 0;
            break;
        }
    }

    if (allReady == 1)
    {
        return true;
    }

    return false;
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
