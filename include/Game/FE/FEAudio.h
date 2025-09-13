#ifndef _FEAUDIO_H_
#define _FEAUDIO_H_

// void FEAudioEventHandler(Event*, void*);
// void nlQSort<AnimAudioEventLookup>(AnimAudioEventLookup*, int, int (*)(const AnimAudioEventLookup*, const AnimAudioEventLookup*));
// void nlDefaultQSortComparer<AnimAudioEventLookup>(const AnimAudioEventLookup*, const AnimAudioEventLookup*);
// void nlBSearch<AnimAudioEventLookup, unsigned long>(const unsigned long&, AnimAudioEventLookup*, int);
// void nlListAddEnd<ListEntry<AnimAudioEventLookup>>(ListEntry<AnimAudioEventLookup>**, ListEntry<AnimAudioEventLookup>**,
// ListEntry<AnimAudioEventLookup>*); void nlStrICmp<char>(const char*, const char*); void nlStrCmp<char>(const char*, const char*); void
// nlToUpper<char>(char);

class FEAudio
{
public:
    static void EnableSounds(bool);
    void ResetRandomVoiceToggleSFX();
    void PlayRandomVoiceToggleSFX();
    void PlayAnimAudioEvent(unsigned long, bool);
    void StopAnimAudioEvent(const char*);
    void PlayAnimAudioEvent(const char*, bool);
    void BuildAnimAudioEventLookup();
};

// class ListContainerBase<AnimAudioEventLookup, BasicSlotPoolHigh<ListEntry<AnimAudioEventLookup>>>
// {
// public:
//     void DeleteEntry(ListEntry<AnimAudioEventLookup>*);
// };

// class BasicSlotPoolHigh<ListEntry<AnimAudioEventLookup>>
// {
// public:
//     void freeFN(void*);
//     void allocFN(unsigned long);
// };

// class nlWalkList<ListEntry<AnimAudioEventLookup>, ListContainerBase<AnimAudioEventLookup,
// BasicSlotPoolHigh<ListEntry<AnimAudioEventLookup>>>>(ListEntry<AnimAudioEventLookup>*, ListContainerBase<AnimAudioEventLookup,
// BasicSlotPoolHigh<ListEntry<AnimAudioEventLookup>>>*, void (ListContainerBase<AnimAudioEventLookup,
// BasicSlotPoolHigh<ListEntry<AnimAudioEventLookup>>>
// {
// public:
//     void *)(ListEntry<AnimAudioEventLookup>*));
// };

#endif // _FEAUDIO_H_
