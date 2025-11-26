#include "Game/AI/GoalieLooseBall.h"

#include "Game/AI/FilteredRandom.h"
#include "NL/nlMath.h"
// #include "PowerPC_EABI_Support/Runtime/global_destructor_chain.h"

LooseBallInfo LooseBallAnims::mLooseBallKickInfo;
LooseBallInfo LooseBallAnims::mTrapBallInfo;
LooseBallInfo LooseBallAnims::mAttackSTSInfo;
LooseBallInfo LooseBallAnims::mSwatSTSInfo[2];
LooseBallInfo LooseBallAnims::mDiveBallInfo;
LooseBallInfo* LooseBallAnims::mLooseBallDesperationInfo[4];

LooseBallInfo* LooseBallAnims::mpLooseBallInfo = NULL;
unsigned int LooseBallAnims::muNumLooseBallAnims = 0;

static LooseBallInfo gCatches[8];
static int gLooseBallAnimIDs[8] = {
    0x00000033,
    0x00000076,
    0x0000007F,
    0x0000007E,
    0x00000079,
    0x0000007B,
    0x00000078,
    0x0000007A
};
static int gLooseBallKickAnims[3] = { 0x3, 0x4, 0x5 };
static int gSwatSTSAnim[2] = { 0x6, 0x7 };

/**
 * Offset/Address/Size: 0x6FC | 0x80053404 | size: 0x1C
 */
static bool LooseBallCallback(float fTime, float fDuration, unsigned long uEventID, float, void* pUserData)
{
    if ((uEventID + 0x307c0000U) == 0xe7cd)
    {
        LooseBallInfo* info = (LooseBallInfo*)pUserData;
        info->mfPickupTime = fTime;
        info->mfAnimDuration = fDuration;
    }

    return true;
}

/**
 * Offset/Address/Size: 0x1D8 | 0x80052EE0 | size: 0x524
 */
void LooseBallAnims::Init(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x1C8 | 0x80052ED0 | size: 0x10
 */
void LooseBallAnims::Destroy()
{
    mpLooseBallInfo = NULL;
    muNumLooseBallAnims = 0;
}

/**
 * Offset/Address/Size: 0xB0 | 0x80052DB8 | size: 0x118
 */
const LooseBallInfo* LooseBallAnims::FindLooseBallAnim(const nlVector3& rv3Pos, bool bCheckDistance)
{
    float fSquaredDist3D = 0.2f + ((rv3Pos.f.x * rv3Pos.f.x) + (rv3Pos.f.y * rv3Pos.f.y) + (rv3Pos.f.z * rv3Pos.f.z));
    float fBestDist2D = 1000000.0f;
    const LooseBallInfo* pBestInfo = &mpLooseBallInfo[0];

    for (unsigned int i = 0; i < muNumLooseBallAnims; i++)
    {
        if (!bCheckDistance || mpLooseBallInfo[i].mv3PickupPos.f.x >= 0.0f)
        {
            float fDX = rv3Pos.f.x - mpLooseBallInfo[i].mv3PickupPos.f.x;
            float fDY = rv3Pos.f.y - mpLooseBallInfo[i].mv3PickupPos.f.y;
            float fDist2D = nlSqrt((fDX * fDX) + (fDY * fDY), true);

            if (fDist2D < fBestDist2D)
            {
                float fPickupDistSq = mpLooseBallInfo[i].mfPickupDistance * mpLooseBallInfo[i].mfPickupDistance;
                if (fSquaredDist3D > fPickupDistSq)
                {
                    fBestDist2D = fDist2D;
                    pBestInfo = &mpLooseBallInfo[i];
                }
            }
        }
    }

    return pBestInfo;
}

/**
 * Offset/Address/Size: 0x14 | 0x80052D1C | size: 0x9C
 */
const LooseBallInfo* LooseBallAnims::GetSwatSTSInfo(int nSide)
{
    static FilteredRandomRange randgenSwats;
    // __register_global_object(&randgenSwats, FilteredRandomRange::~FilteredRandomRange(), (void*)0x8030EC80);

    if (nSide < 0)
    {
        int index = randgenSwats.genrand(2);
        return &mSwatSTSInfo[index];
    }
    else if (nSide == 0)
    {
        return &mSwatSTSInfo[0];
    }
    else
    {
        return &mSwatSTSInfo[1];
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x80052D08 | size: 0x14
 */
const LooseBallInfo* LooseBallAnims::GetDesperationInfo(unsigned int type)
{
    return mLooseBallDesperationInfo[type];
}
