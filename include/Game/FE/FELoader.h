#ifndef _FELOADER_H_
#define _FELOADER_H_

#include "Game/Loader.h"

class FELoader : public Loader
{
public:
    virtual bool StartLoad(LoadingManager*);
};

#endif // _FELOADER_H_
