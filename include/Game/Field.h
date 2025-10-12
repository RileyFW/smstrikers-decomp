#ifndef _FIELD_H_
#define _FIELD_H_

#include "NL/nlMath.h"
#include "Game/Net.h"
#include "Game/Ball.h"

#pragma push
#pragma pack(1)
struct sCornerSegment
{
    /* 0x0 */ nlVector2 vCenter;
    /* 0x8 */ u16 thetaStart;
    /* 0xA */ u16 thetaEnd;
    /* 0xC */ f32 fRadius;
}; // total size: 0x10
#pragma pop

struct Corner
{
    float unk0;
    float unk1;
    float unk2;
    float unk3;
    float unk4;
    float unk5;
    float unk6;
    float unk7;
    float unk8;
    float unk9;
    // float unk10;
    void (*callback)();
    // void (cBall::*callback)();
    // void (*wallCollisionFunc)(); // Changed from member function pointer to regular function pointer
    float unk11;
    float unk12;
    float unk13;
    float unk14;
    float unk15;
};

class cField
{
public:
    static void Init(cNet*, cNet*);
    static float GetGoalLineX(float);
    static float GetGoalLineX(unsigned int);
    static float GetSidelineY(unsigned int);
    static float GetCornerRadius();
    static float GetPenaltyBoxX(unsigned int);
    static float GetPenaltyBoxY();
    static cNet* GetNet(float);
    static bool IsOnField(const nlVector3&);
    static void FixOutOfBoundsPosition(nlVector3&, float);
    static void SetFieldDimensions(float, float, float);

    static nlVector3_ mv3FieldPosition;
    static nlVector3_ mSidelines[4];
    // static sCornerSegment mCorners[4];
    static Corner mCorners;
    static float mfPenaltyBoxX;
    static float mfPenaltyBoxY;
    static cNet* mpNet[2];
};

#endif // _FIELD_H_
