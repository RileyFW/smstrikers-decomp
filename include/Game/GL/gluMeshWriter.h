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

    struct glModel* pModel;          // offset 0x4, size 0x4
    struct glModelStream stream[15]; // offset 0x8, size 0x5A
    int currentIndex;                // offset 0x64, size 0x4
    int maximumVerts;                // offset 0x68, size 0x4
    int elementCount;                // offset 0x6C, size 0x4
};

#endif // _GLUMESHWRITER_H_
