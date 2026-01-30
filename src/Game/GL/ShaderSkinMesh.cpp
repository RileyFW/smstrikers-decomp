#include "Game/GL/ShaderSkinMesh.h"

#include "Game/GL/GLSkinMesh.h"
#include "NL/gl/glUserData.h"
#include "NL/nlDLRing.h"
#include "NL/nlMemory.h"
#include "string.h"
#include "types.h"

// /**
//  * Offset/Address/Size: 0x14C | 0x801E2240 | size: 0x58
//  */
// BoneMapList::~BoneMapList()
// {
// }

// /**
//  * Offset/Address/Size: 0xD8 | 0x801E21CC | size: 0x74
//  */
// void nlDeleteRing<BoneMapList>(BoneMapList**)
// {
// }

// /**
//  * Offset/Address/Size: 0xAC | 0x801E21A0 | size: 0x2C
//  */
// void nlRingAddStart<SkinPairList>(SkinPairList**, SkinPairList*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801E20F4 | size: 0x70
//  */
// void nlDeleteRing<SkinPairList>(SkinPairList**)
// {
// }

// /**
//  * Offset/Address/Size: 0xC9C | 0x801E20D0 | size: 0x24
//  */
// void AVLTreeBase<unsigned long, SkinMatrix, NewAdapter<AVLTreeEntry<unsigned long, SkinMatrix> >, DefaultKeyCompare<unsigned long> >::DeleteEntry(AVLTreeEntry<unsigned long, SkinMatrix>*)
// {
// }

// /**
//  * Offset/Address/Size: 0xBE0 | 0x801E2014 | size: 0xBC
//  */
// void AVLTreeBase<unsigned long, SkinMatrix, NewAdapter<AVLTreeEntry<unsigned long, SkinMatrix> >, DefaultKeyCompare<unsigned long> >::AllocateEntry(void*, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0xBB4 | 0x801E1FE8 | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, SkinMatrix, NewAdapter<AVLTreeEntry<unsigned long, SkinMatrix> >, DefaultKeyCompare<unsigned long> >::CompareKey(void*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0xB88 | 0x801E1FBC | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, SkinMatrix, NewAdapter<AVLTreeEntry<unsigned long, SkinMatrix> >, DefaultKeyCompare<unsigned long> >::CompareNodes(AVLTreeNode*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0xB80 | 0x801E1FB4 | size: 0x8
//  */
// void AVLTreeBase<unsigned long, SkinMatrix, NewAdapter<AVLTreeEntry<unsigned long, SkinMatrix> >, DefaultKeyCompare<unsigned long> >::CastUp(AVLTreeNode*) const
// {
// }

// /**
//  * Offset/Address/Size: 0x428 | 0x801E185C | size: 0x758
//  */
// void AVLTreeBase<unsigned long, SkinMatrix, NewAdapter<AVLTreeEntry<unsigned long, SkinMatrix> >, DefaultKeyCompare<unsigned long> >::PostorderTraversal(AVLTreeEntry<unsigned long, SkinMatrix>*, void (AVLTreeBase<unsigned long, SkinMatrix, NewAdapter<AVLTreeEntry<unsigned long, SkinMatrix> >, DefaultKeyCompare<unsigned long> >::*)(AVLTreeEntry<unsigned long, SkinMatrix>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x3C4 | 0x801E17F8 | size: 0x64
//  */
// void AVLTreeBase<unsigned long, SkinMatrix, NewAdapter<AVLTreeEntry<unsigned long, SkinMatrix> >, DefaultKeyCompare<unsigned long> >::DestroyTree(void (AVLTreeBase<unsigned long, SkinMatrix, NewAdapter<AVLTreeEntry<unsigned long, SkinMatrix> >, DefaultKeyCompare<unsigned long> >::*)(AVLTreeEntry<unsigned long, SkinMatrix>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x36C | 0x801E17A0 | size: 0x58
//  */
// void AVLTreeBase<unsigned long, SkinMatrix, NewAdapter<AVLTreeEntry<unsigned long, SkinMatrix> >, DefaultKeyCompare<unsigned long> >::Clear()
// {
// }

