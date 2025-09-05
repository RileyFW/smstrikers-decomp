#include "Game/AudioLoader.h"

/**
 * Offset/Address/Size: 0x0 | 0x80143DCC | size: 0x68
 */
void AudioLoader::InitCrowdFromStateTransition()
{
}

/**
 * Offset/Address/Size: 0x68 | 0x80143E34 | size: 0xDC
 */
void AudioLoader::ResetForRematch()
{
}

/**
 * Offset/Address/Size: 0x144 | 0x80143F10 | size: 0x64
 */
void AudioLoader::ResetForNewGame()
{
}

/**
 * Offset/Address/Size: 0x1A8 | 0x80143F74 | size: 0x50
 */
void AudioLoader::ReadEntireSampleFileIntoMem(bool)
{
}

/**
 * Offset/Address/Size: 0x1F8 | 0x80143FC4 | size: 0x6EC
 */
void AudioLoader::LoadInGameAudioData()
{
}

/**
 * Offset/Address/Size: 0x8E4 | 0x801446B0 | size: 0x350
 */
void AudioLoader::LoadStadiumSpecificSoundGroups(eStadiumID)
{
}

/**
 * Offset/Address/Size: 0xC34 | 0x80144A00 | size: 0x54
 */
void AudioLoader::SetupBowserStadiumSoundTable(Bowser*)
{
}

/**
 * Offset/Address/Size: 0xC88 | 0x80144A54 | size: 0x308
 */
void AudioLoader::SetupCharStadiumSoundTable()
{
}

/**
 * Offset/Address/Size: 0xF90 | 0x80144D5C | size: 0x1E0
 */
void GetSoundPropTableFromPlayerStadium(eStadiumID, eCharacterClass)
{
}

/**
 * Offset/Address/Size: 0x1170 | 0x80144F3C | size: 0x19C
 */
void AudioLoader::SetupPostPhysicsCameraLoad()
{
}

/**
 * Offset/Address/Size: 0x130C | 0x801450D8 | size: 0x1E8
 */
void AudioLoader::UnloadInGame()
{
}

/**
 * Offset/Address/Size: 0x14F4 | 0x801452C0 | size: 0x13C
 */
void AudioLoader::LoadInGame()
{
}

/**
 * Offset/Address/Size: 0x1630 | 0x801453FC | size: 0x75C
 */
void AudioLoader::LoadPermanentSoundGroups(bool)
{
}

/**
 * Offset/Address/Size: 0x1D8C | 0x80145B58 | size: 0x90
 */
void AudioLoader::LoadFEButtonSoundGroup()
{
}

/**
 * Offset/Address/Size: 0x1E1C | 0x80145BE8 | size: 0x9C
 */
void AudioLoader::LoadNLGDialogueGroup(bool)
{
}

/**
 * Offset/Address/Size: 0x1EB8 | 0x80145C84 | size: 0x9C
 */
void AudioLoader::LoadNintendoDialogueGroup(bool)
{
}

/**
 * Offset/Address/Size: 0x1F54 | 0x80145D20 | size: 0x108
 */
void AudioLoader::LoadFEAudioData(bool)
{
}

/**
 * Offset/Address/Size: 0x205C | 0x80145E28 | size: 0x88
 */
void AudioLoader::UnloadFE()
{
}

/**
 * Offset/Address/Size: 0x20E4 | 0x80145EB0 | size: 0x298
 */
void AudioLoader::LoadFE(bool)
{
}

/**
 * Offset/Address/Size: 0x237C | 0x80146148 | size: 0x38
 */
void AudioLoader::SetupSoundBuffers()
{
}

/**
 * Offset/Address/Size: 0x23B4 | 0x80146180 | size: 0x20
 */
void AudioLoader::StopStreaming()
{
}

/**
 * Offset/Address/Size: 0x23D4 | 0x801461A0 | size: 0x114
 */
void AudioLoader::StopPauseMenuMusic()
{
}

/**
 * Offset/Address/Size: 0x24E8 | 0x801462B4 | size: 0x308
 */
void AudioLoader::PlayPauseMenuMusic()
{
}

/**
 * Offset/Address/Size: 0x27F0 | 0x801465BC | size: 0x3E4
 */
