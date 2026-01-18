#ifndef _AUDIOLOADER_H_
#define _AUDIOLOADER_H_

#include "types.h"
#include "Game/Audio/AudioStream.h"
#include "Game/Audio/CrowdMood.h"
#include "Game/Audio/WorldAudio.h"
#include "Game/FE/FEAudio.h"
#include "Game/GameAudio.h"
#include "Game/GameInfo.h"
#include "Game/Loader.h"
#include "Game/Render/Bowser.h"
#include "Game/Sys/audio.h"
#include "Game/Sys/GCStream.h"
#include "NL/nlConfig.h"

extern Config g_FEStreamConfig;
extern AudioStreamTrack::TrackManagerBase* g_pTrackManager;

class SoundPropAccessor;
SoundPropAccessor* GetSoundPropTableFromPlayerStadium(eStadiumID, eCharacterClass);
// void 0x80149078..0x801490F4 | size: 0x7C;

enum LoadType
{
    SND_GROUP_LOAD_NOT_LOADED = 0,
    SND_GROUP_LOAD_FROM_SAMPLE_FILE_IN_MEM = 1,
    SND_GROUP_LOAD_FROM_DISC = 2,
};

struct SndGroupData
{
    /* 0x00 */ const char* szGroupName;
    /* 0x04 */ unsigned short groupID;
    /* 0x08 */ int stackEnum;
    /* 0x0C */ int uLoadOrder;
    /* 0x10 */ LoadType loadType;
}; // total size: 0x14

extern SndGroupData sebringAudioGroups[47];

struct AudioFileData
{
    /* 0x00 */ char* szPoolFile;
    /* 0x04 */ char* szSampleFile;
    /* 0x08 */ char* szProjectFile;
    /* 0x0C */ char* szDirFile;
    /* 0x10 */ unsigned char* pool_buffer;
    /* 0x14 */ unsigned char* proj_buffer;
    /* 0x18 */ unsigned char* sdir_buffer;
    /* 0x1C */ unsigned char* samp_buffer;
    /* 0x20 */ SndGroupData* soundGroups;
    /* 0x24 */ int numSoundGroups;
}; // total size: 0x28

class LoadingManager;
class SoundStrToIDNode;
class Bowser;

class AudioLoader : public Loader
{
public:
    virtual bool StartLoad(LoadingManager*);
    // virtual bool Update() { return false; };
    virtual const char* GetName() { return "Audio Loader"; };

    void InitCrowdFromStateTransition();
    void ResetForRematch();
    void ResetForNewGame();
    void ReadEntireSampleFileIntoMem(bool);
    void LoadInGameAudioData();
    void LoadStadiumSpecificSoundGroups(eStadiumID);
    static void SetupBowserStadiumSoundTable(Bowser*);
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
    static void PlayFEMenuMusic();
    void PlayFETitleMusicWithFade();
    static void StartFEStream(const char*, bool, const char*);
    static bool IsInited();
    bool Initialize();
    void ActivateDPL2(bool, bool);
    void SetupSoundGroups();
    void GetWorldSFXTypeFromStr(const char*);
    void GetCharSFXTypeFromStr(const char*);
    void GetSFXIDFromStr(const char*, SoundStrToIDNode**);
    void SetupWorldSoundTypesAVLTree();
    void SetupCharSoundTypesAVLTree();
    void SetupSoundDefinesAVLTree();

    static bool gbDisableAudio;
    static bool gbDisableCrowd;
    static bool gbAsyncLoadEntireSampleFileIntoMemRequestMade;
    static AudioFileData sebringAudioFileData;
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