// /**
//  * Offset/Address/Size: 0x310 | 0x801E1744 | size: 0x5C
//  */
// void AVLTreeBase<unsigned long, SkinMatrix, NewAdapter<AVLTreeEntry<unsigned long, SkinMatrix> >, DefaultKeyCompare<unsigned long> >::~AVLTreeBase()
// {
// }

// /**
//  * Offset/Address/Size: 0x44 | 0x801E1478 | size: 0x2CC
//  */
// void AVLTreeBase<unsigned long, unsigned long, NewAdapter<AVLTreeEntry<unsigned long, unsigned long> >, DefaultKeyCompare<unsigned long> >::InorderWalk<UserDataBuilder>(AVLTreeEntry<unsigned long, unsigned long>*, UserDataBuilder*, void (UserDataBuilder::*)(const unsigned long&, unsigned long*))
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801E1434 | size: 0x44
//  */
// void AVLTreeBase<unsigned long, unsigned long, NewAdapter<AVLTreeEntry<unsigned long, unsigned long> >, DefaultKeyCompare<unsigned long> >::Walk<UserDataBuilder>(UserDataBuilder*, void (UserDataBuilder::*)(const unsigned long&, unsigned long*))
// {
// }

/**
 * Offset/Address/Size: 0xD28 | 0x801E136C | size: 0xC8
 */
ShaderSkinMesh::ShaderSkinMesh()
{
}

// /**
//  * Offset/Address/Size: 0xCC8 | 0x801E130C | size: 0x60
//  */
// void nlAVLTree<unsigned long, SkinMatrix, DefaultKeyCompare<unsigned long> >::~nlAVLTree()
// {
// }

/**
 * Offset/Address/Size: 0xBE4 | 0x801E1228 | size: 0xE4
 */
ShaderSkinMesh::~ShaderSkinMesh()
{
    // Delete morph-related arrays
    delete[] morphNumDeltas;
    delete[] morphData;
    delete[] morphIDs;

    // Delete bone maps ring if it exists
    if (boneMaps != nullptr)
    {
        nlDeleteRing<BoneMapList>(&boneMaps);
    }

    // Delete temporary arrays
    delete[] tempNormals;
    delete[] tempMatrices;

    // Delete skin pairs ring if it exists
    if (skinPairs != nullptr)
    {
        nlDeleteRing<SkinPairList>(&skinPairs);
    }

    // Delete stitch array if it exists
    if (stitchArray != nullptr)
    {
        delete[] stitchArray;
    }
}

/**
 * Offset/Address/Size: 0xB74 | 0x801E11B8 | size: 0x70
 */
void ShaderSkinMesh::SetMorphIDs(const unsigned long* ids)
{
    if (morphIDs != nullptr)
    {
        delete[] morphIDs;
    }
    morphIDs = (unsigned long*)nlMalloc(numMorphs * sizeof(unsigned long), 8, false);
    memcpy(morphIDs, ids, numMorphs * sizeof(unsigned long));
}

/**
 * Offset/Address/Size: 0xB70 | 0x801E11B4 | size: 0x4
 */
void ShaderSkinMesh::ConnectToPose(cPoseAccumulator*)
{
    // EMPTY
}

/**
 * Offset/Address/Size: 0xB04 | 0x801E1148 | size: 0x6C
 */
void ShaderSkinMesh::SetBoneMatrix(unsigned long boneID, const nlMatrix4* matrix)
{
    AVLTreeNode* existingNode;
    SkinMatrix skinMatrix;

    skinMatrix.Set(*matrix);

    boneMatrices.AddAVLNode((AVLTreeNode**)&boneMatrices.m_Root, &boneID, &skinMatrix, &existingNode, boneMatrices.m_NumElements);

    if (existingNode == NULL)
    {
        boneMatrices.m_NumElements++;
    }
}

/**
 * Offset/Address/Size: 0xA94 | 0x801E10D8 | size: 0x70
 */
