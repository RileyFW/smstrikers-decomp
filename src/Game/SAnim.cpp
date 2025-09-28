#include "Game/SAnim.h"

#include "NL/nlMemory.h"
#include "NL/nlList.h"

/**
 * Offset/Address/Size: 0xD40 | 0x801E9F54 | size: 0x68C
 */
cSAnim* cSAnim::Initialize(nlChunk* arg0)
{
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_f1;
    f32 temp_f3;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f6;
    f32 temp_f7;
    s32* temp_r5_12;
    s32* temp_r6;
    s32 temp_r3_3;
    s32 temp_r3_4;
    s32 temp_r3_5;
    s32 temp_r3_6;
    s32 temp_r4;
    s32 temp_r4_10;
    s32 temp_r4_11;
    s32 temp_r4_12;
    s32 temp_r4_2;
    s32 temp_r4_3;
    s32 temp_r4_4;
    s32 temp_r4_5;
    s32 temp_r4_6;
    s32 temp_r4_8;
    s32 temp_r4_9;
    s32 temp_r5;
    s32 temp_r5_2;
    s32 temp_r5_3;
    s32 temp_r5_4;
    s32 temp_r5_5;
    s32 temp_r5_6;
    s32 temp_r5_7;
    s32 temp_r5_8;
    s32 temp_r7_4;
    s32 temp_r7_5;
    s32 temp_r7_6;
    s32 temp_r7_7;
    s32 temp_r8;
    s32 temp_r8_2;
    s32 temp_r8_3;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r0_4;
    s32 var_r3;
    s32 var_r3_2;
    s32 var_r3_3;
    s32 var_r3_4;
    s32 var_r3_5;
    s32 var_r4;
    s32 var_r5;
    s32 var_r7;
    s32 var_r7_2;
    s32 var_r7_3;
    u32 temp_r4_7;
    u32 temp_r6_5;
    u32 temp_r6_6;
    u32 temp_r7_8;
    u32 var_r3_6;
    void* temp_r3;
    void* temp_r3_2;
    void* temp_r5_10;
    void* temp_r5_11;
    void* temp_r5_9;
    void* temp_r6_2;
    void* temp_r6_3;
    void* temp_r6_4;
    void* temp_r6_7;
    void* temp_r7;
    void* temp_r7_2;
    void* temp_r7_3;
    void* var_r30;
    void* var_r3_7;

    // Treat the incoming chunk as “temp_r6” (matches original &this->unk8 usage)
    temp_r6 = (s32*)arg0;

    // First: align to get the cSAnim object base ("var_r4" -> ret object)
    temp_r5 = ((nlChunk*)temp_r6)->m_ID & 0x7F000000;
    cSAnim* var_r4_obj;
    if (((-temp_r5 | temp_r5) >> 0x1F) != 0)
    {
        temp_r5_2 = 1 << (temp_r5 >> 0x18);
        var_r4 = ((s32)((u8*)temp_r6 + temp_r5_2 + 7) & ~(temp_r5_2 - 1));
    }
    else
    {
        var_r4 = (s32)((u8*)temp_r6 + 8);
    }
    var_r4_obj = (cSAnim*)var_r4;

    // Clear callback head (0x3C)
    var_r4_obj->m_cbHead = 0;

    // Walk siblings: set m_chunkHdr (kept structurally; stores aligned ptr value just like decomp’s unk0)
    temp_r7 = (u8*)temp_r6 + (((nlChunk*)temp_r6)->m_Size + 8);
    temp_r4 = ((nlChunk*)temp_r7)->m_ID & 0x7F000000;
    if (((-temp_r4 | temp_r4) >> 0x1F) != 0)
    {
        temp_r5_3 = 1 << (temp_r4 >> 0x18);
        var_r3 = (s32)((s32)temp_r7 + temp_r5_3 + 7) & ~(temp_r5_3 - 1);
    }
    else
    {
        var_r3 = (s32)temp_r7 + 8;
    }
    var_r4_obj->m_chunkID = (u32)var_r3; // structurally matches "var_r4->unk0 = var_r3"

    // Next: m_rotTracks (0x18)
    temp_r6_2 = (u8*)temp_r7 + (((nlChunk*)temp_r7)->m_Size + 8);
    temp_r4_2 = ((nlChunk*)temp_r6_2)->m_ID & 0x7F000000;
    if (((-temp_r4_2 | temp_r4_2) >> 0x1F) != 0)
    {
        temp_r5_4 = 1 << (temp_r4_2 >> 0x18);
        var_r3_2 = (s32)((s32)temp_r6_2 + temp_r5_4 + 7) & ~(temp_r5_4 - 1);
    }
    else
    {
        var_r3_2 = (s32)temp_r6_2 + 8;
    }
    var_r4_obj->m_rotTracks = (void**)var_r3_2;

    // Next: m_scaleTracks (0x1C)
    temp_r7_2 = (u8*)temp_r6_2 + (((nlChunk*)temp_r6_2)->m_Size + 8);
    temp_r4_3 = ((nlChunk*)temp_r7_2)->m_ID & 0x7F000000;
    if (((-temp_r4_3 | temp_r4_3) >> 0x1F) != 0)
    {
        temp_r5_5 = 1 << (temp_r4_3 >> 0x18);
        var_r3_3 = (s32)((s32)temp_r7_2 + temp_r5_5 + 7) & ~(temp_r5_5 - 1);
    }
    else
    {
        var_r3_3 = (s32)temp_r7_2 + 8;
    }
    var_r4_obj->m_scaleTracks = (void**)var_r3_3;

    // Next: m_transTracks (0x20)
    temp_r6_3 = (u8*)temp_r7_2 + (((nlChunk*)temp_r7_2)->m_Size + 8);
    temp_r4_4 = ((nlChunk*)temp_r6_3)->m_ID & 0x7F000000;
    if (((-temp_r4_4 | temp_r4_4) >> 0x1F) != 0)
    {
        temp_r5_6 = 1 << (temp_r4_4 >> 0x18);
        var_r3_4 = (s32)((s32)temp_r6_3 + temp_r5_6 + 7) & ~(temp_r5_6 - 1);
    }
    else
    {
        var_r3_4 = (s32)temp_r6_3 + 8;
    }
    var_r4_obj->m_transTracks = (void**)var_r3_4;

    // Next: m_rootRot (0x28)
    temp_r7_3 = (u8*)temp_r6_3 + (((nlChunk*)temp_r6_3)->m_Size + 8);
    temp_r4_5 = ((nlChunk*)temp_r7_3)->m_ID & 0x7F000000;
    if (((-temp_r4_5 | temp_r4_5) >> 0x1F) != 0)
    {
        temp_r5_7 = 1 << (temp_r4_5 >> 0x18);
        var_r3_5 = (s32)((s32)temp_r7_3 + temp_r5_7 + 7) & ~(temp_r5_7 - 1);
    }
    else
    {
        var_r3_5 = (s32)temp_r7_3 + 8;
    }
    var_r4_obj->m_rootRot = (unsigned short*)var_r3_5;

    // Next: m_rootTrans (0x2C)
    temp_r6_4 = (u8*)temp_r7_3 + (((nlChunk*)temp_r7_3)->m_Size + 8);
    temp_r4_6 = ((nlChunk*)temp_r6_4)->m_ID & 0x7F000000;
    if (((-temp_r4_6 | temp_r4_6) >> 0x1F) != 0)
    {
        temp_r5_8 = 1 << (temp_r4_6 >> 0x18);
        var_r3_6 = (s32)((s32)temp_r6_4 + temp_r5_8 + 7) & ~(temp_r5_8 - 1);
    }
    else
    {
        var_r3_6 = (s32)temp_r6_4 + 8;
    }
    var_r4_obj->m_rootTrans = (nlVector3*)var_r3_6;

    var_r5 = 0;
    var_r30 = (u8*)temp_r6_4 + (((nlChunk*)temp_r6_4)->m_Size + 8);

    // Scan groups to fill per-bone track pointer tables
loop_43:
    if ((var_r30 != ((u8*)arg0 + (arg0->m_Size + 8)))
        && ((temp_r4_7 = ((nlChunk*)var_r30)->m_ID & 0x80FFFFFF, (((temp_r4_7 + 0x7FFF0000) == 0x7100) != 0)) || (temp_r4_7 == 0x1001)))
    {
        if ((temp_r4_7 + 0x7FFF0000) == 0x7100)
        {
            var_r3_7 = (u8*)var_r30 + 8;
        loop_40:
            if (var_r3_7 != ((u8*)var_r30 + (((nlChunk*)var_r30)->m_Size + 8)))
            {
                temp_r7_4 = ((nlChunk*)var_r3_7)->m_ID;
                temp_r6_5 = (temp_r7_4 & 0x80FFFFFF) + 0xFFFF0000;
                switch (temp_r6_5)
                { /* irregular */
                case 0x7101:
                { // ROT
                    temp_r7_5 = temp_r7_4 & 0x7F000000;
                    if (((-temp_r7_5 | temp_r7_5) >> 0x1F) != 0)
                    {
                        temp_r8 = 1 << (temp_r7_5 >> 0x18);
                        var_r7 = (s32)((s32)var_r3_7 + temp_r8 + 7) & ~(temp_r8 - 1);
                    }
                    else
                    {
                        var_r7 = (s32)var_r3_7 + 8;
                    }
                    *(void**)((u8*)var_r4_obj->m_rotTracks + var_r5) = (void*)var_r7;
                    break;
                }
                case 0x7102:
                { // SCALE
                    temp_r7_6 = temp_r7_4 & 0x7F000000;
                    if (((-temp_r7_6 | temp_r7_6) >> 0x1F) != 0)
                    {
                        temp_r8_2 = 1 << (temp_r7_6 >> 0x18);
                        var_r7_2 = (s32)((s32)var_r3_7 + temp_r8_2 + 7) & ~(temp_r8_2 - 1);
                    }
                    else
                    {
                        var_r7_2 = (s32)var_r3_7 + 8;
                    }
                    *(void**)((u8*)var_r4_obj->m_scaleTracks + var_r5) = (void*)var_r7_2;
                    break;
                }
                case 0x7103:
                { // TRANS
                    temp_r7_7 = temp_r7_4 & 0x7F000000;
                    if (((-temp_r7_7 | temp_r7_7) >> 0x1F) != 0)
                    {
                        temp_r8_3 = 1 << (temp_r7_7 >> 0x18);
                        var_r7_3 = (s32)((s32)var_r3_7 + temp_r8_3 + 7) & ~(temp_r8_3 - 1);
                    }
                    else
                    {
                        var_r7_3 = (s32)var_r3_7 + 8;
                    }
                    *(void**)((u8*)var_r4_obj->m_transTracks + var_r5) = (void*)var_r7_3;
                    break;
                }
                }
                var_r3_7 = (u8*)var_r3_7 + (((nlChunk*)var_r3_7)->m_Size + 8);
                goto loop_40;
            }
            var_r5 += 4;
        }
        var_r30 = (u8*)var_r30 + (((nlChunk*)var_r30)->m_Size + 8);
        goto loop_43;
    }

    // Root speed from rootTrans (0x2C) and rootKeyCount (0x24)
    if (var_r4_obj->m_rootTrans != 0)
    {
        temp_r6_6 = var_r4_obj->m_rootKeyCount;
        if (temp_r6_6 != 0)
        {
            if (temp_r6_6 == 1)
            {
                temp_r5_9 = (u8*)var_r4_obj->m_rootTrans + ((temp_r6_6 - 1) * 0xC);
                sp14 = ((nlVector3*)temp_r5_9)->f.x;
                sp18 = ((nlVector3*)temp_r5_9)->f.y;
                sp1C = ((nlVector3*)temp_r5_9)->f.z;
            }
            else
            {
                temp_f4 = 0.0f * (temp_r6_6 - 1);
                temp_r4_8 = (s32)temp_f4;
                temp_r3 = (u8*)var_r4_obj->m_rootTrans + ((temp_r4_8 + 1) * 0xC);
                temp_f6 = temp_f4 - (f32)temp_r4_8;
                temp_r3_2 = (u8*)var_r4_obj->m_rootTrans + (temp_r4_8 * 0xC);
                temp_f7 = 1.0f - temp_f6;
                sp14 = (temp_f7 * ((nlVector3*)temp_r3_2)->f.x) + (temp_f6 * ((nlVector3*)temp_r3)->f.x);
                sp18 = (temp_f7 * ((nlVector3*)temp_r3_2)->f.y) + (temp_f6 * ((nlVector3*)temp_r3)->f.y);
                sp1C = (temp_f7 * ((nlVector3*)temp_r3_2)->f.z) + (temp_f6 * ((nlVector3*)temp_r3)->f.z);
            }
        }
        else
        {
            sp14 = 0.0f;
            sp18 = 0.0f;
            sp1C = 0.0f;
        }

        if (temp_r6_6 != 0)
        {
            temp_r5_10 = (u8*)var_r4_obj->m_rootTrans + ((temp_r6_6 - 1) * 0xC);
            sp8 = ((nlVector3*)temp_r5_10)->f.x;
            spC = ((nlVector3*)temp_r5_10)->f.y;
            sp10 = ((nlVector3*)temp_r5_10)->f.z;
        }
        else
        {
            sp8 = 0.0f;
            spC = 0.0f;
            sp10 = 0.0f;
        }

        temp_f4_2 = spC - sp18;
        temp_f3 = sp8 - sp14;
        temp_f1 = sp10 - sp1C;

        // divide by (numFrames / 30.0f)
        var_r4_obj->m_rootSpeed
            = nlSqrt((temp_f1 * temp_f1) + ((temp_f3 * temp_f3) + (temp_f4_2 * temp_f4_2)), 1) / (var_r4_obj->m_numFrames / 30.0f);
    }
    else
    {
        var_r4_obj->m_rootSpeed = 0.0f;
    }

    // Tail: set morph/mask pointers: 0x34, 0x30, 0x38, 0x14
    temp_r3_3 = ((nlChunk*)var_r30)->m_ID & 0x7F000000;
    if (((-temp_r3_3 | temp_r3_3) >> 0x1F) != 0)
    {
        temp_r4_9 = 1 << (temp_r3_3 >> 0x18);
        var_r0 = (s32)((s32)var_r30 + temp_r4_9 + 7) & ~(temp_r4_9 - 1);
    }
    else
    {
        var_r0 = (s32)var_r30 + 8;
    }
    var_r4_obj->m_morphIdx = (unsigned long*)var_r0;

    temp_r5_11 = (u8*)var_r30 + (((nlChunk*)var_r30)->m_Size + 8);
    temp_r3_4 = ((nlChunk*)temp_r5_11)->m_ID & 0x7F000000;
    if (((-temp_r3_4 | temp_r3_4) >> 0x1F) != 0)
    {
        temp_r4_10 = 1 << (temp_r3_4 >> 0x18);
        var_r0_2 = (s32)((s32)temp_r5_11 + temp_r4_10 + 7) & ~(temp_r4_10 - 1);
    }
    else
    {
        var_r0_2 = (s32)temp_r5_11 + 8;
    }
    var_r4_obj->m_morphTable = (void*)var_r0_2;

    temp_r6_7 = (u8*)temp_r5_11 + (((nlChunk*)temp_r5_11)->m_Size + 8);
    temp_r3_5 = ((nlChunk*)temp_r6_7)->m_ID & 0x7F000000;
    if (((-temp_r3_5 | temp_r3_5) >> 0x1F) != 0)
    {
        temp_r4_11 = 1 << (temp_r3_5 >> 0x18);
        var_r0_3 = (s32)((s32)temp_r6_7 + temp_r4_11 + 7) & ~(temp_r4_11 - 1);
    }
    else
    {
        var_r0_3 = (s32)temp_r6_7 + 8;
    }
    var_r4_obj->m_morphBytes = (unsigned char*)var_r0_3;

    temp_r5_12 = (s32*)((u8*)temp_r6_7 + (((nlChunk*)temp_r6_7)->m_Size + 8));
    temp_r3_6 = (*temp_r5_12) & 0x7F000000;
    if (((-temp_r3_6 | temp_r3_6) >> 0x1F) != 0)
    {
        temp_r4_12 = 1 << (temp_r3_6 >> 0x18);
        var_r0_4 = (s32)((s32)temp_r5_12 + temp_r4_12 + 7) & ~(temp_r4_12 - 1);
    }
    else
    {
        var_r0_4 = (s32)temp_r5_12 + 8;
    }
    var_r4_obj->m_flags = (unsigned long*)var_r0_4;

    return var_r4_obj;
}

