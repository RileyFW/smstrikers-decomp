#ifndef _AVLTREEBASE_H_
#define _AVLTREEBASE_H_

#include "NL/nlMemory.h"

#include "dolphin/types.h"
#include "types.h"

#include "dolphin/types.h"

typedef struct AVLTreeNode
{
    /* 0x00 */ struct AVLTreeNode* s_leftChild;
    /* 0x04 */ struct AVLTreeNode* s_rightChild;
    /* 0x08 */ u8 s_balance;
    /* 0x0C */ s32 s_key;
    /* 0x10 */ void* s_data;

    // AVLTreeNode()
    // {
    //     s_leftChild = NULL;
    //     s_rightChild = NULL;
    //     s_data = NULL;
    //     s_key = 0;
    // }

} AVLTreeNode, *AVLTreeNodePtr;

class AVLTreeUntemplated
{
public:
    virtual s32 CompareNodes(AVLTreeNode* node1, AVLTreeNode* node2) = 0; // vtable offset 0xc
    virtual AVLTreeNode* AllocateEntry(void* key, void* value) = 0;

    AVLTreeNode* RemoveAVLNode(AVLTreeNode**, void*, unsigned int);
    void AddAVLNode(AVLTreeNode**, void*, void*, AVLTreeNode**, unsigned int);
};

// Forward declarations
template <typename KeyType, typename ValueType>
class AVLTreeEntry;

template <typename T>
class NewAdapter;

template <typename KeyType>
class DefaultKeyCompare;

template <typename KeyType, typename ValueType, typename AllocatorType, typename CompareType>
class AVLTreeBase : public AVLTreeUntemplated
{
public:
    // Tree management functions
    void DeleteEntry(AVLTreeEntry<KeyType, ValueType>* entry);
    void Clear();
    void DestroyTree(void (AVLTreeBase::*)(AVLTreeEntry<KeyType, ValueType>*));

    // Tree traversal functions
    void PostorderTraversal(AVLTreeEntry<KeyType, ValueType>* node,
        void (AVLTreeBase::*)(AVLTreeEntry<KeyType, ValueType>*));

    // Template traversal functions (for specific use cases)
    template <typename CallbackType>
    void Walk(CallbackType* callback, void (CallbackType::*)(const KeyType&, ValueType**));

    template <typename CallbackType>
    void InorderWalk(AVLTreeEntry<KeyType, ValueType>* node, CallbackType* callback,
        void (CallbackType::*)(const KeyType&, ValueType**));

    // Node comparison and allocation functions - FIXED RETURN TYPES
    virtual s32 CompareNodes(AVLTreeNode* node1, AVLTreeNode* node2);
    s32 CompareKey(void* key, AVLTreeNode* node);
    virtual AVLTreeNode* AllocateEntry(void* key, void* value);

    // Type casting function
    AVLTreeNode* CastUp(AVLTreeNode* node) const;

    AVLTreeBase();
    virtual ~AVLTreeBase();

    // /* 0x04 */ AVLTreeEntry<KeyType, ValueType>* m_first_entry_0x00;
    // /* 0x08 */ AVLTreeEntry<KeyType, ValueType>* m_root_entry_0x08;
    // /* 0x0C */ AVLTreeEntry<KeyType, ValueType>* m_unk_0x0C;
    // /* 0x10 */ AVLTreeNode* m_root_node_0x10;

    // AllocatorType m_allocator;
    // CompareType m_comparator;

    // /* 0x04 */ class NewAdapter m_Allocator;             // offset 0x4, size 0x1
    /* 0x04 */ AllocatorType m_allocator;                // offset 0x4, size 0x1
    /* 0x08 */ AVLTreeEntry<KeyType, ValueType>* m_Root; // offset 0x8, size 0x4
                                                         // /* 0x0C */ class DefaultKeyCompare* m_Compare;       // offset 0xC, size 0x4
    /* 0x0C */ CompareType m_Compare;                    // offset 0xC, size 0x4
                                                         // /* 0x10 */ unsigned int m_NumElements;               // offset 0x10, size 0x4
    /* 0x10 */ AVLTreeNode* m_root_node_0x10;
};

template <typename KeyType, typename ValueType, typename AllocatorType, typename CompareType>
void AVLTreeBase<KeyType, ValueType, AllocatorType, CompareType>::DeleteEntry(AVLTreeEntry<KeyType, ValueType>* entry)
{
    m_allocator.Free(entry);
}

template <typename KeyType, typename ValueType, typename AllocatorType, typename CompareType>
void AVLTreeBase<KeyType, ValueType, AllocatorType, CompareType>::Clear()
{
    DestroyTree(&AVLTreeBase::DeleteEntry);
    m_Root = nullptr;
}

template <typename KeyType, typename ValueType, typename AllocatorType, typename CompareType>
void AVLTreeBase<KeyType, ValueType, AllocatorType, CompareType>::DestroyTree(void (AVLTreeBase::*deleteFunc)(AVLTreeEntry<KeyType, ValueType>*))
{
    if (m_Root != NULL)
    {
        PostorderTraversal(m_Root, deleteFunc);
        m_Root = nullptr;
    }
}

