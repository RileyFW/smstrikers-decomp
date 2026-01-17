#ifndef _RENDERSHADOW_H_
#define _RENDERSHADOW_H_

#include "types.h"
#include "NL/nlMath.h"
#include "NL/nlPrint.h"
#include "NL/gl/gl.h"
#include "NL/gl/glConstant.h"

class ProjectedShadowParams;
class nlColour;
class glQuad3;
class glModel;

void RenderProjectedShadow(const ProjectedShadowParams&);
void RenderBlobShadow(const nlVector3&, const nlVector3*, int, const int*, const nlColour*);
void SubdivideAndRender(glQuad3&, eGLView);
void SetCharacterShadowUpdated(int, bool);
void RenderCharacterIntoTexture(const ProjectedShadowParams&);
void ShouldShadowBeUpdated(const ProjectedShadowParams&);
void GetShadowPartitionIndex();
void RenderShadowModel(unsigned long, glModel*, unsigned long);
void ShadowStartup();

#endif // _RENDERSHADOW_H_
