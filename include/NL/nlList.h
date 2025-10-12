#ifndef _NLLIST_H_
#define _NLLIST_H_

#include "types.h"

#include "NL/nlAdapter.h"
#include "NL/nlDLRing.h"
#include "NL/nlSlotPool.h"

template <typename T>
class ListEntry
{
public:
    /* 0x00 */ ListEntry<T>* next;
    /* 0x04 */ ListEntry<T>* prev; // not sure if this is used
    /* 0x08 */ T data;

    ListEntry()
        : next(nullptr)
        , data(nullptr)
    {
    }

    ListEntry(T* data)
        : next(nullptr)
        , data(data)
    {
    }
};

// template <typename T>
// class NewAdapter
// {
// public:
//     typedef ListEntry<T> EntryType; // Add this line

//     static void DeleteEntry(ListEntry<T>* entry)
//     {
//         if (entry)
//         {
//             delete entry;
//         }
//     }
// };

template <typename T, typename Adapter>
class ListContainerBase
{
public:
    typedef typename Adapter::EntryType EntryType;

    void DeleteEntry(EntryType* entry) { Adapter::DeleteEntry(entry); }

    // Add more list operations as needed
    void AddEntry(EntryType* entry)
    {
        // Implementation for adding entries
    }

    void RemoveEntry(EntryType* entry)
    {
        // Implementation for removing entries
    }

    /* 0x0 */ NewAdapter<T> m_Allocator; // offset 0x0, size 0x1
    /* 0x4 */ ListEntry<T>* m_Head;      // offset 0x4, size 0x4
    /* 0x8 */ ListEntry<T>* m_Tail;      // offset 0x8, size 0x4
};

template <typename T>
class nlListContainer : public ListContainerBase<T, NewAdapter<T> >
{
public:
    // todo: ...
}; // total size: 0xC

template <typename T>
ListEntry<T>* nlListRemoveStart(ListEntry<T>** head, ListEntry<T>** tail)
{
    ListEntry<T>* first = *head;
    if (first == 0)
        return 0;

    if (tail != 0)
    {
        if (*tail == first)
            *tail = 0;
    }

    // Remove first element
    ListEntry<T>* tmp = *head;
    *head = tmp->next;
    return tmp;
}

template <typename T>
void nlListAddStart(ListEntry<T>** head, ListEntry<T>* entry, ListEntry<T>** tail)
{
    if (tail != 0)
    {
        if (*head == 0)
        {
            *tail = entry;
        }
    }

    // Insert at start
    entry->next = *head;
    *head = entry;
}

template <typename T>
void nlDeleteList(T** head)
{
    T* next;
    while (*head != NULL)
    {
        next = (*head)->next;
        delete *head;
        *head = next;
    }
    *head = NULL;
}

#endif
