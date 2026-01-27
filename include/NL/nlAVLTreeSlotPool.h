#ifndef _NLAVLTREESLOTPOOL_H_
#define _NLAVLTREESLOTPOOL_H_

#include "NL/nlSlotPool.h"
#include "NL/nlAVLTreeBase.h"

template <typename KeyType, typename ValueType, typename CompareType>
class nlAVLTreeSlotPool : public AVLTreeBase<KeyType, ValueType, BasicSlotPool<AVLTreeEntry<KeyType, ValueType> >, CompareType>
{
public:
    nlAVLTreeSlotPool()
        : AVLTreeBase<KeyType, ValueType, BasicSlotPool<AVLTreeEntry<KeyType, ValueType> >, CompareType>() { };
    ~nlAVLTreeSlotPool()
    {
        FORCE_DONT_INLINE;
    };
};

#endif // _NLAVLTREESLOTPOOL_H_
