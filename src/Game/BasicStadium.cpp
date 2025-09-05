#include "Game/BasicStadium.h"

// /**
//  * Offset/Address/Size: 0xA8 | 0x8019EBE4 | size: 0x84
//  */
// void Config::TagValuePair::Get<BasicString<char, Detail::TempStringAllocator>>() const
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8019EB3C | size: 0xA8
//  */
// void Config::Get<BasicString<char, Detail::TempStringAllocator>>(const char*, BasicString<char, Detail::TempStringAllocator>)
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x8019EB34 | size: 0x8
 */
void BasicStadium::GetTerrainType(const nlVector3&) const
{
}

/**
 * Offset/Address/Size: 0x2D70 | 0x8019EAF0 | size: 0x44
 */
void BasicStadium::BasicStadiumEventHandler(Event*, void*)
{
}

/**
 * Offset/Address/Size: 0x2B64 | 0x8019E8E4 | size: 0x20C
 */
BasicStadium::BasicStadium(const char* name)
    : World(name)
{
}

/**
 * Offset/Address/Size: 0x2ABC | 0x8019E83C | size: 0xA8
 */
BasicStadium::~BasicStadium()
{
}

/**
 * Offset/Address/Size: 0x28F0 | 0x8019E670 | size: 0x1CC
 */
void BasicStadium::DoLoad()
{
}

/**
 * Offset/Address/Size: 0x2E8 | 0x8019C068 | size: 0x2608
 */
void BasicStadium::DoInitialize()
{
}

/**
 * Offset/Address/Size: 0x8C | 0x8019BE0C | size: 0x25C
 */
void BasicStadium::Update(float)
{
}

/**
 * Offset/Address/Size: 0x48 | 0x8019BDC8 | size: 0x44
 */
void BasicStadium::UpdateInReplay(float)
{
}

/**
 * Offset/Address/Size: 0x8 | 0x8019BD88 | size: 0x40
 */
void BasicStadium::Render()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8019BD80 | size: 0x8
 */
void BasicStadium::GetCurrentStadium()
{
}
