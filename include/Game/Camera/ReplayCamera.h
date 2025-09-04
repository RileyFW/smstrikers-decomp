#ifndef _REPLAYCAMERA_H_
#define _REPLAYCAMERA_H_


class ReplayCamera
{
public:
    void GetFOV() const;
    void GetCameraPosition() const;
    void GetTargetPosition() const;
    void GetType();
    void UpdateTweakMode();
    ReplayCamera();
    void GetViewMatrix() const;
    void Update(float);
    void ManualUpdate(float);
    void SetSideOfInterest(int);
    void CutTo(ReplayCameraPosition);
    void GetFov(ReplayCameraPosition) const;
    void GetPosition(ReplayCameraPosition, float) const;
};


class BasicString<char, Detail
{
public:
    void TempStringAllocator>::AppendInPlace<Detail::TempStringAllocator>(const BasicString<char, Detail::TempStringAllocator>&);
};

#endif // _REPLAYCAMERA_H_