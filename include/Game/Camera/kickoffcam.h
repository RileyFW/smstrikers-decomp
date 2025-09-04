#ifndef _KICKOFFCAM_H_
#define _KICKOFFCAM_H_


class cKickOffCamera
{
public:
    void GetViewMatrix() const;
    void GetCameraPosition() const;
    void GetTargetPosition() const;
    void GetType();
    cKickOffCamera();
    ~cKickOffCamera();
    void Update(float);
};

#endif // _KICKOFFCAM_H_