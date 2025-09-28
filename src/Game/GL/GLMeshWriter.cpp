#include "Game/GL/GLMeshWriter.h"

#include "NL/nlMemory.h"
#include "NL/gl/glMemory.h"
#include "NL/gl/glState.h"

static const int gl_stream_stride[15] = {
    12, 3, 4, 4, 4, 4, 4, 4, 4, 12, 12, 12, 1, 16, 16
};

/**
 * Offset/Address/Size: 0x510 | 0x801E04B0 | size: 0x58
 */
GLMeshWriterCore::GLMeshWriterCore()
{
    pModel = nullptr;
    stream[0].id = GLStream_Invalid;
    stream[1].id = GLStream_Invalid;
    stream[2].id = GLStream_Invalid;
    stream[3].id = GLStream_Invalid;
    stream[4].id = GLStream_Invalid;
    stream[5].id = GLStream_Invalid;
    stream[6].id = GLStream_Invalid;
    stream[7].id = GLStream_Invalid;
    stream[8].id = GLStream_Invalid;
    stream[9].id = GLStream_Invalid;
    stream[10].id = GLStream_Invalid;
    stream[11].id = GLStream_Invalid;
    stream[12].id = GLStream_Invalid;
    stream[13].id = GLStream_Invalid;
    stream[14].id = GLStream_Invalid;
}

/**
 * Offset/Address/Size: 0x4C8 | 0x801E0468 | size: 0x48
 */
GLMeshWriterCore::~GLMeshWriterCore()
{
}

/**
 * Offset/Address/Size: 0x134 | 0x801E00D4 | size: 0x394
 */