/**
 * Offset/Address/Size: 0x91C | 0x801E9B30 | size: 0x424
 */
void cSAnim::BlendRot(int arg0, int arg1, float arg2, float arg3, cPoseAccumulator* arg4, bool arg5) const
{
    float sp44;
    float sp40;
    float sp3C;
    float sp38;
    float sp34;
    float sp30;
    float sp2C;
    float sp28;
    float sp24;
    float sp20;
    float sp1C;
    float sp18;
    float sp14;
    float sp10;
    float spC;
    float sp8;
    float temp_f1;
    float temp_f1_2;
    float temp_f31;
    int temp_r0;
    int temp_r30;
    int temp_r31;
    int temp_r5;
    void* temp_r7;
    void* temp_r7_2;
    void* temp_r8;
    void* temp_r8_2;

    temp_r31 = arg1 * 4;
    temp_r8 = m_rotTracks[arg1];
    if ((temp_r8 != NULL) && (arg1 < (int)m_numBones))
    {
        temp_r5 = (int)m_flags[arg1];
        if (temp_r5 & 2)
        {
            if (temp_r5 & 1)
            {
                arg4->BlendRotAroundZ(arg0, *((const unsigned short*)temp_r8), arg3);
                return;
            }
            sp38 = 0.000061035156f * (float)((const short*)temp_r8)[0];
            sp3C = 0.000061035156f * (float)((const short*)temp_r8)[1];
            sp40 = 0.000061035156f * (float)((const short*)temp_r8)[2];
            sp44 = 0.000061035156f * (float)((const short*)temp_r8)[3];
            nlQuaternion __q0;
            __q0.f.x = sp38;
            __q0.f.y = sp3C;
            __q0.f.z = sp40;
            __q0.f.w = sp44;
            arg4->BlendRot(arg0, &__q0, arg3, arg5);
            return;
        }
        if (arg2 == 1.0f)
        {
            temp_r0 = (int)m_numFrames - 1;
            if (temp_r5 & 1)
            {
                arg4->BlendRotAroundZ(arg0, ((const unsigned short*)temp_r8)[temp_r0], arg3);
                return;
            }
            temp_r7 = (void*)((char*)temp_r8 + (temp_r0 * 8));
            sp28 = 0.000061035156f * (float)((const short*)temp_r7)[0];
            sp2C = 0.000061035156f * (float)((const short*)temp_r7)[1];
            sp30 = 0.000061035156f * (float)((const short*)temp_r7)[2];
            sp34 = 0.000061035156f * (float)((const short*)temp_r7)[3];
            nlQuaternion __q1;
            __q1.f.x = sp28;
            __q1.f.y = sp2C;
            __q1.f.z = sp30;
            __q1.f.w = sp34;
            arg4->BlendRot(arg0, &__q1, arg3, arg5);
            return;
        }
        temp_f1 = arg2 * ((float)m_numFrames - 1.0f);
        temp_r30 = (int)temp_f1;
        temp_f31 = arg3 * (temp_f1 - (float)temp_r30);
        temp_f1_2 = arg3 - temp_f31;
        if (temp_r5 & 1)
        {
            arg4->BlendRotAroundZ(arg0, ((const unsigned short*)temp_r8)[temp_r30], temp_f1_2);
        }
        else
        {
            temp_r8_2 = (void*)((char*)temp_r8 + (temp_r30 * 8));
            sp18 = 0.000061035156f * (float)((const short*)temp_r8_2)[0];
            sp1C = 0.000061035156f * (float)((const short*)temp_r8_2)[1];
            sp20 = 0.000061035156f * (float)((const short*)temp_r8_2)[2];
            sp24 = 0.000061035156f * (float)((const short*)temp_r8_2)[3];
            nlQuaternion __q2;
            __q2.f.x = sp18;
            __q2.f.y = sp1C;
            __q2.f.z = sp20;
            __q2.f.w = sp24;
            arg4->BlendRot(arg0, &__q2, temp_f1_2, arg5);
        }
        if ((m_flags[arg1] & 1U) != 0U)
        {
            arg4->BlendRotAroundZ(arg0, ((const unsigned short*)m_rotTracks[arg1])[(temp_r30 * 1) + 1], temp_f31);
            return;
        }
        temp_r7_2 = (void*)((char*)m_rotTracks[arg1] + ((temp_r30 + 1) * 8));
        sp8 = 0.000061035156f * (float)((const short*)temp_r7_2)[0];
        spC = 0.000061035156f * (float)((const short*)temp_r7_2)[1];
        sp10 = 0.000061035156f * (float)((const short*)temp_r7_2)[2];
        sp14 = 0.000061035156f * (float)((const short*)temp_r7_2)[3];
        nlQuaternion __q3;
        __q3.f.x = sp8;
        __q3.f.y = spC;
        __q3.f.z = sp10;
        __q3.f.w = sp14;
        arg4->BlendRot(arg0, &__q3, temp_f31, arg5);
        return;
    }
    arg4->BlendRotIdentity(arg0, arg3);
}

