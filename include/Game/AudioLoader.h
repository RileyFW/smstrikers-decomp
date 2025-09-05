#ifndef _AUDIOLOADER_H_
#define _AUDIOLOADER_H_

#include "types.h"

// void GetSoundPropTableFromPlayerStadium(eStadiumID, eCharacterClass);
// void 0x80149078..0x801490F4 | size: 0x7C;

class LoadingManager;
class SoundStrToIDNode;
class Bowser;

enum eStadiumID
{
    eStadiumID_0 = 0
};

class AudioLoader
{
public:
    void InitCrowdFromStateTransition();
    void ResetForRematch();
    void ResetForNewGame();
    void ReadEntireSampleFileIntoMem(bool);
    void LoadInGameAudioData();
    void LoadStadiumSpecificSoundGroups(eStadiumID);
    void SetupBowserStadiumSoundTable(Bowser*);
    void SetupCharStadiumSoundTable();
    void SetupPostPhysicsCameraLoad();
    void UnloadInGame();
    void LoadInGame();
    void LoadPermanentSoundGroups(bool);
    void LoadFEButtonSoundGroup();
    void LoadNLGDialogueGroup(bool);
    void LoadNintendoDialogueGroup(bool);
    void LoadFEAudioData(bool);
    void UnloadFE();
    void LoadFE(bool);
    void SetupSoundBuffers();
    void StopStreaming();
    void StopPauseMenuMusic();
    void PlayPauseMenuMusic();
    void PlayLoadLoopMusic();
    void PlayFEMenuMusic();
    void PlayFETitleMusicWithFade();
    void StartFEStream(const char*, bool, const char*);
    static bool IsInited();
    void Initialize();
    void StartLoad(LoadingManager*);
    void ActivateDPL2(bool, bool);
    void SetupSoundGroups();
    void GetWorldSFXTypeFromStr(const char*);
    void GetCharSFXTypeFromStr(const char*);
    void GetSFXIDFromStr(const char*, SoundStrToIDNode**);
    void SetupWorldSoundTypesAVLTree();
    void SetupCharSoundTypesAVLTree();
    void SetupSoundDefinesAVLTree();
};


// class GCAudioStreaming
// {
// public:
//     void StereoAudioStream::~StereoAudioStream();
//     void AudioStream::Destructor();
//     void AudioStream::Purge();
//     void AudioStream::~AudioStream();
//     void AudioStream::WarmReadDone(GCAudioStreaming::AudioStreamBuffer*);
// };


// class AVLTreeBase<int, SoundStrToIDNode*, BasicSlotPool<AVLTreeEntry<int, SoundStrToIDNode*>>, DefaultKeyCompare<int>>
// {
// public:
//     void Clear();
//     void DestroyTree(void (AVLTreeBase<int, SoundStrToIDNode*, BasicSlotPool<AVLTreeEntry<int, SoundStrToIDNode*>>, DefaultKeyCompare<int>>::*)(AVLTreeEntry<int, SoundStrToIDNode*>*));
//     void PostorderTraversal(AVLTreeEntry<int, SoundStrToIDNode*>*, void (AVLTreeBase<int, SoundStrToIDNode*, BasicSlotPool<AVLTreeEntry<int, SoundStrToIDNode*>>, DefaultKeyCompare<int>>::*)(AVLTreeEntry<int, SoundStrToIDNode*>*));
//     void CastUp(AVLTreeNode*) const;
//     void DeleteEntry(AVLTreeEntry<int, SoundStrToIDNode*>*);
//     void ~AVLTreeBase();
//     void CompareNodes(AVLTreeNode*, AVLTreeNode*);
//     void CompareKey(void*, AVLTreeNode*);
//     void AllocateEntry(void*, void*);
// };


// class nlDLRingIsEnd<DLListEntry<GCAudioStreaming
// {
// public:
//     void StereoAudioStream*>>(DLListEntry<GCAudioStreaming::StereoAudioStream*>*, DLListEntry<GCAudioStreaming::StereoAudioStream*>*);
// };


// class nlDLRingGetStart<DLListEntry<GCAudioStreaming
// {
// public:
//     void StereoAudioStream*>>(DLListEntry<GCAudioStreaming::StereoAudioStream*>*);
// };


// class nlDLRingRemove<DLListEntry<GCAudioStreaming
// {
// public:
//     void StereoAudioStream*>>(DLListEntry<GCAudioStreaming::StereoAudioStream*>**, DLListEntry<GCAudioStreaming::StereoAudioStream*>*);
// };


// class nlAVLTreeSlotPool<int, SoundStrToIDNode*, DefaultKeyCompare<int>>
// {
// public:
//     void ~nlAVLTreeSlotPool();
// };

#endif // _AUDIOLOADER_H_
