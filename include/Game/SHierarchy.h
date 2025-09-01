#ifndef _SHIERARCHY_H_
#define _SHIERARCHY_H_

#include "types.h"
#include "NL/nlMath.h"

class nlChunk;

class cSHierarchy
{
public:
    bool PreserveBoneLength(int) const;
    nlVector3* GetTranslationOffset(int) const;
    s32 GetParent(int) const;
    s32 GetPushPop(int) const;
    s32 GetMirroredNode(int) const;
    s32 GetNumChildren(int) const;
    u32 GetNodeID(int) const;
    s32 GetNodeIndexByID(unsigned int) const;
    s32 GetChild(int, int) const;
    void BuildPushPopFlags(int, int, int&);
    cSHierarchy* Initialize(nlChunk*);

    /* 0x00 */ void* m_hierarchyMetadata; // Pointer to hierarchy metadata or root node
    /* 0x04 */ char m_pad_0x04[4];
    /* 0x08 */ s32 m_nodeCount;             // Number of nodes in the hierarchy
    /* 0x0C */ u32* m_nodeIDs;              // Array of node IDs
    /* 0x10 */ void* m_parentIndices;       // Array of parent indices for each node
    /* 0x14 */ s32* m_childCounts;          // Array of child counts for each node
    /* 0x18 */ void* m_childArrays;         // Array of child index arrays for each node
    /* 0x1C */ void* m_pushPopFlags;        // Push/pop flags for hierarchy traversal
    /* 0x20 */ void* m_mirroredNodeIndices; // Mirrored node indices for symmetry
    /* 0x24 */ s32 m_minNode;
    /* 0x28 */ s32 m_maxNode;
    /* 0x2C */ nlVector3* m_translationOffsets; // Translation offset data for each node
    /* 0x30 */ bool* m_boneLengthFlags;         // Array of bone length preservation flags
};

#endif // _SHIERARCHY_H_