/**
 * Offset/Address/Size: 0x608 | 0x801E981C | size: 0x314
 */
void cSAnim::BlendScale(int arg0, int arg1, float arg2, float arg3, cPoseAccumulator* arg4, bool arg5) const
{
    float sp34;
    float sp30;
    float sp2C;
    float sp28;
    float sp24;
    float sp20;
    float sp1C;
    float sp18;
    float sp14;
    float sp10;
    float spC;
    float sp8;
    float temp_f1;
    float temp_f31;
    int temp_r26;
    int temp_r31;
    void* temp_r7;
    void* temp_r7_2;
    void* temp_r8;
    void* temp_r8_2;

    temp_r31 = arg1 * 4;
    temp_r8 = m_scaleTracks[arg1];
    if ((temp_r8 != NULL) && (arg1 < (int)m_numBones))
    {
        if (m_flags[arg1] & 8)
        {
            sp2C = 0.00024414062f * (float)((const short*)temp_r8)[0];
            sp30 = 0.00024414062f * (float)((const short*)temp_r8)[1];
            sp34 = 0.00024414062f * (float)((const short*)temp_r8)[2];
            nlVector3 v0;
            nlVec3Set(v0, sp2C, sp30, sp34);
            arg4->BlendScale(arg0, &v0, arg3, arg5);
            return;
        }
        if (arg2 == 1.0f)
        {
            temp_r7 = (void*)((char*)temp_r8 + (((int)m_numFrames - 1) * 6));
            sp20 = 0.00024414062f * (float)((const short*)temp_r7)[0];
            sp24 = 0.00024414062f * (float)((const short*)temp_r7)[1];
            sp28 = 0.00024414062f * (float)((const short*)temp_r7)[2];
            nlVector3 v1;
            nlVec3Set(v1, sp20, sp24, sp28);
            arg4->BlendScale(arg0, &v1, arg3, arg5);
            return;
        }
        temp_f1 = arg2 * ((float)m_numFrames - 1.0f);
        temp_r26 = (int)temp_f1;
        temp_r7_2 = (void*)((char*)temp_r8 + (temp_r26 * 6));
        temp_f31 = arg3 * (temp_f1 - (float)temp_r26);
        sp14 = 0.00024414062f * (float)((const short*)temp_r7_2)[0];
        sp18 = 0.00024414062f * (float)((const short*)temp_r7_2)[1];
        sp1C = 0.00024414062f * (float)((const short*)temp_r7_2)[2];
        nlVector3 v2;
        nlVec3Set(v2, sp14, sp18, sp1C);
        arg4->BlendScale(arg0, &v2, arg3 - temp_f31, arg5);
        temp_r8_2 = (void*)((char*)m_scaleTracks[arg1] + ((temp_r26 + 1) * 6));
        sp8 = 0.00024414062f * (float)((const short*)temp_r8_2)[0];
        spC = 0.00024414062f * (float)((const short*)temp_r8_2)[1];
        sp10 = 0.00024414062f * (float)((const short*)temp_r8_2)[2];
        nlVector3 v3;
        nlVec3Set(v3, sp8, spC, sp10);
        arg4->BlendScale(arg0, &v3, temp_f31, arg5);
        return;
    }
    arg4->BlendScaleIdentity(arg0, arg3);
}

