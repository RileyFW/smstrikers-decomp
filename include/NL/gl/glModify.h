#ifndef _GLMODIFY_H_
#define _GLMODIFY_H_

#include "NL/gl/glUserData.h"

enum eGLModifier
{
    eGLModifier_0,
    eGLModifier_1,
    eGLModifier_2,
    eGLModifier_3
};

void gl_ModifyAddMapping(eGLModifier, unsigned long);
void gl_ModifyAddMapping(eGLModifier, unsigned long, unsigned long);
void gl_ModifyClearLastMapping();
void gl_ModifyClearMappings();
glModelPacket* gl_Modify(const glModelPacket*);
u32 gl_ModifyGetNum();

#endif // _GLMODIFY_H_
