#ifndef _CHAINCHOMP_H_
#define _CHAINCHOMP_H_

#include "Game/Render/SkinAnimatedMovableNPC.h"

#include "Game/SHierarchy.h"
#include "Game/SAnim.h"
#include "Game/Physics/PhysicsNPC.h"
#include "Game/Team.h"
#include "Game/AI/Fielder.h"
#include "Game/PoseAccumulator.h"
#include "Game/World/worldanim.h"

void UpdateChainEmitter(EmissionController&);
// void 0x8028D304..0x8028D308 | size: 0x4;

class ChainChomp : public SkinAnimatedMovableNPC
{
public:
    ChainChomp(cSHierarchy&, int, PhysicsNPC&, cInventory<cSAnim>*);
    virtual ~ChainChomp();
    virtual SkinAnimatedNPC_Type GetSkinAnimatedNPC_Type() const { return SkinAnimatedNPC_CHAIN_CHOMP; };
    virtual void Update(float);
    void CollisionCallback(PhysicsObject*, PhysicsObject*, const nlVector3&);
    void FindTarget(cTeam*);
    void Fall(cFielder*, cFielder*);
    void Hide(bool);
    void IsHidden() const;
    void Move(float);
    void DrawShadow(const cPoseAccumulator&, const nlMatrix4&);
};

#endif // _CHAINCHOMP_H_
