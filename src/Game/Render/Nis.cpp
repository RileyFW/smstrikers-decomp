#include "Game/Render/Nis.h"

// /**
//  * Offset/Address/Size: 0xEA0 | 0x8012E074 | size: 0xD74
//  */
// void FormatImpl<BasicString<char, Detail::TempStringAllocator>>::operator%<const char*>(const char* const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x12C | 0x8012D300 | size: 0xD74
//  */
// void FormatImpl<BasicString<char, Detail::TempStringAllocator>>::operator%<int>(const int&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8012D1D4 | size: 0x12C
//  */
// void Format<BasicString<char, Detail::TempStringAllocator>, char[64], int>(const BasicString<char, Detail::TempStringAllocator>&, const char(&)[64], const int&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8012D1BC | size: 0x18
//  */
// void Bind<void, void (*)(EmissionController&, int), Placeholder<0>, int>(void (*)(EmissionController&, int), const Placeholder<0>&, const int&)
// {
// }

// /**
//  * Offset/Address/Size: 0xF0 | 0x8012D194 | size: 0x28
//  */
// void nlListAddStart<Nis::NisAudioData>(Nis::NisAudioData**, Nis::NisAudioData*, Nis::NisAudioData**)
// {
// }

// /**
//  * Offset/Address/Size: 0x54 | 0x8012D0F8 | size: 0x9C
//  */
// void nlListRemoveElement<Nis::NisAudioData>(Nis::NisAudioData**, Nis::NisAudioData*, Nis::NisAudioData**)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8012D0A4 | size: 0x54
//  */
// void nlDeleteList<Nis::NisAudioData>(Nis::NisAudioData**)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8012D048 | size: 0x5C
//  */
// void Function1<void, EmissionController&>::FunctorImpl<BindExp2<void, void (*)(EmissionController&, int), Placeholder<0>, int>>::~FunctorImpl()
// {
// }

// /**
//  * Offset/Address/Size: 0x70 | 0x8012D014 | size: 0x34
//  */
// void Function1<void, EmissionController&>::FunctorImpl<BindExp2<void, void (*)(EmissionController&, int), Placeholder<0>, int>>::operator()(EmissionController&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8012CFA4 | size: 0x70
//  */
// void Function1<void, EmissionController&>::FunctorImpl<BindExp2<void, void (*)(EmissionController&, int), Placeholder<0>, int>>::Clone() const
// {
// }

/**
 * Offset/Address/Size: 0x1658 | 0x8012CA68 | size: 0x53C
 */
Nis::Nis(NisHeader&, char*, int)
{
}

/**
 * Offset/Address/Size: 0x1650 | 0x8012CA60 | size: 0x8
 */
void Nis::Name() const
{
}

/**
 * Offset/Address/Size: 0x13C0 | 0x8012C7D0 | size: 0x290
 */
Nis::~Nis()
{
}

/**
 * Offset/Address/Size: 0x1350 | 0x8012C760 | size: 0x70
 */
void Nis::Update(float)
{
}

/**
 * Offset/Address/Size: 0x1270 | 0x8012C680 | size: 0xE0
 */
void Nis::UpdateTriggers(float, float, float)
{
}

/**
 * Offset/Address/Size: 0xF80 | 0x8012C390 | size: 0x2F0
 */
void Nis::SelectCamera(cAnimCamera&, int)
{
}

/**
 * Offset/Address/Size: 0xF18 | 0x8012C328 | size: 0x68
 */
void Nis::SelectRandomCamera(cAnimCamera&)
{
}

/**
 * Offset/Address/Size: 0xD18 | 0x8012C128 | size: 0x200
 */
void Nis::Render()
{
}

/**
 * Offset/Address/Size: 0xCF8 | 0x8012C108 | size: 0x20
 */
void Nis::Offset() const
{
}

// /**
//  * Offset/Address/Size: 0xC10 | 0x8012C020 | size: 0xE8
//  */
// void Nis::AddTrigger(NisTriggerType, float, const char*, const char*, Nis::TriggerParams*)
// {
// }

// /**
//  * Offset/Address/Size: 0x834 | 0x8012BC44 | size: 0x3DC
//  */
// void Nis::Trigger::FireEffect(const Nis&) const
// {
// }

// /**
//  * Offset/Address/Size: 0x2D0 | 0x8012B6E0 | size: 0x564
//  */
// void Nis::Trigger::Fire(Nis&) const
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x8012B410 | size: 0x2D0
 */
void Nis::StopAllOutstandingNisAudio()
{
}
