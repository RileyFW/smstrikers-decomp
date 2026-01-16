#ifndef _SHTOURNSETPARAMS_H_
#define _SHTOURNSETPARAMS_H_

#include "types.h"
#include "Game/BaseSceneHandler.h"
#include "Game/FE/tlComponentInstance.h"
#include "Game/FE/feButtonComponent.h"

class TournSetParamsScene : public BaseSceneHandler
{
public:
    TournSetParamsScene();
    virtual ~TournSetParamsScene();
    virtual void Update(float);
    virtual void SceneCreated();

    void BuildSubMenuList(int, TLComponentInstance*, bool, int);
    void SetInitialParams(bool, int, int);
    void ApplyMenuDefaults();
    void InitializeMenu();

    /* 0x004 */ char pad4[4];
    /* 0x008 */ s8 m_unk_0x08;
    /* 0x009 */ char pad9[3];
    /* 0x00C */ s32 m_unk_0x0C;
    /* 0x010 */ s32 m_unk_0x10;
    /* 0x014 */ s32 m_unk_0x14;
    /* 0x018 */ FEPackage** m_unk_0x18;
    /* 0x01C */ u32 m_unk_0x1C;
    // /* 0x01C */ char pad1C[4];
    /* 0x020 */ u32* m_unk_0x20;
    /* 0x024 */ char pad24[0x54];
    /* 0x078 */ void* m_unk_0x78;
    /* 0x07C */ s8 m_unk_0x7C;
    /* 0x07D */ char pad7D[0x1A3];
    /* 0x220 */ s32 m_unk_0x220;
    /* 0x224 */ s32 m_unk_0x224;
    /* 0x228 */ char pad228[4];
    /* 0x22C */ s32 m_unk_0x22C;
    /* 0x230 */ void** m_unk_0x230;
    /* 0x234 */ void* m_unk_0x234;
    /* 0x238 */ void* m_unk_0x238;
    /* 0x23C */ u8 m_unk_0x23C;
    /* 0x23D */ char pad23D[3];
    /* 0x240 */ s32 m_unk_0x240;
    /* 0x244 */ s32 m_unk_0x244;
    /* 0x248 */ ButtonComponent m_unk_0x248;
    /* 0x248 */ char pad248[1];
};

// class FEFinder<TLComponentInstance, 4>
// {
// public:
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
// };

#endif // _SHTOURNSETPARAMS_H_
