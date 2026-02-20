#ifndef _STATICMODELEXPLODABLE_H_
#define _STATICMODELEXPLODABLE_H_

#include "types.h"
#include "NL/nlMath.h"
#include "Game/Render/SidelineExplodable.h"

// void 0x8028D320..0x8028D324 | size: 0x4;

enum StaticModelExplodableCategory
{
    EXPLODABLE_BENCH1 = 0,
    EXPLODABLE_BENCH2 = 1,
    NUM_STATIC_MODEL_EXPLODABLE_CATEGORIES = 2,
};

class DrawableObject;

class StaticModelExplodable : public SidelineExplodable
{
public:
    static void CleanUp();
    StaticModelExplodable(StaticModelExplodableCategory, const nlMatrix4&);
    ~StaticModelExplodable();
    virtual ExplodableCategoryData& GetCategoryData() const;
    void SetUnexplodedModelVisibility(bool);
    virtual const nlMatrix4& GetWorldMatrix() const;

    static bool LoadGeometry();
    static void CreateExplodablesFromHelperObjects();
    static u8 bIsModelLoaded[2];
    static nlList<SidelineExplodableNode> sStaticModelExplodableList;
    static ExplodableCategoryData sCategoryData[NUM_STATIC_MODEL_EXPLODABLE_CATEGORIES];

    /* 0x2C */ DrawableObject* m_pUnexplodedModel;
    /* 0x30 */ StaticModelExplodableCategory mCategory;
    /* 0x34 */ nlMatrix4 mWorldMatrix;
};

#endif // _STATICMODELEXPLODABLE_H_
