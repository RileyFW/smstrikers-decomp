#ifndef _STATICMODELEXPLODABLE_H_
#define _STATICMODELEXPLODABLE_H_

#include "types.h"
#include "NL/nlMath.h"

// void 0x8028D320..0x8028D324 | size: 0x4;

enum StaticModelExplodableCategory
{
    EXPLODABLE_BENCH1 = 0,
    EXPLODABLE_BENCH2 = 1,
    NUM_STATIC_MODEL_EXPLODABLE_CATEGORIES = 2,
};

class StaticModelExplodable
{
public:
    void CleanUp();
    StaticModelExplodable(StaticModelExplodableCategory, const nlMatrix4&);
    ~StaticModelExplodable();
    void GetCategoryData() const;
    void GetWorldMatrix() const;
    void SetUnexplodedModelVisibility(bool);

    static bool LoadGeometry();
    static void CreateExplodablesFromHelperObjects();
};

#endif // _STATICMODELEXPLODABLE_H_
