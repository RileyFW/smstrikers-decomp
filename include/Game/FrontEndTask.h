#ifndef _FRONTENDTASK_H_
#define _FRONTENDTASK_H_

#include "NL/nlTask.h"

class FrontEndTask : public nlTask
{
public:
    virtual void Run(float);
    virtual const char* GetName() { return "Front End"; };
    void HandleE3IdleReset(float);
};

#endif // _FRONTENDTASK_H_
