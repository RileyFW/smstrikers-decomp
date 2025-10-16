#ifndef _STREAMTRACK_H_
#define _STREAMTRACK_H_

// namespace AudioStreamTrack
// {
// class TrackManagerBase
// {
// public:
//     void Update(float);

//     class FadeManager
//     {
//     public:
//         void UpdateFade(STREAM_FADE_CTRL*);
//     };
// };

// class StreamTrack
// {
// public:
//     void Update(float);
//     void PlayStream(unsigned long, float, bool, unsigned long, unsigned long, const char*, Audio::MasterVolume::VOLUME_GROUP);
//     void QueueStream(unsigned long, float, bool, unsigned long, const char*, Audio::MasterVolume::VOLUME_GROUP);
//     void ProcessNewHeadStream();
//     void StopHead(unsigned long);
//     void Stop(unsigned long);
//     void StopQStream(AudioStreamTrack::StreamTrack::QUEUED_STREAM*);
//     void StopStream(GCAudioStreaming::StereoAudioStream*, bool);
//     void FadeOutDone(AudioStreamTrack::StreamTrack::QUEUED_STREAM*);
//     void FadeOutDoneStartNext(AudioStreamTrack::StreamTrack::QUEUED_STREAM*);
//     void Pause(unsigned long, bool);
//     void Resume();
//     void AttachStream(GCAudioStreaming::StereoAudioStream*, Audio::MasterVolume::VOLUME_GROUP, unsigned long, unsigned long, bool, bool);
// }

// }; // namespace AudioStreamTrack

// class Function0<void>
// {
// public:
//     void FunctorImpl<BindExp2<void, Detail::MemFunImpl<void, void (AudioStreamTrack::StreamTrack::*)(AudioStreamTrack::StreamTrack::QUEUED_STREAM*)>, AudioStreamTrack::StreamTrack*, AudioStreamTrack::StreamTrack::QUEUED_STREAM*>>::~FunctorImpl();
//     void FunctorImpl<BindExp2<void, Detail::MemFunImpl<void, void (AudioStreamTrack::StreamTrack::*)(AudioStreamTrack::StreamTrack::QUEUED_STREAM*)>, AudioStreamTrack::StreamTrack*, AudioStreamTrack::StreamTrack::QUEUED_STREAM*>>::operator()();
//     void FunctorImpl<BindExp2<void, Detail::MemFunImpl<void, void (AudioStreamTrack::StreamTrack::*)(AudioStreamTrack::StreamTrack::QUEUED_STREAM*)>, AudioStreamTrack::StreamTrack*, AudioStreamTrack::StreamTrack::QUEUED_STREAM*>>::Clone() const;
// };

// class DLListContainerBase<AudioStreamTrack
// {
// public:
//     void TrackManagerBase::FadeManager::STREAM_FADE_CTRL, BasicSlotPool<DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>>>::AllocateAtEnd(unsigned long*);
// };

// class ListContainerBase<AudioStreamTrack
// {
// public:
//     void TrackManagerBase::StreamFileLookup::STREAM_FILE_LIST_LOOKUP, BasicSlotPoolHigh<ListEntry<AudioStreamTrack::TrackManagerBase::StreamFileLookup::STREAM_FILE_LIST_LOOKUP>>>::DeleteEntry(ListEntry<AudioStreamTrack::TrackManagerBase::StreamFileLookup::STREAM_FILE_LIST_LOOKUP>*);
// };

// class BasicSlotPoolHigh<ListEntry<AudioStreamTrack
// {
// public:
//     void TrackManagerBase::StreamFileLookup::STREAM_FILE_LIST_LOOKUP>>::allocFN(unsigned long);
//     void TrackManagerBase::StreamFileLookup::STREAM_FILE_LIST_LOOKUP>>::freeFN(void*);
// };

// class nlQSort<AudioStreamTrack
// {
// public:
//     void TrackManagerBase::StreamFileLookup::STREAM_FILE_LOOKUP>(AudioStreamTrack::TrackManagerBase::StreamFileLookup::STREAM_FILE_LOOKUP*, int, int (*)(const AudioStreamTrack::TrackManagerBase::StreamFileLookup::STREAM_FILE_LOOKUP*, const AudioStreamTrack::TrackManagerBase::StreamFileLookup::STREAM_FILE_LOOKUP*));
// };

// class nlDefaultQSortComparer<AudioStreamTrack
// {
// public:
//     void TrackManagerBase::StreamFileLookup::STREAM_FILE_LOOKUP>(const AudioStreamTrack::TrackManagerBase::StreamFileLookup::STREAM_FILE_LOOKUP*, const AudioStreamTrack::TrackManagerBase::StreamFileLookup::STREAM_FILE_LOOKUP*);
// };

// class nlBSearch<AudioStreamTrack
// {
// public:
//     void TrackManagerBase::StreamFileLookup::STREAM_FILE_LOOKUP, unsigned long>(const unsigned long&, AudioStreamTrack::TrackManagerBase::StreamFileLookup::STREAM_FILE_LOOKUP*, int);
// };