/**
 * Offset/Address/Size: 0x404 | 0x801E9618 | size: 0x204
 */
void cSAnim::BlendTrans(int bone, int track, float tNorm, float weight, cPoseAccumulator* acc, bool additive) const
{
    if ((unsigned long)track >= m_numBones)
    {
        acc->BlendTransIdentity(bone, weight);
        return;
    }

    if (acc->m_BaseSHierarchy->PreserveBoneLength(bone))
        return;

    void* data = m_transTracks[track];
    if (data)
    {
        const unsigned long flags = m_flags[track];

        // constant translation track (3 * float)
        if ((flags & 0x4U) != 0U)
        {
            const float* v = (const float*)data;
            nlVector3 T;
            nlVec3Set(T, v[0], v[1], v[2]);
            acc->BlendTrans(bone, &T, weight, additive);
            return;
        }

        const int last = (int)m_numFrames - 1;
        if (tNorm == 1.0f)
        {
            const float* v = (const float*)((const char*)data + last * 12); // 3*4
            nlVector3 T;
            nlVec3Set(T, v[0], v[1], v[2]);
            acc->BlendTrans(bone, &T, weight, additive);
            return;
        }

        const float f = tNorm * (float)last;
        const int k = (int)f;
        const float a1 = f - (float)k;
        const float a0w = weight - (weight * a1); // = weight * (1 - a1)
        const float a1w = weight * a1;

        const float* v0 = (const float*)((const char*)data + k * 12);
        const float* v1 = (const float*)((const char*)data + (k + 1) * 12);

        nlVector3 P0;
        nlVec3Set(P0, v0[0], v0[1], v0[2]);
        nlVector3 P1;
        nlVec3Set(P1, v1[0], v1[1], v1[2]);

        acc->BlendTrans(bone, &P0, a0w, additive);
        acc->BlendTrans(bone, &P1, a1w, additive);
        return;
    }

    acc->BlendTransIdentity(bone, weight);
}