bool GLMeshWriterCore::Begin(int numVerts, eGLPrimitive prim, int numStreams, const eGLStream* pStreamIDs, bool bPermanent)
{
    eGLStream* var_r23;
    eGLStream* var_r3_2;
    s32* var_r4_2;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r10;
    s32 temp_r11;
    s32 temp_r12;
    s32 temp_r22_2;
    s32 temp_r23;
    s32 temp_r4;
    s32 temp_r5;
    s32 temp_r5_2;
    s32 var_ctr_2;
    s32 var_r21;
    s32 var_r8;
    u32 temp_r22;
    u32 temp_r3;
    u32 var_ctr;
    void* temp_r10_2;
    void* temp_r11_2;
    void* temp_r12_2;
    glModelStream* temp_r22_3;
    void* temp_r5_3;
    void* temp_r5_4;
    void* temp_r6;
    void* temp_r7;
    void* temp_r7_2;
    void* temp_r9;
    glModelPacket* var_r25;
    glModelStream* var_r26;
    glModel* var_r3;
    void* var_r3_3;
    void* var_r3_4;
    void* var_r4;

    var_r23 = (eGLStream*)pStreamIDs;
    var_r21 = 0;
    this->maximumVerts = numVerts;
    this->currentIndex = 0;
    this->elementCount = 0;

loop_7:

    // temp_r4 = *var_r23->unk0;
    temp_r4 = var_r23[0];
    temp_r0_2 = gl_stream_stride[temp_r4];
    // temp_r22_3 = this + (temp_r4 * 6);
    temp_r22_3 = &stream[temp_r4];

    // temp_r22_3->unkC = temp_r4;
    temp_r22_3->id = temp_r4;

    temp_r3 = numVerts * temp_r0_2;
    // temp_r22_3->unkD = temp_r0_2;
    temp_r22_3->stride = (u8)temp_r0_2;

    if (bPermanent)
    {
        var_r3_4 = glResourceAlloc(temp_r3, GLM_VertexData);
    }
    else
    {
        var_r3_4 = glFrameAlloc(temp_r3, GLM_VertexData);
    }

    if (var_r3_4 == NULL)
    {
        return false;
    }

    // temp_r22_3->unk8 = var_r3_4;
    temp_r22_3->address = (u32)var_r3_4;

    if (var_r21 >= numStreams)
    {
        if (bPermanent)
        {
            var_r3 = (glModel*)glResourceAlloc(sizeof(glModel), GLM_Header);
        }
        else
        {
            var_r3 = (glModel*)glFrameAlloc(sizeof(glModel), GLM_Header);
        }

        this->pModel = var_r3;
        if (this->pModel == NULL)
        {
            return false;
        }
        memset(this->pModel, NULL, sizeof(glModel));

        if (bPermanent)
        {
            var_r25 = (glModelPacket*)glResourceAlloc(sizeof(glModelPacket), GLM_Header);
        }
        else
        {
            var_r25 = (glModelPacket*)glFrameAlloc(sizeof(glModelPacket), GLM_Header);
        }

        if (var_r25 == NULL)
        {
            return false;
        }
        memset(var_r25, 0, sizeof(glModelPacket));

        temp_r22 = numStreams * sizeof(glModelStream);
        if (bPermanent)
        {
            var_r26 = (glModelStream*)glResourceAlloc(temp_r22, GLM_Header);
        }
        else
        {
            var_r26 = (glModelStream*)glFrameAlloc(temp_r22, GLM_Header);
        }
        if (var_r26 == NULL)
        {
            return 0;
        }
        memset(var_r26, 0, temp_r22);

        this->pModel->numPackets = 1;
        this->pModel->packets = var_r25;

        var_r25->numVertices = numVerts;
        var_r25->primType = prim;
        var_r25->numStreams = numStreams;
        var_r25->streams = var_r26;
        var_r25->materialset = 0;

        glStateSave(var_r25->state);

        for (int i = 0; i < numStreams; i++)
        {
            eGLStream id = pStreamIDs[i];
            glModelStream* pCore = &stream[id];
            stream[id].id = id;
            stream[id].stride = gl_stream_stride[id];
            stream[id].address = 0;
        }

        // var_r8 = 0;
        // if (numStreams > 0)
        // {
        //     temp_r5 = numStreams - 8;
        //     if (numStreams > 8)
        //     {
        //         var_r3_2 = (eGLStream*)pStreamIDs;
        //         var_r4 = var_r26;
        //         var_ctr = (temp_r5 + 7) >> 3;
        //         if (temp_r5 > 0)
        //         {
        //             do
        //             {
        //                 var_r8 += 8;
        //                 temp_r10 = var_r3_2->unkC;
        //                 temp_r11 = var_r3_2->unk10;
        //                 temp_r7 = this + (var_r3_2->unk0 * 6);
        //                 temp_r12 = var_r3_2->unk14;
        //                 temp_r22_2 = var_r3_2->unk1C;

        //                 var_r4->unk4 = temp_r7->unkC;

        //                 temp_r5_2 = var_r3_2->unk8 * 6;
        //                 temp_r23 = var_r3_2->unk18;
        //                 temp_r9 = this + (var_r3_2->unk4 * 6);
        //                 var_r3_2 += 0x20;

        //                 var_r4->unk5 = temp_r7->unkD;

        //                 temp_r10_2 = this + temp_r5_2;

        //                 var_r4->unk0 = temp_r7->unk8;

        //                 temp_r11_2 = this + (temp_r10 * 6);

        //                 var_r4->unkA = temp_r9->unkC;

        //                 temp_r12_2 = this + (temp_r11 * 6);
        //                 temp_r5_3 = this + (temp_r12 * 6);

        //                 var_r4->unkB = temp_r9->unkD;

        //                 temp_r6 = this + (temp_r23 * 6);

        //                 var_r4->unk6 = temp_r9->unk8;

        //                 temp_r7_2 = this + (temp_r22_2 * 6);

        //                 var_r4->unk10 = temp_r10_2->unkC;
        //                 var_r4->unk11 = temp_r10_2->unkD;
        //                 var_r4->unkC = temp_r10_2->unk8;

        //                 var_r4->unk16 = temp_r11_2->unkC;
        //                 var_r4->unk17 = temp_r11_2->unkD;
        //                 var_r4->unk12 = temp_r11_2->unk8;

        //                 var_r4->unk1C = temp_r12_2->unkC;
        //                 var_r4->unk1D = temp_r12_2->unkD;
        //                 var_r4->unk18 = temp_r12_2->unk8;

        //                 var_r4->unk22 = temp_r5_3->unkC;
        //                 var_r4->unk23 = temp_r5_3->unkD;
        //                 var_r4->unk1E = temp_r5_3->unk8;

        //                 var_r4->unk28 = temp_r6->unkC;
        //                 var_r4->unk29 = temp_r6->unkD;
        //                 var_r4->unk24 = temp_r6->unk8;

        //                 var_r4->unk2E = temp_r7_2->unkC;
        //                 var_r4->unk2F = temp_r7_2->unkD;
        //                 var_r4->unk2A = temp_r7_2->unk8;

        //                 var_r4 += 0x30;
        //                 var_ctr -= 1;
        //             } while (var_ctr != 0);
        //         }
        //     }

        //     var_r4_2 = arg3 + (var_r8 * 4);
        //     var_r3_3 = var_r26 + (var_r8 * 6);
        //     var_ctr_2 = arg2 - var_r8;
        //     if (var_r8 < numStreams)
        //     {
        //         do
        //         {
        //             temp_r0 = *var_r4_2;
        //             var_r4_2 += 4;
        //             temp_r5_4 = this + (temp_r0 * 6);
        //             var_r3_3->unk4 = temp_r5_4->unkC;
        //             var_r3_3->unk5 = temp_r5_4->unkD;
        //             var_r3_3->unk0 = temp_r5_4->unk8;
        //             var_r3_3 += 6;
        //             var_ctr_2 -= 1;
        //         } while (var_ctr_2 != 0);
        //     }
        // }
        return true;
    }

    var_r23 += 4;
    var_r21 += 1;
    goto loop_7;

    return true;
}

