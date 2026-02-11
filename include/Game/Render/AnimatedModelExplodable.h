#ifndef _ANIMATEDMODELEXPLODABLE_H_
#define _ANIMATEDMODELEXPLODABLE_H_

#include "types.h"
#include "NL/nlMath.h"
#include "Game/Render/SidelineExplodable.h"
#include "Game/Render/SkinAnimatedNPC.h"

enum AnimatedModelExplodableCategory
{
    EXPLODABLE_CAMERAGUY = 0,
    EXPLODABLE_STANDUPCAMERA = 1,
    NUM_ANIMATED_MODEL_EXPLODABLE_CATEGORIES = 2,
};

// void nlListRemoveStart<SidelineExplodableNode>(SidelineExplodableNode**, SidelineExplodableNode**);
// void nlListAddEnd<SidelineExplodableNode>(SidelineExplodableNode**, SidelineExplodableNode**, SidelineExplodableNode*);
// void 0x8028D2FC..0x8028D300 | size: 0x4;

class AnimatedModelExplodable : public SidelineExplodable
{
public:
    static void CleanUp();
    AnimatedModelExplodable(AnimatedModelExplodableCategory, SkinAnimatedNPC*);
    ~AnimatedModelExplodable();
    void GetCategoryData() const;
    const nlMatrix4& GetWorldMatrix() const;
    void SetUnexplodedModelVisibility(bool);
    static bool LoadGeometry();

    /* 0x2C */ SkinAnimatedNPC* mpAnimatedNPC;
    /* 0x30 */ AnimatedModelExplodableCategory mCategory;
}; // total size: 0x34

#endif // _ANIMATEDMODELEXPLODABLE_H_
