#include "Game/Render/Presentation.h"

// /**
//  * Offset/Address/Size: 0x60 | 0x80127308 | size: 0x8
//  */
// void LexicalCast<const char*, const char*>(const char* const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x48 | 0x801272F0 | size: 0x18
//  */
// void LexicalCast<const char*, bool>(const bool&)
// {
// }

// /**
//  * Offset/Address/Size: 0x24 | 0x801272CC | size: 0x24
//  */
// void LexicalCast<const char*, int>(const int&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801272A8 | size: 0x24
//  */
// void LexicalCast<const char*, float>(const float&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801272A0 | size: 0x8
//  */
// void NISData::GetID()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801267BC | size: 0xAE4
//  */
// void Presentation::DoFunctionCall(unsigned int)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80126750 | size: 0x6C
//  */
// void 0x801267BC..0x801272A0 | size: 0xAE4
// {
// }

/**
 * Offset/Address/Size: 0x1E58 | 0x8012663C | size: 0x114
 */
Presentation& Presentation::Instance()
{
    FORCE_DONT_INLINE;
    static Presentation instance;
    return instance;
}

/**
 * Offset/Address/Size: 0x1D18 | 0x801264FC | size: 0x140
 */
void ReadTrophyTexture(void*, unsigned long, void*)
{
}

/**
 * Offset/Address/Size: 0x1CA8 | 0x8012648C | size: 0x70
 */
void ReadTrophyModel(void*, unsigned long, void*)
{
}

/**
 * Offset/Address/Size: 0x1848 | 0x8012602C | size: 0x460
 */
void Presentation::LoadTrophyModel()
{
}

/**
 * Offset/Address/Size: 0x14EC | 0x80125CD0 | size: 0x35C
 */
void Presentation::Finish()
{
}

/**
 * Offset/Address/Size: 0xE70 | 0x80125654 | size: 0x67C
 */
void Presentation::Update(float)
{
}

/**
 * Offset/Address/Size: 0xDBC | 0x801255A0 | size: 0xB4
 */
void Presentation::DuringEndOfGamePresentation() const
{
}

/**
 * Offset/Address/Size: 0xCF0 | 0x801254D4 | size: 0xCC
 */
void Presentation::Call(const char*, const char*)
{
}

/**
 * Offset/Address/Size: 0x57C | 0x80124D60 | size: 0x774
 */
void Presentation::EventHandler(Event*)
{
}

/**
 * Offset/Address/Size: 0x3D0 | 0x80124BB4 | size: 0x1AC
 */
void Presentation::PlayOverlay(const char*, float, float)
{
}

/**
 * Offset/Address/Size: 0x36C | 0x80124B50 | size: 0x64
 */
void Presentation::StopOverlay()
{
}

/**
 * Offset/Address/Size: 0x19C | 0x80124980 | size: 0x1D0
 */
void CupWinStingerDone()
{
}

/**
 * Offset/Address/Size: 0x60 | 0x80124844 | size: 0x13C
 */
void Presentation::Reset()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801247E4 | size: 0x60
 */
Presentation::~Presentation()
{
}
