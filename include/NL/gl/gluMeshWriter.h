#ifndef _GLUMESHWRITER_H_
#define _GLUMESHWRITER_H_

#include "NL/nlMath.h"
#include "Game/GL/GLMeshWriter.h"

class GLMeshWriter : public GLMeshWriterCore
{
public:
    virtual void Texcoord(short, short);
    virtual void Texcoord(const nlVector2&);
    virtual void Normal(const nlVector3&);
    virtual bool End();
};

#endif // _GLUMESHWRITER_H_
