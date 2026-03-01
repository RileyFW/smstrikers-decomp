#include "Game/DB/StatsTracker.h"
#include "Game/GameInfo.h"

// /**
//  * Offset/Address/Size: 0x2C7C | 0x80189818 | size: 0x144
//  */
// void Format<BasicString<char, Detail::TempStringAllocator>, const char*, const char*, const char*, const char*, const char*>(const BasicString<char, Detail::TempStringAllocator>&, const char* const&, const char* const&, const char* const&, const char* const&, const char* const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x2B20 | 0x801896BC | size: 0x15C
//  */
// void Format<BasicString<char, Detail::TempStringAllocator>, int, int, int, int, int, int, int>(const BasicString<char, Detail::TempStringAllocator>&, const int&, const int&, const int&, const int&, const int&, const int&, const int&)
// {
// }

// /**
//  * Offset/Address/Size: 0x1DAC | 0x80188948 | size: 0xD74
//  */
// void FormatImpl<BasicString<char, Detail::TempStringAllocator>>::operator%<const char*>(const char* const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x1038 | 0x80187BD4 | size: 0xD74
//  */
// void FormatImpl<BasicString<char, Detail::TempStringAllocator>>::operator%<float>(const float&)
// {
// }

// /**
//  * Offset/Address/Size: 0xEDC | 0x80187A78 | size: 0x15C
//  */
// void Format<BasicString<char, Detail::TempStringAllocator>, const char*, const char*, const char*, const char*, const char*, float, float>(const BasicString<char, Detail::TempStringAllocator>&, const char* const&, const char* const&, const char* const&, const char* const&, const char* const&, const float&, const float&)
// {
// }

// /**
//  * Offset/Address/Size: 0x168 | 0x80186D04 | size: 0xD74
//  */
// void FormatImpl<BasicString<char, Detail::TempStringAllocator>>::operator%<int>(const int&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80186B9C | size: 0x168
//  */
// void Format<BasicString<char, Detail::TempStringAllocator>, int, int, int, int, int, int, int, int>(const BasicString<char, Detail::TempStringAllocator>&, const int&, const int&, const int&, const int&, const int&, const int&, const int&, const int&)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x801869B8 | size: 0x1E4
//  */
// void BasicString<char, Detail::TempStringAllocator>::AppendInPlace<Detail::TempStringAllocator>(const BasicString<char, Detail::TempStringAllocator>&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801868FC | size: 0xBC
//  */
// void BasicString<char, Detail::TempStringAllocator>::Append<Detail::TempStringAllocator>(const BasicString<char, Detail::TempStringAllocator>&) const
// {
// }

/**
 * Offset/Address/Size: 0x52FC | 0x8018685C | size: 0xA0
 */
StatsTracker::StatsTracker()
{
}

/**
 * Offset/Address/Size: 0x50C8 | 0x80186628 | size: 0x234
 */
void StatsTracker::SetBasicGameInfoPointer(BasicGameInfo*, bool)
{
}

/**
 * Offset/Address/Size: 0x4FD0 | 0x80186530 | size: 0xF8
 * TODO: 94.2% match - r29/r30 register swap for this pointer vs teamIdx (MWCC register allocation quirk)
 */
void StatsTracker::ResetCurrentStats()
{
    eTeamID teamIdx;
    int i;

    mIsOvertime = false;
    mHasGameEnded = false;

    teamIdx = mCumulativeTeamStats[0].mTeamIndex;
    memset(&mCurrentTeamStats[0].mPlayerTotalStats, 0, sizeof(PlayerStats));
    mCurrentTeamStats[0].mPlayerTotalStats.mRecordType.mTeamID = teamIdx;
    mCurrentTeamStats[0].mPlayerTotalStats.mType = TYPE_TEAM;
    mCurrentTeamStats[0].mTeamIndex = teamIdx;
    mCurrentTeamStats[0].mNumWins = 0;
    mCurrentTeamStats[0].mNumLosses = 0;
    mCurrentTeamStats[0].mNumOTLosses = 0;
    mCurrentTeamStats[0].mNumPoints = 0;

    teamIdx = mCumulativeTeamStats[1].mTeamIndex;
    memset(&mCurrentTeamStats[1].mPlayerTotalStats, 0, sizeof(PlayerStats));
    mCurrentTeamStats[1].mPlayerTotalStats.mRecordType.mTeamID = teamIdx;
    mCurrentTeamStats[1].mPlayerTotalStats.mType = TYPE_TEAM;
    mCurrentTeamStats[1].mTeamIndex = teamIdx;
    mCurrentTeamStats[1].mNumWins = 0;
    mCurrentTeamStats[1].mNumLosses = 0;
    mCurrentTeamStats[1].mNumOTLosses = 0;
    mCurrentTeamStats[1].mNumPoints = 0;

    mNumConsecutiveGamesPlayed = mNumConsecutiveGamesPlayed + 1;

    i = 0;
    do
    {
        memset(&mCurrentUserStats[i], 0, sizeof(PlayerStats));
        mCurrentUserStats[i].mRecordType.mControllerID = i;
        mCurrentUserStats[i].mType = TYPE_USER;
        i++;
    } while (i < 4);
}