// {
//     maximumVerts = numVerts;
//     currentIndex = 0;
//     elementCount = 0;

//     void* modelMem = bPermanent ? glResourceAlloc(0x10, GLM_Header) : glFrameAlloc(0x10, GLM_Header);
//     pModel = (glModel*)modelMem;
//     if (!pModel)
//         return false;
//     memset(pModel, 0, 0x10);

//     glModelPacket* pPacket = (glModelPacket*)(bPermanent ? glResourceAlloc(0x4A, GLM_Header)
//                                                          : glFrameAlloc(0x4A, GLM_Header));
//     if (!pPacket)
//         return false;
//     memset(pPacket, 0, 0x4A);

//     unsigned long streamsSize = (unsigned long)(numStreams * 6);
//     glModelStream* pPktStreams = (glModelStream*)(bPermanent ? glResourceAlloc(streamsSize, GLM_Header)
//                                                              : glFrameAlloc(streamsSize, GLM_Header));
//     if (!pPktStreams)
//         return false;
//     memset(pPktStreams, 0, streamsSize);

//     pModel->numPackets = 1;
//     pModel->packets = pPacket;

//     pPacket->numVertices = (unsigned short)numVerts;
//     pPacket->primType = (unsigned char)prim;
//     pPacket->numStreams = (unsigned char)numStreams;
//     pPacket->streams = pPktStreams;

//     int i;
//     for (i = 0; i < numStreams; ++i)
//     {
//         eGLStream id = pStreamIDs[i];
//         glModelStream* pCore = &stream[id];

//         pCore->id = (unsigned char)id;
//         pCore->stride = (unsigned char)gl_stream_stride[id];

//         unsigned long byteSize = (unsigned long)(maximumVerts * (unsigned long)pCore->stride);
//         void* addr = bPermanent ? glResourceAlloc(byteSize, GLM_VertexData) : glFrameAlloc(byteSize, GLM_VertexData);
//         if (!addr)
//             return false;
//         memset(addr, 0, byteSize);
//         pCore->address = (unsigned long)addr;

//         pPktStreams[i].address = pCore->address;
//         pPktStreams[i].id = pCore->id;
//         pPktStreams[i].stride = pCore->stride;
//     }

//     return true;
// }

/**
 * Offset/Address/Size: 0x11C | 0x801E00BC | size: 0x18
 */
bool GLMeshWriterCore::End()
{
    return (currentIndex == maximumVerts);
}

/**
 * Offset/Address/Size: 0x114 | 0x801E00B4 | size: 0x8
 */
glModel* GLMeshWriterCore::GetModel()
{
    return pModel;
}

/**
 * Offset/Address/Size: 0xF0 | 0x801E0090 | size: 0x24
 */
void GLMeshWriterCore::Colour(const nlColour& c)
{
    unsigned long* p = (unsigned long*)stream[GLStream_Colour].address;
    p[currentIndex] = *(const unsigned long*)&c;
    elementCount += 1;
}

/**
 * Offset/Address/Size: 0xD0 | 0x801E0070 | size: 0x20
 */
void GLMeshWriterCore::ColourPlat(unsigned long rgba)
{
    unsigned long* p = (unsigned long*)stream[GLStream_Colour].address;
    p[currentIndex] = rgba;
    elementCount += 1;
}

/**
 * Offset/Address/Size: 0xA0 | 0x801E0040 | size: 0x30
 */
void GLMeshWriterCore::Texcoord(const nlVector2& uv)
{
    char* base = (char*)stream[GLStream_Diffuse].address;
    *(nlVector2*)(base + currentIndex * 8) = uv;
    elementCount += 1;
}

/**
 * Offset/Address/Size: 0x54 | 0x801DFFF4 | size: 0x4C
 */
void GLMeshWriterCore::Vertex(const nlVector3& pos)
{
    char* base = (char*)stream[GLStream_Position].address;
    *(nlVector3*)(base + currentIndex * 12) = pos;
    elementCount += 1;
    elementCount = 0;
    currentIndex += 1;
}

/**
 * Offset/Address/Size: 0x0 | 0x801DFFA0 | size: 0x54
 */
void GLMeshWriterCore::Vertex(const nlVector4& pos)
{
    char* base = (char*)stream[GLStream_Position4].address;
    *(nlVector4*)(base + currentIndex * 16) = pos;
    elementCount += 1;
    elementCount = 0;
    currentIndex += 1;
}
