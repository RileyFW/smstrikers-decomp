#include "Game/Render/CrowdManager.h"

#include "Game/NisPlayer.h"
#include "NL/gl/glConstant.h"
#include "NL/gl/glMemory.h"
#include "NL/gl/glState.h"
#include "NL/gl/glTexture.h"
#include "NL/gc/gcSwizzler.h"
#include "NL/glx/glxTexture.h"
#include "NL/nlMath.h"
#include "NL/nlPrint.h"
#include "NL/nlString.h"

#include "Game/ReplaySpecializations.h"

/**
 * Offset/Address/Size: 0x978 | 0x801647F4 | size: 0x10C
 */
void CrowdManager::Initialize()
{
    m_State = Crowd_Idle;
    m_fTime = 0.0f;
    m_fAnimScale = 1.0f;
    m_CurrentTexture = -1;
    m_nCurrentFrame = -1;
    m_nNumFrames = 8;

    nlStrNCpy(m_szTexture, "idle/idle", 64);
    m_TextureHandle = glGetTexture(m_szTexture);

    GCTextureSize(GXTex_CMPR, 256, 512, 6, -1); // Result discarded
    m_BundleLoadBase = (u32)glResourceAlloc(0x155A0, GLM_TextureData);

    PlatTexture* platTex = glx_CreatePlatTexture();
    platTex->CreateWithMemory(256, 512, GXTex_CMPR, 6, (void*)(m_BundleLoadBase + 0x60));

    nlZeroMemory(platTex->m_SwizzledData, GCTextureSize(platTex->m_Format, platTex->m_Width, platTex->m_Height, platTex->m_Levels, -1));

    platTex->Prepare();
    glx_AddTex(m_TextureHandle, platTex);

    m_szStadium[0] = '\0';
}

/**
 * Offset/Address/Size: 0x974 | 0x801647F0 | size: 0x4
 */
void CrowdManager::Uninitialize()
{
}

/**
 * Offset/Address/Size: 0x938 | 0x801647B4 | size: 0x3C
 */
void CrowdManager::SetStadium(const char* stadium)
{
    if (stadium == nullptr)
    {
        m_szStadium[0] = '\0';
    }
    else
    {
        nlStrNCpy(m_szStadium, stadium, 64);
    }
}

/**
 * Offset/Address/Size: 0x918 | 0x80164794 | size: 0x20
 */
u32 CrowdManager::GetTextureHandle(unsigned long) const
{
    if (m_CurrentTexture == 0xFFFFFFFF)
    {
        return -1;
    }
    return m_TextureHandle;
}

/**
 * Offset/Address/Size: 0x79C | 0x80164618 | size: 0x17C
 */
void CrowdManager::Replay(LoadFrame& frame)
{
    int replayState = 0;
    void (*replayInt)(LoadFrame&, int&) = Replayable<1, LoadFrame, int>;
    replayInt(frame, replayState);

    if (replayState != (int)m_State)
    {
        m_State = (eCrowdState)replayState;
        const char* szBundle = NULL;
        m_fTime = 0.0f;

        switch (m_State)
        {
        case Crowd_Idle:
            szBundle = "idle";
            break;
        case Crowd_Happy:
            szBundle = "idle";
            break;
        case Crowd_Excited:
            szBundle = "excited";
            break;
        default:
            break;
        }

        char szFilename[64];
        if (m_szStadium[0] == '\0')
        {
            nlSNPrintf(szFilename, 64, "crowd/%s", szBundle);
        }
        else
        {
            nlSNPrintf(szFilename, 64, "crowd/%s/%s", m_szStadium, szBundle);
        }

        glBeginLoadTextureBundle(szFilename, CrowdBundleLoad_cb, (void*)m_BundleLoadBase);

        m_nCurrentFrame = 0;
        nlStrNCpy(m_szTexture, "idle/idle", 64);

        float frameValue = (float)(u32)m_nCurrentFrame / 8.0f;
        nlVector4 frameVector = {};
        frameVector.f.x = frameValue;
        frameVector.f.y = frameValue;
        frameVector.f.z = frameValue;
        frameVector.f.w = frameValue;
        glConstantSet("crowd/frame", frameVector);
    }
}

