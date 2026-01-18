#ifndef _FEPOPUPMENU_H_
#define _FEPOPUPMENU_H_

#include "Game/FE/fePresentation.h"

// void CastToSomeType<TLInstance>(TLInstance*, void*);
// void CastToSomeType<TLSlide>(TLSlide*, void*);
// void FindItemByHashID<TLInstance>(TLInstance*, unsigned long);
// void FindItemByHashID<TLSlide>(TLSlide*, unsigned long);

enum ePopupMenu
{
    INVALID_TYPE = -1,
    POPUP_END_CUP = 0,
    POPUP_FLOWER_CUP_LOCKED = 1,
    POPUP_STAR_CUP_LOCKED = 2,
    POPUP_BOWSER_CUP_LOCKED = 3,
    POPUP_SUPER_CUPS_LOCKED = 4,
    POPUP_INGAME_FORFEIT_MATCH = 5,
    POPUP_INGAME_QUIT_MATCH = 6,
    POPUP_INGAME_QUIT_STRIKERS_101 = 7,
    POPUP_NO_SIDES_CHOSEN = 8,
    POPUP_NO_HUMAN_TOURNAMENT = 9,
    POPUP_START_NEW_CUP = 10,
    POPUP_START_NEW_TOURNAMENT = 11,
    POPUP_FILLALLSLOTS = 12,
    POPUP_REVERT_OPTION_CHANGES = 13,
    POPUP_TOURNEY_OVER = 14,
    POPUP_NO_FORFEIT = 15,
    POPUP_REALLY_OVERWRITE = 16,
    POPUP_APPLYING_AUDIO = 17,
    POPUP_NO_MEMCARD = 18,
    POPUP_MEMCARD_CORRUPTED = 19,
    POPUP_MEMCARD_WRONGFORMAT = 20,
    POPUP_FILE_CORRUPTED = 21,
    POPUP_MEMCARD_DAMAGED = 22,
    POPUP_WRONG_DEVICE = 23,
    POPUP_NOT_ENOUGH_SPACE = 24,
    POPUP_NOT_ENOUGH_SPACE_CANMANAGE = 25,
    POPUP_ABOUTTOSAVE = 26,
    POPUP_NOTSAMECARD = 27,
    POPUP_MEMCARD_ASK_SAVE_OVERWRITE = 28,
};

class FEPopupMenu
{
public:
    void SetOptionTextColourOnCurrent(bool);
    void ResizeHighlight();
    void CentrePopup(float, float);
    void SetPositions();
    void Update(float);
    void SceneCreated();
    ~FEPopupMenu();
    FEPopupMenu();
    static void Create(ePopupMenu);

    /* 0x0 */ TLSlide* m_slides;
};

// class FEFinder<TLTextInstance, 3>
// {
// public:
//     void Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
//     void _Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
//     long); void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long); void
//     _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
// };

// class FEFinder<TLImageInstance, 2>
// {
// public:
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
// };

// class FEFinder<TLComponentInstance, 4>
// {
// public:
//     void Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
//     void _Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
//     long); void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long); void
//     _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long); void
//     Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
// };

// class BasicString<unsigned short, Detail
// {
// public:
//     void TempStringAllocator>::operator=(BasicString<unsigned short, Detail::TempStringAllocator>);
//     void TempStringAllocator>::~BasicString();
//     void TempStringAllocator>::BasicString(const unsigned short*);
//     void TempStringAllocator>::insert(unsigned short*, const unsigned short*, const unsigned short*);
//     void TempStringAllocator>::erase(const unsigned short*, const unsigned short*);
// };

// class nlBSearch<nlLocalization
// {
// public:
//     void StringLookup, unsigned long>(const unsigned long&, nlLocalization::StringLookup*, int);
// };

// class LexicalCast<BasicString<unsigned short, Detail
// {
// public:
//     void TempStringAllocator>, BasicString<unsigned short, Detail::TempStringAllocator>>(const BasicString<unsigned short,
//     Detail::TempStringAllocator>&); void TempStringAllocator>, const unsigned short*>(const unsigned short* const&);
// };

// class Detail
// {
// public:
//     void LexicalCastImpl<BasicString<unsigned short, Detail::TempStringAllocator>, BasicString<unsigned short,
//     Detail::TempStringAllocator>>::Do(const BasicString<unsigned short, Detail::TempStringAllocator>&); void
//     LexicalCastImpl<BasicString<unsigned short, Detail::TempStringAllocator>, const unsigned short*>::Do(const unsigned short* const&);
// };

// class Format<BasicString<unsigned short, Detail
// {
// public:
//     void TempStringAllocator>, BasicString<unsigned short, Detail::TempStringAllocator>, BasicString<unsigned short,
//     Detail::TempStringAllocator>, BasicString<unsigned short, Detail::TempStringAllocator>>(const BasicString<unsigned short,
//     Detail::TempStringAllocator>&, const BasicString<unsigned short, Detail::TempStringAllocator>&, const BasicString<unsigned short,
//     Detail::TempStringAllocator>&, const BasicString<unsigned short, Detail::TempStringAllocator>&); void TempStringAllocator>,
//     BasicString<unsigned short, Detail::TempStringAllocator>>(const BasicString<unsigned short, Detail::TempStringAllocator>&, const
//     BasicString<unsigned short, Detail::TempStringAllocator>&); void TempStringAllocator>, unsigned short[4]>(const BasicString<unsigned
//     short, Detail::TempStringAllocator>&, const unsigned short(&)[4]);
// };

// class FormatImpl<BasicString<unsigned short, Detail
// {
// public:
//     void TempStringAllocator>>::operator BasicString<unsigned short, Detail::TempStringAllocator>() const;
//     void TempStringAllocator>>::operator%<BasicString<unsigned short, Detail::TempStringAllocator>>(const BasicString<unsigned short,
//     Detail::TempStringAllocator>&); void TempStringAllocator>>::operator%<const unsigned short*>(const unsigned short* const&);
// };

#endif // _FEPOPUPMENU_H_
