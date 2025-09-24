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
    eGLStream_0,
    eGLStream_1,
    eGLStream_2,
    eGLStream_3,
};

class GLMeshWriterCore
{
public:
    GLMeshWriterCore() { };
    ~GLMeshWriterCore() { };
    virtual bool Begin(int, eGLPrimitive, int, const eGLStream*, bool);
    virtual bool End();
    virtual void Colour(const nlColour&);
    virtual void ColourPlat(unsigned long);
    virtual void Normal(const nlVector3&) = 0;
    virtual void Texcoord(const nlVector2&);
    virtual void Vertex(const nlVector3&);
    virtual void Vertex(const nlVector4&);
    void Position(const nlVector3&);
    glModel* GetModel();

    /* 0x04 */ glModel* pModel;
    /* 0x08 */ glModelStream stream[15];
    /* 0x64 */ int currentIndex;
    /* 0x68 */ int maximumVerts;
    /* 0x6C */ int elementCount;
};

#endif // _GLMESHWRITER_H_
