#include "Game/Sys/PlatStream.h"
#include "Game/Sys/GCStream.h"
#include "NL/nlSortedSlot.h"

extern "C"
{
    void sndStreamMixParameterEx(unsigned long stid, unsigned char vol, unsigned char pan, unsigned char span, unsigned char auxa, unsigned char auxb);
    void sndStreamDeactivate(unsigned long stid);
}

extern GCAudioStreaming::AudioBufferMgr g_BufferMgr;

static nlStaticSortedSlot<GCAudioStreaming::AudioStream*, 7> g_Streams;
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
 * TODO: 84.9% match - volatile counters force stack spill (stmw r27) but add
 * extra reloads. Without volatile, MWCC allocates counters to NV regs (stmw r23).
 * Remaining diffs: r29/r30 register swap (stream vs compiler-generated offset),
 * volatile extra lwz after stw, ble vs beq for cmplwi 0 (volatile interaction).
 * DWARF shows loop counter named "stream" (unsigned long) in r28.
 */
void PlatAudio::StopAllStreams()
{
    using namespace GCAudioStreaming;

    AudioStream* stream;
    AudioStreamBuffer* buffer;
    unsigned long i = 0;

    while (i < g_Streams.m_EntryCount)
    {
        stream = *g_Streams.m_pEntryLookup[i].pEntry;
        stream->m_Flags &= ~(1 << SF_Play);
        if (stream->m_State == SS_Playing)
        {
            volatile unsigned long j = 0;
            buffer = NULL;
            if (stream->m_BufferCount > 0)
                buffer = stream->m_Buffers[0];
            while (buffer != NULL)
            {
                buffer->m_Volume = 0;
                sndStreamMixParameterEx(buffer->m_StreamId, buffer->m_Volume, buffer->m_Pan, buffer->m_SurroundPan, 0, 0);
                sndStreamDeactivate(buffer->m_StreamId);
                stream->m_State = SS_Warm;
                j++;
                if (j < stream->m_BufferCount)
                    buffer = stream->m_Buffers[j];
                else
                    buffer = NULL;
            }
            stream->m_StreamPos = 0;
            stream->m_State = SS_Warm;
        }
        stream->CancelPendingReads();
        if (stream->m_Flags & (1 << SF_CoolOnStop))
        {
            stream->m_Flags &= ~(1 << SF_CoolOnStop);
            if (stream->m_State > SS_Initd)
            {
                unsigned long flags = stream->m_Flags;
                flags &= ~(1 << SF_SeriousStop);
                flags |= (1 << SF_SeriousStop);
                stream->m_Flags = flags;
                volatile unsigned long k = 0;
                buffer = NULL;
                if (stream->m_BufferCount > 0)
                    buffer = stream->m_Buffers[0];
                while (buffer != NULL)
                {
                    stream->m_BuffMgr.FreeBuffer(buffer);
                    stream->m_Buffers[k] = NULL;
                    k++;
                    if (k < stream->m_BufferCount)
                        buffer = stream->m_Buffers[k];
                    else
                        buffer = NULL;
                }
                stream->m_State = SS_Initd;
            }
        }
        i++;
    }
}
