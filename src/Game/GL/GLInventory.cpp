#include "Game/GL/GLInventory.h"

GLInventory glInventory;

/**
 * Offset/Address/Size: 0x1058 | 0x801E32F0 | size: 0x50
 */
GLInventory::~GLInventory()
{
    Delete();
}

/**
 * Offset/Address/Size: 0xD54 | 0x801E2FEC | size: 0x304
 */
void GLInventory::Create()
{
}

/**
 * Offset/Address/Size: 0xC4C | 0x801E2EE4 | size: 0x108
 */
void GLInventory::Delete()
{
    FORCE_DONT_INLINE;
    m_bCreated = false;

    for (int level = 0; level < 16; level++)
    {
        ReleaseLevel(level);

        nlListContainer<void*>* fileData = m_pFileData[level];

        if (fileData != nullptr)
        {
            // nlWalkList<ListEntry<void*>, ListContainerBase<void*, NewAdapter<ListEntry<void*> > > >(
            //     fileData->m_Head,
            //     fileData,
            //     &ListContainerBase<void*, NewAdapter<ListEntry<void*> > >::DeleteEntry);

            fileData->m_Head = nullptr;
            fileData->m_Tail = nullptr;
            delete fileData;
        }
        delete m_pSkinData[level];
        delete m_pModels[level];
        delete m_pShadowVolumes[level];
        delete m_pTextureAnims[level];
        delete m_pVertexAnims[level];
        delete m_pMaterialLists[level];
    }
}

/**
 * Offset/Address/Size: 0xB68 | 0x801E2E00 | size: 0xE4
 */
void GLInventory::ReleaseLevel(int nLevel)
{
    FORCE_DONT_INLINE;
    nlListContainer<void*>* fileData = m_pFileData[nLevel];

    if (fileData != nullptr)
    {
        ListEntry<void*>* current = fileData->m_Head;
        while (current != nullptr)
        {
            ListEntry<void*>* next = current->next;
            delete current->data; // Delete the actual data
            current = next;
        }

        // nlWalkList<ListEntry<void*>, ListContainerBase<void*, NewAdapter<ListEntry<void*> > > >(fileData->m_Head, fileData, &ListContainerBase<void*, NewAdapter<ListEntry<void*> > >::DeleteEntry);

        fileData->m_Head = nullptr;
        fileData->m_Tail = nullptr;
    }

    m_pSkinData[nLevel]->Release();      // freeing_GLInventory<nlChunk>
    m_pModels[nLevel]->Release();        // clearing_GLInventory<glModel>
    m_pShadowVolumes[nLevel]->Release(); // deleting_GLInventory<GLShadowVolume>
    m_pTextureAnims[nLevel]->Release();  // deleting_GLInventory<GLTextureAnim>
    m_pVertexAnims[nLevel]->Release();   // deleting_GLInventory<GLVertexAnim>
    m_pMaterialLists[nLevel]->Release(); // deleting_GLInventory<GLMaterialList>
}

/**
 * Offset/Address/Size: 0xB58 | 0x801E2DF0 | size: 0x10
 */
void GLInventory::ResourceMark()
{
    m_nLevel++;
}

/**
 * Offset/Address/Size: 0xB00 | 0x801E2D98 | size: 0x58
 */
void GLInventory::ResourceRelease(int nLevel)
{
    while (m_nLevel != nLevel)
    {
        ReleaseLevel(m_nLevel);
        m_nLevel--;
    }
}

/**
 * Offset/Address/Size: 0xA8C | 0x801E2D24 | size: 0x74
 */
void GLInventory::AddModel(unsigned long key, glModel* model)
{
    unsigned long k = key;
    glModel* value = model;
    nlAVLTree<unsigned long, glModel*, DefaultKeyCompare<unsigned long> >* pTree = m_pModels[m_nLevel]->m_pItems;
    AVLTreeNode* existingNode;
    pTree->AddAVLNode((AVLTreeNode**)&pTree->m_Root, &k, &value, &existingNode, pTree->m_NumElements);
    if (existingNode == nullptr)
    {
        pTree->m_NumElements++;
    }
}

/**
 * Offset/Address/Size: 0x9C4 | 0x801E2C5C | size: 0xC8
 */
glModel* GLInventory::GetModel(unsigned long id)
{
    for (int i = m_nLevel; i >= 0; i--)
    {
        bool found;
        glModel** pResult;
        AVLTreeEntry<unsigned long, glModel*>* node = m_pModels[i]->m_pItems->m_Root;

        while (node != nullptr)
        {
            int cmpResult;
            if (id == node->key)
            {
                cmpResult = 0;
            }
            else if (id < node->key)
            {
                cmpResult = -1;
            }
            else
            {
                cmpResult = 1;
            }

            if (cmpResult == 0)
            {
                if (&pResult != nullptr)
                {
                    pResult = &node->value;
                }
                found = true;
                goto check_found;
            }
            else if (cmpResult < 0)
            {
                node = (AVLTreeEntry<unsigned long, glModel*>*)node->node.left;
            }
            else
            {
                node = (AVLTreeEntry<unsigned long, glModel*>*)node->node.right;
            }
        }
        found = false;
    check_found:
        glModel* result;
        if (found)
        {
            result = *pResult;
        }
        else
        {
            result = nullptr;
        }
        if (result != nullptr)
        {
            return result;
        }
    }
    return nullptr;
}

