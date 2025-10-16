#ifndef _GRAPHICSLOADER_H_
#define _GRAPHICSLOADER_H_

#include "Game/Loader.h"

// void 0x8028D308..0x8028D30C | size: 0x4;

class GraphicsLoader : public Loader
{
public:
    virtual bool StartLoad(LoadingManager*);
};

#endif // _GRAPHICSLOADER_H_
