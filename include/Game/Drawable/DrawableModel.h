#ifndef _DRAWABLEMODEL_H_
#define _DRAWABLEMODEL_H_

#include "Game/Drawable/DrawableObj.h"

#include "NL/nlMath.h"
#include "NL/gl/glView.h"

class glModel;
class glModelPacket;
class BallShadowParams;

void CleanBoundingBoxCache();
void RenderBoundingBox(const glModel*, const nlMatrix4&);
void GetCoPlanar0Z();
void SetCoPlanarZ(float);
void GetCoPlanarZ();
void SetPlanarShadowOpacity(float);
void GetPlanarShadowOpacity();
void DrawPlanarShadow(const glModel*, const nlMatrix4&, float, bool, bool, bool, unsigned long);
void DrawCoPlanarReference(eGLView, const glModel&, const nlMatrix4&, unsigned long);
void GetShadowBoundingSquare(const glModel*, const nlMatrix4&, float&, float&, float&, float&, unsigned long);
void GetAABBDimensions(const glModel*, AABBDimensions&, unsigned long);
void Fresnelify(glModelPacket*, eGLView);
void DrawBallShadow(const nlVector3&, const BallShadowParams&, bool);

class DrawableModel
{
public:
    void DrawPlanarShadow();
    void GetAABBDimensions(AABBDimensions&, bool) const;
    void Clone() const;
    void Draw();
    void DrawModel(const nlMatrix4&);
    ~DrawableModel();
    void IsDrawableModel();
    void AsDrawableModel();
};

class DrawableShadow
{
public:
    void Draw();
    ~DrawableShadow();
};

// class nlAVLTreeSlotPool<unsigned long, AABBDimensions, DefaultKeyCompare<unsigned long>>
// {
// public:
//     void ~nlAVLTreeSlotPool();
// };

// class AVLTreeBase<unsigned long, AABBDimensions, BasicSlotPool<AVLTreeEntry<unsigned long, AABBDimensions>>, DefaultKeyCompare<unsigned long>>
// {
// public:
//     void Clear();
//     void DestroyTree(void (AVLTreeBase<unsigned long, AABBDimensions, BasicSlotPool<AVLTreeEntry<unsigned long, AABBDimensions>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, AABBDimensions>*));
//     void PostorderTraversal(AVLTreeEntry<unsigned long, AABBDimensions>*, void (AVLTreeBase<unsigned long, AABBDimensions, BasicSlotPool<AVLTreeEntry<unsigned long, AABBDimensions>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, AABBDimensions>*));
//     void CastUp(AVLTreeNode*) const;
//     void DeleteEntry(AVLTreeEntry<unsigned long, AABBDimensions>*);
//     void ~AVLTreeBase();
//     void CompareNodes(AVLTreeNode*, AVLTreeNode*);
//     void CompareKey(void*, AVLTreeNode*);
//     void AllocateEntry(void*, void*);
// };

#endif // _DRAWABLEMODEL_H_
