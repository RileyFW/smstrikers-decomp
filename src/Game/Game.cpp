#include "Game/Game.h"
#include "Game/Sys/clock.h"
#include "Game/Sys/eventman.h"
#include "Game/Team.h"
#include "Game/AI/Fielder.h"
#include "Game/AI/ScriptAction.h"
#include "Game/AI/Powerups.h"
#include "Game/GameInfo.h"
#include "Game/Camera/CameraMan.h"
#include "Game/Camera/GameplayCam.h"
#include "NL/nlConfig.h"
#include "NL/nlLexicalCast.h"
#include "NL/nlMath.h"

extern cTeam* g_pTeams[2];
extern PowerupBase* g_pPowerups[25];

// /**
//  * Offset/Address/Size: 0x24 | 0x800401E8 | size: 0x4
//  */
// void std::allocator<std::pair<const unsigned long, FuzzyVariant> >::destroy(std::pair<const unsigned long, FuzzyVariant>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800401C4 | size: 0x24
//  */
// void std::allocator<std::__tree<std::pair<const unsigned long, FuzzyVariant>, std::map<unsigned long, FuzzyVariant, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, FuzzyVariant> > >::value_compare, std::allocator<std::pair<const unsigned long, FuzzyVariant> > >::node>::deallocate(std::__tree<std::pair<const unsigned long, FuzzyVariant>, std::map<unsigned long, FuzzyVariant, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, FuzzyVariant> > >::value_compare, std::allocator<std::pair<const unsigned long, FuzzyVariant> > >::node*, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x4 | 0x800401C0 | size: 0x4
//  */
// void Metrowerks::details::compressed_pair_imp<std::allocator<std::pair<const unsigned long, FuzzyVariant> >, unsigned long, 1>::first()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800401BC | size: 0x4
//  */
// void Metrowerks::details::compressed_pair_imp<std::allocator<std::__tree<std::pair<const unsigned long, FuzzyVariant>, std::map<unsigned long, FuzzyVariant, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, FuzzyVariant> > >::value_compare, std::allocator<std::pair<const unsigned long, FuzzyVariant> > >::node>, std::__red_black_tree<1>::anchor, 1>::first()
// {
// }

// /**
//  * Offset/Address/Size: 0xAC | 0x80040190 | size: 0x2C
//  */
// void nlListAddEnd<ListEntry<unsigned long> >(ListEntry<unsigned long>**, ListEntry<unsigned long>**, ListEntry<unsigned long>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x68 | 0x8004014C | size: 0x44
//  */
// void nlListRemoveStart<ListEntry<unsigned long> >(ListEntry<unsigned long>**, ListEntry<unsigned long>**)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800400E4 | size: 0x68
//  */
// void nlWalkList<ListEntry<unsigned long>, ListContainerBase<unsigned long, NewAdapter<ListEntry<unsigned long> > > >(ListEntry<unsigned long>*, ListContainerBase<unsigned long, NewAdapter<ListEntry<unsigned long> > >*, void (ListContainerBase<unsigned long, NewAdapter<ListEntry<unsigned long> > >::*)(ListEntry<unsigned long>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8004006C | size: 0x78
//  */
// void cCameraManager::GetCamera<GameplayCamera>(eCameraType)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80040064 | size: 0x8
//  */
// void GoalScoredData::GetID()
// {
// }

// /**
//  * Offset/Address/Size: 0x420 | 0x80040044 | size: 0x20
//  */
// void std::__tree<std::pair<const unsigned long, FuzzyVariant>, std::map<unsigned long, FuzzyVariant, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, FuzzyVariant> > >::value_compare, std::allocator<std::pair<const unsigned long, FuzzyVariant> > >::__tree(const std::map<unsigned long, FuzzyVariant, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, FuzzyVariant> > >::value_compare&, const std::allocator<std::pair<const unsigned long, FuzzyVariant> >&)
// {
// }

