#ifndef _SHOOTTOSCORECAM_H_
#define _SHOOTTOSCORECAM_H_


class cShootToScoreCamera
{
public:
    void GetViewMatrix() const;
    void GetType();
    void GetTargetPosition() const;
    void GetCameraPosition() const;
    cShootToScoreCamera();
    ~cShootToScoreCamera();
    void Update(float);
};

#endif // _SHOOTTOSCORECAM_H_