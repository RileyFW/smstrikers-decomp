#ifndef _TIMEREGIONS_H_
#define _TIMEREGIONS_H_

void DestroyTimeRegions();
void InitializeTimeRegions();
bool IsShotInProgress();
bool IsBowserAround();
bool IsDuringAutoreplay();
bool IsDuringNIS();
void RightSideOfField();
void LeftSideOfField();
void CentreOfField();
bool IsDuringGameplay();
void WriteFrameRateStatsToFile();
// void nlListAddEnd<ListEntry<TimeRegion*>>(ListEntry<TimeRegion*>**, ListEntry<TimeRegion*>**, ListEntry<TimeRegion*>*);

class TimeRegion
{
public:
    ~TimeRegion();
};

#endif // _TIMEREGIONS_H_
