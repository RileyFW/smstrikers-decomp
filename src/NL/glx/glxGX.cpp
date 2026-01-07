#include "NL/glx/glxGX.h"
#include "dolphin/GX.h"

GXTevAlphaArg gx_alphaArg[2][32];

bool gx_dither;
bool gx_colourupdate;
bool gx_alphaupdate;
bool gx_zcomploc;
bool gx_ztest;
GXCompare gx_zfunc;
bool gx_zwrite;

bool save_ztest = gx_ztest;
GXCompare save_zfunc = gx_zfunc;
bool save_zwrite = gx_zwrite;

u8 /*GXCompare*/ gx_alphafunc;
u8 gx_alpharef;
u8 /*GXBlendMode*/ gx_blend;
u8 /*GXLogicOp*/ gx_blendSubtract;
GXBlendFactor gx_srcfactor;
GXBlendFactor gx_dstfactor;
GXCullMode gx_cullmode;
u32 gx_currentmtx;
u32 gx_numChans;
u32 gx_numTEV;
u32 gx_numGens;
u32 gx_matColour[2];
u32 gx_ambColour[2];
bool gx_coplanar = false;

/**
 * Offset/Address/Size: 0x0 | 0x801C14E8 | size: 0x48
 */
bool gxSetCoPlanar(bool coplanar)
{
    bool prev = gx_coplanar;
    if ((u8)gx_coplanar != coplanar)
    {
        gx_coplanar = coplanar;
        GXSetCoPlanar(coplanar);
    }
    return prev;
}

/**
 * Offset/Address/Size: 0x48 | 0x801C1530 | size: 0x54
 */
nlColour gxSetChanAmbColour(int chan, const nlColour& color)
{
    u32 local_14 = *(u32*)&color;
    u32 local_10 = *(u32*)((u8*)&gx_ambColour + chan * 4);
    if (local_10 != local_14)
    {
        *(int*)((u8*)&gx_ambColour + chan * 4) = *(u32*)&color;
        GXSetChanAmbColor(*(GXChannelID*)&chan, *(GXColor*)&color);
    }
    return *(nlColour*)&local_10;
}

/**
 * Offset/Address/Size: 0x9C | 0x801C1584 | size: 0x54
 */
nlColour gxSetChanMatColour(int chan, const nlColour& color)
{
    u32 local_14 = *(u32*)&color;
    u32 local_10 = *(u32*)((u8*)&gx_matColour + chan * 4);
    if (local_10 != local_14)
    {
        *(int*)((u8*)&gx_matColour + chan * 4) = *(u32*)&color;
        GXSetChanMatColor(*(GXChannelID*)&chan, *(GXColor*)&color);
    }
    return *(nlColour*)&local_10;
}

/**
 * Offset/Address/Size: 0xF0 | 0x801C15D8 | size: 0x28
 */
// void GXSetTexCoordGen2(GXTexCoordID dst_coord, GXTexGenType func, GXTexGenSrc src_param, u32 mtx, GXBool normalize, u32 pt_texmtx)

void gxSetTexCoordGen(int dst_coord, _GXTexGenType func, _GXTexGenSrc src_param, unsigned long arg)
{
    GXSetTexCoordGen2(*(GXTexCoordID*)&dst_coord, func, src_param, arg, false, 125);
}

/**
 * Offset/Address/Size: 0x118 | 0x801C1600 | size: 0x30
 */
//  void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg)
void gxSetTevAlphaOp(int stage, _GXTevOp op, _GXTevBias bias, _GXTevScale scale, bool clamp, _GXTevRegID out_reg)
{
    GXSetTevAlphaOp(*(GXTevStageID*)&stage, op, bias, scale, (u32)(-clamp | clamp) >> 0x1FU, out_reg);
}

/**
 * Offset/Address/Size: 0x148 | 0x801C1630 | size: 0x30
 */
