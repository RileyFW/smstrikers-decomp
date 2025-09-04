#ifndef _DEBUGCAM_H_
#define _DEBUGCAM_H_


class cDebugCamera
{
public:
    void GetViewMatrix() const;
    void GetFOV() const;
    void GetCameraPosition() const;
    void GetTargetPosition() const;
    void GetType();
    cDebugCamera();
    ~cDebugCamera();
    void UpdateCameraControls(float);
    void Update(float);
};

#endif // _DEBUGCAM_H_