/**
 * Offset/Address/Size: 0x4F8C | 0x801864EC | size: 0x44
 */
void StatsTracker::CreateEventHandler()
{
    mEventHandler = g_pEventManager->AddEventHandler(eventHandler, NULL, 1);
}

/**
 * Offset/Address/Size: 0x4F48 | 0x801864A8 | size: 0x44
 */
void StatsTracker::DestroyEventHandler()
{
    if (mEventHandler)
    {
        g_pEventManager->RemoveEventHandler(mEventHandler);
        mEventHandler = NULL;
    }
}

/**
 * Offset/Address/Size: 0x4730 | 0x80185C90 | size: 0x818
 */
void StatsTracker::eventHandler(Event*, void*)
{
}

/**
 * Offset/Address/Size: 0x3EF0 | 0x80185450 | size: 0x840
 */
void StatsTracker::TrackStat(ePlayerStats, int, int, int, int, int, int)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x3708 | 0x80184C68 | size: 0x7E8
 */
void StatsTracker::GetSortedStats(PlayerStats*, int, int*, int, ePlayerStats, eSortOrder)
{
}

/**
 * Offset/Address/Size: 0x3340 | 0x801848A0 | size: 0x3C8
 */
void StatsTracker::GetSortedTeamStats(TeamStats*, int, int*, int)
{
}

/**
 * Offset/Address/Size: 0x2E00 | 0x80184360 | size: 0x540
 */
void StatsTracker::CompileEndOfGameStats()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x2B34 | 0x80184094 | size: 0x2CC
 */
void StatsTracker::SimulateRemainingGames()
{
}

/**
 * Offset/Address/Size: 0x2974 | 0x80183ED4 | size: 0x1C0
 */
void StatsTracker::SimulateGame()
{
    int goalsFor = 0;
    int goalsAgainst = 0;
    int i;

    for (i = 0; i < 15; i++) {
        int rand = (int)nlRandom(100, &nlDefaultSeed);
        if (rand < 20) {
            goalsFor++;
            s_pInstance->TrackStat(STATS_GOALS_FOR, 0, 0, -1, 0, 1, 0);
        } else if (rand < 40) {
            goalsAgainst++;
            s_pInstance->TrackStat(STATS_GOALS_FOR, 1, 0, -1, 0, 1, 0);
        }
    }

    if (goalsFor == goalsAgainst) {
        if ((int)nlRandom(100, &nlDefaultSeed) < 50) {
            s_pInstance->TrackStat(STATS_GOALS_FOR, 0, 0, -1, 0, 1, 0);
            s_pInstance->TrackStat(STATS_OT_WIN, 0, 0, goalsFor + 1, goalsAgainst, 0, 0);
        } else {
            s_pInstance->TrackStat(STATS_GOALS_FOR, 1, 0, -1, 0, 1, 0);
            s_pInstance->TrackStat(STATS_OT_WIN, 1, 0, goalsFor, goalsAgainst + 1, 0, 0);
        }
    } else if (goalsFor > goalsAgainst) {
        s_pInstance->TrackStat(STATS_WIN, 0, 0, goalsFor, goalsAgainst, 0, 0);
    } else {
        s_pInstance->TrackStat(STATS_WIN, 1, 0, goalsFor, goalsAgainst, 0, 0);
    }
}

/**
 * Offset/Address/Size: 0x2200 | 0x80183760 | size: 0x774
 */
void StatsTracker::AddStat(ePlayerStats, int, int, int)
{
}

/**
 * Offset/Address/Size: 0x1E5C | 0x801833BC | size: 0x3A4
 */
void StatsTracker::AddUserStatByPad(ePlayerStats, int, int)
{
}

/**
 * Offset/Address/Size: 0x1C88 | 0x801831E8 | size: 0x1D4
 */