void gxSetTevColourOp(int stage, _GXTevOp op, _GXTevBias bias, _GXTevScale scale, bool clamp, _GXTevRegID out_reg)
{
    GXSetTevColorOp(*(GXTevStageID*)&stage, op, bias, scale, (u32)(-clamp | clamp) >> 0x1FU, out_reg);
}

/**
 * Offset/Address/Size: 0x178 | 0x801C1660 | size: 0x50
 */
u32 gxSetNumTexGens(unsigned long numGens)
{
    u32 temp_r31 = gx_numGens;
    if (numGens != gx_numGens)
    {
        GXSetNumTexGens(numGens);
        gx_numGens = numGens;
    }
    return temp_r31;
}

/**
 * Offset/Address/Size: 0x1C8 | 0x801C16B0 | size: 0x50
 */
u32 gxSetNumTevStages(unsigned long numTEV)
{
    u32 temp_r31 = gx_numTEV;
    if (numTEV != gx_numTEV)
    {
        GXSetNumTevStages(numTEV);
        gx_numTEV = numTEV;
    }
    return temp_r31;
}

/**
 * Offset/Address/Size: 0x218 | 0x801C1700 | size: 0x50
 */
u32 gxSetNumChans(unsigned long numChans)
{
    u32 temp_r31 = gx_numChans;
    if (numChans != gx_numChans)
    {
        GXSetNumChans(numChans);
        gx_numChans = numChans;
    }
    return temp_r31;
}

/**
 * Offset/Address/Size: 0x268 | 0x801C1750 | size: 0x48
 */
_GXCullMode gxSetCullMode(_GXCullMode mode)
{
    _GXCullMode temp_r31 = gx_cullmode;
    if (mode != temp_r31)
    {
        GXSetCullMode(mode);
        gx_cullmode = mode;
    }
    return temp_r31;
}

/**
 * Offset/Address/Size: 0x2B0 | 0x801C1798 | size: 0xDC
 */
void gxSetBlendMode(bool arg0, _GXBlendFactor arg1, _GXBlendFactor arg2, bool arg3)
{
    if ((arg0 != (u8)gx_blend) || (arg1 != (s32)gx_srcfactor) || (arg2 != (s32)gx_dstfactor) || (arg3 != (u8)gx_blendSubtract))
    {
        if ((arg3 != 0) && (arg0 != 0))
        {
            GXSetBlendMode(GX_BM_LOGIC, arg1, arg2, GX_LO_CLEAR);
        }
        else
        {
            GXSetBlendMode((GXBlendMode)((u32)(-(s32)arg0 | arg0) >> 0x1FU), arg1, arg2, GX_LO_CLEAR);
        }
        gx_blend = (GXBlendMode)arg0;
        gx_blendSubtract = (GXLogicOp)arg3;
        gx_srcfactor = arg1;
        gx_dstfactor = arg2;
    }
}

/**
 * Offset/Address/Size: 0x38C | 0x801C1874 | size: 0x70
 */
void gxSetAlphaCompare(_GXCompare arg0, u8 arg1)
{
    if (((s32)gx_alphafunc != arg0) || ((u8)gx_alpharef != arg1))
    {
        GXSetAlphaCompare(arg0, arg1, GX_AOP_AND, arg0, arg1);
        gx_alphafunc = arg0;
        gx_alpharef = arg1;
    }
}

/**
 * Offset/Address/Size: 0x3FC | 0x801C18E4 | size: 0x40
 */
void gxRestoreZMode()
{
    gx_ztest = save_ztest;
    gx_zfunc = save_zfunc;
    gx_zwrite = save_zwrite;
    GXSetZMode(save_ztest, save_zfunc, save_zwrite);
}

/**
 * Offset/Address/Size: 0x43C | 0x801C1924 | size: 0x1C
 */
void gxSaveZMode()
{
    save_ztest = gx_ztest;
    save_zfunc = gx_zfunc;
    save_zwrite = gx_zwrite;
}

/**
 * Offset/Address/Size: 0x458 | 0x801C1940 | size: 0x88
 */