nlMatrix4& ShaderSkinMesh::GetPoseMatrix(unsigned long boneID)
{
    nlMatrix4* foundMatrix = (nlMatrix4*)poseMatrices.FindGet(boneID);
    return *foundMatrix;
}

/**
 * Offset/Address/Size: 0x8E8 | 0x801E0F2C | size: 0x1AC
 */
void ShaderSkinMesh::GetPoseMatrices(GLSkinMeshMatrix*)
{
}

/**
 * Offset/Address/Size: 0x76C | 0x801E0DB0 | size: 0x17C
 */
void ShaderSkinMesh::SetPoseMatrices(int, GLSkinMeshMatrix*)
{
}

/**
 * Offset/Address/Size: 0x58C | 0x801E0BD0 | size: 0x1E0
 */
void ShaderSkinMesh::PrepareToRender(unsigned long, const nlMatrix4*)
{
}

/**
 * Offset/Address/Size: 0x500 | 0x801E0B44 | size: 0x8C
 */
void ShaderSkinMesh::AppendSkinPairList(int numPairs, const SkinPair* pairs)
{
    SkinPairList* node = (SkinPairList*)nlMalloc(sizeof(SkinPairList), 8, false);

    if (node != nullptr)
    {
        node->pairs = nullptr;
        node->m_next = nullptr;
    }

    node->num = numPairs;

    if (numPairs == 0)
    {
        node->pairs = nullptr;
    }
    else
    {
        node->pairs = (SkinPair*)pairs;
    }

    nlRingAddEnd<SkinPairList>(&skinPairs, node);
}

/**
 * Offset/Address/Size: 0x4F4 | 0x801E0B38 | size: 0xC
 */
void ShaderSkinMesh::SetSoftwareVertices(int num, const SkinVertex* skinVertices)
{
    numSoftwareVerts = num;
    softwareVertices = (SkinVertex*)skinVertices;
}

/**
 * Offset/Address/Size: 0x458 | 0x801E0A9C | size: 0x9C
 */
void ShaderSkinMesh::AppendStitchingInfo(int packetIndex, int _numPackets, int num, const unsigned char* pIndices)
{
    if (stitchArray == NULL)
    {
        numPackets = _numPackets;
        stitchArray = (unsigned char**)nlMalloc(numPackets * sizeof(unsigned char*), 8, false);
        memset(stitchArray, 0, numPackets * sizeof(unsigned char*));
    }

    if (num > 0)
    {
        stitchArray[packetIndex] = (unsigned char*)pIndices;
    }
}

/**
 * Offset/Address/Size: 0x398 | 0x801E09DC | size: 0xC0
 */
void UserDataBuilder::AddEntry(const unsigned long& boneID, unsigned long* registerIndex)
{
    SkinMatrix* foundMatrix = (SkinMatrix*)m_PoseMatrices->FindGet(boneID);

    m_Bone->reg = (*registerIndex) * 3 - 0x60;
    foundMatrix->Get4x3(m_Bone->mat);

    m_Bone++;
}

/**
 * Offset/Address/Size: 0x2E4 | 0x801E0928 | size: 0xB4
 */
void* ShaderSkinMesh::MakeUserData(nlAVLTree<unsigned long, unsigned long, DefaultKeyCompare<unsigned long> >* boneMap)
{
    unsigned int count = boneMap->m_NumElements;
    unsigned long size = count * 0x34 + 4;

    void* userData = glUserAlloc(GLUD_Skin, size, false);
    if (userData == nullptr)
    {
        return nullptr;
    }

    void* data = glUserGetData(userData);
    *(unsigned int*)data = count;

    GLSkinUserData* skinDataArray = (GLSkinUserData*)((char*)data + 4);

    UserDataBuilder builder;
    builder.m_Bone = skinDataArray;
    builder.m_PoseMatrices = (nlAVLTree<unsigned long, SkinMatrix, DefaultKeyCompare<unsigned long> >*)&poseMatrices;

    boneMap->Walk(&builder, &UserDataBuilder::AddEntry);

    return userData;
}

