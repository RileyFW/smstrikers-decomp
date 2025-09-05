#ifndef _TWEAKSBASE_H_
#define _TWEAKSBASE_H_

#include "NL/nlString.h"

class TweaksBase
{
public:
    TweaksBase(const char*);  
    virtual ~TweaksBase();
    virtual void Init() = 0;

    /* 0x04 */ char m_unk_0x04[0x20];
};

#endif // _TWEAKSBASE_H_
