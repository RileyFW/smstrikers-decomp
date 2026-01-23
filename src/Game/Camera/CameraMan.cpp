#include "Game/Camera/CameraMan.h"

#include "NL/nlDLRing.h"
#include "NL/nlString.h"

#include "Game/Sys/eventman.h"

#include "Game/Camera/animcam.h"
#include "Game/Camera/rumblefilter.h"

#include "math.h"

f32 CANT_COLLIDE = *(f32*)__float_max;

nlMatrix4 cCameraManager::m_matView;
nlVector3 cCameraManager::m_cameraPosition;
nlMatrix4 cCameraManager::m_matPrevView;
eCameraTransition cCameraManager::m_transition;
void (*cCameraManager::m_pCallback)(enum eCameraMessage);

int cCameraManager::m_UpVectorStackSize;

nlVector3 cCameraManager::m_UpVectorStack[2] = { { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } };

cRumbleFilter* pRumbleFilter;

/**
 * Offset/Address/Size: 0x1D04 | 0x801A838C | size: 0x68
 */
void FireCameraRumbleFilter(float fRumbleX, float fRumbleY)
{
    nlDLRingGetStart<cBaseCamera>(cCameraManager::m_cameraStack);
    if (nlDLRingGetStart<cBaseCamera>(cCameraManager::m_cameraStack)->m_pFilter != NULL)
    {
        nlDLRingGetStart<cBaseCamera>(cCameraManager::m_cameraStack)->m_pFilter->Rumble(fRumbleX, fRumbleY);
    }
}

/**
 * Offset/Address/Size: 0x1768 | 0x801A7DF0 | size: 0x59C
 */
void cCameraManager::Startup()
{
}

/**
 * Offset/Address/Size: 0x1730 | 0x801A7DB8 | size: 0x38
 */
void cCameraManager::Shutdown()
{
    nlDeleteDLRing<cBaseCamera>(&cCameraManager::m_cameraStack);
    cCameraManager::m_cameraStack = NULL;
    cAnimCamera::FreeCameraAnimations();
    delete pRumbleFilter;
}

/**
 * Offset/Address/Size: 0x10CC | 0x801A7754 | size: 0x664
 */
void cCameraManager::Update(float)
{
}

/**
 * Offset/Address/Size: 0xD78 | 0x801A7400 | size: 0x354
 */
void cCameraManager::UpdateGameCameraType()
{
}

/**
 * Offset/Address/Size: 0xD50 | 0x801A73D8 | size: 0x28
 */
bool cCameraManager::HasCamera(cBaseCamera* pCamera)
{
    return nlDLRingValidateContainsElement<cBaseCamera>(cCameraManager::m_cameraStack, pCamera);
}

/**
 * Offset/Address/Size: 0xC58 | 0x801A72E0 | size: 0xF8
 */
void cCameraManager::PushCamera(cBaseCamera* pCamera)
{
    if (cCameraManager::m_transition != eCT_NONE)
    {
        nlPrintf("Camera Transition In Progress\n");
        if (cCameraManager::m_pCallback != NULL)
        {
            (*cCameraManager::m_pCallback)(eCM_ABORTED_BY_PUSH);
        }
    }

    cCameraManager::m_transition = eCT_NONE;

    if ((nlDLRingGetStart<cBaseCamera>(cCameraManager::m_cameraStack) != NULL)
        && (nlDLRingGetStart<cBaseCamera>(cCameraManager::m_cameraStack)->m_pFilter != 0))
    {
        cRumbleFilter* filter1 = nlDLRingGetStart<cBaseCamera>(cCameraManager::m_cameraStack)->m_pFilter;
        cRumbleFilter* filter2 = nlDLRingGetStart<cBaseCamera>(cCameraManager::m_cameraStack)->m_pFilter;

        nlVector2 diff_pos;
        nlVec2Set(diff_pos, filter2->v2Pos0.f.x - filter1->v2Pos1.f.x, filter2->v2Pos0.f.y - filter1->v2Pos1.f.y);
        if (nlSqrt((diff_pos.f.x * diff_pos.f.x) + (diff_pos.f.y * diff_pos.f.y), 1) > 0.0f)
        {
            g_pEventManager->CreateValidEvent(0x58, 0x14);
        }
    }

    nlDLRingAddStart<cBaseCamera>(&cCameraManager::m_cameraStack, pCamera);
}

/**
 * Offset/Address/Size: 0xBA8 | 0x801A7230 | size: 0xB0
 */
void cCameraManager::Remove(const cBaseCamera& camera)
{
    bool actuallyRemoved = true;
    while (actuallyRemoved)
    {
        actuallyRemoved = nlDLRingRemoveSafely<cBaseCamera>(&cCameraManager::m_cameraStack, &camera);
        if (actuallyRemoved
            && (nlDLRingGetStart<cBaseCamera>(cCameraManager::m_cameraStack) != NULL)
            && (nlDLRingGetStart<cBaseCamera>(cCameraManager::m_cameraStack)->m_pFilter != 0))
        {
            cRumbleFilter* pFilter = nlDLRingGetStart<cBaseCamera>(cCameraManager::m_cameraStack)->m_pFilter;
            pFilter->Reset();
            nlDLRingGetStart<cBaseCamera>(cCameraManager::m_cameraStack)->Reactivate();
        }
    }
}

/**
 * Offset/Address/Size: 0xA94 | 0x801A711C | size: 0x114
 */
