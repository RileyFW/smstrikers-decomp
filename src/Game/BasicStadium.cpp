#pragma pool_data off

#include "Game/BasicStadium.h"

#include "Game/Render/CrowdManager.h"

#include "NL/nlString.h"
#include "NL/nlPrint.h"
#include "NL/gl/glPlat.h"
#include "string.h"

// extern WorldLoader TheWorldLoader;
extern bool g_GoalLightEnabled;
extern float g_fCloudRotationTime;
extern float g_fSkyboxRotationTime;
extern EventManager* g_pEventManager;

char szBasicStadiumName[0x40];

u32 uSkyBoxHashID;
u32 uCloudsHashID;
u32 uNetHelperHashID;
u32 uFieldHelperHashID;
u32 uPenaltyHelperHashID;
BasicStadium* pBasicStadiumInstance;

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
    m_unk13C = NULL;
    m_unk140 = 0;
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

    CrowdManager::instance->SetStadium(m_szBaseName); // SetStadium__12CrowdManagerFPCc(&instance__12CrowdManager, &this->unk168);

    float fTime = 0.0f;
    char* temp_ret = strstr(m_szBaseName, "super");
    if (temp_ret != nullptr)
    {
        fTime = 800.0f;
    }
    else
    {
        fTime = 1420.0f;
    }
    // temp_r6 = &this->unk168;
    g_fSkyboxRotationTime = fTime;

    char sp8[0x100];
    nlSNPrintf(szBasicStadiumName, 0x40, "Environment/%s/%s", m_szBaseName, temp_ret);
    nlStrNCat<char>(sp8, m_szBaseName, "/skybox back", 0x100);
    uSkyBoxHashID = nlStringLowerHash(sp8);
    nlStrNCat<char>(sp8, m_szBaseName, "/skybox clouds", 0x100);
    uCloudsHashID = nlStringLowerHash(sp8);
    nlStrNCat<char>(sp8, m_szBaseName, "/NetCorner", 0x100);
    uNetHelperHashID = nlStringLowerHash(sp8);
    nlStrNCat<char>(sp8, m_szBaseName, "/FieldCorner", 0x100);
    uFieldHelperHashID = nlStringLowerHash(sp8);
    nlStrNCat<char>(sp8, m_szBaseName, "/PenaltyCorner", 0x100);
    uPenaltyHelperHashID = nlStringLowerHash(sp8);
}

/**
 * Offset/Address/Size: 0x2ABC | 0x8019E83C | size: 0xA8
 */
BasicStadium::~BasicStadium()
{
    g_pEventManager->RemoveEventHandler(m_pEventHandler);
    pBasicStadiumInstance = NULL;

    delete mpNPCManager;

    if (m_unk13C != NULL)
    {
        delete[] m_unk13C;
    }
}

/**
 * Offset/Address/Size: 0x28F0 | 0x8019E670 | size: 0x1CC
 */
void BasicStadium::DoLoad()
{
    // TODO:
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
void BasicStadium::Update(float)
{
    // TODO:
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
