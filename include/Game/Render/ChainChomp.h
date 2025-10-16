#ifndef _CHAINCHOMP_H_
#define _CHAINCHOMP_H_

#include "Game/SHierarchy.h"
#include "Game/SAnim.h"
#include "Game/Physics/PhysicsNPC.h"
#include "Game/Team.h"
#include "Game/AI/Fielder.h"
#include "Game/PoseAccumulator.h"
#include "Game/World/worldanim.h"

void UpdateChainEmitter(EmissionController&);
// void 0x8028D304..0x8028D308 | size: 0x4;

class ChainChomp
{
public:
    void GetSkinAnimatedNPC_Type() const;
    ChainChomp(cSHierarchy&, int, PhysicsNPC&, cInventory<cSAnim>*);
    ~ChainChomp();
    void Update(float);
    void CollisionCallback(PhysicsObject*, PhysicsObject*, const nlVector3&);
    void FindTarget(cTeam*);
    void Fall(cFielder*, cFielder*);
    void Hide(bool);
    void IsHidden() const;
    void Move(float);
    void DrawShadow(const cPoseAccumulator&, const nlMatrix4&);
};

#endif // _CHAINCHOMP_H_
