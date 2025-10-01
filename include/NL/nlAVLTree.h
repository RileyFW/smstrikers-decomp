#ifndef _NLAVLTREE_H_
#define _NLAVLTREE_H_

#include "NL/nlAVLTreeBase.h"

template <typename KeyType, typename ValueType, typename CompareType>
class nlAVLTree : public AVLTreeBase<KeyType, ValueType, NewAdapter<AVLTreeEntry<KeyType, ValueType> >, CompareType>
{
public:
    nlAVLTree();
    // nlAVLTree(const nlAVLTree& other);
    // nlAVLTree& operator=(const nlAVLTree& other);
    // nlAVLTree(nlAVLTree&& other);
    // nlAVLTree& operator=(nlAVLTree&& other);
    ~nlAVLTree();
};

#endif // _NLAVLTREE_H_
