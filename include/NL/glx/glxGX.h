#ifndef _GLXGX_H_
#define _GLXGX_H_

#include "dolphin/gx/GXEnum.h"
#include "NL/nlColour.h"

bool gxSetCoPlanar(bool);
nlColour gxSetChanAmbColour(int, const nlColour&);
nlColour gxSetChanMatColour(int, const nlColour&);
void gxSetTexCoordGen(int, _GXTexGenType, _GXTexGenSrc, unsigned long);
void gxSetTevAlphaOp(int, _GXTevOp, _GXTevBias, _GXTevScale, bool, _GXTevRegID);
void gxSetTevColourOp(int, _GXTevOp, _GXTevBias, _GXTevScale, bool, _GXTevRegID);
u32 gxSetNumTexGens(unsigned long);
u32 gxSetNumTevStages(unsigned long);
u32 gxSetNumChans(unsigned long);
_GXCullMode gxSetCullMode(_GXCullMode);
void gxSetBlendMode(bool, _GXBlendFactor, _GXBlendFactor, bool);
void gxSetAlphaCompare(_GXCompare, unsigned char);
void gxRestoreZMode();
void gxSaveZMode();
void gxSetZMode(bool, _GXCompare, bool);
bool gxSetZCompLoc(bool);
bool gxSetAlphaUpdate(bool);
bool gxSetColourUpdate(bool);
uint gxSetDither(bool);
uint gxSetTevAlphaIn(int, int, _GXTevAlphaArg);
void gxSetTevAlphaIn(int, _GXTevAlphaArg, _GXTevAlphaArg, _GXTevAlphaArg, _GXTevAlphaArg);
void gxInit();

#endif // _GLXGX_H_
