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
 * TODO: 95.0% match - r28/r29 induction variable swap remains and both buffer
 * count zero checks compile to beq with one extra zero-init instruction.
 */
void PlatAudio::StopAllStreams()
{
    using namespace GCAudioStreaming;

    AudioStream* stream;
    AudioStreamBuffer* buffer;
    unsigned long streamIndex = 0;
    unsigned long lookupOffset = 0;

    while (streamIndex < g_Streams.m_EntryCount)
    {
        stream = *g_Streams.m_pEntryLookup[lookupOffset >> 3].pEntry;
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
                {
                    unsigned long next = j + 1;
                    j = next;
                    if (next < stream->m_BufferCount)
                        buffer = stream->m_Buffers[next];
                    else
                        buffer = NULL;
                }
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

                    {
                        unsigned long idx = k;
                        stream->m_Buffers[idx] = NULL;
                        idx = idx + 1;
                        k = idx;
                        if (idx < stream->m_BufferCount)
                            buffer = stream->m_Buffers[idx];
                        else
                            buffer = NULL;
                    }
                }

                stream->m_State = SS_Initd;
            }
        }

        lookupOffset += 8;
        streamIndex++;
    }
}
