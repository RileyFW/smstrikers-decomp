#ifndef _AUDIOLOADER_H_
#define _AUDIOLOADER_H_

#include "Game/GameInfo.h"
#include "Game/Loader/LoadingManager.h"

void GetSoundPropTableFromPlayerStadium(eStadiumID, eCharacterClass);
// void 0x80149078..0x801490F4 | size: 0x7C;

namespace GCAudioStreaming
{

class AudioStreamBuffer
{
    ~AudioStreamBuffer();
};

class StereoAudioStream
{
    ~StereoAudioStream();
};

class AudioStream
{
    ~AudioStream();
    void WarmReadDone(AudioStreamBuffer*);
    void Purge();
    void Destructor();
};

}; // namespace GCAudioStreaming

class SoundStrToIDNode;

class AudioLoader
{
public:
    void SetupSoundDefinesAVLTree();
    void SetupCharSoundTypesAVLTree();
    void SetupWorldSoundTypesAVLTree();
    void GetSFXIDFromStr(const char*, SoundStrToIDNode**);
    void GetCharSFXTypeFromStr(const char*);
    void GetWorldSFXTypeFromStr(const char*);
    void SetupSoundGroups();
    void ActivateDPL2(bool, bool);
    void StartLoad(LoadingManager*);
    void Initialize();
    void IsInited();
    void StartFEStream(const char*, bool, const char*);
    void PlayFETitleMusicWithFade();
    void PlayFEMenuMusic();
    void PlayLoadLoopMusic();
    void PlayPauseMenuMusic();
    void StopPauseMenuMusic();
    void StopStreaming();
    void SetupSoundBuffers();
    void LoadFE(bool);
    void UnloadFE();
    void LoadFEAudioData(bool);
    void LoadNintendoDialogueGroup(bool);
    void LoadNLGDialogueGroup(bool);
    void LoadFEButtonSoundGroup();
    void LoadPermanentSoundGroups(bool);
    void LoadInGame();
    void UnloadInGame();
    void SetupPostPhysicsCameraLoad();
    void SetupCharStadiumSoundTable();
    void SetupBowserStadiumSoundTable(Bowser*);
    void LoadStadiumSpecificSoundGroups(eStadiumID);
    void LoadInGameAudioData();
    void ReadEntireSampleFileIntoMem(bool);
    void ResetForNewGame();
    void ResetForRematch();
    void InitCrowdFromStateTransition();
};

// class AVLTreeBase<int, SoundStrToIDNode*, BasicSlotPool<AVLTreeEntry<int, SoundStrToIDNode*>>, DefaultKeyCompare<int>>
// {
// public:
//     void AllocateEntry(void*, void*);
//     void CompareKey(void*, AVLTreeNode*);
//     void CompareNodes(AVLTreeNode*, AVLTreeNode*);
//     void ~AVLTreeBase();
//     void DeleteEntry(AVLTreeEntry<int, SoundStrToIDNode*>*);
//     void CastUp(AVLTreeNode*) const;
//     void PostorderTraversal(AVLTreeEntry<int, SoundStrToIDNode*>*, void (AVLTreeBase<int, SoundStrToIDNode*, BasicSlotPool<AVLTreeEntry<int, SoundStrToIDNode*>>, DefaultKeyCompare<int>>::*)(AVLTreeEntry<int, SoundStrToIDNode*>*));
//     void DestroyTree(void (AVLTreeBase<int, SoundStrToIDNode*, BasicSlotPool<AVLTreeEntry<int, SoundStrToIDNode*>>, DefaultKeyCompare<int>>::*)(AVLTreeEntry<int, SoundStrToIDNode*>*));
//     void Clear();
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
