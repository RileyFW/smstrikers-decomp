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
    if (m_lockInput)
    {
        return false;
    }

    u8 idx = m_currentSlide;
    bool changed = true;

    if (idx == 0)
    {
        if (m_doWrapAround)
        {
            m_currentSlide = m_size - 1;
        }
        else
        {
            changed = false;
        }
    }
    else
    {
        m_currentSlide = idx - 1;
    }

    if (changed)
    {
        m_pMenuComp->SetActiveSlide(m_menuItems[m_currentSlide].ItemSlide);

        MenuItem* item = &m_menuItems[m_currentSlide];
        s32 tag = item->ItemCBFuncs[1].mTag;
        if (tag != EMPTY)
        {
            if (tag == FREE_FUNCTION)
            {
                ((void (*)(MenuItem*))item->ItemCBFuncs[1].mFreeFunction)(item);
            }
            else
            {
                item->ItemCBFuncs[1].mFunctor->fnc_0x8();
            }
        }

        return true;
    }

    return false;
}

/**
 * Offset/Address/Size: 0x118 | 0x80096D6C | size: 0xE8
 */
bool FESlideMenu::NextItem()
{
    if (m_lockInput)
    {
        return false;
    }

    bool didChange = true;

    if (m_currentSlide == m_size - 1)
    {
        // At end of menu
        if (m_doWrapAround)
        {
            m_currentSlide = 0;
        }
        else
        {
            didChange = false;
        }
    }
    else
    {
        m_currentSlide++;
    }

    if (didChange)
    {
        m_pMenuComp->SetActiveSlide(m_menuItems[m_currentSlide].ItemSlide);

        MenuItem* item = &m_menuItems[m_currentSlide];
        int funcType = item->ItemCBFuncs[1].mTag;

        if (funcType == 0)
        {
            // No callback
        }
        else if (funcType == 1)
        {
            // Direct function call
            void (*fn)() = (void (*)())item->ItemCBFuncs[1].mFreeFunction;
            fn();
        }
        else
        {
            // Virtual call through functor - use inline chained access
            FunctorBase* functor = item->ItemCBFuncs[1].mFunctor;
            ((void (*)(FunctorBase*))(*(unsigned long**)functor)[3])(functor);
        }

        return true;
    }

    return false;
}

/**
 * Offset/Address/Size: 0x200 | 0x80096E54 | size: 0xA4
 * TODO: 92.7% match - early-return branch structure difference (blt+b vs bge)
 */
void FESlideMenu::SetSlideByIndex(unsigned char index)
{
    if (m_currentSlide == index)
    {
        return;
    }
    if (!(index < m_size))
    {
        return;
    }
    m_currentSlide = index;

    // Get pointer to MenuItem and access callback at ON_HIGHLIGHT (index 1)
    char* pThis = (char*)this;
    u32 offset = m_currentSlide * 0x14;
    u32* pItem = (u32*)(pThis + offset);

    // Check callback type at offset 0xC (ItemCBFuncs[1].mTag)
    int tag = (int)pItem[3];
    if (tag != 0)
    {
        if (tag == 1)
        {
            // FREE_FUNCTION - direct call
            void (*func)() = (void (*)())pItem[4];
            func();
        }
        else
        {
            // FUNCTOR - vtable call via fnc_0x8 (vtable[2])
            FunctorBase* functor = (FunctorBase*)pItem[4];
            functor->fnc_0x8();
        }
    }

    m_pMenuComp->SetActiveSlide(m_menuItems[m_currentSlide].ItemSlide);
}

/**
 * Offset/Address/Size: 0x2A4 | 0x80096EF8 | size: 0x84
 */
bool FESlideMenu::ApplyFunction()
{
    if (m_lockInput)
    {
        return false;
    }

    MenuItem* item = &m_menuItems[m_currentSlide];
    int tag = item->ItemCBFuncs[0].mTag;

    if (tag == EMPTY)
    {
        goto ret0;
    }

    if (tag == EMPTY)
    {
        goto ret1;
    }

    if (tag != FREE_FUNCTION)
    {
        goto functor;
    }

    ((void (*)(MenuItem*))item->ItemCBFuncs[0].mFreeFunction)(item);
    goto ret1;

functor:
    item->ItemCBFuncs[0].mFunctor->fnc_0x8();

ret1:
    return true;

ret0:
    return false;
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
