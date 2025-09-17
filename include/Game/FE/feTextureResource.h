#ifndef _FETEXTURERESOURCE_H_
#define _FETEXTURERESOURCE_H_

#include "types.h"
#include "Game/FE/feResourceManager.h"

class FETextureResource : public FEResourceHandle
{
public:
    FETextureResource();

    /* 0x14 */ u32 m_glTextureHandle;
};

#endif // _FETEXTURERESOURCE_H_
