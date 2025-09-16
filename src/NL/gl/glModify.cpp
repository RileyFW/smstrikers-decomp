#include "NL/gl/glModify.h"
#include "NL/gl/glMemory.h"
#include <string.h>

struct Modifier
{
    /* 0x00 */ eGLModifier m_modifier;
    /* 0x04 */ s32 m_unk_0x04;
    /* 0x08 */ s32 m_unk_0x08;
};

Modifier glModifier[6];
u32 glNumModifiers = 0;

static u32 GLTT_Diffuse_bit = 0x00000001;
static u32 GLTT_Gloss_bit = 0x00000010;

/**
 * Offset/Address/Size: 0x0 | 0x801D903C | size: 0x30
 */
void gl_ModifyAddMapping(eGLModifier arg0, unsigned long arg1)
{
    glModifier[glNumModifiers].m_modifier = arg0;
    glModifier[glNumModifiers].m_unk_0x04 = -1;
    glModifier[glNumModifiers].m_unk_0x08 = arg1;
    glNumModifiers++;
}

/**
 * Offset/Address/Size: 0x30 | 0x801D906C | size: 0x2C
 */
void gl_ModifyAddMapping(eGLModifier arg0, unsigned long arg1, unsigned long arg2)
{
    glModifier[glNumModifiers].m_modifier = arg0;
    glModifier[glNumModifiers].m_unk_0x04 = arg1;
    glModifier[glNumModifiers].m_unk_0x08 = arg2;
    glNumModifiers++;
}

/**
 * Offset/Address/Size: 0x5C | 0x801D9098 | size: 0x1C
 */
void gl_ModifyClearLastMapping()
{
    s32 temp_r0;

    temp_r0 = glNumModifiers - 1;
    glNumModifiers = temp_r0;
    if (temp_r0 < 0)
    {
        glNumModifiers = 0;
    }
}

/**
 * Offset/Address/Size: 0x78 | 0x801D90B4 | size: 0xC
 */
void gl_ModifyClearMappings()
{
    glNumModifiers = 0;
}

/**
 * Offset/Address/Size: 0x84 | 0x801D90C0 | size: 0x1F8
 */
void gl_Modify(const glModelPacket* arg0)
{
    glModelPacket* packet = NULL;
    for (u32 i = 0; i < glNumModifiers; i++)
    {
        switch (glModifier[i].m_modifier)
        { /* irregular */
        case eGLModifier_0:
            if (arg0->state.program == glModifier[i].m_unk_0x04)
            {
                if (packet == NULL)
                {
                    packet = (glModelPacket*)glFrameAlloc(0x4A, GLM_Header);
                    memcpy(packet, (u32*)arg0->userData, 0x4A);
                }
                packet->state.program = glModifier[i].m_unk_0x08;
            }
            break;
        case eGLModifier_1:
            // u32 temp_r4 = glModifier[i].m_unk_0x04;
            if (glModifier[i].m_unk_0x04 + 0x10000 == -1U)
            {
                if (packet == NULL)
                {
                    packet = (glModelPacket*)glFrameAlloc(0x4A, GLM_Header);
                    memcpy(packet, (u32*)arg0->userData, 0x4A);
                }
                packet->state.texture[0] = glModifier[i].m_unk_0x08;
                packet->state.texconfig = packet->state.texconfig | GLTT_Diffuse_bit;
            }
            else if (arg0->state.texture[0] == glModifier[i].m_unk_0x04)
            {
                if (packet == NULL)
                {
                    packet = (glModelPacket*)glFrameAlloc(0x4A, GLM_Header);
                    memcpy(packet, (u32*)arg0->userData, 0x4A);
                }
                packet->state.texture[0] = glModifier[i].m_unk_0x08;
                packet->state.texconfig = (u8)(GLTT_Diffuse_bit | packet->state.texconfig);
            }
            break;
        case eGLModifier_2:
            if (packet == NULL)
            {
                packet = (glModelPacket*)glFrameAlloc(0x4A, GLM_Header);
                memcpy(packet, (u32*)arg0->userData, 0x4A);
            }
            packet->state.texture[4] = glModifier[i].m_unk_0x08;
            packet->state.texconfig = (u8)(GLTT_Gloss_bit | packet->state.texconfig);
            break;
        case eGLModifier_3:
            if (packet == NULL)
            {
                packet = (glModelPacket*)glFrameAlloc(0x4A, GLM_Header);
                memcpy(packet, (u32*)arg0->userData, 0x4A);
            }
            packet->state.texconfig = (u8)(packet->state.texconfig & glModifier[i].m_unk_0x08);
            break;
        }
    }
}

/**
 * Offset/Address/Size: 0x27C | 0x801D92B8 | size: 0x8
 */
u32 gl_ModifyGetNum()
{
    return glNumModifiers;
}