void StatsTracker::AddMilestoneUserStat(ePlayerStats stat, int amount)
{
    GameInfoManager* pGIM = GameInfoManager::Instance();

    switch (stat)
    {
        case STATS_GOALS_FOR:
        {
            int val = pGIM->mUserInfo.mNumGoalsScored + amount;
            if (val >= 9999) {
                pGIM->mUserInfo.mNumGoalsScored = 9999;
            } else {
                pGIM->mUserInfo.mNumGoalsScored = val;
            }
            if (!pGIM->HasTrophy(TROPHY_SNIPER_CUP) && pGIM->mUserInfo.mNumGoalsScored >= 300)
            {
                pGIM->mUserInfo.mTrophies[1] |= 0x02;
            }
            break;
        }
        case STATS_HITS_MADE:
        {
            int val = pGIM->mUserInfo.mNumHits + amount;
            if (val >= 9999) {
                pGIM->mUserInfo.mNumHits = 9999;
            } else {
                pGIM->mUserInfo.mNumHits = val;
            }
            if (!pGIM->HasTrophy(TROPHY_PARAMEDIC_CUP) && pGIM->mUserInfo.mNumHits >= 1000)
            {
                pGIM->mUserInfo.mTrophies[1] |= 0x10;
            }
            break;
        }
        case STATS_PERFECT_PASSES:
        {
            int val = pGIM->mUserInfo.mNumPerfectPasses + amount;
            if (val >= 9999) {
                pGIM->mUserInfo.mNumPerfectPasses = 9999;
            } else {
                pGIM->mUserInfo.mNumPerfectPasses = val;
            }
            if (!pGIM->HasTrophy(TROPHY_TACTICIAN_CUP) && pGIM->mUserInfo.mNumPerfectPasses >= 300)
            {
                pGIM->mUserInfo.mTrophies[1] |= 0x08;
            }
            break;
        }
        case STATS_GAMES_PLAYED:
        {
            int val = pGIM->mUserInfo.mNumGamesPlayed + amount;
            if (val >= 9999) {
                pGIM->mUserInfo.mNumGamesPlayed = 9999;
            } else {
                pGIM->mUserInfo.mNumGamesPlayed = val;
            }
            if (!pGIM->HasTrophy(TROPHY_VETERAN_CUP) && pGIM->mUserInfo.mNumGamesPlayed >= 100)
            {
                pGIM->mUserInfo.mTrophies[1] |= 0x01;
            }
            break;
        }
        case STATS_STS_ATTEMPTS:
        {
            int val = pGIM->mUserInfo.mNumSTSAttempts + amount;
            if (val >= 9999) {
                pGIM->mUserInfo.mNumSTSAttempts = 9999;
            } else {
                pGIM->mUserInfo.mNumSTSAttempts = val;
            }
            if (!pGIM->HasTrophy(TROPHY_STRIKER_CUP) && pGIM->mUserInfo.mNumSTSAttempts >= 100)
            {
                pGIM->mUserInfo.mTrophies[1] |= 0x04;
            }
            break;
        }
        default:
            break;
    }
}

/**
 * Offset/Address/Size: 0x1AE0 | 0x80183040 | size: 0x1A8
 */
#pragma push
#pragma bool off
void StatsTracker::TrackWinner(int forfeitSide)
{
    int scoreLeft;
    int scoreRight;
    int startScoreLeft;
    int startScoreRight;
    unsigned char wasForfeit;
    long winningSide;

    wasForfeit = 0;
    startScoreLeft = g_pTeams[0]->m_nScore;
    startScoreRight = g_pTeams[1]->m_nScore;
    scoreLeft = startScoreLeft;
    scoreRight = startScoreRight;

    if (forfeitSide == 0)
    {
        scoreLeft = -5;
        if (startScoreRight < 3)
        {
            nlSingleton<StatsTracker>::s_pInstance->TrackStat(STATS_GOALS_FOR, 1, 0, 0, 0, 3 - startScoreRight, 0);
            scoreRight = 3;
        }
        wasForfeit = 1;
    }
    else if (forfeitSide == 1)
    {
        scoreRight = -5;
        if (startScoreLeft < 3)
        {
            nlSingleton<StatsTracker>::s_pInstance->TrackStat(STATS_GOALS_FOR, 0, 0, 0, 0, 3 - startScoreLeft, 0);
            scoreLeft = 3;
        }
        wasForfeit = 1;
    }

    winningSide = scoreRight >= scoreLeft;

    if (!mHasGameEnded)
    {
        if (nlSingleton<GameInfoManager>::s_pInstance->IsInCupOrTournamentMode())
        {
            if (mIsOvertime && !wasForfeit)
            {
                nlSingleton<StatsTracker>::s_pInstance->TrackStat(STATS_OT_WIN, winningSide, 0, scoreLeft, scoreRight, 0, 0);
                nlSingleton<GameInfoManager>::s_pInstance->SetRoundResult(1, winningSide);
            }
            else
            {
                nlSingleton<StatsTracker>::s_pInstance->TrackStat(STATS_WIN, winningSide, 0, scoreLeft, scoreRight, 0, 0);
                nlSingleton<GameInfoManager>::s_pInstance->SetRoundResult(0, winningSide);
            }
            nlSingleton<StatsTracker>::s_pInstance->CompileEndOfGameStats();
        }
        else
        {
            nlSingleton<StatsTracker>::s_pInstance->mNumGamesWon[winningSide]++;
        }
        mHasGameEnded = 1;
    }
}
#pragma pop

