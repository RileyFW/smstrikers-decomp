#ifndef _GLMESHWRITER_H_
#define _GLMESHWRITER_H_

#include "types.h"

#include "NL/nlColour.h"
#include "NL/nlMath.h"
#include "NL/gl/glModel.h"

enum eGLPrimitive
{
    eGLPrimitive_0 = 0,
    eGLPrimitive_1,
    eGLPrimitive_2,
    eGLPrimitive_3,
};

enum eGLStream
{
    GLStream_Position = 0,
    GLStream_Normal = 1,
    GLStream_Colour = 2,
    GLStream_Diffuse = 3,
    GLStream_Detail = 4,
    GLStream_Shadow = 5,
    GLStream_SelfIllum = 6,
    GLStream_Gloss = 7,
    GLStream_BumpLocal = 8,
    GLStream_BasisS = 9,
    GLStream_BasisT = 10,
    GLStream_BasisSxT = 11,
    GLStream_Indices = 12,
    GLStream_Weights = 13,
    GLStream_Position4 = 14,
    GLStream_Num = 15,
    GLStream_Invalid = 16,
};

class GLMeshWriterCore
{
public:
    GLMeshWriterCore();
    /* 0x08*/ ~GLMeshWriterCore();
    /* 0x0C*/ virtual bool Begin(int, eGLPrimitive, int, const eGLStream*, bool);
    /* 0x10*/ virtual bool End();
    /* 0x14*/ virtual void Colour(const nlColour&);
    /* 0x18*/ virtual void ColourPlat(unsigned long);
    /* 0x1C*/ virtual void Normal(const nlVector3&) = 0;
    /* 0x20*/ virtual void Texcoord(const nlVector2&);
    /* 0x24*/ virtual void Vertex(const nlVector3&);
    /* 0x28*/ virtual void Vertex(const nlVector4&);
    void Position(const nlVector3&);
    glModel* GetModel();

    /* 0x04 */ glModel* pModel;
    /* 0x08 */ glModelStream stream[15];
    /* 0x64 */ int currentIndex;
    /* 0x68 */ int maximumVerts;
    /* 0x6C */ int elementCount;
};

#endif // _GLMESHWRITER_H_
