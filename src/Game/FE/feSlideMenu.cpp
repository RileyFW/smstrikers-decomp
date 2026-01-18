#include "Game/FE/feSlideMenu.h"

#include "NL/nlString.h"

/**
 * Offset/Address/Size: 0x0 | 0x80096C54 | size: 0x34
 */
void FESlideMenu::UpdatePresentation()
{
    m_pMenuComp->SetActiveSlide(m_menuItems[m_currentSlide].ItemSlide);
}

/**
 * Offset/Address/Size: 0x34 | 0x80096C88 | size: 0xE4
 */
bool FESlideMenu::PrevItem()
{
    return false;
}

/**
 * Offset/Address/Size: 0x118 | 0x80096D6C | size: 0xE8
 */
bool FESlideMenu::NextItem()
{
    return false;
}

/**
 * Offset/Address/Size: 0x200 | 0x80096E54 | size: 0xA4
 */
void FESlideMenu::SetSlideByIndex(unsigned char newslide)
{
}

/**
 * Offset/Address/Size: 0x2A4 | 0x80096EF8 | size: 0x84
 * TODO: 85.6% match - double beq pattern from switch/enum optimization not reproducible
 */
bool FESlideMenu::ApplyFunction()
{
    if (m_lockInput) {
        return false;
    }

    FESlideMenu* item = (FESlideMenu*)((char*)this + m_currentSlide * 0x14);
    int tag = *(int*)((char*)item + 4);

    if (tag == EMPTY) {
        return false;
    }

    if (tag != EMPTY) {
        if (tag == FREE_FUNCTION) {
            void (*func)(FESlideMenu*) = *(void (**)(FESlideMenu*))((char*)item + 8);
            func(item);
        } else {
            FunctorBase* fobj = *(FunctorBase**)((char*)item + 8);
            fobj->fnc_0x8();
        }
    }

    return true;
}

/**
 * Offset/Address/Size: 0x420 | 0x80097074 | size: 0x60
 */
FESlideMenu::MenuItem* FESlideMenu::AddMenuItem(const char* name)
{
    MenuItem* item = &m_menuItems[m_size];
    m_menuItems[m_size].ItemSlide = nlStringLowerHash(name);
    m_size++;
    return item;
}

/**
 * Offset/Address/Size: 0x480 | 0x800970D4 | size: 0x60
 */
FESlideMenu::~FESlideMenu()
{
}

/**
 * Offset/Address/Size: 0x4E0 | 0x80097134 | size: 0x64
 */
// void FESlideMenu::MenuItem::~MenuItem()
// {
// }

/**
 * Offset/Address/Size: 0x5C8 | 0x8009721C | size: 0x8C
 */
FESlideMenu::FESlideMenu(TLComponentInstance*)
{
}

/**
 * Offset/Address/Size: 0x654 | 0x800972A8 | size: 0x4C
 */
// void FESlideMenu::MenuItem::MenuItem()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800972F4 | size: 0xC
//  */
// void 0x80375A60..0x80375A68 | size: 0x8
// {
// }
