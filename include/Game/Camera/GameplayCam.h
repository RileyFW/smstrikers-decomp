#ifndef _GAMEPLAYCAM_H_
#define _GAMEPLAYCAM_H_

void 0x8028D364..0x8028D368 | size: 0x4;

class GameplayCamera
{
public:
    void GetFOV() const;
    void GetViewMatrix() const;
    void GetCameraPosition() const;
    void GetTargetPosition() const;
    void GetType();
    GameplayCamera();
    void CalcDynamicZoom();
    void Update(float);
    void Reactivate();
    ~GameplayCamera();
};


class GameplayCameraZoomLevel
{
public:
    void CalcDesiredTarget();
    void Update(float, bool);
};


class KnotTableBlendEntry
{
public:
    KnotTableBlendEntry();
};

#endif // _GAMEPLAYCAM_H_