/**
 * Offset/Address/Size: 0x3CC | 0x801E95E0 | size: 0x38
 */
void cSAnim::Destroy()
{
    nlDeleteList<cSAnimCallback>(&m_cbHead);
    m_cbHead = 0;
}

/**
 * Offset/Address/Size: 0x2EC | 0x801E9500 | size: 0xE0
 */
void cSAnim::GetRootRot(float t, unsigned short* outZ) const
{
    unsigned long count = m_rootKeyCount; // +0x24
    if (count != 0)
    {
        if (t == 1.0f || count == 1)
        {
            const unsigned short* p = &m_rootRot[count];
            *outZ = *p;
            return;
        }

        const unsigned long c1 = count - 1;
        const double dv = (double)t * (double)c1;
        const int k = (int)dv;              // fctiwz
        const double frac = dv - (double)k; // precise fraction
        const float f = (float)frac;

        const unsigned short a = m_rootRot[k];
        const unsigned short b = m_rootRot[k + 1];

        // signed delta then scaled by frac (matches xoris/lfd path)
        short d = (short)((int)b - (int)a);
        const int step = (int)(f * (float)d);
        *outZ = (unsigned short)(a + step);
        return;
    }
    *outZ = 0;
}
/**
 * Offset/Address/Size: 0x1E0 | 0x801E93F4 | size: 0x10C
 */
