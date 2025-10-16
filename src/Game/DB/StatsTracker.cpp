#include "Game/DB/StatsTracker.h"

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
 */
void StatsTracker::ResetCurrentStats()
{
}

/**
 * Offset/Address/Size: 0x4F8C | 0x801864EC | size: 0x44
 */
void StatsTracker::CreateEventHandler()
{
}

/**
 * Offset/Address/Size: 0x4F48 | 0x801864A8 | size: 0x44
 */
void StatsTracker::DestroyEventHandler()
{
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
void StatsTracker::AddMilestoneUserStat(ePlayerStats, int)
{
}

/**
 * Offset/Address/Size: 0x1AE0 | 0x80183040 | size: 0x1A8
 */
void StatsTracker::TrackWinner(int)
{
}

/**
 * Offset/Address/Size: 0x540 | 0x80181AA0 | size: 0x15A0
 */
void StatsTracker::WriteStats(float, float, const char*)
{
}

/**
 * Offset/Address/Size: 0x418 | 0x80181978 | size: 0x128
 */
void StatsTracker::AwardCup(eUserGameResult)
{
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
void StatsTracker::MoveTeamBUp(TeamStats, TeamStats)
{
}
