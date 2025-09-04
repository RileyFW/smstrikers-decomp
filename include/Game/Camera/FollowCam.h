#ifndef _FOLLOWCAM_H_
#define _FOLLOWCAM_H_


class cFollowCamera
{
public:
    void GetCameraPosition() const;
    void GetTargetPosition() const;
    void GetViewMatrix() const;
    void GetType();
    void cFollowCamera(cFollowCamera::FollowTarget);
    void Update(float);
};

#endif // _FOLLOWCAM_H_