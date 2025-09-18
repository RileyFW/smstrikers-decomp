#ifndef _SHSAVELOAD_H_
#define _SHSAVELOAD_H_

void PushNoCardMessage();
void CheckResults();
void CreateFileAndSaveCB();
void OverwriteFileAndContinueCB();
void ManageMemCardCB();
void FormatCB();
void FormatConfirmCB();
void DeleteFileCB();
void RetryCB();
void ContinueLoadingCB();
void ContinueWithoutLoadingCB();
void ContinueWithoutSavingCB();
void SaveLoadCallback(long);
void ResetEnableSaveLoadFlag();
void DidContinueWithoutOperation();

class SaveLoadScene
{
public:
    enum eSaveLoadMode
    {
        eSaveLoadMode_0 = 0
    };

    SaveLoadScene(SaveLoadScene::eSaveLoadMode);
    ~SaveLoadScene();
    void SceneCreated();
    void Update(float);
    void IsIOEnabled();
    void SetupForAboutAutoSave();
    void UpdateForAboutToSaveSlide();
    void HandleSaveLoadFinishedResult();

    static void StartSaveNow();
    static void UpdateCardRemovedFlag();
};

// class FEFinder<TLComponentInstance, 4>
// {
// public:
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
// };

// class FEFinder<TLSlide, 0>
// {
// public:
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
//     long); void Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//     InlineHasher);
// };

// class FEFinder<TLTextInstance, 3>
// {
// public:
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
//     long); void Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//     InlineHasher);
// };

#endif // _SHSAVELOAD_H_
