#ifndef _SIDELINEEXPLODABLE_H_
#define _SIDELINEEXPLODABLE_H_

void SidelineExplodableTextureLoadCallback(unsigned long);
void EmissionControllerFinished(EmissionController&, ExplosionFragment*);
void UpdateEmissionControllerPosition(EmissionController&, ExplosionFragment*);
void nlListCountElements<SidelineExplodableNode>(SidelineExplodableNode*);
void nlListRemoveElement<SidelineExplodableNode>(SidelineExplodableNode**, SidelineExplodableNode*, SidelineExplodableNode**);
void nlListRemoveStart<DrawableFragmentHandleNode>(DrawableFragmentHandleNode**, DrawableFragmentHandleNode**);
void nlListAddEnd<DrawableFragmentHandleNode>(DrawableFragmentHandleNode**, DrawableFragmentHandleNode**, DrawableFragmentHandleNode*);
void Bind<void, void (*)(EmissionController&, ExplosionFragment*), Placeholder<0>, ExplosionFragment*>(void (*)(EmissionController&, ExplosionFragment*), const Placeholder<0>&, ExplosionFragment* const&);

class SidelineExplosionPhysicsObject
{
public:
    void GetObjectType() const;
    void Contact(PhysicsObject*, dContact*, int, PhysicsObject*);
    void SetContactInfo(dContact*, PhysicsObject*, bool);
    void PostUpdate();
    ~SidelineExplosionPhysicsObject();
};


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
    void GetFragmentFromHandle(unsigned short);
    void AssociateEffectWithNearbyFloatingCamera(EmissionController*);
    void UnAssociateEffectWithNearbyFloatingCamera(EmissionController*);
};


class PhysicsBox
{
public:
    void GetObjectType() const;
    ~PhysicsBox();
};


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


class Function1<void, EmissionController&>
{
public:
    void FunctorImpl<BindExp2<void, void (*)(EmissionController&, ExplosionFragment*), Placeholder<0>, ExplosionFragment*>>::operator()(EmissionController&);
    void FunctorImpl<BindExp2<void, void (*)(EmissionController&, ExplosionFragment*), Placeholder<0>, ExplosionFragment*>>::Clone() const;
    void FunctorImpl<BindExp2<void, void (*)(EmissionController&, ExplosionFragment*), Placeholder<0>, ExplosionFragment*>>::~FunctorImpl();
};


class SlotPool<DrawableFragmentHandleNode>
{
public:
    void ~SlotPool();
};


class Vector<ExplosionFragment, DefaultAllocator>
{
public:
    void Vector(int, const char*);
    void reserve(int);
    void resize(int);
};


class CollisionExplosionFragmentPlayerData
{
public:
    void GetID();
};


class SlotPool<SidelineExplodableNode>
{
public:
    void ~SlotPool();
};

#endif // _SIDELINEEXPLODABLE_H_