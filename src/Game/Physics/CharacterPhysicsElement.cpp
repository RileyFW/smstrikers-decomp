#include "Game/Physics/CharacterPhysicsElement.h"

#include "NL/nlFile.h"
#include "NL/nlMemory.h"

#include "Game/SAnim.h"

/**
 * Offset/Address/Size: 0x0 | 0x801FE13C | size: 0x2AC
 */

// bool LoadCharacterPhysicsElements(const char* pFileData, CharacterPhysicsData* pPhysicsData)
// {
//     u32 _dataSize;
//     void* rawdata = nlLoadEntireFile(pFileData, &_dataSize, 0x20, AllocateStart);
//     if (rawdata == 0)
//     {
//         return false;
//     }

//     nlChunk* pChunk = (nlChunk*)(((u8*)rawdata + 8));
//     u32 totalChunks = pChunk->m_Size;
//     for (u32 i = 0; i < totalChunks; i++)
//     {
//         pChunk++;
//     }

//     return true;
// }

bool LoadCharacterPhysicsElements(const char* pFileData, CharacterPhysicsData* pPhysicsData)
{
    u8* temp_r29;
    u8* var_r30;

    u32 dataSize;
    u8* rawData = (u8*)nlLoadEntireFile(pFileData, &dataSize, 0x20, AllocateStart);
    if (rawData == 0)
    {
        return false;
    }

    var_r30 = rawData + 8;
    temp_r29 = rawData + (*((u32*)((u8*)rawData + 4)) + 8);

    do
    {
        s32 temp_r5 = *(s32*)var_r30;       // chunk header
        s32 temp_r4 = temp_r5 & 0x80FFFFFF; // masked kind (irregular switch domain)

        switch (temp_r4)
        {
        case 0x0001D001:
        {
            s32 temp_r3_2 = temp_r5 & 0x7F000000;
            u8* var_r3;
            if (((-temp_r3_2 | temp_r3_2) >> 31) != 0)
            {
                s32 temp_r4_2 = 1 << (s32)((u32)temp_r3_2 >> 24);
                var_r3 = (u8*)(((u32)(var_r30 + temp_r4_2 + 7)) & ~(u32)(temp_r4_2 - 1));
            }
            else
            {
                var_r3 = var_r30 + 8;
            }

            pPhysicsData->physicsElementCount = *(u32*)var_r3;
            pPhysicsData->pPhysicsElements = (CharacterPhysicsElement*)nlMalloc(pPhysicsData->physicsElementCount * sizeof(CharacterPhysicsElement), 8, false);
            break;
        }

        case 0x0001D002:
        {
            s32 temp_r3_3 = temp_r5 & 0x7F000000;

            u8* var_r5 = (temp_r3_3 != 0)
                           ? (u8*)(((u32)(var_r30 + (1 << (s32)((u32)temp_r3_3 >> 24)) + 7)) & ~(u32)((1 << (s32)((u32)temp_r3_3 >> 24)) - 1))
                           : (var_r30 + 8);

            for (u32 i = 0; i < pPhysicsData->physicsElementCount; i++)
            {
                pPhysicsData->pPhysicsElements[i] = ((CharacterPhysicsElement*)var_r5)[i];
            }
            break;
        }
        }

        var_r30 += *((u32*)(var_r30 + 4)) + 8; // advance to next chunk

    } while (var_r30 < temp_r29);

    delete rawData;
    return true;
}
