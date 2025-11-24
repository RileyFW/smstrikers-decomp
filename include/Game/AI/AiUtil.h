#ifndef _AIUTIL_H_
#define _AIUTIL_H_

#include "NL/nlMath.h"

void GetClosestPointOnSidelines(const nlVector3&);
char* GetPowerupName(int powerup);
void SortToMinOrMaxTotalSum(unsigned int*, float (*)[4], bool);
void GetClosestPointOnLineABFromPointC(const nlVector3&, const nlVector3&, const nlVector3&);
float AIsgn(float fValue);
float NormalizeVal(float fromVal, float fromMin, float fromMax);
float NormalizeVal(float fromVal, const nlVector2& fromExtrema);
void InterpolateRangeClamped(const nlVector2&, const nlVector2&, float);
float InterpolateRangeClamped(float, float, float, float, float);
float Interpolate(float fMin, float fMax, float fPercent);
void RotateVector(nlVector3&, const nlVector3&, nlQuaternion&);
void GetRotationBetweenVectors(nlQuaternion&, const nlVector3&, const nlVector3&);
void RotateVectorZAxis(nlVector3&, const nlVector3&, unsigned short);
void GetWorldPoint(nlVector3&, const nlVector3&, const nlVector3&, unsigned short);
void GetLocalPoint(nlVector3& v3LocalPointOut, const nlVector3& v3WorldPointIn, const nlVector3& v3RefPosition, unsigned short aRefAngle);
void GetClosingSpeed(const nlVector3&, const nlVector3&, const nlVector3&, const nlVector3&);
void GetClosingSpeed2D(const nlVector3&, const nlVector3&, const nlVector3&, const nlVector3&);
void Exp(float);
void TestCollision(float, const nlVector3&, const nlVector3&, float, const nlVector3&, const nlVector3&);
void ClipPositionToSidelines(nlVector3&, float);
void CalcInterceptXY(const nlVector3&, float, float, const nlVector3&, const nlVector3&, int&, float*);
void SeekSpeed(float, float, float, float, float);
unsigned short SeekDirection(unsigned short, unsigned short, float, float, float);
void IsPointInCone(const nlVector3&, const nlVector3&, const nlVector3&, const nlVector3&);
void MakePerpendicularPlane(const nlVector3&, const nlVector3&, nlVector4&, float);
void MakePerpendicularPlane(const nlVector3&, unsigned short, nlVector4&, float);

#endif // _AIUTIL_H_