void cSAnim::GetRootTrans(float t, nlVector3* out) const
{
    unsigned long count = m_rootKeyCount; // +0x24
    if (count == 0)
    {
        out->f.x = 0.0f;
        out->f.y = 0.0f;
        out->f.z = 0.0f;
        return;
    }
    // t == 1.0f or count == 1 -> last sample
    if (t == 1.0f || count == 1)
    {
        const nlVector3* v = m_rootTrans + (count - 1);
        out->f.x = v->f.x;
        out->f.y = v->f.y;
        out->f.z = v->f.z;
        return;
    }

    // general case: lerp between floor(t*(count-1)) and +1
    const unsigned long c1 = count - 1;
    const double dv = (double)t * (double)c1;
    const int k = (int)dv; // fctiwz
    const double frac = dv - (double)k;
    const float f = (float)frac;
    const float g = 1.0f - f;

    const nlVector3* v0 = m_rootTrans + k;
    const nlVector3* v1 = v0 + 1;

    out->f.x = g * v0->f.x + f * v1->f.x;
    out->f.y = g * v0->f.y + f * v1->f.y;
    out->f.z = g * v0->f.z + f * v1->f.z;
}

/**
 * Offset/Address/Size: 0x160 | 0x801E9374 | size: 0x80
 */
void cSAnim::CreateCallback(float arg0, unsigned int arg1, void (*arg2)(unsigned int))
{
    cSAnimCallback* temp_r3;
    temp_r3 = (cSAnimCallback*)nlMalloc(0x10, 8, 0);

    if (temp_r3 != NULL)
    {
        temp_r3->time = arg0;
        temp_r3->mask = arg1;
        temp_r3->fn = arg2;
    }

    nlListAddStart<cSAnimCallback>(&m_cbHead, temp_r3, NULL);
}

