#ifndef _EMISSIONMANAGER_H_
#define _EMISSIONMANAGER_H_

#include "NL/gl/gl.h"
#include "Game/Effects/EmissionController.h"

void fxSetTerrain(unsigned long);
u32 fxGetTerrain();

class LoadFrame;
class SaveFrame;

#include "Game/Effects/EffectsGroup.h"

class EffectsLight
{
public:
    /* 0x00 */ nlVector3 m_v3Position;
    /* 0x0C */ f32 m_fRadius;
    /* 0x10 */ nlColour m_Colour;
}; // size: 0x14

struct LingerMessage : public efNode
{
    /* 0x008 */ char szMessage[256];
    /* 0x108 */ int nLingers;
    /* 0x10C */ int nParticles;
}; // size: 0x110

class EmissionManager
{
public:
    void KillOldest(int, bool);
    void Replay(SaveFrame&);
    void Replay(LoadFrame&);
    static void AddError(const char*, ...);
    void ResetLingerers();
    static void Destroy(unsigned long, const EffectsGroup*);
    void DestroyAll(bool);
    static bool IsPlaying(unsigned long, const EffectsGroup*);
    static void Kill(unsigned long, const EffectsGroup*);
    bool IsStillAlive(EmissionController*);
    static EmissionController* Create(EffectsGroup*, unsigned short);
    efList* GetContainer();
    static void Render(); // not sure it's static
    void AddEffectsLight(const EffectsLight&);
    void GetLight(int);
    s32 GetNumLights();
    static void Update(float); // not sure it's static
    void Shutdown();
    void Startup(eGLView);

    static EmissionManager& InstanceForReplayOnly();

    /* 0x00 */ bool m_bRecording;
};

// void Replayable<0, LoadFrame, unsigned short>(LoadFrame&, unsigned short&);
// void Replayable<0, LoadFrame, unsigned long>(LoadFrame&, unsigned long&);
// void Replayable<0, LoadFrame, EmissionController>(LoadFrame&, EmissionController&);
// void Replayable<0, SaveFrame, unsigned short>(SaveFrame&, unsigned short&);
// void Replayable<0, SaveFrame, unsigned long>(SaveFrame&, unsigned long&);
// void Replayable<0, SaveFrame, EmissionController>(SaveFrame&, EmissionController&);
// void Replayable<0, LoadFrame, char>(LoadFrame&, char&);
// void Replayable<0, SaveFrame, char>(SaveFrame&, char&);
// void Replayable<0, LoadFrame, FloatCompressor<-255, 255, 6>>(LoadFrame&, const FloatCompressor<-255, 255, 6>&);
// void Replayable<0, SaveFrame, FloatCompressor<-255, 255, 6>>(SaveFrame&, const FloatCompressor<-255, 255, 6>&);

// class nlAVLTree<unsigned long, LingerMessage*, DefaultKeyCompare<unsigned long>>
// {
// public:
//     void ~nlAVLTree();
// };

// class AVLTreeBase<unsigned long, LingerMessage*, NewAdapter<AVLTreeEntry<unsigned long, LingerMessage*>>, DefaultKeyCompare<unsigned
// long>>
// {
// public:
//     void DeleteValue(AVLTreeEntry<unsigned long, LingerMessage*>*);
//     void DeleteEntry(AVLTreeEntry<unsigned long, LingerMessage*>*);
//     void DeleteValues();
//     void DestroyTree(void (AVLTreeBase<unsigned long, LingerMessage*, NewAdapter<AVLTreeEntry<unsigned long, LingerMessage*>>,
//     DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, LingerMessage*>*)); void PostorderTraversal(AVLTreeEntry<unsigned
//     long, LingerMessage*>*, void (AVLTreeBase<unsigned long, LingerMessage*, NewAdapter<AVLTreeEntry<unsigned long, LingerMessage*>>,
//     DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, LingerMessage*>*)); void CastUp(AVLTreeNode*) const; void
//     ~AVLTreeBase(); void Clear(); void AllocateEntry(void*, void*); void CompareKey(void*, AVLTreeNode*); void CompareNodes(AVLTreeNode*,
//     AVLTreeNode*);
// };

// class NewAdapter<AVLTreeEntry<unsigned long, LingerMessage*>>
// {
// public:
//     void Delete(AVLTreeEntry<unsigned long, LingerMessage*>*);
// };

// class LoadFrame
// {
// public:
//     void Replayable<0, EmissionController>(EmissionController&);
//     void Replayable<0, EmissionController>(EmissionController&, NotReplayablePod);
// };

#endif // _EMISSIONMANAGER_H_