void AudioLoader::PlayLoadLoopMusic()
{
}

/**
 * Offset/Address/Size: 0x2BD4 | 0x801469A0 | size: 0x300
 */
void AudioLoader::PlayFEMenuMusic()
{
}

/**
 * Offset/Address/Size: 0x2ED4 | 0x80146CA0 | size: 0x300
 */
void AudioLoader::PlayFETitleMusicWithFade()
{
}

/**
 * Offset/Address/Size: 0x31D4 | 0x80146FA0 | size: 0x2F0
 */
void AudioLoader::StartFEStream(const char*, bool, const char*)
{
}

/**
 * Offset/Address/Size: 0x34C4 | 0x80147290 | size: 0x34
 */
bool AudioLoader::IsInited()
{
    return false;
}

/**
 * Offset/Address/Size: 0x34F8 | 0x801472C4 | size: 0x74
 */
void AudioLoader::Initialize()
{
}

/**
 * Offset/Address/Size: 0x356C | 0x80147338 | size: 0x80
 */
void AudioLoader::StartLoad(LoadingManager*)
{
}

/**
 * Offset/Address/Size: 0x35EC | 0x801473B8 | size: 0x408
 */
void AudioLoader::ActivateDPL2(bool, bool)
{
}

/**
 * Offset/Address/Size: 0x39F4 | 0x801477C0 | size: 0x104
 */
void AudioLoader::SetupSoundGroups()
{
}

/**
 * Offset/Address/Size: 0x3AF8 | 0x801478C4 | size: 0xB4
 */
void AudioLoader::GetWorldSFXTypeFromStr(const char*)
{
}

/**
 * Offset/Address/Size: 0x3BAC | 0x80147978 | size: 0xB4
 */
void AudioLoader::GetCharSFXTypeFromStr(const char*)
{
}

/**
 * Offset/Address/Size: 0x3C60 | 0x80147A2C | size: 0xE0
 */
void AudioLoader::GetSFXIDFromStr(const char*, SoundStrToIDNode**)
{
}

/**
 * Offset/Address/Size: 0x3D40 | 0x80147B0C | size: 0xB4
 */
void AudioLoader::SetupWorldSoundTypesAVLTree()
{
}

/**
 * Offset/Address/Size: 0x3DF4 | 0x80147BC0 | size: 0x154
 */
void AudioLoader::SetupCharSoundTypesAVLTree()
{
}

/**
 * Offset/Address/Size: 0x3F48 | 0x80147D14 | size: 0x14C
 */
void AudioLoader::SetupSoundDefinesAVLTree()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80147E60 | size: 0x70
 */
void GCAudioStreaming::StereoAudioStream::~StereoAudioStream()
{
}

/**
 * Offset/Address/Size: 0x70 | 0x80147ED0 | size: 0x2D4
 */
void GCAudioStreaming::AudioStream::Destructor()
{
}

/**
 * Offset/Address/Size: 0x344 | 0x801481A4 | size: 0xC
 */
void GCAudioStreaming::AudioStream::Purge()
{
}

/**
 * Offset/Address/Size: 0x350 | 0x801481B0 | size: 0x48
 */
void GCAudioStreaming::AudioStream::~AudioStream()
{
}

/**
 * Offset/Address/Size: 0x398 | 0x801481F8 | size: 0xD4
 */
void GCAudioStreaming::AudioStream::WarmReadDone(GCAudioStreaming::AudioStreamBuffer*)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801482CC | size: 0x58
 */
void AVLTreeBase<int, SoundStrToIDNode*, BasicSlotPool<AVLTreeEntry<int, SoundStrToIDNode*> >, DefaultKeyCompare<int> >::Clear()
{
}

/**
 * Offset/Address/Size: 0x58 | 0x80148324 | size: 0x64
 */
void AVLTreeBase<int, SoundStrToIDNode*, BasicSlotPool<AVLTreeEntry<int, SoundStrToIDNode*> >, DefaultKeyCompare<int> >::DestroyTree(
    void (AVLTreeBase<int, SoundStrToIDNode*, BasicSlotPool<AVLTreeEntry<int, SoundStrToIDNode*> >, DefaultKeyCompare<int> >::*)(
        AVLTreeEntry<int, SoundStrToIDNode*>*))
{
}

