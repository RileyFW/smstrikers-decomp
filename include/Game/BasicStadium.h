#ifndef _BASICSTADIUM_H_
#define _BASICSTADIUM_H_

#include "Game/GameInfo.h"
#include "types.h"

#include "Game/World.h"
#include "Game/Sys/eventman.h"
#include "Game/Render/NPCManager.h"

class SomeClass2
{
public:
    /* 0x00 */ s32 unk0;  /* inferred */
    /* 0x04 */ s32 unk4;  /* inferred */
    /* 0x08 */ s32 unk8;  /* inferred */
    /* 0x0C */ s32 unkC;  /* inferred */
    /* 0x10 */ s32 unk10; /* inferred */
};

class BasicStadium : public World
{
public:
    BasicStadium(const char*);
    /* 0x04 */ virtual ~BasicStadium();
    /* 0x08 */ virtual eTerrain GetTerrainType(const nlVector3&) const { return m_TerrainType; };
    /* 0x14 */ virtual void Render();
    /* 0x18 */ virtual void Update(float);
    /* 0x1C */ virtual void UpdateInReplay(float);
    /* 0x2C */ virtual bool DoLoad();
    /* 0x30 */ virtual void DoInitialize();

    static void BasicStadiumEventHandler(Event*, void*);
    static BasicStadium* GetCurrentStadium();

    /* 0x134 */ nlVector3* m_CameraFlashPositions;
    /* 0x138 */ s32 m_NumCameraFlashPositions;
    /* 0x13C */ SomeClass2* m_unk13C; // ??
    /* 0x140 */ u32 m_unk140;         // ??
    /* 0x144 */ float m_fSkyboxRotationAng;
    /* 0x148 */ float m_fCloudRotationAng;
    /* 0x14C */ DrawableObject* m_pSkyboxObject;
    /* 0x150 */ DrawableObject* m_pCloudsObject;
    /* 0x154 */ DrawableObject* m_pPropObject;
    /* 0x158 */ EventHandler* m_pEventHandler;
    /* 0x15C */ bool m_bCameraFlashesEnabled;
    /* 0x160 */ float m_fTimeUntilNextCameraFlash;
    /* 0x164 */ eTerrain m_TerrainType;
    /* 0x168 */ char m_szBaseName[0x20];
    /* 0x188 */ NPCManager* mpNPCManager;
};

#endif // _BASICSTADIUM_H_
