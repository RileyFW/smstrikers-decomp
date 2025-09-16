#include "NL/gl/glModel.h"
#include "NL/gl/glMemory.h"
#include "NL/gl/glUserData.h"
#include <string.h>

/**
 * Offset/Address/Size: 0x0 | 0x801DED34 | size: 0x160
 */
void* glModelDupArrayNoStreams(const glModel* models, unsigned long count, bool arg2, bool arg3)
{
    glModel* new_models[4];
    glModelPacket* new_packets;
    glModelPacket* dst_pack;
    glModelPacket* src_pack;
    glModel* src_model;
    glModel* dst_model;

    if (arg3 != 0)
    {
        new_models[0] = (glModel*)glResourceAlloc(count * 0x10, GLM_Header);
    }
    else
    {
        new_models[0] = (glModel*)glFrameAlloc(count * 0x10, GLM_Header);
    }

    if (new_models == NULL)
    {
        return NULL;
    }

    memcpy(new_models, models, count * 0x10);

    src_model = (glModel*)&models[0];
    dst_model = new_models[0];

    for (int i = 0; i < count; i++)
    {
        if (arg3 != 0)
        {
            new_packets = (glModelPacket*)glResourceAlloc(src_model->numPackets * 0x4A, GLM_Header);
        }
        else
        {
            new_packets = (glModelPacket*)glFrameAlloc(src_model->numPackets * 0x4A, GLM_Header);
        }

        if (new_packets == NULL)
        {
            return NULL;
        }

        memcpy(new_packets, src_model->packets, src_model->numPackets * 0x4A);
        dst_model->packets = new_packets;
        if (arg2 != 0)
        {
            dst_pack = new_packets;
            src_pack = src_model->packets;
            u8* last_pack = (u8*)src_pack + src_model->numPackets * 0x4A;

            while ((u8*)src_pack < last_pack)
            {
                if (src_pack->userData != 0)
                {
                    dst_pack->userData = 0;
                    glUserDup((glModelPacket*)dst_pack, (glModelPacket*)src_pack, false);
                }
                src_pack = (glModelPacket*)((u8*)src_pack + 0x4A);
                dst_pack = (glModelPacket*)((u8*)dst_pack + 0x4A);
            }
        }
        src_model++;
        dst_model++;
    }
    return new_models[0];
}

/**
 * Offset/Address/Size: 0x160 | 0x801DEE94 | size: 0x12C
 */
glModel* glModelDupNoStreams(const glModel* src, bool arg2, bool arg3)
{
    return NULL;
}

/**
 * Offset/Address/Size: 0x28C | 0x801DEFC0 | size: 0x114
 */
glModel* glModelDup(const glModel* src, bool arg1)
{
    glModel* model;
    glModelPacket* packets;
    glModelPacket* src_packets;
    glModelPacket* dst_packets;

    model = (glModel*)glFrameAlloc(0x10, GLM_Header);
    if (model == NULL)
    {
        return NULL;
    }

    packets = (glModelPacket*)glFrameAlloc(src->numPackets * 0x4A, GLM_Header);
    if (packets == NULL)
    {
        return NULL;
    }

    memcpy(model, src, 0x10);
    memcpy(packets, src->packets, src->numPackets * 0x4A);

    dst_packets = packets;
    src_packets = src->packets;
    model->packets = packets;

    u8* last_pack = (u8*)src_packets + src->numPackets * 0x4A;

    while ((u8*)src_packets < last_pack)
    {
        dst_packets->m_vertexData = (VertexData*)glFrameAlloc(dst_packets->numStreams * 6, GLM_Header);
        memcpy(dst_packets->m_vertexData, src_packets->m_vertexData, dst_packets->numStreams * 6);

        if ((arg1 != 0) && (src_packets->userData != 0))
        {
            dst_packets->userData = 0;
            glUserDup(dst_packets, src_packets, false);
        }

        src_packets = (glModelPacket*)((u8*)src_packets + 0x4A);
        dst_packets = (glModelPacket*)((u8*)dst_packets + 0x4A);
    }

    return model;
}

/**
 * Offset/Address/Size: 0x3A0 | 0x801DF0D4 | size: 0x8C
 */
void glModelPacketDup(const glModelPacket*, bool)
{
}
