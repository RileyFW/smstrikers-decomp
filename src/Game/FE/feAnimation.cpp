#include "Game/FE/feAnimation.h"
#include "NL/nlMath.h"
#include "NL/nlDLRing.h"

nlVector3_ ZeroVector3 = { 0.0f, 0.0f, 0.0f };

/**
 * Offset/Address/Size: 0x0 | 0x8020E580 | size: 0x19C
 */
void FEAnimation::Update(float arg0)
{
    f32 temp_f0;
    f32 temp_f2;
    f32 var_f31;
    fAnimationKeyframe* var_r31;
    u16 temp_r0;
    fAnimationKeyframe* temp_r9;
    nlVector4 spC;
    static const nlVector4 sZero = { 0.0f, 0.0f, 0.0f, 0.0f };

    temp_r0 = this->unk10;
    switch (temp_r0)
    {
    case 1:
        AnimateTargetAtTimeWithVector3(arg0);
        return;

    case 0:
        var_r31 = nlDLRingGetStart<fAnimationKeyframe>((fAnimationKeyframe*)this->m_DLRingHead);
        if (var_r31 != var_r31->m_next)
        {
            if (arg0 >= var_r31->unkC)
            {
                goto loop_check;

            loop_body:
                var_r31 = var_r31->m_next;
                if (nlDLRingIsEnd<fAnimationKeyframe>((fAnimationKeyframe*)this->m_DLRingHead, var_r31) != 0)
                {
                    goto loop_end;
                }

            loop_check:
                if (arg0 > var_r31->unkC)
                {
                    goto loop_body;
                }

            loop_end:
                temp_f2 = var_r31->unkC;
                if (arg0 == temp_f2)
                {
                    var_f31 = var_r31->unk0.f.x;
                }
                else if (!(arg0 > temp_f2) || (var_r31->unk0.f.y != -1.0f))
                {
                    temp_r9 = var_r31->m_prev;
                    temp_f0 = temp_r9->unkC;
                    spC = sZero;
                    spC.f.x = temp_r9->unk0.f.x;
                    spC.f.y = temp_r9->unk0.f.y;
                    spC.f.z = temp_r9->unk0.f.z;
                    spC.f.w = var_r31->unk0.f.x;
                    var_f31 = nlBezier(&spC.f.x, 3, (arg0 - temp_f0) / (temp_f2 - temp_f0));
                }
                else
                {
                    var_f31 = var_r31->unk0.f.x;
                }

                if ((var_f31 != -1.0f) && (this->unk14 == 6))
                {
                    nlColour newColor = m_instance->GetAssetColour();
                    newColor.c[3] = (u8)var_f31;
                    m_instance->SetAssetColour(newColor);
                }
            }
        }
        return;
    }
}

/**
 * Offset/Address/Size: 0x19C | 0x8020E71C | size: 0x298
 */
void FEAnimation::AnimateTargetAtTimeWithVector3(float arg0)
{
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f29;
    f32 temp_f2;
    f32 var_f29;
    f32 var_f30;
    f32 var_f31;
    f32 var_f3;
    s32 temp_r0;
    v3AnimationKeyframe* temp_r3;
    v3AnimationKeyframe* var_r31;
    v3AnimationKeyframe* temp_r29;

    var_f29 = arg0;
    temp_r3 = nlDLRingGetStart<v3AnimationKeyframe>((v3AnimationKeyframe*)this->m_DLRingHead);
    temp_f0 = temp_r3->unkC;
    var_r31 = temp_r3;
    if (var_f29 < temp_f0)
    {
        var_f29 = temp_f0;
    }
loop_4:
    if ((var_f29 > var_r31->unkC) && ((var_r31->unk4 != -1.0f) || (var_r31->unk8 != -1.0f)))
    {
        var_r31 = var_r31->m_next;
        if (nlDLRingIsEnd<v3AnimationKeyframe>((v3AnimationKeyframe*)this->m_DLRingHead, var_r31) == 0)
        {
            goto loop_4;
        }
    }
    temp_f2 = var_r31->unkC;
    if (var_f29 == temp_f2)
    {
        var_f31 = var_r31->unk0;
        var_f30 = var_r31->unk10;
        var_f3 = var_r31->unk20;
    }
    else if (!(var_f29 > temp_f2) || (var_r31->unk4 != -1.0f))
    {
        temp_r29 = var_r31->m_prev;
        temp_f0_2 = temp_r29->unkC;
        // Initialize with zeros (equivalent to @211, @212, @213 constants)
        sp28 = 0.0f;
        sp2C = 0.0f;
        temp_f29 = (var_f29 - temp_f0_2) / (temp_f2 - temp_f0_2);
        sp30 = 0.0f;
        sp34 = 0.0f;
        sp28 = temp_r29->unk0;
        sp2C = temp_r29->unk4;
        sp30 = temp_r29->unk8;
        sp34 = var_r31->unk0;
        sp18 = 0.0f;
        sp1C = 0.0f;
        sp20 = 0.0f;
        sp24 = 0.0f;
        sp18 = temp_r29->unk10;
        sp1C = temp_r29->unk14;
        sp20 = temp_r29->unk18;
        sp24 = var_r31->unk10;
        sp8 = 0.0f;
        spC = 0.0f;
        sp10 = 0.0f;
        sp14 = 0.0f;
        sp8 = temp_r29->unk20;
        spC = temp_r29->unk24;
        sp10 = temp_r29->unk28;
        sp14 = var_r31->unk20;
        var_f31 = nlBezier(&sp28, 3, temp_f29);
        var_f30 = nlBezier(&sp18, 3, temp_f29);
        var_f3 = nlBezier(&sp8, 3, temp_f29);
    }
    else
    {
        var_f31 = var_r31->unk0;
        var_f30 = var_r31->unk10;
        var_f3 = var_r31->unk20;
    }
    temp_r0 = this->unk14;
    switch (temp_r0)
    {
    case 1:
        this->m_instance->SetAssetPosition(var_f31, var_f30, var_f3);
        return;
    case 2:
        this->m_instance->SetAssetRotation(var_f31, var_f30, var_f3);
        return;
    case 3:
        this->m_instance->SetAssetScale(var_f31, var_f30, var_f3);
        return;
    }
}

// /**
//  * Offset/Address/Size: 0x0 | 0x8020E9B4 | size: 0x20
//  */
// void nlDLRingIsEnd<v3AnimationKeyframe>(v3AnimationKeyframe*, v3AnimationKeyframe*)
// {
// }

// /**
//  * Offset/Address/Size: 0x20 | 0x8020E9D4 | size: 0x20
//  */
// void nlDLRingIsEnd<fAnimationKeyframe>(fAnimationKeyframe*, v3AnimationKeyframe*)
// {
// }

// /**
//  * Offset/Address/Size: 0x40 | 0x8020E9F4 | size: 0x18
//  */
// void nlDLRingGetStart<v3AnimationKeyframe>(v3AnimationKeyframe*)
// {
// }
