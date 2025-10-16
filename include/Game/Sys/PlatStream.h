#ifndef _PLATSTREAM_H_
#define _PLATSTREAM_H_

class PlatAudio
{
public:
    void InitStreaming();
    void ShutdownStreaming();
    void ConfigureStreamBuffers(unsigned long);
    void IsStreamingInited();
    void StopAllStreams();
};

// class GCAudioStreaming
// {
// public:
//     void AudioStreamBuffer::AudioStreamBuffer();
// };

// class nlStaticSortedSlot<GCAudioStreaming
// {
// public:
//     void AudioStream*, 7>::GetNewEntry();
//     void AudioStream*, 7>::FreeEntry(GCAudioStreaming::AudioStream**);
//     void AudioStream*, 7>::FreeLookup();
//     void AudioStream*, 7>::ExpandLookup();
// };

#endif // _PLATSTREAM_H_
