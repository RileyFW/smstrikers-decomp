#ifndef _LOADINGMANAGER_H_
#define _LOADINGMANAGER_H_

#include "Game/Loader.h"

class LoadingManager
{
public:
    LoadingManager(unsigned int);
    void GetName();
    void Run(float);
    void QueueLoader(Loader*);
};

#endif // _LOADINGMANAGER_H_