// /**
//  * Offset/Address/Size: 0x3D4 | 0x8003FFF8 | size: 0x4C
//  */
// void std::__tree<std::pair<const unsigned long, FuzzyVariant>, std::map<unsigned long, FuzzyVariant, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, FuzzyVariant> > >::value_compare, std::allocator<std::pair<const unsigned long, FuzzyVariant> > >::clear()
// {
// }

// /**
//  * Offset/Address/Size: 0x3D0 | 0x8003FFF4 | size: 0x4
//  */
// void std::__tree<std::pair<const unsigned long, FuzzyVariant>, std::map<unsigned long, FuzzyVariant, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, FuzzyVariant> > >::value_compare, std::allocator<std::pair<const unsigned long, FuzzyVariant> > >::alloc()
// {
// }

// /**
//  * Offset/Address/Size: 0x3C8 | 0x8003FFEC | size: 0x8
//  */
// void std::__tree<std::pair<const unsigned long, FuzzyVariant>, std::map<unsigned long, FuzzyVariant, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, FuzzyVariant> > >::value_compare, std::allocator<std::pair<const unsigned long, FuzzyVariant> > >::node_alloc()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8003FC24 | size: 0x3C8
//  */
// void std::__tree<std::pair<const unsigned long, FuzzyVariant>, std::map<unsigned long, FuzzyVariant, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, FuzzyVariant> > >::value_compare, std::allocator<std::pair<const unsigned long, FuzzyVariant> > >::destroy(std::__tree<std::pair<const unsigned long, FuzzyVariant>, std::map<unsigned long, FuzzyVariant, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, FuzzyVariant> > >::value_compare, std::allocator<std::pair<const unsigned long, FuzzyVariant> > >::node*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8003FBA8 | size: 0x7C
//  */
// void operator== <char, Detail::TempStringAllocator>(const BasicString<char, Detail::TempStringAllocator>&, const char*)
// {
// }

// /**
//  * Offset/Address/Size: 0xA8 | 0x8003FB24 | size: 0x84
//  */
// void Config::TagValuePair::Get<BasicString<char, Detail::TempStringAllocator> >() const
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8003FA7C | size: 0xA8
//  */
// void Config::Get<BasicString<char, Detail::TempStringAllocator> >(const char*, BasicString<char, Detail::TempStringAllocator>)
// {
// }

// /**
//  * Offset/Address/Size: 0x8F0 | 0x8003F994 | size: 0xE8
//  */
// void AVLTreeBase<unsigned long, FuzzyVariant, BasicSlotPool<AVLTreeEntry<unsigned long, FuzzyVariant> >, DefaultKeyCompare<unsigned long> >::AllocateEntry(void*, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x8C4 | 0x8003F968 | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, FuzzyVariant, BasicSlotPool<AVLTreeEntry<unsigned long, FuzzyVariant> >, DefaultKeyCompare<unsigned long> >::CompareKey(void*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x898 | 0x8003F93C | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, FuzzyVariant, BasicSlotPool<AVLTreeEntry<unsigned long, FuzzyVariant> >, DefaultKeyCompare<unsigned long> >::CompareNodes(AVLTreeNode*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x890 | 0x8003F934 | size: 0x8
//  */
// void AVLTreeBase<unsigned long, FuzzyVariant, BasicSlotPool<AVLTreeEntry<unsigned long, FuzzyVariant> >, DefaultKeyCompare<unsigned long> >::CastUp(AVLTreeNode*) const
// {
// }

// /**
//  * Offset/Address/Size: 0x138 | 0x8003F1DC | size: 0x758
//  */
// void AVLTreeBase<unsigned long, FuzzyVariant, BasicSlotPool<AVLTreeEntry<unsigned long, FuzzyVariant> >, DefaultKeyCompare<unsigned long> >::PostorderTraversal(AVLTreeEntry<unsigned long, FuzzyVariant>*, void (AVLTreeBase<unsigned long, FuzzyVariant, BasicSlotPool<AVLTreeEntry<unsigned long, FuzzyVariant> >, DefaultKeyCompare<unsigned long> >::*)(AVLTreeEntry<unsigned long, FuzzyVariant>*))
// {
// }

