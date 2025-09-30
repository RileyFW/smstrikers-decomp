#ifndef _MODELTRANSITION_H_
#define _MODELTRANSITION_H_

void UpdateEffectsFromLeafNodes(cPoseAccumulator&, EmissionController**, cSHierarchy&, int, int);
void ShuffleIntoOutline(Vector<nlVector3, DefaultAllocator>&);
void GetNumLeafNodesInHierarchy(cSHierarchy&, int, int);

class ModeledScreenTransition : public ScreenTransition
{
public:
    ModeledScreenTransition();
    ~ModeledScreenTransition();
    void DoSanityCheck();
    void Update(float);
    void Render(eGLView);
    void RenderOutline() const;
    void IsFinished();
    void Time() const;
    void Reset();
    void Cancel();
    void LoadFromParser(SimpleParser*);
    void GetTransitionLength();
};

// class ScreenTransition
// {
// public:
//     void DoSanityCheck();
//     ~ScreenTransition();
//     void CutTime() const;
// };

// class nlMatrix4
// {
// public:
//     void GetTranslation() const;
// };

// class nlAVLTree<unsigned long, TransitionModelStore, DefaultKeyCompare<unsigned long>>
// {
// public:
//     void ~nlAVLTree();
// };

// class AVLTreeBase<unsigned long, TransitionModelStore, NewAdapter<AVLTreeEntry<unsigned long, TransitionModelStore>>, DefaultKeyCompare<unsigned long>>
// {
// public:
//     void DeleteEntry(AVLTreeEntry<unsigned long, TransitionModelStore>*);
//     void AllocateEntry(void*, void*);
//     void CompareKey(void*, AVLTreeNode*);
//     void CompareNodes(AVLTreeNode*, AVLTreeNode*);
//     void CastUp(AVLTreeNode*) const;
//     void PostorderTraversal(AVLTreeEntry<unsigned long, TransitionModelStore>*, void (AVLTreeBase<unsigned long, TransitionModelStore, NewAdapter<AVLTreeEntry<unsigned long, TransitionModelStore>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, TransitionModelStore>*));
//     void DestroyTree(void (AVLTreeBase<unsigned long, TransitionModelStore, NewAdapter<AVLTreeEntry<unsigned long, TransitionModelStore>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, TransitionModelStore>*));
//     void Clear();
//     void ~AVLTreeBase();
// };

#endif // _MODELTRANSITION_H_
