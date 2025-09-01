#ifndef _EMISSIONMANAGER_H_
#define _EMISSIONMANAGER_H_

#include "NL/gl/gl.h"
#include "Game/Effects/EmissionController.h"

// void fxSetTerrain(unsigned long);
// void fxGetTerrain();
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

class LoadFrame;
class SaveFrame;
class EffectsGroup;
class EffectsLight;

class EmissionManager
{
public:
    void KillOldest(int, bool);
    void Replay(SaveFrame&);
    void Replay(LoadFrame&);
    void AddError(const char*, ...);
    void ResetLingerers();
    static void Destroy(unsigned long, const EffectsGroup*);
    void DestroyAll(bool);
    static bool IsPlaying(unsigned long, const EffectsGroup*);
    static void Kill(unsigned long, const EffectsGroup*);
    void IsStillAlive(EmissionController*);
    static EmissionController* Create(EffectsGroup*, unsigned short);
    void GetContainer();
    void Render();
    void AddEffectsLight(const EffectsLight&);
    void GetLight(int);
    void GetNumLights();
    void Update(float);
    void Shutdown();
    void Startup(eGLView);
    void InstanceForReplayOnly();

    /* 0x00 */ bool m_bRecording;
};

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
