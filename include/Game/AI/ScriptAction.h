#ifndef _SCRIPTACTION_H_
#define _SCRIPTACTION_H_

#include "Game/AI/DecisionEntity.h"
#include "Game/AI/FuzzyVariant.h"

enum eScriptActionType
{
    SAT_NONE = -1,
    SAT_SET_PLAY = 0,
    SAT_SET_DESIRE = 1,
    NUM_SCRIPT_ACTIONS = 2,
};

enum eFielderDesireState
{
    FIELDERDESIRE_END_OF_LIST = -1,
    FIELDERDESIRE_NEED_DESIRE = 0,
    FIELDERDESIRE_CUT_AND_BREAK = 1,
    FIELDERDESIRE_DEKE = 2,
    FIELDERDESIRE_GET_IN_POSITION = 3,
    FIELDERDESIRE_GET_OPEN = 4,
    FIELDERDESIRE_HIT = 5,
    FIELDERDESIRE_INTERCEPT_BALL = 6,
    FIELDERDESIRE_MARK = 7,
    FIELDERDESIRE_PROTECT_BALL = 8,
    FIELDERDESIRE_RUN_TO_NET = 9,
    FIELDERDESIRE_RUN_UPFIELD = 10,
    FIELDERDESIRE_RUN_DOWNFIELD = 11,
    FIELDERDESIRE_RUN_TO_LOCATION = 12,
    FIELDERDESIRE_PASS = 13,
    FIELDERDESIRE_SHOOT = 14,
    FIELDERDESIRE_SLIDE_ATTACK = 15,
    FIELDERDESIRE_SUPPORT_BALL_DEFENSIVE = 16,
    FIELDERDESIRE_SUPPORT_BALL_OFFENSIVE = 17,
    FIELDERDESIRE_USE_POWERUP = 18,
    FIELDERDESIRE_WINDUP_PASS = 19,
    FIELDERDESIRE_WINDUP_SHOT = 20,
    FIELDERDESIRE_WAIT_FOR_THOUGHT_CAP = 21,
    FIELDERDESIRE_USER_CONTROLLED = 22,
    FIELDERDESIRE_FINISH_ACTION = 23,
    FIELDERDESIRE_ONETIMER = 24,
    FIELDERDESIRE_POST_WHISTLE = 25,
    FIELDERDESIRE_RECEIVE_PASS_FROM_IDLE = 26,
    FIELDERDESIRE_RECEIVE_PASS_FROM_RUN = 27,
    FIELDERDESIRE_WAIT = 28,
    NUM_FIELDERDESIRES = 29,
};

struct sPlayParams
{
    /* 0x0 */ int ePlayType;
    /* 0x4 */ float fDuration;
}; // total size: 0x8

struct sDesireParams
{
    float fDuration;                 // offset 0x0, size 0x4
    eFielderDesireState eDesireType; // offset 0x4, size 0x4
    FuzzyVariant opt1;               // offset 0x8, size 0x30
    FuzzyVariant opt2;               // offset 0x38, size 0x30
}; // total size: 0x68

class ScriptAction
{
public:
    ScriptAction();
    ScriptAction(eScriptActionType, float);
    void CalcSelectionChance();
    void RollChanceDice();

public:
    /* 0x00 */ ScriptAction* next;            // offset 0x0, size 0x4
    /* 0x04 */ eScriptActionType m_eType;     // offset 0x4, size 0x4
    /* 0x08 */ float m_fConfidence;           // offset 0x8, size 0x4
    /* 0x0C */ float m_fSelectionChance;      // offset 0xC, size 0x4
    /* 0x10 */ sDesireParams m_sDesireParams; // offset 0x10, size 0x68
    /* 0x78 */ sPlayParams m_sPlayParams;     // offset 0x78, size 0x8
}; // total size: 0x80

// class SlotPool<ScriptAction>
// {
// public:
//     void ~SlotPool();
// };

#endif // _SCRIPTACTION_H_
