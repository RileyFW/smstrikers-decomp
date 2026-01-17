#include "Game/FE/FEAudio.h"

#include "NL/nlString.h"

class Event;

static bool mIsEnabled = true;
static void* gpLastSoundFromPlayer;

/**
 * Offset/Address/Size: 0x0 | 0x8009EDAC | size: 0x8
 */
void FEAudio::EnableSounds(bool enable)
{
    mIsEnabled = enable;
}

/**
 * Offset/Address/Size: 0x8 | 0x8009EDB4 | size: 0x27C
 */
void FEAudioEventHandler(Event*, void*)
{
}

/**
 * Offset/Address/Size: 0x284 | 0x8009F030 | size: 0xC
 */
void FEAudio::ResetRandomVoiceToggleSFX()
{
    gpLastSoundFromPlayer = nullptr;
}

/**
 * Offset/Address/Size: 0x290 | 0x8009F03C | size: 0x360
 */
void FEAudio::PlayRandomVoiceToggleSFX()
{
}

/**
 * Offset/Address/Size: 0x5F0 | 0x8009F39C | size: 0xB8
 */
void FEAudio::PlayAnimAudioEvent(unsigned long, bool)
{
}

/**
 * Offset/Address/Size: 0x6A8 | 0x8009F454 | size: 0x90
 */
void FEAudio::StopAnimAudioEvent(const char*)
{
}

/**
 * Offset/Address/Size: 0x738 | 0x8009F4E4 | size: 0xBC
 */
void FEAudio::PlayAnimAudioEvent(const char*, bool)
{
}

/**
 * Offset/Address/Size: 0x7F4 | 0x8009F5A0 | size: 0x408
 */
void FEAudio::BuildAnimAudioEventLookup()
{
}

// /**
//  * Offset/Address/Size: 0x0 | 0x8009F9A8 | size: 0x10
//  */
// void ListContainerBase<AnimAudioEventLookup, BasicSlotPoolHigh<ListEntry<AnimAudioEventLookup>>>::DeleteEntry(
//     ListEntry<AnimAudioEventLookup>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8009F9B8 | size: 0x20
//  */
// void BasicSlotPoolHigh<ListEntry<AnimAudioEventLookup>>::freeFN(void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x20 | 0x8009F9D8 | size: 0x28
//  */
// void BasicSlotPoolHigh<ListEntry<AnimAudioEventLookup>>::allocFN(unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8009FA00 | size: 0x28
//  */
// void nlQSort<AnimAudioEventLookup>(AnimAudioEventLookup*, int, int (*)(const AnimAudioEventLookup*, const AnimAudioEventLookup*))
// {
// }

// /**
//  * Offset/Address/Size: 0x28 | 0x8009FA28 | size: 0x2C
//  */
// void nlDefaultQSortComparer<AnimAudioEventLookup>(const AnimAudioEventLookup*, const AnimAudioEventLookup*)
// {
// }

// /**
//  * Offset/Address/Size: 0x54 | 0x8009FA54 | size: 0x8C
//  */
// void nlBSearch<AnimAudioEventLookup, unsigned long>(const unsigned long&, AnimAudioEventLookup*, int)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8009FAE0 | size: 0x68
//  */
// void nlWalkList<ListEntry<AnimAudioEventLookup>,
//                 ListContainerBase<AnimAudioEventLookup, BasicSlotPoolHigh<ListEntry<AnimAudioEventLookup>>>>(
//     ListEntry<AnimAudioEventLookup>*, ListContainerBase<AnimAudioEventLookup, BasicSlotPoolHigh<ListEntry<AnimAudioEventLookup>>>*,
//     void (ListContainerBase<AnimAudioEventLookup,
//     BasicSlotPoolHigh<ListEntry<AnimAudioEventLookup>>>::*)(ListEntry<AnimAudioEventLookup>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x68 | 0x8009FB48 | size: 0x2C
//  */
// void nlListAddEnd<ListEntry<AnimAudioEventLookup>>(ListEntry<AnimAudioEventLookup>**, ListEntry<AnimAudioEventLookup>**,
//                                                    ListEntry<AnimAudioEventLookup>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8009FB74 | size: 0x84
//  */
// void nlStrICmp<char>(const char*, const char*)
// {
// }

// /**
//  * Offset/Address/Size: 0x84 | 0x8009FBF8 | size: 0x40
//  */
// void nlStrCmp<char>(const char*, const char*)
// {
// }

// /**
//  * Offset/Address/Size: 0xC4 | 0x8009FC38 | size: 0x20
//  */
// void nlToUpper<char>(char)
// {
// }