/**
 * Offset/Address/Size: 0x108 | 0x801E074C | size: 0x1DC
 * TODO: 87.79% match - register allocation differs: target uses stmw r26, current uses stmw r27.
 *       Target directly moves GetNodeMatrix result to r26 (mr r26,r3), but current goes through
 *       r0 (mr r0,r3; mr r27,r0). This is a mwcc compiler register allocation quirk.
 */
void ShaderSkinMesh::Pose(cPoseAccumulator* pPoseAccumulator)
{
    SkinMatrix* foundMatrix;
    unsigned long nodeID;
    AVLTreeNode* existingNode;
    SkinMatrix result;
    SkinMatrix skinMat;
    AVLTreeNode** pRoot = (AVLTreeNode**)&poseMatrices.m_Root;

    for (int i = 0; i < pPoseAccumulator->GetNumNodes(); i++)
    {
        cSHierarchy* hierarchy = pPoseAccumulator->m_BaseSHierarchy;
        nlMatrix4* nodeMatrix = &pPoseAccumulator->GetNodeMatrix(i);
        nodeID = hierarchy->GetNodeID(i);

        // Inline FindGet with bool return
        u8 found;
        {
            AVLTreeEntry<unsigned long, SkinMatrix>* node = boneMatrices.m_Root;
            while (node != nullptr)
            {
                int cmpResult;
                if (nodeID == node->key)
                    cmpResult = 0;
                else if (nodeID < node->key)
                    cmpResult = -1;
                else
                    cmpResult = 1;

                if (cmpResult == 0)
                {
                    if (&foundMatrix != nullptr)
                    {
                        foundMatrix = &node->value;
                    }
                    found = 1;
                    goto check_found;
                }
                else if (cmpResult < 0)
                {
                    node = (AVLTreeEntry<unsigned long, SkinMatrix>*)node->node.left;
                }
                else
                {
                    node = (AVLTreeEntry<unsigned long, SkinMatrix>*)node->node.right;
                }
            }
            found = 0;
        }

check_found:
        if (found)
        {
            skinMat.Set(*nodeMatrix);

            nlMultMatrices(result, *foundMatrix, skinMat);

            poseMatrices.AddAVLNode(pRoot, &nodeID, &result, &existingNode, poseMatrices.m_NumElements);

            SkinMatrix* existing;
            if (existingNode == nullptr)
            {
                poseMatrices.m_NumElements++;
                existing = nullptr;
            }
            else
            {
                existing = (SkinMatrix*)(((char*)existingNode) + 0x10);
            }

            foundMatrix = existing;
            if (foundMatrix != nullptr)
            {
                *foundMatrix = result;
            }
        }
    }
}

/**
 * Offset/Address/Size: 0x98 | 0x801E06DC | size: 0x70
 */
void ShaderSkinMesh::SetMorphNumDeltas(const unsigned long* numDeltas)
{
    if (morphNumDeltas != nullptr)
    {
        delete[] morphNumDeltas;
    }
    morphNumDeltas = (unsigned long*)nlMalloc(numMorphs * sizeof(unsigned long), 8, false);
    memcpy(morphNumDeltas, numDeltas, numMorphs * sizeof(unsigned long));
}

/**
 * Offset/Address/Size: 0x0 | 0x801E0644 | size: 0x98
 */
void ShaderSkinMesh::SetMorphDeltas(int numDeltas, const MorphDelta* p)
{
    if (morphData != nullptr)
    {
        delete[] morphData;
    }

    unsigned int largestBlock = nlVirtualLargestBlock();
    unsigned long size = numDeltas * sizeof(MorphDelta);
    MorphDelta* newData;

    if (largestBlock >= size + 0x100)
    {
        newData = (MorphDelta*)nlVirtualAlloc(size, false);
    }
    else
    {
        newData = (MorphDelta*)nlMalloc(size, 0x20, false);
    }

    morphData = newData;
    memcpy(morphData, p, size);
}
