#ifndef _ANIMATEDMODELEXPLODABLE_H_
#define _ANIMATEDMODELEXPLODABLE_H_

#include "types.h"
#include "NL/nlMath.h"
// #include "Game/Drawable/SkinAnimatedNPC.h"

class SkinAnimatedNPC;

enum AnimatedModelExplodableCategory
{
    EXPLODABLE_CAMERAGUY = 0,
    EXPLODABLE_STANDUPCAMERA = 1,
    NUM_ANIMATED_MODEL_EXPLODABLE_CATEGORIES = 2,
};

// void nlListRemoveStart<SidelineExplodableNode>(SidelineExplodableNode**, SidelineExplodableNode**);
// void nlListAddEnd<SidelineExplodableNode>(SidelineExplodableNode**, SidelineExplodableNode**, SidelineExplodableNode*);
// void 0x8028D2FC..0x8028D300 | size: 0x4;

class AnimatedModelExplodable
{
public:
    void CleanUp();
    AnimatedModelExplodable(AnimatedModelExplodableCategory, SkinAnimatedNPC*);
    ~AnimatedModelExplodable();
    void GetCategoryData() const;
    void GetWorldMatrix() const;
    void SetUnexplodedModelVisibility(bool);
    static bool LoadGeometry();
};

#endif // _ANIMATEDMODELEXPLODABLE_H_
