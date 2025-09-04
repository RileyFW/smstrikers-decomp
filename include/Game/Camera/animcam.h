#ifndef _ANIMCAM_H_
#define _ANIMCAM_H_

void LoadAnimCameraData(nlChunk*, nlChunk*, cCameraData*, bool);
void EnableDofDebug();
void nlDeleteList<cCameraData>(cCameraData**);
void nlListRemoveElement<cCameraData>(cCameraData**, cCameraData*, cCameraData**);
void nlListAddStart<cCameraData>(cCameraData**, cCameraData*, cCameraData**);
void 0x8028D358..0x8028D35C | size: 0x4;

class cAnimCamera
{
public:
    void GetViewMatrix() const;
    void GetFOV() const;
    void GetCameraPosition() const;
    void GetTargetPosition() const;
    void GetType();
    void LoadCameraAnimation(nlChunk*, nlChunk*, const char*, bool);
    void LoadCameraAnimation(const char*, const char*, bool);
    void FreeCameraAnimations();
    cAnimCamera();
    ~cAnimCamera();
    void BuildAnimViewMatrix(nlMatrix4&);
    void UnselectCameraAnimation();
    void SelectCameraAnimation(const char*);
    void CameraAnimationExists(const char*) const;
    void FreeCameraAnimation(const char*);
    void Update(float);
    void ManualUpdate(float);
};

#endif // _ANIMCAM_H_