// class nlWalkList<ListEntry<AudioStreamTrack
// {
// public:
//     void TrackManagerBase::StreamFileLookup::STREAM_FILE_LIST_LOOKUP>, ListContainerBase<AudioStreamTrack::TrackManagerBase::StreamFileLookup::STREAM_FILE_LIST_LOOKUP, BasicSlotPoolHigh<ListEntry<AudioStreamTrack::TrackManagerBase::StreamFileLookup::STREAM_FILE_LIST_LOOKUP>>>>(ListEntry<AudioStreamTrack::TrackManagerBase::StreamFileLookup::STREAM_FILE_LIST_LOOKUP>*, ListContainerBase<AudioStreamTrack::TrackManagerBase::StreamFileLookup::STREAM_FILE_LIST_LOOKUP, BasicSlotPoolHigh<ListEntry<AudioStreamTrack::TrackManagerBase::StreamFileLookup::STREAM_FILE_LIST_LOOKUP>>>*, void (ListContainerBase<AudioStreamTrack::TrackManagerBase::StreamFileLookup::STREAM_FILE_LIST_LOOKUP, BasicSlotPoolHigh<ListEntry<AudioStreamTrack::TrackManagerBase::StreamFileLookup::STREAM_FILE_LIST_LOOKUP>>>::*)(ListEntry<AudioStreamTrack::TrackManagerBase::StreamFileLookup::STREAM_FILE_LIST_LOOKUP>*));
// };

// class nlListAddEnd<ListEntry<AudioStreamTrack
// {
// public:
//     void TrackManagerBase::StreamFileLookup::STREAM_FILE_LIST_LOOKUP>>(ListEntry<AudioStreamTrack::TrackManagerBase::StreamFileLookup::STREAM_FILE_LIST_LOOKUP>**, ListEntry<AudioStreamTrack::TrackManagerBase::StreamFileLookup::STREAM_FILE_LIST_LOOKUP>**, ListEntry<AudioStreamTrack::TrackManagerBase::StreamFileLookup::STREAM_FILE_LIST_LOOKUP>*);
// };

// class nlDLRingRemoveEnd<DLListEntry<AudioStreamTrack
// {
// public:
//     void StreamTrack::QUEUED_STREAM>>(DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>**);
// };

// class nlDLRingRemoveStart<DLListEntry<AudioStreamTrack
// {
// public:
//     void StreamTrack::QUEUED_STREAM>>(DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>**);
// };

// class nlDLRingIsEnd<DLListEntry<AudioStreamTrack
// {
// public:
//     void StreamTrack::QUEUED_STREAM>>(DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>*, DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>*);
// };

// class nlDLRingRemove<DLListEntry<AudioStreamTrack
// {
// public:
//     void TrackManagerBase::FadeManager::STREAM_FADE_CTRL>>(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>**, DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*);
//     void StreamTrack::QUEUED_STREAM>>(DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>**, DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>*);
// };

// class nlDLRingAddEnd<DLListEntry<AudioStreamTrack
// {
// public:
//     void TrackManagerBase::FadeManager::STREAM_FADE_CTRL>>(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>**, DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*);
//     void StreamTrack::QUEUED_STREAM>>(DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>**, DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>*);
// };

// class nlDLRingAddEnd<DLListEntry<GCAudioStreaming
// {
// public:
//     void StereoAudioStream*>>(DLListEntry<GCAudioStreaming::StereoAudioStream*>**, DLListEntry<GCAudioStreaming::StereoAudioStream*>*);
// };

// class nlDLRingAddStart<DLListEntry<GCAudioStreaming
// {
// public:
//     void StereoAudioStream*>>(DLListEntry<GCAudioStreaming::StereoAudioStream*>**, DLListEntry<GCAudioStreaming::StereoAudioStream*>*);
// };

// class nlDLRingAddStart<DLListEntry<AudioStreamTrack
// {
// public:
//     void StreamTrack::QUEUED_STREAM>>(DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>**, DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>*);
//     void TrackManagerBase::FadeManager::STREAM_FADE_CTRL>>(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>**, DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*);
// };

// class Bind<void, Detail
// {
// public:
//     void MemFunImpl<void, void (AudioStreamTrack::StreamTrack::*)(AudioStreamTrack::StreamTrack::QUEUED_STREAM*)>, AudioStreamTrack::StreamTrack*, AudioStreamTrack::StreamTrack::QUEUED_STREAM*>(Detail::MemFunImpl<void, void (AudioStreamTrack::StreamTrack::*)(AudioStreamTrack::StreamTrack::QUEUED_STREAM*)>, AudioStreamTrack::StreamTrack* const&, AudioStreamTrack::StreamTrack::QUEUED_STREAM* const&);
// };

// class MemFun<AudioStreamTrack
// {
// public:
//     void StreamTrack, void, AudioStreamTrack::StreamTrack::QUEUED_STREAM*>(void (AudioStreamTrack::StreamTrack::*)(AudioStreamTrack::StreamTrack::QUEUED_STREAM*));
// };

#endif // _STREAMTRACK_H_
