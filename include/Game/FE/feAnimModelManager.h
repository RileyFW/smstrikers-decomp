#ifndef _FEANIMMODELMANAGER_H_
#define _FEANIMMODELMANAGER_H_

#include "NL/nlSingleton.h"

class FEAnimModelManager : public nlSingleton<FEAnimModelManager>
{
public:
    void Update(float);
    void Initialize();
    ~FEAnimModelManager();
    FEAnimModelManager();
};

#endif // _FEANIMMODELMANAGER_H_
