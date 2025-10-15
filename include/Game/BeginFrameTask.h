#ifndef _BEGINFRAMETASK_H_
#define _BEGINFRAMETASK_H_

#include "NL/nlTask.h"
#include "NL/gl/glModel.h"

void DrawGrid(int);
void DrawSafeFrame();
void SetupRenderInfo();
void SetupMatrices();
void cb_ParticleLighting(glModel* pModel);

class BeginFrameTask : public nlTask
{
public:
    virtual const char* GetName() { return "Begin Frame"; };
    virtual void Run(float dt);
};

// class Config
// {
// public:
//     void TagValuePair::Get<BasicString<char, Detail::TempStringAllocator> >() const;
//     void Get<BasicString<char, Detail::TempStringAllocator> >(const char*, BasicString<char, Detail::TempStringAllocator>);
// };

#endif // _BEGINFRAMETASK_H_