/**
 * Offset/Address/Size: 0xBC | 0x80148388 | size: 0x758
 */
void AVLTreeBase<int, SoundStrToIDNode*, BasicSlotPool<AVLTreeEntry<int, SoundStrToIDNode*> >, DefaultKeyCompare<int> >::PostorderTraversal(
    AVLTreeEntry<int, SoundStrToIDNode*>*,
    void (AVLTreeBase<int, SoundStrToIDNode*, BasicSlotPool<AVLTreeEntry<int, SoundStrToIDNode*> >, DefaultKeyCompare<int> >::*)(
        AVLTreeEntry<int, SoundStrToIDNode*>*))
{
}

/**
 * Offset/Address/Size: 0x814 | 0x80148AE0 | size: 0x8
 */
void AVLTreeBase<int, SoundStrToIDNode*, BasicSlotPool<AVLTreeEntry<int, SoundStrToIDNode*> >, DefaultKeyCompare<int> >::CastUp(
    AVLTreeNode*) const
{
}

/**
 * Offset/Address/Size: 0x81C | 0x80148AE8 | size: 0x10
 */
void AVLTreeBase<int, SoundStrToIDNode*, BasicSlotPool<AVLTreeEntry<int, SoundStrToIDNode*> >, DefaultKeyCompare<int> >::DeleteEntry(
    AVLTreeEntry<int, SoundStrToIDNode*>*)
{
}

/**
 * Offset/Address/Size: 0x82C | 0x80148AF8 | size: 0x7C
 */
void AVLTreeBase<int, SoundStrToIDNode*, BasicSlotPool<AVLTreeEntry<int, SoundStrToIDNode*> >, DefaultKeyCompare<int> >::~AVLTreeBase()
{
}

/**
 * Offset/Address/Size: 0x8A8 | 0x80148B74 | size: 0x2C
 */
void AVLTreeBase<int, SoundStrToIDNode*, BasicSlotPool<AVLTreeEntry<int, SoundStrToIDNode*> >, DefaultKeyCompare<int> >::CompareNodes(
    AVLTreeNode*, AVLTreeNode*)
{
}

/**
 * Offset/Address/Size: 0x8D4 | 0x80148BA0 | size: 0x2C
 */
void AVLTreeBase<int, SoundStrToIDNode*, BasicSlotPool<AVLTreeEntry<int, SoundStrToIDNode*> >, DefaultKeyCompare<int> >::CompareKey(
    void*, AVLTreeNode*)
{
}

/**
 * Offset/Address/Size: 0x900 | 0x80148BCC | size: 0xA0
 */
void AVLTreeBase<int, SoundStrToIDNode*, BasicSlotPool<AVLTreeEntry<int, SoundStrToIDNode*> >, DefaultKeyCompare<int> >::AllocateEntry(void*,
    void*)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80148C6C | size: 0x40C
 */
void 0x80149078..0x801490F4 | size : 0x7C
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80149078 | size: 0x20
 */
void nlDLRingIsEnd<DLListEntry<GCAudioStreaming::StereoAudioStream*> >(DLListEntry<GCAudioStreaming::StereoAudioStream*>*,
    DLListEntry<GCAudioStreaming::StereoAudioStream*>*)
{
}

/**
 * Offset/Address/Size: 0x20 | 0x80149098 | size: 0x18
 */
void nlDLRingGetStart<DLListEntry<GCAudioStreaming::StereoAudioStream*> >(DLListEntry<GCAudioStreaming::StereoAudioStream*>*)
{
}

/**
 * Offset/Address/Size: 0x38 | 0x801490B0 | size: 0x44
 */
void nlDLRingRemove<DLListEntry<GCAudioStreaming::StereoAudioStream*> >(DLListEntry<GCAudioStreaming::StereoAudioStream*>**,
    DLListEntry<GCAudioStreaming::StereoAudioStream*>*)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801490F4 | size: 0x60
 */
void nlAVLTreeSlotPool<int, SoundStrToIDNode*, DefaultKeyCompare<int> >::~nlAVLTreeSlotPool()
{
}