/**
 * Offset/Address/Size: 0x0 | 0x801E9214 | size: 0x160
 */
float cSAnim::GetMorphWeight(int index, float t) const
{
    // r6 = m_morphIdx, r7 = m_morphBytes
    const unsigned long* idxTbl = m_morphIdx; // +0x34
    const unsigned char* base = m_morphBytes; // +0x38

    // r5 = (index<<2); r8 = idxTbl[index]
    unsigned long* idxPtr = (unsigned long*)((char*)idxTbl + (index << 2));
    unsigned long off = *idxPtr;
    const unsigned char* p = base;
    int i = 0;

    // sum bytes from base by repeatedly adding the same offset (the table carries absolute offset).
    if (index > 0)
    {
        int n = index;
        if (n > 8)
        {
            int bulk = (n - 8 + 7) >> 3;
            while (bulk--)
            {
                // unrolled 8x “p += off;”
                p = p + (int)off;
                p = p + (int)off;
                p = p + (int)off;
                p = p + (int)off;
                p = p + (int)off;
                p = p + (int)off;
                p = p + (int)off;
                p = p + (int)off;
                i += 8;
            }
        }
        for (; i < index; ++i)
        {
            p = p + (int)off;
        }
    }

    // if first entry or t == 1.0f -> return last sample / 255.0f
    if (off == 1 || t == 1.0f)
    {
        const unsigned char last = *(p + ((int)off) - 1);
        return (float)last / 255.0f;
    }

    // general case: lerp between floor(t*(off-1)) and next, divide by 255
    const int countMinus1 = (int)off - 1;
    const int k = (int)(t * (double)countMinus1); // fctiwz path
    const unsigned char a = p[k];
    const unsigned char b = p[k + 1];

    // fractional part via doubles (matches the xoris/lfd sequence)
    const float inv255 = 1.0f / 255.0f;
    const float fa = (float)a * inv255;
    const float fb = (float)b * inv255;

    // precise frac: (t*(off-1) - k)
    const float frac = (float)((double)t * (double)countMinus1 - (double)k);
    // weight = (1 - frac)*fa + frac*fb
    return (1.0f - frac) * fa + frac * fb;
}
