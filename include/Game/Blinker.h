#ifndef _BLINKER_H_
#define _BLINKER_H_

#include "NL/gl/glModel.h"
#include "Game/GL/GLMaterial.h"

#include "Game/NisPlayer.h"

class Blinker
{
public:
    void Blink(glModel*);
    void Update(float);
    Blinker(const char*, unsigned long, GLMaterialList*, GLMaterialList*, unsigned long);

    // /* 0x00 */ u32 m_unk_0x00;

    /* 0x00 */ u32 m_unk_0x00;
    /* 0x04 */ GLMaterialList* m_unk_0x04;
    /* 0x08 */ GLMaterialList* m_unk_0x08;
    /* 0x0C */ GLMaterialEntry* m_unk_0x0C;
    /* 0x10 */ GLMaterialEntry* m_unk_0x10;
    /* 0x14 */ u32 m_unk_0x14;
    /* 0x18 */ u32 m_unk_0x18;
    /* 0x1C */ u32 m_unk_0x1C;
    /* 0x20 */ u32 m_unk_0x20;
    /* 0x24 */ u32 m_unk_0x24;
    /* 0x28 */ f32 m_unk_0x28;
    /* 0x2C */ s32 m_unk_0x2C;
    /* 0x30 */ f32 m_unk_0x30[4];
    /* 0x40 */ u8 m_unk_0x40;
    /* 0x41 */ s8 m_unk_0x41;
}; /* size >= 0x42 */

#endif // _BLINKER_H_
