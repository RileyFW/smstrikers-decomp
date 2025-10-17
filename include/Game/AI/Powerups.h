#ifndef _POWERUPS_H_
#define _POWERUPS_H_

#include "NL/nlMath.h"
#include "NL/nlTimer.h"
#include "Game/Physics/PhysicsObject.h"
#include "Game/Drawable/DrawableObj.h"
#include "Game/ObjectBlur.h"

class cFielder;
class cTeam;
class BlurHandler;
class SFXEmitter;
class Bowser;

enum ePowerUpType
{
    POWER_UP_NONE = -1,
    POWER_UP_GREEN_SHELL = 0,
    POWER_UP_RED_SHELL = 1,
    POWER_UP_SPINY_SHELL = 2,
    POWER_UP_FREEZE_SHELL = 3,
    POWER_UP_BANANA = 4,
    POWER_UP_BOBOMB = 5,
    POWER_UP_CHAIN_CHOMP = 6,
    NUM_DRAWABLE_POWER_UPS = 6,
    POWER_UP_MUSHROOM = 7,
    POWER_UP_STAR = 8,
    NUM_POWER_UPS = 9,
};

enum ePowerupSize
{
    POWERUPSIZE_SMALL = 0,
    POWERUPSIZE_MEDIUM = 1,
    POWERUPSIZE_LARGE = 2,
};

struct PowerUpTeamType
{
    /* 0x0 */ enum ePowerUpType eType;
    /* 0x4 */ int nnumOfPowerups;
    /* 0x8 */ unsigned char bIsNew;
}; // total size: 0xC

enum eThrowStyle
{
    THROW_ARROW = 0,
    THROW_HORIZONTAL_LINE = 1,
    THROW_SURROUND = 2,
    THROW_SPREAD = 3,
    NUM_THROW_TYPES = 4,
};

class Bobomb
{
public:
    ~Bobomb();
    void Update(float);
    void ThrowAt(cFielder*, Bowser*);
    void Destroy(bool);
};

class FreezeShell
{
public:
    ~FreezeShell();
    void Update(float);
    void Destroy(bool);
};

class SpinyShell
{
public:
    ~SpinyShell();
    void Update(float);
    void Destroy(bool);
};

class Banana
{
public:
    ~Banana();
    void Update(float);
    void Destroy(bool);
};

class RedShell
{
public:
    ~RedShell();
    void Update(float);
    void Destroy(bool);
    void SeekTarget();
};

class GreenShell
{
public:
    ~GreenShell();
    void Update(float);
    void Destroy(bool);
};

class PowerupBase
{
public:
    enum PowerupSound
    {
        PWRUP_SOUND_ACQUIRE = 0,
        PWRUP_SOUND_ACTIVATE = 1,
        PWRUP_SOUND_IN_EFFECT = 2,
        PWRUP_SOUND_HIT = 3,
        PWRUP_SOUND_BOUNCE_WALL = 4,
        PWRUP_SOUND_BOUNCE_GROUND = 5,
        PWRUP_SOUND_EXPLODE = 6,
        PWRUP_SOUND_END = 7,
    };

    PowerupBase(cFielder*, ePowerUpType, float, ePowerupSize, bool, int);
    virtual ~PowerupBase();
    void GetRadius() const;
    void Update(float);
    void AwardPowerup(cTeam*);
    void CollisionCallback(PhysicsObject*, PhysicsObject*, const nlVector3&, void*);
    void ThrowAt(cFielder*, Bowser*);
    void Destroy(bool);
    void PreThrow(cFielder*, Bowser*);
    void UpdateTransform();
    void Init(cFielder*, Bowser*);
    void PlayPowerupSound(ePowerUpType, PowerupBase::PowerupSound, const nlVector3&, float);
    static void PlayPowerupSound(ePowerUpType, PowerupBase::PowerupSound, PhysicsObject*, float);
    static void StopPowerupInEffectSound(SFXEmitter*);

    /* 0x04 */ bool m_bShouldDestroy;
    /* 0x08 */ DrawableObject* m_pDrawableObj;
    /* 0x0C */ PhysicsObject* m_pPhysicsObject;
    /* 0x10 */ cFielder* m_pTarget;
    /* 0x14 */ cFielder* m_pThrower;
    /* 0x18 */ ePowerUpType m_eType;
    /* 0x1C */ Timer mtActiveTimer;
    /* 0x20 */ Timer mtNoHitTimer;
    /* 0x24 */ u16 m_aOrientation;
    /* 0x28 */ f32 m_scale;
    /* 0x2C */ nlVector3 m_v3Position;
    /* 0x38 */ nlVector3 m_v3PrevPosition;
    /* 0x44 */ nlVector3 m_v3Velocity;
    /* 0x50 */ const char* m_szStreakTexture;
    /* 0x54 */ f32 m_fBlurWidth;
    /* 0x58 */ f32 m_fBlurLength;
    /* 0x5C */ u32 m_uVoiceID;
    /* 0x60 */ BlurHandler* m_pBlurHandler;
    /* 0x64 */ s32 m_nIndex;
    /* 0x68 */ s32 m_nThrowerPadID;
    /* 0x6C */ ePowerupSize meSize;
    /* 0x70 */ bool mbExploder;
}; // total size: 0x74

void CompactPowerups();
void InitializePowerups();
void FindPowerUp(unsigned long);
void PowerupCreateAndThrow(cFielder*, ePowerUpType, int, Bowser*);
void PowerupThrowPosition(int, eThrowStyle, PowerupBase*, PowerupBase*);
void FindPowerupTarget(cFielder*, Bowser*);

// class PhysicsShell
// {
// public:
//     ~PhysicsShell();
// };

// class PowerupModelPool
// {
// public:
//     void Initialize(int, unsigned long);
// };

// class DrawableObject
// {
// public:
//     void Clone() const;
// };

// class PowerupUsedEventData
// {
// public:
//     void GetID();
// };

// class PowerupHitPlayerEventData
// {
// public:
//     void GetID();
// };

// class Format < BasicString < char, Detail
// {
// public:
//     void TempStringAllocator >, int > (const BasicString<char, Detail::TempStringAllocator>&, const int&);
// };

// class FormatImpl < BasicString < char, Detail
// {
// public:
//     void TempStringAllocator >> ::operator% <int>(const int&);
// };

// class SlotPool<Bobomb>
// {
// public:
//     void ~SlotPool();
// };

// class SlotPool<Banana>
// {
// public:
//     void ~SlotPool();
// };

// class SlotPool<RedShell>
// {
// public:
//     void ~SlotPool();
// };

// class SlotPool<SpinyShell>
// {
// public:
//     void ~SlotPool();
// };

// class SlotPool<GreenShell>
// {
// public:
//     void ~SlotPool();
// };

// class SlotPool<FreezeShell>
// {
// public:
//     void ~SlotPool();
// };

#endif // _POWERUPS_H_
