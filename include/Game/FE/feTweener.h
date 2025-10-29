#ifndef _FETWEENER_H_
#define _FETWEENER_H_

class FETweener;

class FETweenManager
{
public:
    void startTween(FETweener*);
    void clearTweensOnObj(void*);
    void clearTweens();
    void Update(float);
    void createTween(float*, float*, float, float, unsigned char, float (*)(float, float, float, float), void*,
        void (*)(void*, const float*));
    ~FETweenManager();
    FETweenManager();
};

class FETweener
{
public:
    void setDoneCallFunc(void (*)(void*), void*);
    void setNextTween(FETweener*);

    /* 0x00 */ unsigned char m_arraySize;                        // offset 0x0, size 0x1
    /* 0x01 */ unsigned char m_tweenActive;                      // offset 0x1, size 0x1
    /* 0x02 */ unsigned char m_completed;                        // offset 0x2, size 0x1
    /* 0x04 */ float m_curTime;                                  // offset 0x4, size 0x4
    /* 0x08 */ float m_delay;                                    // offset 0x8, size 0x4
    /* 0x0C */ float m_startTime;                                // offset 0xC, size 0x4
    /* 0x10 */ float m_startVal[4];                              // offset 0x10, size 0x10
    /* 0x20 */ float m_diffVal[4];                               // offset 0x20, size 0x10
    /* 0x30 */ float m_duration;                                 // offset 0x30, size 0x4
    /* 0x34 */ float (*m_tweenFunc)(float, float, float, float); // offset 0x34, size 0x4
    /* 0x38 */ void* m_applyObj;                                 // offset 0x38, size 0x4
    /* 0x3C */ void (*m_setterFunc)(void*, float*);              // offset 0x3C, size 0x4
    /* 0x40 */ FETweener* m_nextTween;                           // offset 0x40, size 0x4
    /* 0x44 */ void (*m_doneFunc)(void*);                        // offset 0x44, size 0x4
    /* 0x48 */ void* m_doneFuncParam;                            // offset 0x48, size 0x4

    virtual ~FETweener();
}; // total size: 0x50

// class DLListContainerBase<FETweener*, BasicSlotPool<DLListEntry<FETweener*>>>
// {
// public:
//     void DeleteEntry(DLListEntry<FETweener*>*);
// };

// class nlWalkDLRing<DLListEntry<FETweener*>, DLListContainerBase<FETweener*,
// BasicSlotPool<DLListEntry<FETweener*>>>>(DLListEntry<FETweener*>*, DLListContainerBase<FETweener*,
// BasicSlotPool<DLListEntry<FETweener*>>>*, void (DLListContainerBase<FETweener*, BasicSlotPool<DLListEntry<FETweener*>>>
// {
// public:
//     void *)(DLListEntry<FETweener*>*));
// };

// class nlWalkRing<DLListEntry<FETweener*>, DLListContainerBase<FETweener*,
// BasicSlotPool<DLListEntry<FETweener*>>>>(DLListEntry<FETweener*>*, DLListContainerBase<FETweener*,
// BasicSlotPool<DLListEntry<FETweener*>>>*, void (DLListContainerBase<FETweener*, BasicSlotPool<DLListEntry<FETweener*>>>
// {
// public:
//     void *)(DLListEntry<FETweener*>*));
// };

#endif // _FETWEENER_H_
