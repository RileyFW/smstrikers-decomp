#ifndef NL_ADAPTER_H
#define NL_ADAPTER_H

template <typename T>
class NewAdapter
{
public:
    // For AVL Tree interface
    T* Allocate() { return new T(); }
    void Allocate(T*& out) { out = new T(); }
    void Free(T* ptr) { delete ptr; }

    // For List interface
    typedef T EntryType;
    static void DeleteEntry(T* entry)
    {
        if (entry)
        {
            delete entry;
        }
    }
};

#endif // NL_ADAPTER_H