/**
 * Offset/Address/Size: 0x540 | 0x80181AA0 | size: 0x15A0
 */
void StatsTracker::WriteStats(float, float, const char*)
{
}

/**
 * Offset/Address/Size: 0x418 | 0x80181978 | size: 0x128
 */
void StatsTracker::AwardCup(eUserGameResult gameResult)
{
    eUserGameResult neededResult = nlSingleton<GameInfoManager>::s_pInstance->mCupMatchRequirement;
    mIsUserCupWinner = false;

    if (neededResult == RESULT_USER_LOSES)
    {
        mIsUserCupWinner = false;
    }
    else if (neededResult == RESULT_CUP_WIN)
    {
        mIsUserCupWinner = true;
    }
    else if (neededResult == RESULT_USER_OT_LOSES)
    {
        if (gameResult == RESULT_USER_WINS || gameResult == RESULT_USER_OT_WINS || gameResult == RESULT_USER_OT_LOSES)
        {
            mIsUserCupWinner = true;
        }
        else
        {
            mIsUserCupWinner = false;
        }
    }
    else if (neededResult == RESULT_USER_OT_WINS)
    {
        if (gameResult == RESULT_USER_WINS || gameResult == RESULT_USER_OT_WINS)
        {
            mIsUserCupWinner = true;
        }
        else
        {
            mIsUserCupWinner = false;
        }
    }
    else if (neededResult == RESULT_USER_WINS)
    {
        if (gameResult == RESULT_USER_WINS)
        {
            mIsUserCupWinner = true;
        }
        else
        {
            mIsUserCupWinner = false;
        }
    }

    if (mIsUserCupWinner == true)
    {
        eTrophyType tourneyCup = nlSingleton<GameInfoManager>::s_pInstance->GetTrophyTypeByCurrentMode();
        nlSingleton<GameInfoManager>::s_pInstance->mUserInfo.mTrophies[tourneyCup / 8] |= (1 << (tourneyCup % 8));
        nlSingleton<GameInfoManager>::s_pInstance->SetResultsOfLastUserGame(RESULT_CUP_WIN);
    }
}

/**
 * Offset/Address/Size: 0x148 | 0x801816A8 | size: 0x2D0
 */
void StatsTracker::WriteCurrentlyPlaying() const
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80181560 | size: 0x148
 */
bool StatsTracker::MoveTeamBUp(TeamStats b, TeamStats a)
{
    s32 bGoals = b.mPlayerTotalStats.mNumGoalsFor;
    s32 aGoals = a.mPlayerTotalStats.mNumGoalsFor;
    if (aGoals > bGoals)
        return true;
    if (bGoals > aGoals)
        return false;

    s32 bShots = b.mPlayerTotalStats.mNumShotsOnGoal;
    s32 aShots = a.mPlayerTotalStats.mNumShotsOnGoal;
    if (aShots > bShots)
        return true;
    if (bShots > aShots)
        return false;

    s32 bHits = b.mPlayerTotalStats.mNumHitsMade;
    s32 aHits = a.mPlayerTotalStats.mNumHitsMade;
    if (aHits > bHits)
        return true;
    if (bHits > aHits)
        return false;

    s32 bInterSteals = b.mPlayerTotalStats.mNumPassesIntercepted + b.mPlayerTotalStats.mNumSteals;
    s32 aInterSteals = a.mPlayerTotalStats.mNumPassesIntercepted + a.mPlayerTotalStats.mNumSteals;
    if (aInterSteals > bInterSteals)
        return true;
    if (bInterSteals > aInterSteals)
        return false;

    s32 bPU = b.mPlayerTotalStats.mNumPowerupsUsed;
    s32 aPU = a.mPlayerTotalStats.mNumPowerupsUsed;
    if (aPU > bPU)
        return true;
    if (bPU > aPU)
        return false;

    s32 bPP = b.mPlayerTotalStats.mNumPerfectPasses;
    s32 aPP = a.mPlayerTotalStats.mNumPerfectPasses;
    if (aPP > bPP)
        return true;
    if (bPP > aPP)
        return false;

    s32 bBP = b.mPlayerTotalStats.mNumButtonPresses;
    s32 aBP = a.mPlayerTotalStats.mNumButtonPresses;
    if (aBP > bBP)
        return true;
    if (bBP > aBP)
        return false;

    return (s32)a.mTeamIndex < (s32)b.mTeamIndex;
}