// /**
//  * Offset/Address/Size: 0xD4 | 0x8003F178 | size: 0x64
//  */
// void AVLTreeBase<unsigned long, FuzzyVariant, BasicSlotPool<AVLTreeEntry<unsigned long, FuzzyVariant> >, DefaultKeyCompare<unsigned long> >::DestroyTree(void (AVLTreeBase<unsigned long, FuzzyVariant, BasicSlotPool<AVLTreeEntry<unsigned long, FuzzyVariant> >, DefaultKeyCompare<unsigned long> >::*)(AVLTreeEntry<unsigned long, FuzzyVariant>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x7C | 0x8003F120 | size: 0x58
//  */
// void AVLTreeBase<unsigned long, FuzzyVariant, BasicSlotPool<AVLTreeEntry<unsigned long, FuzzyVariant> >, DefaultKeyCompare<unsigned long> >::Clear()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8003F0A4 | size: 0x7C
//  */
// void AVLTreeBase<unsigned long, FuzzyVariant, BasicSlotPool<AVLTreeEntry<unsigned long, FuzzyVariant> >, DefaultKeyCompare<unsigned long> >::~AVLTreeBase()
// {
// }

// /**
//  * Offset/Address/Size: 0xE0 | 0x8003F064 | size: 0x40
//  */
// void ScriptQuestionCache::Clear()
// {
// }

// /**
//  * Offset/Address/Size: 0x80 | 0x8003F004 | size: 0x60
//  */
// void nlAVLTreeSlotPool<unsigned long, FuzzyVariant, DefaultKeyCompare<unsigned long> >::~nlAVLTreeSlotPool()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8003EF84 | size: 0x80
//  */
// ScriptQuestionCache::~ScriptQuestionCache()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8003EF4C | size: 0x38
//  */
// void nlSingleton<ScriptQuestionCache>::DestroyInstance()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8003EEEC | size: 0x60
//  */
// GameTweaks::~GameTweaks()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8003EEC8 | size: 0x24
//  */
// void ListContainerBase<unsigned long, NewAdapter<ListEntry<unsigned long> > >::DeleteEntry(ListEntry<unsigned long>*)
// {
// }

/**
 * Offset/Address/Size: 0x2274 | 0x8003E7E8 | size: 0x6E0
 */
void CreateGame()
{
}

/**
 * Offset/Address/Size: 0x2118 | 0x8003E68C | size: 0x15C
 */
void DestroyGame()
{
}

/**
 * Offset/Address/Size: 0x2024 | 0x8003E598 | size: 0xF4
 */
void DestroyPowerups()
{
}

/**
 * Offset/Address/Size: 0x1D30 | 0x8003E2A4 | size: 0x2F4
 */
cGame::cGame()
{
}

/**
 * Offset/Address/Size: 0x1BA8 | 0x8003E11C | size: 0x188
 */
cGame::~cGame()
{
}

/**
 * Offset/Address/Size: 0x1B2C | 0x8003E0A0 | size: 0x7C
 */
void cGame::DoPerfectPassSlowDown()
{
}

/**
 * Offset/Address/Size: 0x1B18 | 0x8003E08C | size: 0x14
 */
float cGame::GetNormalizedGameTime()
{
    return m_pGameClock->m_fTimer / m_fGameDuration;
}

/**
 * Offset/Address/Size: 0x1B0C | 0x8003E080 | size: 0xC
 */
float cGame::GetGameTime()
{
    return m_pGameClock->m_fTimer;
}

/**
 * Offset/Address/Size: 0x1720 | 0x8003DC94 | size: 0x3EC
 */
void cGame::ResetForKickOff()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x16DC | 0x8003DC50 | size: 0x44
 */
