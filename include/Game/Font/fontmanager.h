#ifndef _FONTMANAGER_H_
#define _FONTMANAGER_H_

void nlDLRingIsEnd<DLListEntry<nlFont*>>(DLListEntry<nlFont*>*, DLListEntry<nlFont*>*);
void nlDLRingGetStart<DLListEntry<nlFont*>>(DLListEntry<nlFont*>*);
void nlDLRingAddEnd<DLListEntry<nlFont*>>(DLListEntry<nlFont*>**, DLListEntry<nlFont*>*);
void nlDLRingAddStart<DLListEntry<nlFont*>>(DLListEntry<nlFont*>**, DLListEntry<nlFont*>*);

class FontManager
{
public:
    FontManager();
    ~FontManager();
    void GetFontByHashID(unsigned long);
    void LoadFont(const char*, const char*, const char*);
};


class DLListContainerBase<nlFont*, BasicSlotPool<DLListEntry<nlFont*>>>
{
public:
    void DeleteEntry(DLListEntry<nlFont*>*);
};


class nlWalkDLRing<DLListEntry<nlFont*>, DLListContainerBase<nlFont*, BasicSlotPool<DLListEntry<nlFont*>>>>(DLListEntry<nlFont*>*, DLListContainerBase<nlFont*, BasicSlotPool<DLListEntry<nlFont*>>>*, void (DLListContainerBase<nlFont*, BasicSlotPool<DLListEntry<nlFont*>>>
{
public:
    void *)(DLListEntry<nlFont*>*));
};


class nlWalkRing<DLListEntry<nlFont*>, DLListContainerBase<nlFont*, BasicSlotPool<DLListEntry<nlFont*>>>>(DLListEntry<nlFont*>*, DLListContainerBase<nlFont*, BasicSlotPool<DLListEntry<nlFont*>>>*, void (DLListContainerBase<nlFont*, BasicSlotPool<DLListEntry<nlFont*>>>
{
public:
    void *)(DLListEntry<nlFont*>*));
};

#endif // _FONTMANAGER_H_