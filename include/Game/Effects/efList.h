#ifndef _EFLIST_H_
#define _EFLIST_H_

#include "types.h"

struct efBaseNode
{
public:
    /* 0x0, */ efBaseNode* m_nextNode;
    /* 0x4, */ efBaseNode* m_prevNode;
};

class efNode : public efBaseNode
{
    // todo
}; // size: 0x8

class efBaseList
{
public:
    void Insert(efBaseNode*);
    void Append(efBaseNode*);
    efBaseNode* Remove();
    efBaseNode* Remove(efBaseNode*);

    /* 0x0, */ struct efBaseNode* m_headNode;
    /* 0x4, */ struct efBaseNode* m_tailNode;
    /* 0x8, */ int m_numNodes;
};

#endif // _EFLIST_H_
