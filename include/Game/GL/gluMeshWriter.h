#ifndef _GLUMESHWRITER_H_
#define _GLUMESHWRITER_H_

#include "Game/GL/GLMeshWriter.h"

#include "NL/nlMath.h"

class GLMeshWriter : public GLMeshWriterCore
{
public:
    GLMeshWriter()
        : GLMeshWriterCore() { };
    virtual ~GLMeshWriter() { };

    virtual bool End();
    virtual void Normal(const nlVector3&);
    virtual void Texcoord(const nlVector2&);
    void Texcoord(short, short);

    /* 0x04 */ glModel* pModel;
    /* 0x08 */ glModelStream stream[15];
    /* 0x64 */ int currentIndex;
    /* 0x68 */ int maximumVerts;
    /* 0x6C */ int elementCount;
};

#endif // _GLUMESHWRITER_H_
