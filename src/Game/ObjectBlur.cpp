#include "Game/ObjectBlur.h"

#include "NL/nlMath.h"
#include "NL/nlString.h"
#include "NL/nlMemory.h"

#include "Game/Camera/CameraMan.h"
#include "Game/GL/gluMeshWriter.h"

#include "NL/gl/glState.h"
#include "NL/gl/glMatrix.h"

#include "Game/ReplayManager.h"

BlurHandler* BlurManager::m_activeBlurHandler = NULL;

SlotPool<BlurHandler> BlurManager::m_BlurHandlerSlotPool;

f32 fFlimmerOffset = 0.01f;

const eGLStream stream_decl_[3] = { GLStream_Position, GLStream_Colour, GLStream_Diffuse };

/**
 * Offset/Address/Size: 0x0 | 0x801627D4 | size: 0x3C
 */
void BlurManager::Shutdown()
{
    nlDeleteDLRing<BlurHandler>(&m_activeBlurHandler);
    m_activeBlurHandler = NULL;
    SlotPoolBase::BaseFreeBlocks(&m_BlurHandlerSlotPool, 0x4C);
}

/**
 * Offset/Address/Size: 0x3C | 0x80162810 | size: 0x128
 */
void BlurManager::Update(float deltaTime)
{
    if (m_activeBlurHandler == NULL)
        return;

    bool isEnd;
    BlurHandler* current = nlDLRingGetStart<BlurHandler>(m_activeBlurHandler);
    do
    {
        isEnd = nlDLRingIsEnd<BlurHandler>(m_activeBlurHandler, current);
        BlurHandler* next = current->m_next;

        if (current->m_bDying)
        {
            current->m_fDyingTimer -= deltaTime;
            if (current->m_fDyingTimer <= 0.0f)
            {
                current->m_fDyingTimer = 0.0f;
            }
        }

        bool shouldRemove;
        if (current->m_bDying && current->m_fDyingTimer <= 0.0f)
        {
            shouldRemove = true;
        }
        else
        {
            shouldRemove = false;
        }

        if (shouldRemove)
        {
            nlDLRingRemove<BlurHandler>(&m_activeBlurHandler, current);
            if (current != NULL)
            {
                delete[] current->m_pointRingBuffer;
                current->m_next = (BlurHandler*)m_BlurHandlerSlotPool.m_FreeList;
                m_BlurHandlerSlotPool.m_FreeList = (SlotPoolEntry*)current;
            }
        }
        else
        {
            current->RenderMesh(current->m_uTexHashID);
        }

        current = next;
    } while (!isEnd);
}

/**
 * Offset/Address/Size: 0x164 | 0x80162938 | size: 0x78
 */
void BlurManager::DestroyHandler(BlurHandler* handler, float timeToDie)
{
    if (timeToDie == 0.0f)
    {
        nlDLRingRemove<BlurHandler>(&m_activeBlurHandler, handler);
        if (handler != NULL)
        {
            delete[] handler->m_pointRingBuffer;
            handler->m_next = (BlurHandler*)m_BlurHandlerSlotPool.m_FreeList;
            m_BlurHandlerSlotPool.m_FreeList = (SlotPoolEntry*)handler;
        }
    }
    else
    {
        handler->m_bDying = true;
        handler->m_fDyingTimer = timeToDie;
        handler->m_fTimeToDie = timeToDie;
    }
}

/**
 * Offset/Address/Size: 0x1DC | 0x801629B0 | size: 0xD0
 */
BlurHandler* BlurManager::GetNewHandler(const char* szTextureName, float fLineWidth, int maxPositionEntries, bool bAdditive)
{
    BlurHandler* handler = nullptr;

    if (m_BlurHandlerSlotPool.m_FreeList == nullptr)
    {
        SlotPoolBase::BaseAddNewBlock(&m_BlurHandlerSlotPool, 0x4C);
    }

    if (m_BlurHandlerSlotPool.m_FreeList != nullptr)
    {
        handler = (BlurHandler*)m_BlurHandlerSlotPool.m_FreeList;
        m_BlurHandlerSlotPool.m_FreeList = (SlotPoolEntry*)handler->m_next;
    }

    if (handler != nullptr)
    {
        handler->m_bAdditive = bAdditive;
        handler->m_fLineWidth = fLineWidth;
        handler->m_pLastPoint = nullptr;
        handler->m_bDying = false;
        handler->m_maxPositionEntries = maxPositionEntries;
        handler->m_nInsertIndex = 0;
        handler->m_nTrailEndPointer = 0;
        handler->m_uTexHashID = nlStringLowerHash(szTextureName);
        handler->m_pointRingBuffer = (BlurPointEntry*)nlMalloc(maxPositionEntries * sizeof(BlurPointEntry), 8, false);
    }

    nlDLRingAddEnd<BlurHandler>(&m_activeBlurHandler, handler);

    return handler;
}