void cGame::PostResetCallback(unsigned long, unsigned long)
{
    g_pEventManager->CreateValidEvent(0xa, 0x14);
    GameplayCamera* pCamera = cCameraManager::GetCamera<GameplayCamera>(eCameraType_Gameplay);
    if (pCamera != nullptr)
    {
        pCamera->m_ForceNeutralAndNearZoom = false;
    }
}

/**
 * Offset/Address/Size: 0x113C | 0x8003D6B0 | size: 0x5A0
 */
void cGame::BeginGame(bool, bool)
{
}

/**
 * Offset/Address/Size: 0xE5C | 0x8003D3D0 | size: 0x2E0
 */
void cGame::CheckForGoal()
{
}

/**
 * Offset/Address/Size: 0xDF0 | 0x8003D364 | size: 0x6C
 */
void cGame::BlowUpPowerups(const nlVector3& pos, float radius)
{
    float radiusSq = radius * radius;
    float posZ = pos.f.z;
    float posY = pos.f.y;
    float posX = pos.f.x;

    for (int i = 0; i < 25; i++)
    {
        PowerupBase* pPowerup = g_pPowerups[i];
        if (pPowerup != nullptr)
        {
            float dx = posX - pPowerup->m_v3Position.f.x;
            float dy = posY - pPowerup->m_v3Position.f.y;
            float dz = posZ - pPowerup->m_v3Position.f.z;

            if (dx * dx + dy * dy + dz * dz < radiusSq)
            {
                pPowerup->m_bShouldDestroy = true;
            }
        }
    }
}

/**
 * Offset/Address/Size: 0xCE4 | 0x8003D258 | size: 0x10C
 */
void cGame::ResetPowerups(bool)
{
}

/**
 * Offset/Address/Size: 0xB00 | 0x8003D074 | size: 0x1E4
 */
void cGame::ResetBowser()
{
    if (GameInfoManager::s_pInstance->IsTiltingFieldOn() || GameInfoManager::s_pInstance->mIsInStrikers101Mode)
    {
        mBowserTimer.m_uPackedTime = 0;
        return;
    }

    if (GetConfigBool(Config::Global(), "bowser_repeat", false))
    {
        g_pGame->m_pGameTweaks->unk308 = 1.0f;
        g_pGame->m_pGameTweaks->unk30C = 4.0f;
        g_pGame->m_pGameTweaks->unk310 = -1.0f;
    }

    GameTweaks* pTweaks_ = g_pGame->m_pGameTweaks;
    if (nlRandomf(1.0f, &nlDefaultSeed) < pTweaks_->unk308)
    {
        GameTweaks* pTweaks = g_pGame->m_pGameTweaks;
        float fMinTime = pTweaks->unk30C;
        float fMaxTime = pTweaks->unk310;

        if (fMinTime < 0.0f)
        {
            fMinTime = 0.0f;
        }
        else if (fMinTime > m_fGameDuration)
        {
            fMinTime = m_fGameDuration - 10.f;
        }

        float fThreshold = 0.0f;
        float fTimeRange = fThreshold;

        if (fMaxTime > fThreshold)
        {
            fTimeRange = m_fGameDuration - fMaxTime - fMinTime;
        }

        if (fTimeRange > fThreshold)
        {
            mBowserTimer.SetSeconds(fMinTime + nlRandomf(fTimeRange, &nlDefaultSeed));
            return;
        }

        mBowserTimer.SetSeconds(fMinTime);
        return;
    }

    mBowserTimer.m_uPackedTime = 0;
}

/**
 * Offset/Address/Size: 0xA80 | 0x8003CFF4 | size: 0x80
 */
void cGame::ResetBowserTimer(float seconds)
{
    if (seconds > 0.0f && !GameInfoManager::s_pInstance->IsTiltingFieldOn() && !GameInfoManager::s_pInstance->mIsInStrikers101Mode)
    {
        mBowserTimer.SetSeconds(seconds);
        return;
    }
    mBowserTimer.m_uPackedTime = 0;
}

