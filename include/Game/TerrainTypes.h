#ifndef _TERRAINTYPES_H_
#define _TERRAINTYPES_H_

enum eTerrain
{
    TERRAIN_GRASS = 0,
    TERRAIN_BLUEGRASS = 1,
    TERRAIN_CONCRETE = 2,
    TERRAIN_BLUECONCRETE = 3,
    TERRAIN_WOOD = 4,
    TERRAIN_METAL = 5,
    TERRAIN_RUBBER = 6
};

const char* GetTerrainName(eTerrain terrain);

void TerrainInitialize();

extern int g_TerrainTypeHashes[7];

#endif // _TERRAINTYPES_H_
