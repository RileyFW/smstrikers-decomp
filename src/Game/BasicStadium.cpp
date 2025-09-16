#pragma pool_data off

#include "Game/BasicStadium.h"
#include "Game/NetMesh.h"
#include "Game/AI/Powerups.h"
#include "Game/Render/CrowdManager.h"
#include "Game/Render/Presentation.h"
#include "Game/Render/StaticModelExplodable.h"
#include "Game/Render/AnimatedModelExplodable.h"
#include "Game/WorldTriggers.h"

#include "NL/nlString.h"
#include "NL/nlPrint.h"
#include "NL/gl/glPlat.h"
#include "NL/gl/glState.h"
#include "NL/gl/glTexture.h"
#include "string.h"

// extern WorldLoader TheWorldLoader;
extern bool g_GoalLightEnabled;
float g_fSkyboxRotationTime = 1420.0f;
float g_fCloudRotationTime = 720.0f;
EventManager* g_pEventManager = nullptr;

char szBasicStadiumName[0x40];

const char szBallName[] = "gameplay/ball";
const char szPowerupsName[] = "gameplay/powerups";

u32 uSkyBoxHashID;
u32 uCloudsHashID;
u32 uNetHelperHashID;
u32 uFieldHelperHashID;
u32 uPenaltyHelperHashID;
BasicStadium* pBasicStadiumInstance;

static nlMatrix4 mSkyBoxTM;
static nlMatrix4 mCloudTM;

extern unsigned int nlDefaultSeed;

/**
 * Offset/Address/Size: 0x2D70 | 0x8019EAF0 | size: 0x44
 */
void BasicStadium::BasicStadiumEventHandler(Event* pEvent, void*)
{
    switch (pEvent->m_type)
    {
    case 5:
        g_GoalLightEnabled = true;
        return;
    case 9:
        g_GoalLightEnabled = false;
        return;
    case 6:
    case 4:
        return;
    }
}

/**
 * Offset/Address/Size: 0x2B64 | 0x8019E8E4 | size: 0x20C
 */
BasicStadium::BasicStadium(const char* name)
    : World(name)
{
    m_CameraFlashPositions = NULL;
    m_NumCameraFlashPositions = 0;
    m_fSkyboxRotationAng = 0.0f;
    m_fCloudRotationAng = 0.0f;
    m_bCameraFlashesEnabled = false;
    mpNPCManager = NULL;
    pBasicStadiumInstance = this;

    m_pEventHandler = g_pEventManager->AddEventHandler(BasicStadium::BasicStadiumEventHandler, NULL, 4);

    nlStrNCpy<char>(m_szBaseName, name, 0x20);
    nlToLower<char>(m_szBaseName);
    if (strstr(m_szBaseName, "mario_") != 0)
    {
        glx_SetFog(0);
    }
    else if (strstr(m_szBaseName, "palace") != 0)
    {
        glx_SetFog(1);
    }
    else if (strstr(m_szBaseName, "dk_daisy") != 0)
    {
        glx_SetFog(2);
    }

    CrowdManager::instance.SetStadium(m_szBaseName);

    g_fSkyboxRotationTime = (strstr(m_szBaseName, "super") != nullptr) ? 800.0f : 1420.0f;

    nlSNPrintf(szBasicStadiumName, 0x40, "Environment/%s/%s", m_szBaseName, m_szBaseName);

    char szTemp[0x100];
    nlStrNCat<char>(szTemp, m_szBaseName, "/skybox back", 0x100);
    uSkyBoxHashID = nlStringLowerHash(szTemp);
    nlStrNCat<char>(szTemp, m_szBaseName, "/skybox clouds", 0x100);
    uCloudsHashID = nlStringLowerHash(szTemp);
    nlStrNCat<char>(szTemp, m_szBaseName, "/NetCorner", 0x100);
    uNetHelperHashID = nlStringLowerHash(szTemp);
    nlStrNCat<char>(szTemp, m_szBaseName, "/FieldCorner", 0x100);
    uFieldHelperHashID = nlStringLowerHash(szTemp);
    nlStrNCat<char>(szTemp, m_szBaseName, "/PenaltyCorner", 0x100);
    uPenaltyHelperHashID = nlStringLowerHash(szTemp);
}

/**
 * Offset/Address/Size: 0x2ABC | 0x8019E83C | size: 0xA8
 */
BasicStadium::~BasicStadium()
{
    g_pEventManager->RemoveEventHandler(m_pEventHandler);
    pBasicStadiumInstance = NULL;

    delete mpNPCManager;

    if (m_CameraFlashPositions != NULL)
    {
        delete[] m_CameraFlashPositions;
    }
}

