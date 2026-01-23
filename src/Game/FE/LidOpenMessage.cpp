#include "Game/FE/LidOpenMessage.h"
#include "types.h"

extern int g_Language;

struct LoadingTextEntry {
    int x;
    int y;
    unsigned long param;
    const unsigned char* text;
};

extern LoadingTextEntry LOADING_TEXT_DATA[];

/**
 * Offset/Address/Size: 0x624 | 0x80094540 | size: 0x26C
 */
void DisplayMessage(int, int, const unsigned char*, int, unsigned long, bool)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x278 | 0x80094194 | size: 0x3AC
 */
void DisplayDVDMessageSebring(int)
{
}

/**
 * Offset/Address/Size: 0x58 | 0x80093F74 | size: 0x220
 */
void DVDAllClearSebring(int)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80093F1C | size: 0x58
 */
void DisplayLoadingMessageFast()
{
    int lang = g_Language;
    if (lang > 6) {
        lang = 0;
    }

    DisplayMessage(
        LOADING_TEXT_DATA[lang].x,
        LOADING_TEXT_DATA[lang].y,
        LOADING_TEXT_DATA[lang].text,
        LOADING_TEXT_DATA[lang].param,
        0xFFFFA800,
        true
    );
}
