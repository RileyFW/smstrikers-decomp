#ifndef _SIDELINEEXPLODABLE_H_
#define _SIDELINEEXPLODABLE_H_

#include "Game/Physics/PhysicsBox.h"
#include "Game/Effects/EmissionController.h"
// #include "Game/Physics/PhysicsObject.h"

class ExplodableCategoryData
{
public:
    void LoadGeometry();
};

class SidelineExplodable
{
public:
    SidelineExplodable();
    ~SidelineExplodable();
    void Initialize(int);
    void Allocate();
    void Update(float);
    void DestroyAllActiveFragments(bool);
    void Explode();
    void FindExplosionAngleRange(unsigned short&, unsigned short&) const;
};

class ExplosionFragment
{
public:
    ExplosionFragment();
    ~ExplosionFragment();
    void GetPosition() const;
    void GetRotation(nlMatrix4*) const;
};

void SidelineExplodableTextureLoadCallback(unsigned long);
void EmissionControllerFinished(EmissionController&, ExplosionFragment*);
void UpdateEmissionControllerPosition(EmissionController&, ExplosionFragment*);
// void nlListCountElements<SidelineExplodableNode>(SidelineExplodableNode*);
// void nlListRemoveElement<SidelineExplodableNode>(SidelineExplodableNode**, SidelineExplodableNode*, SidelineExplodableNode**);
// void nlListRemoveStart<DrawableFragmentHandleNode>(DrawableFragmentHandleNode**, DrawableFragmentHandleNode**);
// void nlListAddEnd<DrawableFragmentHandleNode>(DrawableFragmentHandleNode**, DrawableFragmentHandleNode**, DrawableFragmentHandleNode*);
// void Bind<void, void (*)(EmissionController&, ExplosionFragment*), Placeholder<0>, ExplosionFragment*>(void (*)(EmissionController&, ExplosionFragment*), const Placeholder<0>&, ExplosionFragment* const&);

class SidelineExplosionPhysicsObject : public PhysicsBox
{
public:
    virtual ~SidelineExplosionPhysicsObject();
    virtual int GetObjectType() const { return 0x1C; };
    virtual bool SetContactInfo(dContact* contact, PhysicsObject* other, bool first);
    virtual int Contact(PhysicsObject* other, dContact* contact, int what, PhysicsObject* otherObject);
    virtual void PostUpdate();

    ExplosionFragment* mpExplosionFragment;
}; // total size: 0x30

class SidelineExplodableManager
{
public:
    void CleanUp();
    void Update(float);
    void GetNumExplodables();
    void GetVisibilityOfExplodableModels(bool*, int);
    void SetVisibilityOfUnexplodedModels(bool*, int);
    void TriggerExplosions(const nlVector3&, float);
    void DestroyAllActiveFragments(bool);
    void RemoveSidelineExplodable(SidelineExplodable*);
    static ExplosionFragment* GetFragmentFromHandle(unsigned short);
    void AssociateEffectWithNearbyFloatingCamera(EmissionController*);
    void UnAssociateEffectWithNearbyFloatingCamera(EmissionController*);

    static ExplosionFragment** sFragmentLookupTable;
};

// class PhysicsBox
// {
// public:
//     void GetObjectType() const;
//     ~PhysicsBox();
// };

// class Function1<void, EmissionController&>
// {
// public:
//     void FunctorImpl<BindExp2<void, void (*)(EmissionController&, ExplosionFragment*), Placeholder<0>, ExplosionFragment*> >::operator()(EmissionController&);
//     void FunctorImpl<BindExp2<void, void (*)(EmissionController&, ExplosionFragment*), Placeholder<0>, ExplosionFragment*> >::Clone() const;
//     void FunctorImpl<BindExp2<void, void (*)(EmissionController&, ExplosionFragment*), Placeholder<0>, ExplosionFragment*> >::~FunctorImpl();
// };

// class SlotPool<DrawableFragmentHandleNode>
// {
// public:
//     void ~SlotPool();
// };

// class Vector<ExplosionFragment, DefaultAllocator>
// {
// public:
//     void Vector(int, const char*);
//     void reserve(int);
//     void resize(int);
// };

// class CollisionExplosionFragmentPlayerData
// {
// public:
//     void GetID();
// };

// class SlotPool<SidelineExplodableNode>
// {
// public:
//     void ~SlotPool();
// };

#endif // _SIDELINEEXPLODABLE_H_