/**
 * Offset/Address/Size: 0x2AC | 0x80162A80 | size: 0x514
 */
void BlurHandler::RenderMesh(unsigned long textureID)
{
    f32 sp88;
    nlMatrix4 sp50;
    eGLStream stream_decl[3];
    nlVector3 sp38;
    nlVector3 sp2C;
    nlVector2 sp24;
    nlVector2 sp1C;
    nlVector2 sp14;
    nlVector2 spC;

    nlColour sp8;
    f32 temp_f2;
    f32 temp_f3;
    f32 var_f30;
    f32 var_f31;
    BlurPointEntry* temp_r27;
    s32 var_r26;
    s32 var_r27;
    s32 var_r30;
    s8 temp_r0;
    u32 temp_r3_2;
    u32 var_r29;
    u32 var_r31;
    BlurPointEntry* temp_r0_2;
    nlVector3* temp_r5_2;
    nlVector3* temp_r6;
    nlVector3* temp_r7_2;
    nlVector3* temp_r8;

    var_r31 = 0;
    if (m_nTrailEndPointer != m_nInsertIndex)
    {
        if (m_nTrailEndPointer < m_nInsertIndex)
        {
            var_r31 = m_nInsertIndex - m_nTrailEndPointer;
        }
        else
        {
            var_r31 = (m_maxPositionEntries - m_nTrailEndPointer) + m_nInsertIndex;
        }
    }

    if (var_r31 < 2)
    {
        return;
    }

    stream_decl[0] = stream_decl_[0];
    stream_decl[1] = stream_decl_[1];
    stream_decl[2] = stream_decl_[2];

    GLMeshWriter meshWriter;

    glSetDefaultState(1);
    sp50.SetIdentity();

    sp50.f.m43 += fFlimmerOffset;
    temp_r3_2 = glAllocMatrix();
    if (temp_r3_2 != -0x1)
    {
        glSetMatrix(temp_r3_2, sp50);
    }
    glSetCurrentMatrix(temp_r3_2);

    if (m_bAdditive != 0)
    {
        glSetRasterState(GLS_AlphaBlend, 2);
    }
    else
    {
        glSetRasterState(GLS_AlphaBlend, 1);
    }
    glSetRasterState(GLS_AlphaTest, 1);
    glSetRasterState(GLS_AlphaTestRef, 0);
    glSetRasterState(GLS_DepthWrite, 0);
    glSetRasterState(GLS_Culling, 0);
    glSetCurrentRasterState(glHandleizeRasterState());
    glSetCurrentTexture(textureID, GLTT_Diffuse);
    glSetCurrentProgram(glGetProgram("3d unlit"));
    var_f31 = 0.0f;
    *(u32*)&sp8 = 0xFFFFFFFF;
    if (m_bAdditive != 0)
    {
        nlColourSet(sp8, 0xFF, 0xFF, 0xFF, 0xFF);
        if (m_bDying != 0)
        {
            temp_r0 = 255.0f * (m_fDyingTimer / m_fTimeToDie);
            nlColourSeReversed(sp8, temp_r0, temp_r0, temp_r0, temp_r0);
        }
    }
    else if (m_bDying != 0)
    {
        var_f31 = 90.0f * (m_fDyingTimer / m_fTimeToDie);
    }
    else
    {
        var_f31 = 90.0f;
    }
    var_r30 = m_nTrailEndPointer;
    var_f30 = 0.0f;
    if (meshWriter.Begin(var_r31 * 2, GLP_TriStrip, 3, stream_decl, false) != 0)
    {
        for (int var_r29 = 0; var_r29 < var_r31; var_r29++)
        {
            temp_r27 = &m_pointRingBuffer[var_r30];
            if (m_bAdditive == 0)
            {
                sp8.c[3] = var_f31 * var_f30;
            }
            if (((var_r29 == 0) || (var_r29 == (var_r31 - 1))) && (m_bDying == 0))
            {
                if (var_r29 == 0)
                {
                    var_r26 = var_r30 + 1;
                    var_r27 = var_r30;
                    if (var_r26 == m_maxPositionEntries)
                    {
                        var_r26 = 0;
                    }
                }
                else
                {
                    var_r27 = var_r30 - 1;
                    var_r26 = var_r30;
                    if (var_r27 < 0)
                    {
                        var_r27 = m_maxPositionEntries - 1;
                    }
                }
                temp_r0_2 = m_pointRingBuffer;
                temp_f2 = ReplayManager::Instance()->mRender->m_unk1ABC;
                temp_r6 = &temp_r0_2[var_r26].v3Top;
                temp_r5_2 = &temp_r0_2[var_r27].v3Top;
                temp_f3 = 1.0f - temp_f2;
                temp_r8 = &temp_r0_2[var_r26].v3Bottom;
                temp_r7_2 = &temp_r0_2[var_r27].v3Bottom;
                sp38.f.x = (temp_f3 * temp_r5_2->f.x) + (temp_f2 * temp_r6->f.x);
                sp38.f.y = (temp_f3 * temp_r5_2->f.y) + (temp_f2 * temp_r6->f.y);
                sp38.f.z = (temp_f3 * temp_r5_2->f.z) + (temp_f2 * temp_r6->f.z);
                sp2C.f.x = (temp_f3 * temp_r7_2->f.x) + (temp_f2 * temp_r8->f.x);
                sp2C.f.y = (temp_f3 * temp_r7_2->f.y) + (temp_f2 * temp_r8->f.y);
                sp2C.f.z = (temp_f3 * temp_r7_2->f.z) + (temp_f2 * temp_r8->f.z);
                meshWriter.Colour(sp8);
                sp24.f.x = var_f30;
                sp24.f.y = 0.0f;
                meshWriter.Texcoord(sp24);
                meshWriter.Vertex(sp38);
                meshWriter.Colour(sp8);
                sp1C.f.x = var_f30;
                sp1C.f.y = 1.0f;
                meshWriter.Texcoord(sp1C);
                meshWriter.Vertex(sp2C);
            }
            else
            {
                meshWriter.Colour(sp8);
                sp14.f.x = var_f30;
                sp14.f.y = 0.0f;
                meshWriter.Texcoord(sp14);
                meshWriter.Vertex(temp_r27->v3Top);
                meshWriter.Colour(sp8);
                spC.f.x = var_f30;
                spC.f.y = 1.0f;
                meshWriter.Texcoord(spC);
                meshWriter.Vertex(temp_r27->v3Bottom);
            }
            var_r30 += 1;
            if (var_r30 == m_maxPositionEntries)
            {
                var_r30 = 0;
            }
        }

        if (meshWriter.End() == 0)
        {
            return;
        }
        glViewAttachModel(GLV_Particles, 5, meshWriter.GetModel());
    }
}

