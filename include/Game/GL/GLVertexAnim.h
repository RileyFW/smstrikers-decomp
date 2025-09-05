#ifndef _GLVERTEXANIM_H_
#define _GLVERTEXANIM_H_

#include "types.h"

#include "NL/gl/glModel.h"
#include "NL/gl/glUserData.h"

class GLVertexAnim
{
public:
    GLVertexAnim();

    void GetModel(int);
    void Update(float);
    void Reset();

    /* 0x00 */ s32 m_unk_0x00;
    /* 0x04 */ s32 m_unk_0x04;
    /* 0x08 */ u32 m_unk_0x08;
    /* 0x0C */ f32 m_unk_0x0C;
    /* 0x10 */ s32 m_unk_0x10;
    /* 0x14 */ bool m_unk_0x14;
    /* 0x18 */ f32 m_unk_0x18;
    /* 0x1C */ f32 m_unk_0x1C;
    /* 0x20 */ FrameVertexData* m_frames;
    /* 0x24 */ glModel* m_unk_0x24;
};

#endif // _GLVERTEXANIM_H_
