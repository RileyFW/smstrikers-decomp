#include "Game/Drawable/DrawableSkinModel.h"
#include "Game/World/worldanim.h"
#include "Game/World.h"
#include "NL/gl/glModel.h"
#include "NL/gl/gl.h"

extern u8 g_bEnableDrawableSkinModel;
extern u8 g_bSkinModelTextureLighting;
extern u32 UnlitProgram;
extern u32 LitProgram;
extern u32 LightTexture;
extern u32 GLTT_BumpLocal_bit;

u32 glAllocMatrix();
void glSetMatrix(u32 matrix, const nlMatrix4& m);
u8 glViewAttachPacket(eGLView view, const glModelPacket* pPacket);

/**
 * Offset/Address/Size: 0x0 | 0x80122D5C | size: 0x60
 */
DrawableSkinModel::~DrawableSkinModel()
{
}

/**
 * Offset/Address/Size: 0x60 | 0x80122DBC | size: 0x170
 * TODO: 99.57% match - r4/r5/r0 register allocation swap in GLTT_BumpLocal_bit/LightTexture block
 */
void DrawableSkinModel::Draw()
{
    if (!g_bEnableDrawableSkinModel)
    {
        return;
    }

    if (m_pAnimController == NULL)
    {
        return;
    }

    glModel* pModel;
    u8 isLit = (u8)((m_uObjectCreationFlags >> 7) & 1) ^ 1;
    if (isLit)
    {
        void* pLightData;
        if (g_bSkinModelTextureLighting)
        {
            pLightData = m_pWorldContext->m_pIntensityPerm;
        }
        else
        {
            pLightData = m_pWorldContext->m_pLightData;
        }
        pModel = m_pAnimController->GetUpdatedModel(LitProgram, pLightData);
    }
    else
    {
        pModel = m_pAnimController->GetUpdatedModel(UnlitProgram, NULL);
    }

    u32 matrixHandle;
    if (m_pAnimController->m_bIsGanged)
    {
        const nlMatrix4& worldMat = GetWorldMatrix();
        matrixHandle = glAllocMatrix();
        if (matrixHandle + 0x10000 != 0xFFFF)
        {
            glSetMatrix(matrixHandle, worldMat);
        }
    }

    glModelPacket* pPacket = pModel->packets;
    while (pPacket < pModel->packets + pModel->numPackets)
    {
        glModelPacket* pDup = glModelPacketDup(pPacket, true);

        if (m_pAnimController->m_bIsGanged)
        {
            pDup->state.matrix = matrixHandle;
        }

        if (g_bSkinModelTextureLighting)
        {
            u32 lightTex = LightTexture;
            pDup->state.texconfig |= GLTT_BumpLocal_bit;
            pDup->state.texture[5] = lightTex;
        }

        glViewAttachPacket((eGLView)6, pDup);
        pPacket++;
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x80122F2C | size: 0x24
 */
void DrawableSkinModel::SetAnimation(const char* szAnimationName, unsigned long playMode)
{
    m_pAnimController->SetAnimation(szAnimationName, (ePlayMode)playMode);
}

/**
 * Offset/Address/Size: 0x24 | 0x80122F50 | size: 0xC
 */
void DrawableSkinModel::SetAnimationSpeed(float fSpeed)
{
    m_pAnimController->m_fSpeed = fSpeed;
}

/**
 * Offset/Address/Size: 0x30 | 0x80122F5C | size: 0x24
 */
float DrawableSkinModel::GetAnimationTime()
{
    return m_pAnimController->GetAnimationTime();
}

/**
 * Offset/Address/Size: 0x54 | 0x80122F80 | size: 0x24
 */
void DrawableSkinModel::SetAnimationTime(float fTime)
{
    m_pAnimController->SetAnimationTime(fTime);
}

/**
 * Offset/Address/Size: 0x78 | 0x80122FA4 | size: 0x24
 */
float DrawableSkinModel::GetAnimationDuration()
{
    return m_pAnimController->GetAnimationDuration();
}
