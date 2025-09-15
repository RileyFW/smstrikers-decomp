#ifndef _PRESENTATION_H_
#define _PRESENTATION_H_

#include "types.h"
#include "Game/Sys/eventman.h"

void CupWinStingerDone();
void ReadTrophyModel(void*, unsigned long, void*);
void ReadTrophyTexture(void*, unsigned long, void*);
// void 0x801267BC..0x801272A0 | size: 0xAE4;
// void LexicalCast<const char*, float>(const float&);
// void LexicalCast<const char*, int>(const int&);
// void LexicalCast<const char*, bool>(const bool&);
// void LexicalCast<const char*, const char*>(const char* const&);

class Presentation
{
public:
    ~Presentation();
    void DoFunctionCall(unsigned int);
    static Presentation& Instance();
    void LoadTrophyModel();
    void Finish();
    void Update(float);
    void DuringEndOfGamePresentation() const;
    void Call(const char*, const char*);
    void EventHandler(Event*);
    void PlayOverlay(const char*, float, float);
    void StopOverlay();
    void Reset();
};

// class NISData
// {
// public:
//     void GetID();
// };

#endif // _PRESENTATION_H_
