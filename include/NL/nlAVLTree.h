#ifndef _NLAVLTREE_H_
#define _NLAVLTREE_H_

#include "NL/nlAdapter.h"
#include "NL/nlAVLTreeBase.h"

template <typename KeyType, typename ValueType, typename CompareType>
class nlAVLTree : public AVLTreeBase<KeyType, ValueType, NewAdapter<AVLTreeEntry<KeyType, ValueType> >, CompareType>
{
public:
    nlAVLTree()
        : AVLTreeBase<KeyType, ValueType, NewAdapter<AVLTreeEntry<KeyType, ValueType> >, CompareType>() { };
    ~nlAVLTree() { };
};

#endif // _NLAVLTREE_H_
