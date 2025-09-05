#ifndef _GAMETWEAKS_H_
#define _GAMETWEAKS_H_

// Function SetDifficulty__5cGameF13eDifficultyID13eDifficultyID13eDifficultyID checks explicitly for -1
//    Presumably invalid ID, so it's prepended to the enums here
enum eDifficultyID
{
    en_DIFFICULTY_INVALID = -1,
    en_DIFFICULTY_ROOKIE,
    en_DIFFICULTY_PROFESSIONAL,
    en_DIFFICULTY_SUPERSTAR,
    en_DIFFICULTY_LEGEND,
};

#endif // _GAMETWEAKS_H_
