#ifndef _GCSTREAM_H_
#define _GCSTREAM_H_

// void ___blank(const char*, ...);
// void 0x8028D52C..0x8028D530 | size: 0x4;

// class GCAudioStreaming
// {
// public:
//     void MonoAudioStream::_AsyncCancelCB(nlFile*, void*, unsigned int, unsigned long, void (*)(nlFile*, void*, unsigned int, unsigned long));
//     void MonoAudioStream::CancelPendingReads();
//     void MonoAudioStream::GetUpdateReadLength();
//     void AudioStreamBuffer::_UpdateHandler(void*, unsigned long, void*, unsigned long, unsigned long);
//     void StereoAudioStream::GetUpdateReadLength();
//     void StereoAudioStream::_InterleavedHdrReadCB(nlFile*, void*, unsigned int, unsigned long);
//     void StereoAudioStream::_AsyncCancelCB(nlFile*, void*, unsigned int, unsigned long, void (*)(nlFile*, void*, unsigned int, unsigned long));
//     void StereoAudioStream::CancelPendingReads();
//     void AudioStream::Stop();
//     void AudioStream::_HdrReadCB(nlFile*, void*, unsigned int, unsigned long);
//     void AudioStream::_WarmReadCB(nlFile*, void*, unsigned int, unsigned long);
//     void AudioStream::_UpdateReadCB(nlFile*, void*, unsigned int, unsigned long);
//     void MonoAudioStream::Warm(bool);
//     void MonoAudioStream::DoUpdateRead(unsigned long, unsigned long, unsigned long, unsigned long, GCAudioStreaming::AudioStreamBuffer*);
//     void StereoAudioStream::Warm(bool);
//     void StereoAudioStream::InterleavedHdrReadCB(nlFile*, void*, unsigned int);
//     void StereoAudioStream::DoUpdateRead(unsigned long, unsigned long, unsigned long, unsigned long, GCAudioStreaming::AudioStreamBuffer*);
//     void AudioBufferMgr::Init(unsigned long);
//     void AudioBufferMgr::CreateBuffers(unsigned long);
//     void AudioBufferMgr::DeleteBuffers();
//     void AudioBufferMgr::FreeBuffer(GCAudioStreaming::AudioStreamBuffer*);
// };

namespace GCAudioStreaming
{

class AudioStreamBuffer
{

    /* 0x00 */ unsigned char* m_MRAMBuffer;   // offset 0x0, size 0x4
    /* 0x04 */ unsigned long m_BufferSize;    // offset 0x4, size 0x4
    /* 0x08 */ unsigned long m_BufferSamples; // offset 0x8, size 0x4
    /* 0x0C */ unsigned long m_StreamId;      // offset 0xC, size 0x4
    /* 0x10 */ unsigned long m_UpdateOffset;  // offset 0x10, size 0x4
    /* 0x14 */ class AudioStream* m_pStream;  // offset 0x14, size 0x4
    /* 0x18 */ unsigned char m_Volume;        // offset 0x18, size 0x1
    /* 0x19 */ signed char m_Pan;             // offset 0x19, size 0x1
    /* 0x1A */ unsigned char m_SurroundPan;   // offset 0x1A, size 0x1
    /* 0x1B */ unsigned char m_bLPFOn;        // offset 0x1B, size 0x1
    /* 0x1C */ unsigned short m_LPFFreq;      // offset 0x1C, size 0x2
}; // total size: 0x20

class AudioBufferMgr
{
public:
    void Init(unsigned long);
    void CreateBuffers(unsigned long);
    void DeleteBuffers();
    void FreeBuffer(GCAudioStreaming::AudioStreamBuffer*);

    /* 0x000 */ unsigned long m_PoolSize;         // offset 0x0, size 0x4
    /* 0x004 */ unsigned char* m_MRAMBuffer;      // offset 0x4, size 0x4
    /* 0x008 */ AudioStreamBuffer m_Buffers[8];   // offset 0x8, size 0x100
    /* 0x108 */ unsigned char m_ADPCMHdrMem[128]; // offset 0x108, size 0x80
    /* 0x188 */ unsigned long m_BuffersFree;      // offset 0x188, size 0x4
    /* 0x18C */ unsigned long m_BufferCount;      // offset 0x18C, size 0x4
    /* 0x190 */ unsigned long m_BufferSize;       // offset 0x190, size 0x4
}; // total size: 0x194

} // namespace GCAudioStreaming

#endif // _GCSTREAM_H_
