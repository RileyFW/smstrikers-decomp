#include "Game/Sys/PlatStream.h"
#include "Game/Sys/GCStream.h"

extern GCAudioStreaming::AudioBufferMgr g_BufferMgr;

static bool g_StreamingInitd;

// /**
//  * Offset/Address/Size: 0x30 | 0x801C778C | size: 0x24
//  */
// void nlStaticSortedSlot<GCAudioStreaming::AudioStream*, 7>::GetNewEntry()
// {
// }

// /**
//  * Offset/Address/Size: 0x20 | 0x801C777C | size: 0x10
//  */
// void nlStaticSortedSlot<GCAudioStreaming::AudioStream*, 7>::FreeEntry(GCAudioStreaming::AudioStream**)
// {
// }

// /**
//  * Offset/Address/Size: 0x14 | 0x801C7770 | size: 0xC
//  */
// void nlStaticSortedSlot<GCAudioStreaming::AudioStream*, 7>::FreeLookup()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801C775C | size: 0x14
//  */
// void nlStaticSortedSlot<GCAudioStreaming::AudioStream*, 7>::ExpandLookup()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801C7748 | size: 0x14
//  */
// void GCAudioStreaming::AudioStreamBuffer::AudioStreamBuffer()
// {
// }

// /**
//  * Offset/Address/Size: 0x5B8 | 0x801C767C | size: 0xCC
//  */
// void 0x801C7748..0x801C775C | size: 0x14
// {
// }

/**
 * Offset/Address/Size: 0x574 | 0x801C7638 | size: 0x44
 */
void PlatAudio::InitStreaming()
{
    if (!g_StreamingInitd)
    {
        g_BufferMgr.Init(0x5DD80);
        g_StreamingInitd = true;
    }
}

/**
 * Offset/Address/Size: 0x208 | 0x801C72CC | size: 0x36C
 */
void PlatAudio::ShutdownStreaming()
{
}

/**
 * Offset/Address/Size: 0x1C4 | 0x801C7288 | size: 0x44
 */
void PlatAudio::ConfigureStreamBuffers(unsigned long count)
{
    g_BufferMgr.DeleteBuffers();
    g_BufferMgr.CreateBuffers(count);
}

/**
 * Offset/Address/Size: 0x1BC | 0x801C7280 | size: 0x8
 */
bool PlatAudio::IsStreamingInited()
{
    return g_StreamingInitd;
}

/**
 * Offset/Address/Size: 0x0 | 0x801C70C4 | size: 0x1BC
 */
void PlatAudio::StopAllStreams()
{
}