/**
 * Offset/Address/Size: 0xA20 | 0x8003CF94 | size: 0x60
 */
void cGame::PreUpdate(float deltaTime)
{
    for (int i = 0; i < 2; i++)
    {
        g_pTeams[i]->PreUpdate(deltaTime);
    }
}

/**
 * Offset/Address/Size: 0x5A4 | 0x8003CB18 | size: 0x47C
 */
void cGame::Update(float)
{
}

/**
 * Offset/Address/Size: 0x508 | 0x8003CA7C | size: 0x9C
 */
void cGame::SetPotentialScorer(cPlayer* pPlayer)
{
    cPlayer* pOldScorer = m_pScorer;

    if (pOldScorer != nullptr && pPlayer != nullptr && pOldScorer != pPlayer && pOldScorer->IsOnSameTeam(pPlayer))
    {
        m_pAssister = m_pScorer;
    }
    else
    {
        m_pAssister = nullptr;
    }

    m_pScorer = pPlayer;

    if (pPlayer != nullptr && pPlayer->m_eClassType == FIELDER)
    {
        m_pTeamTouch[pPlayer->m_pTeam->m_nSide] = pPlayer;
    }
}

/**
 * Offset/Address/Size: 0x4DC | 0x8003CA50 | size: 0x2C
 */
void cGame::ChangeGameState(eGameState state)
{
    if (state != m_eGameState)
    {
        InitGameState(state);
    }
}

/**
 * Offset/Address/Size: 0x374 | 0x8003C8E8 | size: 0x168
 */
void cGame::InitGameState(eGameState state)
{
    // Check if transitioning from GS_GAMEPLAY to GS_OVERTIME
    if (m_eGameState == GS_GAMEPLAY && state == GS_OVERTIME)
    {
        g_pEventManager->CreateValidEvent(0xC, 0x14);
    }

    // Update the game state
    m_eGameState = state;

    // Handle state-specific logic
    switch (state)
    {
    case GS_PRE_GAME:
        m_pGameClock->Stop();
        break;

    case GS_KICKOFF:
        m_pGameClock->Stop();
        ResetForKickOff();
        break;

    case GS_POST_GOAL:
        m_pGameClock->Stop();
        // Loop through all teams and fielders
        for (int i = 0; i < 2; i++)
        {
            cTeam* pTeam = g_pTeams[i];
            for (int j = 0; j < 4; j++)
            {
                cFielder* pFielder = pTeam->GetFielder(j);
                pFielder->CleanUpPowerupEffect();
                pFielder->EndBlur();
            }
        }
        break;

    case GS_END_GAME:
        m_pPostGameDoneClock->Start();
        m_pGameClock->Stop();
        break;

    case GS_GAMEPLAY:
        m_pGameClock->Start();
        // Loop through all teams and fielders
        for (int i = 0; i < 2; i++)
        {
            cTeam* pTeam = g_pTeams[i];
            for (int j = 0; j < 4; j++)
            {
                cFielder* pFielder = pTeam->GetFielder(j);
                // End desire if fielder is in WAIT state
                if (pFielder->m_eFielderDesireState == FIELDERDESIRE_WAIT)
                {
                    pFielder->EndDesire(false);
                }
            }
        }
        break;

    case GS_OVERTIME:
        // No specific action for overtime
        break;

    default:
        break;
    }
}

/**
 * Offset/Address/Size: 0x25C | 0x8003C7D0 | size: 0x118
 */
void cGame::IsThoughtAllowed(unsigned long)
{
}

/**
 * Offset/Address/Size: 0x1A0 | 0x8003C714 | size: 0xBC
 */
void cGame::AbortPendingThought(unsigned long)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8003C574 | size: 0x1A0
 */
void cGame::SetDifficulty(eDifficultyID, eDifficultyID, eDifficultyID)
{
}