/**
 * Offset/Address/Size: 0x8FC | 0x801E2B94 | size: 0xC8
 */
void GLInventory::GetShadowVolume(unsigned long)
{
}

/**
 * Offset/Address/Size: 0x888 | 0x801E2B20 | size: 0x74
 */
void GLInventory::AddTextureAnim(unsigned long key, GLTextureAnim* anim)
{
    unsigned long k = key;
    GLTextureAnim* value = anim;
    nlAVLTree<unsigned long, GLTextureAnim*, DefaultKeyCompare<unsigned long> >* pTree = m_pTextureAnims[m_nLevel]->m_pItems;
    AVLTreeNode* existingNode;
    pTree->AddAVLNode((AVLTreeNode**)&pTree->m_Root, &k, &value, &existingNode, pTree->m_NumElements);
    if (existingNode == nullptr)
    {
        pTree->m_NumElements++;
    }
}

/**
 * Offset/Address/Size: 0x7C0 | 0x801E2A58 | size: 0xC8
 * TODO: 82% match. The FindGet inline method needs adjustment for exact match.
 * Target tracks bool 'found' separately and stores value pointer to stack at 0x08(r1).
 * Missing the clrlwi./beq pattern for bool test before dereferencing result.
 */
GLTextureAnim* GLInventory::GetTextureAnim(unsigned long id)
{
    for (int i = m_nLevel; i >= 0; i--)
    {
        GLTextureAnim** pResult = m_pTextureAnims[i]->m_pItems->FindGet(id);
        if (pResult != nullptr)
        {
            return *pResult;
        }
    }
    return nullptr;
}

/**
 * Offset/Address/Size: 0x74C | 0x801E29E4 | size: 0x74
 */
void GLInventory::AddVertexAnim(unsigned long key, GLVertexAnim* vertexAnim)
{
    unsigned long k = key;
    GLVertexAnim* value = vertexAnim;
    nlAVLTree<unsigned long, GLVertexAnim*, DefaultKeyCompare<unsigned long> >* pTree = m_pVertexAnims[m_nLevel]->m_pItems;
    AVLTreeNode* existingNode;
    pTree->AddAVLNode((AVLTreeNode**)&pTree->m_Root, &k, &value, &existingNode, pTree->m_NumElements);
    if (existingNode == nullptr)
    {
        pTree->m_NumElements++;
    }
}

/**
 * Offset/Address/Size: 0x684 | 0x801E291C | size: 0xC8
 */
GLVertexAnim* GLInventory::GetVertexAnim(unsigned long)
{
    return nullptr; // TODO: Implement actual lookup
}

/**
 * Offset/Address/Size: 0x610 | 0x801E28A8 | size: 0x74
 */
void GLInventory::AddMaterialList(unsigned long key, GLMaterialList* materialList)
{
    deleting_GLInventory<GLMaterialList>* pMaterialLists = m_pMaterialLists[m_nLevel];
    AVLTreeNode** existingNode = nullptr;

    u32 result = pMaterialLists->m_pItems->AddAVLNode(
        (AVLTreeNode**)&pMaterialLists->m_pItems->m_Root,
        &key,
        &materialList,
        existingNode,
        0);

    if (existingNode == nullptr)
    {
        pMaterialLists->m_pItems->m_NumElements++;
    }
}

/**
 * Offset/Address/Size: 0x548 | 0x801E27E0 | size: 0xC8
 */
GLMaterialList* GLInventory::GetMaterialList(unsigned long key)
{
    GLMaterialList* result = nullptr;

    for (int level = m_nLevel; level >= 0; level--)
    {
        deleting_GLInventory<GLMaterialList>* pMaterialLists = m_pMaterialLists[level];
        AVLTreeEntry<unsigned long, GLMaterialList*>* node = pMaterialLists->m_pItems->m_Root;

        while (node != nullptr)
        {
            if (key == node->key)
            {
                result = node->value;
                break;
            }
            else if (key < node->key)
            {
                node = (AVLTreeEntry<unsigned long, GLMaterialList*>*)node->node.left;
            }
            else
            {
                node = (AVLTreeEntry<unsigned long, GLMaterialList*>*)node->node.right;
            }
        }

        if (result != nullptr)
        {
            break;
        }
    }

    return result;
}

/**
 * Offset/Address/Size: 0x4D4 | 0x801E276C | size: 0x74
 */
void GLInventory::AddSkinData(unsigned long key, nlChunk* skinData)
{
    unsigned long key2 = key;
    nlChunk* skinData2 = skinData;
    AVLTreeNode* existingNode;
    freeing_GLInventory<nlChunk>* pSkinData = m_pSkinData[m_nLevel];
    nlAVLTree<unsigned long, nlChunk*, DefaultKeyCompare<unsigned long> >* tree = pSkinData->m_pItems;

    tree->AddAVLNode(
        (AVLTreeNode**)&tree->m_Root,
        &key2,
        &skinData2,
        &existingNode,
        tree->m_NumElements);

    if (existingNode == nullptr)
    {
        tree->m_NumElements++;
    }
}

/**
 * Offset/Address/Size: 0x334 | 0x801E25CC | size: 0x1A0
 */
GLSkinMesh* GLInventory::MakeSkinMesh(unsigned long)
{
    return nullptr;
}

/**
 * Offset/Address/Size: 0x0 | 0x801E2298 | size: 0x334
 */
void GLInventory::Update(float)
{
}