template <typename KeyType, typename ValueType, typename AllocatorType, typename CompareType>
void AVLTreeBase<KeyType, ValueType, AllocatorType, CompareType>::PostorderTraversal(AVLTreeEntry<KeyType, ValueType>* node,
    void (AVLTreeBase::*deleteFunc)(AVLTreeEntry<KeyType, ValueType>*))
{
    if (node->m_left != NULL)
    {
        PostorderTraversal(node->m_left, deleteFunc);
    }
    if (node->m_right != NULL)
    {
        PostorderTraversal(node->m_right, deleteFunc);
    }
    (this->*deleteFunc)(node);
}

template <typename KeyType, typename ValueType, typename AllocatorType, typename CompareType>
s32 AVLTreeBase<KeyType, ValueType, AllocatorType, CompareType>::CompareNodes(AVLTreeNode* node1, AVLTreeNode* node2)
{
    u32 k1 = node1->s_key;
    u32 k2 = node2->s_key;

    if (k1 == k2)
    {
        return 0;
    }
    if (k1 < k2)
    {
        return -1;
    }
    return 1;
}

template <typename KeyType, typename ValueType, typename AllocatorType, typename CompareType>
s32 AVLTreeBase<KeyType, ValueType, AllocatorType, CompareType>::CompareKey(void* key, AVLTreeNode* node)
{
    KeyType temp_r3 = *static_cast<KeyType*>(key);
    KeyType temp_r0 = static_cast<KeyType*>(node->s_data);
    if (temp_r3 == temp_r0)
    {
        return 0;
    }
    if (temp_r3 < temp_r0)
    {
        return -1;
    }
    return 1;
}

template <typename KeyType, typename ValueType, typename AllocatorType, typename CompareType>
AVLTreeNode* AVLTreeBase<KeyType, ValueType, AllocatorType, CompareType>::AllocateEntry(void* key, void* value)
{
    AVLTreeNode* node = (AVLTreeNode*)nlMalloc(0x14, 8, 0);
    node->s_leftChild = 0;
    node->s_rightChild = 0;
    node->s_balance = 0;
    node->s_key = *(s32*)key;
    node->s_data = value;
    return node;
}

template <typename KeyType, typename ValueType, typename AllocatorType, typename CompareType>
AVLTreeNode* AVLTreeBase<KeyType, ValueType, AllocatorType, CompareType>::CastUp(AVLTreeNode* node) const
{
    return node;
}

// Template implementations
template <typename KeyType, typename ValueType, typename AllocatorType, typename CompareType>
AVLTreeBase<KeyType, ValueType, AllocatorType, CompareType>::AVLTreeBase()
    : m_Root(nullptr)
{
}

template <typename KeyType, typename ValueType, typename AllocatorType, typename CompareType>
AVLTreeBase<KeyType, ValueType, AllocatorType, CompareType>::~AVLTreeBase()
{
    Clear();
}

// AVLTreeEntry template implementation
template <typename KeyType, typename ValueType>
class AVLTreeEntry
{
public:
    AVLTreeEntry()
        : m_key()
        , m_value()
        , m_left(nullptr)
        , m_right(nullptr)
    {
    }

    void SetKey(const KeyType& key) { m_key = key; }
    void SetValue(const ValueType& value) { m_value = value; }

    const KeyType& GetKey() const { return m_key; }
    ValueType& GetValue() { return m_value; }
    const ValueType& GetValue() const { return m_value; }

    void SetLeft(AVLTreeEntry* left) { m_left = left; }
    void SetRight(AVLTreeEntry* right) { m_right = right; }

    AVLTreeEntry* m_left;
    AVLTreeEntry* m_right;

    KeyType m_key;
    ValueType m_value;
};

// NewAdapter template implementation
template <typename T>
class NewAdapter
{
public:
    T* Allocate() { return new T(); }
    void Free(T* ptr) { delete ptr; }
};

// DefaultKeyCompare template implementation
template <typename KeyType>
class DefaultKeyCompare
{
public:
    int operator()(const KeyType& key1, const KeyType& key2) const
    {
        if (key1 < key2)
            return -1;
        if (key1 > key2)
            return 1;
        return 0;
    }
};

// Add the missing Walk template implementation
template <typename KeyType, typename ValueType, typename AllocatorType, typename CompareType>
template <typename CallbackType>
void AVLTreeBase<KeyType, ValueType, AllocatorType, CompareType>::Walk(CallbackType* callback,
    void (CallbackType::*callbackFunc)(const KeyType&, ValueType**))
{
    if (m_Root != nullptr)
    {
        InorderWalk(m_Root, callback, callbackFunc);
    }
}

template <typename KeyType, typename ValueType, typename AllocatorType, typename CompareType>
template <typename CallbackType>
void AVLTreeBase<KeyType, ValueType, AllocatorType, CompareType>::InorderWalk(AVLTreeEntry<KeyType, ValueType>* node,
    CallbackType* callback, void (CallbackType::*callbackFunc)(const KeyType&, ValueType**))
{
    if (node != nullptr)
    {
        InorderWalk(node->m_left, callback, callbackFunc);
        (callback->*callbackFunc)(node->GetKey(), &node->GetValue());
        InorderWalk(node->m_right, callback, callbackFunc);
    }
}

#endif // _AVLTREEBASE_H_