void gxSetZMode(bool arg0, _GXCompare arg1, bool arg2)
{
    if ((arg0 != (u8)gx_ztest) || (arg1 != (s32)gx_zfunc) || (arg2 != (u8)gx_zwrite))
    {
        GXSetZMode(arg0, arg1, arg2);
        gx_ztest = arg0;
        gx_zfunc = arg1;
        gx_zwrite = arg2;
    }
}

/**
 * Offset/Address/Size: 0x4E0 | 0x801C19C8 | size: 0x5C
 */
bool gxSetZCompLoc(bool arg0)
{
    bool temp_r31 = gx_zcomploc;
    if (arg0 != (u8)gx_zcomploc)
    {
        GXSetZCompLoc((u32)(-(s32)arg0 | arg0) >> 0x1FU);
        gx_zcomploc = arg0;
    }
    return temp_r31;
}

/**
 * Offset/Address/Size: 0x53C | 0x801C1A24 | size: 0x5C
 */
bool gxSetAlphaUpdate(bool arg0)
{
    u8 temp_r31;

    temp_r31 = gx_alphaupdate;
    if (arg0 != (u8)gx_alphaupdate)
    {
        GXSetAlphaUpdate((u32)(-(s32)arg0 | arg0) >> 0x1FU);
        gx_alphaupdate = arg0;
    }
    return temp_r31;
}

/**
 * Offset/Address/Size: 0x598 | 0x801C1A80 | size: 0x5C
 */
bool gxSetColourUpdate(bool arg0)
{
    u8 temp_r31;

    temp_r31 = gx_colourupdate;
    if (arg0 != (u8)gx_colourupdate)
    {
        GXSetColorUpdate((u32)(-(s32)arg0 | arg0) >> 0x1FU);
        gx_colourupdate = arg0;
    }
    return temp_r31;
}

/**
 * Offset/Address/Size: 0x5F4 | 0x801C1ADC | size: 0x5C
 */
uint gxSetDither(bool dither)
{
    u8 prev_dither = (uint)gx_dither;
    if (dither != gx_dither)
    {
        GXSetDither((-(uint)dither | dither) >> 0x1f);
        gx_dither = dither;
    }
    return prev_dither;
}

/**
 * Offset/Address/Size: 0x650 | 0x801C1B38 | size: 0x58
 */
uint gxSetTevAlphaIn(int stage, int arg1, _GXTevAlphaArg arg2)
{
    s32 temp_r0;
    s32 temp_r31;
    u8* temp_r7;

    temp_r0 = arg1 * 4;
    temp_r7 = ((u8*)&gx_alphaArg) + (stage * 0x10);
    temp_r31 = *(GXTevAlphaArg*)(temp_r7 + temp_r0);
    *(GXTevAlphaArg*)(temp_r7 + temp_r0) = arg2;
    GXSetTevAlphaIn(*(GXTevStageID*)&stage, ((GXTevAlphaArg*)temp_r7)[0], ((GXTevAlphaArg*)temp_r7)[1], ((GXTevAlphaArg*)temp_r7)[2], ((GXTevAlphaArg*)temp_r7)[3]);
    return (uint)temp_r31;
}

/**
 * Offset/Address/Size: 0x6A8 | 0x801C1B90 | size: 0x5C
 */
void gxSetTevAlphaIn(int arg0, _GXTevAlphaArg arg1, _GXTevAlphaArg arg2, _GXTevAlphaArg arg3, _GXTevAlphaArg arg4)
{
    GXSetTevAlphaIn(*(GXTevStageID*)&arg0, arg1, arg2, arg3, arg4);
    s32 temp_r0 = arg0 * 0x10;

    GXTevAlphaArg* alphaArg = (GXTevAlphaArg*)(((u8*)&gx_alphaArg) + temp_r0);
    alphaArg[0] = arg1;
    alphaArg[1] = arg2;
    alphaArg[2] = arg3;
    alphaArg[3] = arg4;
}