/**
 * Offset/Address/Size: 0x7C0 | 0x80162F94 | size: 0x14
 */
void BlurHandler::Die(float timeToDie)
{
    m_bDying = true;
    m_fDyingTimer = timeToDie;
    m_fTimeToDie = timeToDie;
}

/**
 * Offset/Address/Size: 0x7D4 | 0x80162FA8 | size: 0x1B0
 */
void BlurHandler::AddViewOrientedPoint(const nlVector3& position, const nlVector3& forwardVector)
{
    nlVector3 topPoint, bottomPoint;

    if (ConstructViewOrientedPoints(topPoint, bottomPoint, position, forwardVector))
    {
        m_pointFinal.v3Top = topPoint;
        m_pointFinal.v3Bottom = bottomPoint;

        if (m_pLastPoint != nullptr)
        {
            nlVector3 delta;
            nlVec3Set(delta, m_pLastPoint->v3Top.f.x - m_pointFinal.v3Top.f.x, m_pLastPoint->v3Top.f.y - m_pointFinal.v3Top.f.y, m_pLastPoint->v3Top.f.z - m_pointFinal.v3Top.f.z);

            if ((delta.f.x * delta.f.x) + (delta.f.y * delta.f.y) + (delta.f.z * delta.f.z) < 0.0025000002f)
            {
                return;
            }
        }

        BlurPointEntry* entry = &m_pointRingBuffer[m_nInsertIndex];
        entry->v3Top = m_pointFinal.v3Top;
        entry->v3Bottom = m_pointFinal.v3Bottom;

        m_pLastPoint = &m_pointRingBuffer[m_nInsertIndex];
        m_nInsertIndex = m_nInsertIndex + 1;
        m_nInsertIndex %= m_maxPositionEntries;

        if (m_nInsertIndex == m_nTrailEndPointer)
        {
            m_nTrailEndPointer = m_nTrailEndPointer + 1;
            m_nTrailEndPointer %= m_maxPositionEntries;
        }
    }
    else
    {
        if (m_nInsertIndex != m_nTrailEndPointer)
        {
            m_nTrailEndPointer = m_nTrailEndPointer + 1;
            m_nTrailEndPointer %= m_maxPositionEntries;
        }
    }
}

