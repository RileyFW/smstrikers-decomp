#ifndef _MATRIXEFFECTCAM_H_
#define _MATRIXEFFECTCAM_H_


class MatrixEffectCam
{
public:
    void GetViewMatrix() const;
    void GetFOV() const;
    void GetType();
    MatrixEffectCam();
    void Reset(const nlVector3&, const nlVector3&, const nlVector3&);
    void Update(float);
    void GetTargetPosition() const;
    void GetCameraPosition() const;
    void SetInitialDistance(float);
    void SetInitialAngle(float);
    void SetInitialHeightAboveTarget(float);
    ~MatrixEffectCam();
};

#endif // _MATRIXEFFECTCAM_H_