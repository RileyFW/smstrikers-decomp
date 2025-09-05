#ifndef _WORLDMANAGER_H_
#define _WORLDMANAGER_H_

#include "Game/World.h"

class WorldManager
{
public:
    static World* s_World;

    static void DestroyWorld();
    static void LoadWorld(const char*, bool);
    static void UpdateWorld(float dt = 0.f);
    static void RenderWorld();
};

#endif // _WORLDMANAGER_H_