/**
 * Offset/Address/Size: 0x28F0 | 0x8019E670 | size: 0x1CC
 */
bool BasicStadium::DoLoad()
{
    if (!LoadGeometry(szBasicStadiumName, false, false, 0, 0))
        return false;
    if (!LoadGeometry(szBallName, true, false, 0, 0))
        return false;
    if (!LoadGeometry(szPowerupsName, true, false, 0, 0))
        return false;

    if (!LoadObjectData(szBasicStadiumName))
        return false;

    if (!StaticModelExplodable::LoadGeometry())
        return false;

    StaticModelExplodable::CreateExplodablesFromHelperObjects();

    if (!AnimatedModelExplodable::LoadGeometry())
        return false;

    nlToLower<char>(m_szBaseName);

    char szTemp[0x40];

    nlSNPrintf(szTemp, 0x40, "%s/lightramp", m_szBaseName);
    u32 lightRamp = glGetTexture(szTemp);

    nlSNPrintf(szTemp, 0x40, "%s/playerlightramp", m_szBaseName);
    u32 playerLightRamp = glGetTexture(szTemp);

    if (glTextureLoad(lightRamp))
    {
        m_LightRampTexA = lightRamp; // at +0x124
        m_LightRampTexB = lightRamp; // at +0x128
    }

    if (glTextureLoad(playerLightRamp))
    {
        m_PlayerLightRampTex = playerLightRamp; // at +0x12C
    }

    m_GlobalLightRampSTSTex = glGetTexture("global/lightramp_sts"); // as +0x130

    Presentation::Instance().LoadTrophyModel();
    InitializePowerups();

    NetMesh::s_bAnimatedNetMeshEnabled = true;
    g_GoalLightEnabled = false;

    return true;
}

/**
 * Offset/Address/Size: 0x2E8 | 0x8019C068 | size: 0x2608
 */
void BasicStadium::DoInitialize()
{
    FindDrawableObject(nlStringLowerHash("gameplay/ball"));
    m_pSkyboxObject = FindDrawableObject(uSkyBoxHashID);
    m_pCloudsObject = FindDrawableObject(uCloudsHashID);
}

/**
 * Offset/Address/Size: 0x8C | 0x8019BE0C | size: 0x25C
 */
void BasicStadium::Update(float dt)
{
    nlMatrix4 mWorld;
    nlMatrix4 mRot;

    World::Update(dt);

    m_fSkyboxRotationAng += dt * (6.2831855f / g_fSkyboxRotationTime);
    m_fCloudRotationAng += dt * (6.2831855f / g_fCloudRotationTime);

    if (m_fSkyboxRotationAng > 6.2831855f)
    {
        m_fSkyboxRotationAng -= 6.2831855f;
    }

    if (m_fCloudRotationAng > 6.2831855f)
    {
        m_fCloudRotationAng -= 6.2831855f;
    }

    if (m_pSkyboxObject != NULL)
    {
        nlMakeRotationMatrixZ(mRot, m_fSkyboxRotationAng);
        nlMultMatrices(mWorld, mRot, mSkyBoxTM);
        m_pSkyboxObject->m_worldMatrix = mWorld;
    }

    if (m_pCloudsObject != NULL)
    {
        nlMakeRotationMatrixZ(mRot, m_fCloudRotationAng);
        nlMultMatrices(mWorld, mRot, mCloudTM);
        m_pCloudsObject->m_worldMatrix = mWorld;
    }

    if (m_bCameraFlashesEnabled)
    {
        if (m_NumCameraFlashPositions != 0)
        {
            u32 randomValue = nlRandom(m_NumCameraFlashPositions, &nlDefaultSeed);
            m_fTimeUntilNextCameraFlash -= dt;
            if (m_fTimeUntilNextCameraFlash < 0.0f)
            {
                EmitCameraFlash(m_CameraFlashPositions[randomValue]);
                m_fTimeUntilNextCameraFlash = 0.01f + nlRandomf(0.05f, &nlDefaultSeed);
            }
        }
    }
}

/**
 * Offset/Address/Size: 0x48 | 0x8019BDC8 | size: 0x44
 */
void BasicStadium::UpdateInReplay(float dt)
{
    World::UpdateInReplay(dt);
    mpNPCManager->UpdateNPCs(dt);
}

/**
 * Offset/Address/Size: 0x8 | 0x8019BD88 | size: 0x40
 */
void BasicStadium::Render()
{
    World::Render();
    if (!World::sbIsHyperShootToScoreRenderingEnabled)
    {
        mpNPCManager->RenderNPCs();
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x8019BD80 | size: 0x8
 */
BasicStadium* BasicStadium::GetCurrentStadium()
{
    return pBasicStadiumInstance;
}