/**
 * Offset/Address/Size: 0x76C | 0x801645E8 | size: 0x30
 */
void CrowdManager::Replay(SaveFrame& frame)
{
    Replayable<1, SaveFrame, int>(frame, reinterpret_cast<int&>(m_State));
}

/**
 * Offset/Address/Size: 0x70C | 0x80164588 | size: 0x60
 */
void CrowdBundleLoad_cb(void*, unsigned long, void*)
{
    if (!glTextureLoad(glGetTexture("idle/idle")))
        return;

    f32 animScale;
    switch (CrowdManager::instance.m_State)
    {
    case Crowd_Happy:
        animScale = 1.625f;
        break;
    default:
        animScale = 1.0f;
        break;
    }
    CrowdManager::instance.m_fAnimScale = animScale;
}
/**
 * Offset/Address/Size: 0x5A0 | 0x8016441C | size: 0x16C
 * TODO: 99.9% match - single remaining diff is fmuls operand order
 *       (`fmuls f0,f1,f0` target vs `fmuls f0,f0,f1` current) in the
 *       frameValue multiply after unsigned int-to-float conversion.
 */
void CrowdManager::SetState(eCrowdState state, bool force)
{
    if (state == m_State && !force)
    {
        return;
    }

    m_State = state;
    const char* szBundle = NULL;
    m_fTime = 0.0f;

    switch (m_State)
    {
    case Crowd_Idle:
        szBundle = "idle";
        break;
    case Crowd_Happy:
        szBundle = "idle";
        break;
    case Crowd_Excited:
        szBundle = "excited";
        break;
    default:
        break;
    }

    char szFilename[64];
    if (m_szStadium[0] == '\0')
    {
        nlSNPrintf(szFilename, 64, "crowd/%s", szBundle);
    }
    else
    {
        nlSNPrintf(szFilename, 64, "crowd/%s/%s", m_szStadium, szBundle);
    }

    glBeginLoadTextureBundle(szFilename, CrowdBundleLoad_cb, (void*)m_BundleLoadBase);

    m_nCurrentFrame = 0;
    nlStrNCpy(m_szTexture, "idle/idle", 64);

    float frameValue = (float)(u32)m_nCurrentFrame;
    frameValue = 0.125f * frameValue;
    nlVector4 frameVector = {};
    frameVector.f.x = frameValue;
    frameVector.f.y = frameValue;
    frameVector.f.z = frameValue;
    frameVector.f.w = frameValue;
    glConstantSet("crowd/frame", frameVector);
}

/**
 * Offset/Address/Size: 0x480 | 0x801642FC | size: 0x120
 */
void CrowdManager::Update(float deltaTime)
{
    float adjustedDeltaTime = deltaTime;

    if (NisPlayer::Instance()->WorldIsFrozen())
    {
        adjustedDeltaTime = 0.0f;
    }

    m_fTime += m_fAnimScale * adjustedDeltaTime;
    if (m_CurrentTexture == 0xFFFFFFFF)
    {
        m_CurrentTexture = glGetTexture(m_szTexture);
    }

    if (m_fTime > 0.13333334f)
    {
        m_fTime = 0.0f;

        int currentFrame = m_nCurrentFrame + 1;
        m_nCurrentFrame = currentFrame;
        if (currentFrame >= m_nNumFrames)
        {
            m_nCurrentFrame = 0;
        }

        float frameValue = 0.125f;
        frameValue = (float)(u32)m_nCurrentFrame * frameValue;
        nlVector4 frameVector = {};
        frameVector.f.x = frameValue;
        frameVector.f.y = frameValue;
        frameVector.f.z = frameValue;
        frameVector.f.w = frameValue;
        glConstantSet("crowd/frame", frameVector);
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x80163E7C | size: 0x480
 */
void CrowdManager::EventHandler(Event*)
{
}