/**
 * Offset/Address/Size: 0x704 | 0x801C1BEC | size: 0x270
 */
void gxInit()
{
    for (int i = 0; i < 2; i++)
    {
        gx_alphaArg[i][0] = GX_CA_A0;
        gx_alphaArg[i][1] = GX_CA_A0;
        gx_alphaArg[i][2] = GX_CA_A0;
        gx_alphaArg[i][3] = GX_CA_A0;
        gx_alphaArg[i][4] = GX_CA_A0;
        gx_alphaArg[i][5] = GX_CA_A0;
        gx_alphaArg[i][6] = GX_CA_A0;
        gx_alphaArg[i][7] = GX_CA_A0;
        gx_alphaArg[i][8] = GX_CA_A0;
        gx_alphaArg[i][9] = GX_CA_A0;
        gx_alphaArg[i][10] = GX_CA_A0;
        gx_alphaArg[i][11] = GX_CA_A0;
        gx_alphaArg[i][12] = GX_CA_A0;
        gx_alphaArg[i][13] = GX_CA_A0;
        gx_alphaArg[i][14] = GX_CA_A0;
        gx_alphaArg[i][15] = GX_CA_A0;
        gx_alphaArg[i][16] = GX_CA_A0;
        gx_alphaArg[i][17] = GX_CA_A0;
        gx_alphaArg[i][18] = GX_CA_A0;
        gx_alphaArg[i][19] = GX_CA_A0;
        gx_alphaArg[i][20] = GX_CA_A0;
        gx_alphaArg[i][21] = GX_CA_A0;
        gx_alphaArg[i][22] = GX_CA_A0;
        gx_alphaArg[i][23] = GX_CA_A0;
        gx_alphaArg[i][24] = GX_CA_A0;
        gx_alphaArg[i][25] = GX_CA_A0;
        gx_alphaArg[i][26] = GX_CA_A0;
        gx_alphaArg[i][27] = GX_CA_A0;
        gx_alphaArg[i][28] = GX_CA_A0;
        gx_alphaArg[i][29] = GX_CA_A0;
        gx_alphaArg[i][30] = GX_CA_A0;
        gx_alphaArg[i][31] = GX_CA_A0;
    }

    GXSetDither(1);
    gx_dither = 1;
    GXSetColorUpdate(1);
    gx_colourupdate = 1;
    GXSetAlphaUpdate(1);
    gx_alphaupdate = 1;
    GXSetZCompLoc(1);
    gx_zcomploc = 1;

    GXSetZMode(true, GX_LEQUAL, true);
    gx_ztest = true;
    gx_zfunc = GX_LEQUAL;
    gx_zwrite = true;

    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    gx_alphafunc = GX_ALWAYS;
    gx_alpharef = 0;

    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
    gx_blend = GX_BM_NONE;
    gx_blendSubtract = GX_LO_CLEAR;
    gx_srcfactor = GX_BL_ONE;
    gx_dstfactor = GX_BL_ZERO;

    GXSetCullMode(GX_CULL_FRONT);
    gx_cullmode = GX_CULL_FRONT;

    GXSetCurrentMtx(0);
    gx_currentmtx = 0;

    GXSetNumChans(1);
    gx_numChans = 1;
    GXSetNumTevStages(1);
    gx_numTEV = 1;
    GXSetNumTexGens(0);
    gx_numGens = 0;

    GXColor color;
    *(u32*)&color = 0xffffffff;
    GXSetChanMatColor(GX_COLOR0, color);
    GXSetChanMatColor(GX_COLOR1, color);
    *(u32*)&color = 0x000000ff;
    GXSetChanAmbColor(GX_COLOR0, color);
    GXSetChanAmbColor(GX_COLOR1, color);
    gx_matColour[0] = 0xffffffff;
    gx_ambColour[0] = 0xff;
    gx_matColour[1] = 0xffffffff;
    gx_ambColour[1] = 0xff;

    GXSetCoPlanar(false);
    gx_coplanar = 0;
}