void cCameraManager::Remove(eCameraType type, bool bDeleteAfterRemoving)
{
    bool actuallyRemoved;
    cBaseCamera* pCamera = cCameraManager::m_cameraStack; // r31

    if (cCameraManager::m_cameraStack != NULL)
    {
        cBaseCamera* pCameraNext; // r30
        do
        {
            pCameraNext = pCamera->m_next;
            if (type == pCamera->GetType())
            {
                actuallyRemoved = true;
                while (actuallyRemoved)
                {
                    actuallyRemoved = nlDLRingRemoveSafely<cBaseCamera>(&cCameraManager::m_cameraStack, pCamera);
                    if (actuallyRemoved
                        && (nlDLRingGetStart<cBaseCamera>(cCameraManager::m_cameraStack) != NULL)
                        && (nlDLRingGetStart<cBaseCamera>(cCameraManager::m_cameraStack)->m_pFilter != 0))
                    {
                        cRumbleFilter* pFilter = nlDLRingGetStart<cBaseCamera>(cCameraManager::m_cameraStack)->m_pFilter;
                        pFilter->Reset();
                        nlDLRingGetStart<cBaseCamera>(cCameraManager::m_cameraStack)->Reactivate();
                    }
                }

                if (bDeleteAfterRemoving)
                {
                    delete pCamera;
                }
            }
            pCamera = pCameraNext;
        } while (pCameraNext != cCameraManager::m_cameraStack);
    }
}

/**
 * Offset/Address/Size: 0x7F8 | 0x801A6E80 | size: 0x29C
 */
void cCameraManager::PushCameraWithTransition(cBaseCamera*, float, eCameraTransition, void (*)(eCameraMessage))
{
}

/**
 * Offset/Address/Size: 0x590 | 0x801A6C18 | size: 0x268
 */
/* static */ void cCameraManager::PopCameraWithTransition(float, eCameraTransition, void (*)(eCameraMessage))
{
}

/**
 * Offset/Address/Size: 0x200 | 0x801A6888 | size: 0x390
 */
bool cCameraManager::IsObjectOccludingField(const DrawableObject* drawable)
{
    return false;
}

/**
 * Offset/Address/Size: 0x1A4 | 0x801A682C | size: 0x5C
 */
float cCameraManager::GetDistanceFromCameraToObject(const nlVector3& objectPosition)
{
    nlVector3 diff;
    nlVec3Set(diff,
        objectPosition.f.x - cCameraManager::m_cameraPosition.f.x,
        objectPosition.f.y - cCameraManager::m_cameraPosition.f.y,
        objectPosition.f.z - cCameraManager::m_cameraPosition.f.z);

    return nlSqrt(((diff.f.x) * (diff.f.x)) + ((diff.f.y) * (diff.f.y)) + ((diff.f.z) * (diff.f.z)), 1);
}

/**
 * Offset/Address/Size: 0x174 | 0x801A67FC | size: 0x30
 */
void cCameraManager::GetViewVector(nlVector3& viewVector)
{
    nlVec3Set(viewVector,
        -cCameraManager::m_matView.f.m13,
        -cCameraManager::m_matView.f.m23,
        -cCameraManager::m_matView.f.m33);
}

/**
 * Offset/Address/Size: 0x150 | 0x801A67D8 | size: 0x24
 */
void cCameraManager::GetUpVector(nlVector3& upVector)
{
    nlVec3Set(upVector,
        cCameraManager::m_matView.f.m12,
        cCameraManager::m_matView.f.m22,
        cCameraManager::m_matView.f.m32);
}

/**
 * Offset/Address/Size: 0x1C | 0x801A66A4 | size: 0x134
 */
void cCameraManager::SetWorldUpVectorTilt(float fXAxisTilt, float fYAxisTilt)
{
    float fSin; // r1+0xC
    float fCos; // r1+0x8

    nlSinCos(&fSin, &fCos, (s16)(65536.0f * fXAxisTilt) / 360);
    nlVec3Set(cCameraManager::m_UpVectorStack[0], 0.0f, fSin, fCos);
    nlSinCos(&fSin, &fCos, (u16)(65536.0f * fYAxisTilt) / 360);

    cCameraManager::m_UpVectorStack[0].f.x = fSin;
    cCameraManager::m_UpVectorStack[0].f.z = cCameraManager::m_UpVectorStack[0].f.z * fCos;

    float xx = cCameraManager::m_UpVectorStack[0].f.x * cCameraManager::m_UpVectorStack[0].f.x;
    float yy = cCameraManager::m_UpVectorStack[0].f.y * cCameraManager::m_UpVectorStack[0].f.y;
    float zz = cCameraManager::m_UpVectorStack[0].f.z * cCameraManager::m_UpVectorStack[0].f.z;
    float temp_f1 = nlRecipSqrt(xx + yy + zz, true);

    nlVec3Set(cCameraManager::m_UpVectorStack[0],
        temp_f1 * cCameraManager::m_UpVectorStack[0].f.x,
        temp_f1 * cCameraManager::m_UpVectorStack[0].f.y,
        temp_f1 * cCameraManager::m_UpVectorStack[0].f.z);
}

/**
 * Offset/Address/Size: 0xC | 0x801A6694 | size: 0x10
 */
void cCameraManager::PushWorldUpVector()
{
    cCameraManager::m_UpVectorStackSize++;
}

/**
 * Offset/Address/Size: 0x0 | 0x801A6688 | size: 0xC
 */
void cCameraManager::PopWorldUpVector()
{
    cCameraManager::m_UpVectorStackSize = 0;
}
