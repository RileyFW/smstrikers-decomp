#ifndef _AISANDBOX_H_
#define _AISANDBOX_H_

#include "NL/nlSingleton.h"

// class AVLTreeBase<unsigned long, FuzzyVariant, BasicSlotPool<AVLTreeEntry<unsigned long, FuzzyVariant>>, DefaultKeyCompare<unsigned long>>
// {
// public:
//     void DeleteEntry(AVLTreeEntry<unsigned long, FuzzyVariant>*);
// };

class AISandbox : public nlSingleton<AISandbox>
{
public:
    // total size: 0x1
};

#endif // _AISANDBOX_H_
