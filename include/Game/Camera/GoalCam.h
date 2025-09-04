#ifndef _GOALCAM_H_
#define _GOALCAM_H_


class GoalCamera
{
public:
    void GetViewMatrix() const;
    void GetCameraPosition() const;
    void GetTargetPosition() const;
    void GetType();
    GoalCamera();
    ~GoalCamera();
    void Update(float);
};

#endif // _GOALCAM_H_