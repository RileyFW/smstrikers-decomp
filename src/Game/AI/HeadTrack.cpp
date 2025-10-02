#include "Game/AI/HeadTrack.h"

#include "math.h"

f32 CANT_COLLIDE = *(f32*)__float_max;

/**
 * Offset/Address/Size: 0x5B0 | 0x800573B4 | size: 0x70
 */
cHeadTrack::cHeadTrack()
{
    m_m4HeadMatrix.SetIdentity();
    nlVec3Set(m_v3OOI, 0.0f, 0.0f, 0.0f);
    m_bTrackOOI = true;
    m_fHeadSpin = 0.0f;
    m_fHeadTilt = 0.0f;
    m_fDesiredHeadSpin = 0.0f;
    m_fDesiredHeadTilt = 0.0f;
    m_fHeadSpinSeekVel = 0.0f;
    m_fHeadTiltSeekVel = 0.0f;
}

/**
 * Offset/Address/Size: 0x160 | 0x80056F64 | size: 0x450
 */
void cHeadTrack::Update(const nlMatrix4& m4HeadMatrix, const nlMatrix4& m4ConstraintMatrix, float fDeltaT, unsigned short aOOIConstraint, int nHeadSpinMax, int nHeadTiltMax, float fSmoothTime)
{
    nlMatrix4 m4Constrain;                   // r1+0x54
    nlMatrix4 m4WorldSpaceToConstraintSpace; // r1+0x14
    nlVector3 v3OOIConstraintSpace;          // r1+0x8
    int nHeadSpin;                           // r19
    int nHeadTilt;                           // r6
    int nAmountOfDeadZoneBehindHeadtrack;    // r5

    s32 halfTilt;
    s32 tmpSpin16;

    if (m_bTrackOOI)
    {
        m4Constrain = m4ConstraintMatrix;
        m4Constrain.f.m41 = m4HeadMatrix.f.m41;
        m4Constrain.f.m42 = m4HeadMatrix.f.m42;
        m4Constrain.f.m43 = m4HeadMatrix.f.m43;
        m4Constrain.f.m44 = 1.0f;

        nlInvertRotTransMatrix(m4WorldSpaceToConstraintSpace, m4Constrain);
        nlMultPosVectorMatrix(v3OOIConstraintSpace, m_v3OOI, m4WorldSpaceToConstraintSpace);

        float xx = v3OOIConstraintSpace.f.x * v3OOIConstraintSpace.f.x;
        float yy = v3OOIConstraintSpace.f.y * v3OOIConstraintSpace.f.y;
        float zz = v3OOIConstraintSpace.f.z * v3OOIConstraintSpace.f.z;

        float len = nlRecipSqrt(xx + yy + zz, true);

        nlVec3Set(v3OOIConstraintSpace, len * v3OOIConstraintSpace.f.x, len * v3OOIConstraintSpace.f.y, len * v3OOIConstraintSpace.f.z);
        // v3OOIConstraintSpace.f.z = len * v3OOIConstraintSpace.f.z;
        // v3OOIConstraintSpace.f.x = len * v3OOIConstraintSpace.f.x;
        // v3OOIConstraintSpace.f.y = len * v3OOIConstraintSpace.f.y;

        s32 desiredSpin16 = (s32)(10430.378f * nlATan2f(v3OOIConstraintSpace.f.z, v3OOIConstraintSpace.f.x));
        s32 desiredTilt16 = 0x4000 - (s32)nlACos(-v3OOIConstraintSpace.f.x);
        int s = desiredSpin16 >> 31;
        int absSpin16 = ((desiredSpin16 ^ s) - s);

        if ((absSpin16 < (int)(unsigned int)aOOIConstraint) || (m_v3OOI.f.z > 1.5f))
        {
            int softenStart = (((int)(unsigned int)aOOIConstraint - nHeadSpinMax) * 3) / 4;

            tmpSpin16 = desiredSpin16;              // var_r31
            int t2 = tmpSpin16 >> 31;               // temp_r3_2
            halfTilt = 0.5f * (float)desiredTilt16; // var_r30

            int absSpin16_b = (tmpSpin16 ^ t2) - t2;
            if (absSpin16_b >= nHeadSpinMax)
            {
                if (tmpSpin16 > 0)
                {
                    if (m_fDesiredHeadSpin < 0.0f)
                    {
                        if (tmpSpin16 > (nHeadSpinMax + softenStart))
                        {
                            tmpSpin16 = -nHeadSpinMax;
                        }
                        else
                        {
                            tmpSpin16 = nHeadSpinMax;
                        }
                    }
                    else
                    {
                        tmpSpin16 = nHeadSpinMax;
                    }
                }
                else if (m_fDesiredHeadSpin > 0.0f)
                {
                    if (tmpSpin16 < -(nHeadSpinMax + softenStart))
                    {
                        tmpSpin16 = nHeadSpinMax;
                    }
                    else
                    {
                        tmpSpin16 = -nHeadSpinMax;
                    }
                }
                else
                {
                    tmpSpin16 = -nHeadSpinMax;
                }
            }
        }
        else
        {
            tmpSpin16 = 0;
            halfTilt = 0;
        }
        if (halfTilt > nHeadTiltMax)
        {
            halfTilt = nHeadTiltMax;
        }

        if (m4HeadMatrix.f.m11 != m4ConstraintMatrix.f.m11)
        {
            float temp_f27 = m4HeadMatrix.f.m22;
            float temp_f28 = m4HeadMatrix.f.m21;
            float temp_f29 = nlATan2f(m4Constrain.f.m21, m4Constrain.f.m21);
            tmpSpin16 += (10430.378f * temp_f29) - (10430.378f * nlATan2f(temp_f27, temp_f28));
        }
        m_fDesiredHeadSpin = tmpSpin16;
        m_fDesiredHeadTilt = halfTilt;
    }
    else
    {
        m_fDesiredHeadSpin = 0.0f;
        m_fDesiredHeadTilt = 0.0f;
    }

    float temp_f8 = 2.0f / fSmoothTime;
    float temp_f7 = m_fHeadSpinSeekVel;
    float temp_f6 = temp_f8 * fDeltaT;
    float temp_f5 = m_fHeadSpin - m_fDesiredHeadSpin;
    float temp_f2_2 = fDeltaT * ((temp_f8 * temp_f5) + temp_f7);
    float temp_f3_2 = 1.0f / ((temp_f6 * (0.235f * temp_f6 * temp_f6)) + ((0.48f * temp_f6 * temp_f6) + (1.0f + temp_f6)));
    m_fHeadSpinSeekVel = temp_f3_2 * -((temp_f8 * temp_f2_2) - temp_f7);
    m_fHeadSpin = (temp_f3_2 * (temp_f5 + temp_f2_2)) + m_fDesiredHeadSpin;
    float temp_f4 = m_fHeadTiltSeekVel;
    float temp_f2_3 = m_fHeadTilt - m_fDesiredHeadTilt;
    float temp_f1_3 = fDeltaT * ((temp_f8 * temp_f2_3) + temp_f4);
    m_fHeadTiltSeekVel = temp_f3_2 * -((temp_f8 * temp_f1_3) - temp_f4);
    m_fHeadTilt = (temp_f3_2 * (temp_f2_3 + temp_f1_3)) + m_fDesiredHeadTilt;
}

inline float AngUnitsToRad_fromUnsignedShort(unsigned short sUnits)
{
    return (float)sUnits * 0.0000958738f;
}

/**
 * Offset/Address/Size: 0x0 | 0x80056E04 | size: 0x160
 */
void CalcHeadTrackMatrix(unsigned short spin, unsigned short tilt, cPoseAccumulator* cPoseAccumulator, int headNodeIndex)
{
    nlMatrix4 m4Intermediate;
    nlMatrix4 m4RotMatrix;
    nlMatrix4 m4NewHeadMatrix;

    const class nlMatrix4& m4AnimatedHeadMatrix = cPoseAccumulator->GetNodeMatrix(headNodeIndex);

    nlMakeRotationMatrixX(m4RotMatrix, AngUnitsToRad_fromUnsignedShort(spin));
    nlMultMatrices(m4Intermediate, m4RotMatrix, m4AnimatedHeadMatrix);
    nlMakeRotationMatrixZ(m4RotMatrix, AngUnitsToRad_fromUnsignedShort(tilt));
    nlMultMatrices(m4NewHeadMatrix, m4RotMatrix, m4Intermediate);

    cPoseAccumulator->m_NodeMatrices.mData[headNodeIndex] = m4NewHeadMatrix;
}
