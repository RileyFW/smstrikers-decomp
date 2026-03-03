#include "Game/FE/FEAudio.h"

#include "Game/Audio/AudioLoader.h"
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
long FEAudio::PlayAnimAudioEvent(unsigned long uHash, bool)
{
    if (!AudioLoader::IsInited())
    {
        return -1;
    }

    if (!mIsEnabled)
    {
        return -1;
    }

    unsigned long stackHash = uHash;
    AnimAudioEventLookup* result = nlBSearch<AnimAudioEventLookup, unsigned long>(stackHash, gp_AnimAudioEventTable, gNumAnimAudioEvents);
    AnimAudioEventLookup* event;
    if (result)
    {
        event = result;
    }
    else
    {
        event = NULL;
    }

    if (nlStrICmp<char>(event->szSFXType, "") == 0)
    {
        return -1;
    }

    Audio::PlayWorldSFXbyStr(event->szSFXType, 1.0f, 0.0f, false, true, NULL, NULL, NULL);
    return 0;
}

/**
 * Offset/Address/Size: 0x6A8 | 0x8009F454 | size: 0x90
 */
void FEAudio::StopAnimAudioEvent(const char* eventName)
{
    if (!AudioLoader::IsInited())
    {
        return;
    }

    unsigned long hash = nlStringLowerHash(eventName);

    if (!AudioLoader::IsInited())
    {
        return;
    }

    unsigned long stackHash = hash;
    AnimAudioEventLookup* result = nlBSearch<AnimAudioEventLookup, unsigned long>(stackHash, gp_AnimAudioEventTable, gNumAnimAudioEvents);
    AnimAudioEventLookup* event;
    if (result)
    {
        event = result;
    }
    else
    {
        event = NULL;
    }

    if (nlStrCmp<char>(event->szSFXType, "") != 0)
    {
        Audio::StopWorldSFXbyStr(event->szSFXType);
    }
}

/**
 * Offset/Address/Size: 0x738 | 0x8009F4E4 | size: 0xBC
 */
long FEAudio::PlayAnimAudioEvent(const char* eventName, bool)
{
    unsigned long hash = nlStringLowerHash(eventName);

    if (!AudioLoader::IsInited())
    {
        return -1;
    }

    if (!mIsEnabled)
    {
        return -1;
    }

    unsigned long stackHash = hash;
    AnimAudioEventLookup* result = nlBSearch<AnimAudioEventLookup, unsigned long>(stackHash, gp_AnimAudioEventTable, gNumAnimAudioEvents);
    AnimAudioEventLookup* event;
    if (result)
    {
        event = result;
    }
    else
    {
        event = NULL;
    }

    if (nlStrICmp<char>(event->szSFXType, "") == 0)
    {
        return -1;
    }

    Audio::PlayWorldSFXbyStr(event->szSFXType, 1.0f, 0.0f, false, true, NULL, NULL, NULL);
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

/**
 * Offset/Address/Size: 0x54 | 0x8009FA54 | size: 0x8C
 */
template <>
AnimAudioEventLookup* nlBSearch(const unsigned long& key, AnimAudioEventLookup* base, int count)
{
    unsigned long keyVal = (unsigned long)key;
    int high = count - 1;
    int low = -1;

    while ((high - low) > 1)
    {
        int mid = (high + low) / 2;
        if (base[mid].hash > keyVal)
            high = mid;
        else
            low = mid;
    }

    unsigned long cmpKey = *(const volatile unsigned long*)&key;

    unsigned long highHash = base[high].hash;
    if (highHash == cmpKey)
        return &base[high];

    if (low == -1)
        return 0;

    unsigned long lowHash = base[low].hash;
    if (lowHash == cmpKey)
        return &base[low];

    return 0;
}

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

/**
 * Offset/Address/Size: 0x0 | 0x8009FB74 | size: 0x84
 * TODO: 87.7% match - MWCC emits extsb r3,r0 before each bl nlToUpper<c>__Fc
 * (sign-extending char arg), but target loads directly into r3 with lbz.
 * Also minor scheduling diff with -O4,p (lbz for 2nd str moved before mr r31).
 * Compiler char sign-extension ABI quirk - not fixable with code changes.
 */
// TEMP removed in scratch-root for decomp iteration
template <>
int nlStrICmp(const char* a, const char* b);

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