inline void nlVec3CrossProduct(nlVector3& result, const nlVector3& a, const nlVector3& b)
{
    result.f.x = (a.f.y * b.f.z) - (a.f.z * b.f.y);
    result.f.y = (a.f.z * b.f.x) - (a.f.x * b.f.z);
    result.f.z = (a.f.x * b.f.y) - (a.f.y * b.f.x);
}

inline float nlVec3DotProduct(const nlVector3& a, const nlVector3& b)
{
    return (a.f.x * b.f.x) + (a.f.y * b.f.y) + (a.f.z * b.f.z);
}

inline float nlVec3LengthSquared(const nlVector3& a)
{
    return (a.f.x * a.f.x) + (a.f.y * a.f.y) + (a.f.z * a.f.z);
}

inline float nlVec3Length(const nlVector3& a)
{
    return sqrtf(nlVec3LengthSquared(a));
}

/**
 * Offset/Address/Size: 0x984 | 0x80163158 | size: 0x1C4
 */
bool BlurHandler::ConstructViewOrientedPoints(nlVector3& topPoint, nlVector3& bottomPoint, nlVector3 position, const nlVector3& forwardVector)
{
    nlVector3 viewVector;
    nlVector3 perp;

    float sLen1 = nlVec3LengthSquared(forwardVector);
    if (sLen1 < 0.01f)
    {
        return false;
    }

    float invLen = nlRecipSqrt(sLen1, 1);
    nlVector3 normDir;
    nlVec3Set(normDir, invLen * forwardVector.f.x, invLen * forwardVector.f.y, invLen * forwardVector.f.z);

    cCameraManager::GetViewVector(viewVector);
    if (nlVec3DotProduct(viewVector, normDir) < 0.99f)
    {
        float normZ_2 = (-normDir.f.x * viewVector.f.z) + (normDir.f.z * viewVector.f.x);
        float normY_2 = (normDir.f.y * viewVector.f.z) - (normDir.f.z * viewVector.f.y);
        float normX_2 = (normDir.f.x * viewVector.f.y) - (normDir.f.y * viewVector.f.x);

        float invLen2 = nlRecipSqrt((normX_2 * normX_2) + ((normY_2 * normY_2) + (normZ_2 * normZ_2)), 1);

        nlVec3Set(perp, m_fLineWidth * (invLen2 * normY_2), m_fLineWidth * (invLen2 * normZ_2), m_fLineWidth * (invLen2 * normX_2));
    }
    else
    {
        if (m_pLastPoint != NULL)
        {
            nlVec3Set(perp, 0.5f * (m_pLastPoint->v3Top.f.x - m_pLastPoint->v3Bottom.f.x), 0.5f * (m_pLastPoint->v3Top.f.y - m_pLastPoint->v3Bottom.f.y), 0.5f * (m_pLastPoint->v3Top.f.z - m_pLastPoint->v3Bottom.f.z));
        }
        else
        {
            return false;
        }
    }
    float pY_5 = position.f.x;
    float pX_2 = position.f.y;
    float pZ_2 = position.f.z;
    topPoint.f.x = pY_5 + perp.f.x;
    topPoint.f.y = pX_2 + perp.f.y;
    topPoint.f.z = pZ_2 + perp.f.z;
    bottomPoint.f.x = pY_5 - perp.f.x;
    bottomPoint.f.y = pX_2 - perp.f.y;
    bottomPoint.f.z = pZ_2 - perp.f.z;
    return true;
}
