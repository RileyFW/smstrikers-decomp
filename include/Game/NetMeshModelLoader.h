#ifndef _NETMESHMODELLOADER_H_
#define _NETMESHMODELLOADER_H_

#include "Game/Render/NetMesh.h"

class glModelPacket
{
public:
    // TODO: Implement this
};

class NetMeshModelLoader
{
public:
    NetMeshModelLoader(NetMesh&, unsigned long);
    ~NetMeshModelLoader();
    void LoadGeometryFromModel();
    void AddEdge(const glModelPacket&, unsigned short, unsigned short);
    void AddTriangleFromGeometry(const glModelPacket&, unsigned short*);
    void ReadEdgesFromGeometryPacket(const glModelPacket&);
    void ProcessEdges(const glModelPacket&, int);
    void CreateNetMeshFromVertexList();
};

// class nlAVLTreeSlotPool<NetMeshModelLoader
// {
// public:
//     void NetMeshEdge, int, DefaultKeyCompare<NetMeshModelLoader::NetMeshEdge>>::~nlAVLTreeSlotPool();
//     void NetMeshVertex, int, DefaultKeyCompare<NetMeshModelLoader::NetMeshVertex>>::~nlAVLTreeSlotPool();
// };

// class AVLTreeBase<NetMeshModelLoader
// {
// public:
//     void NetMeshVertex, int, BasicSlotPool<AVLTreeEntry<NetMeshModelLoader::NetMeshVertex, int>>, DefaultKeyCompare<NetMeshModelLoader::NetMeshVertex>>::DeleteEntry(AVLTreeEntry<NetMeshModelLoader::NetMeshVertex, int>*);
//     void NetMeshVertex, int, BasicSlotPool<AVLTreeEntry<NetMeshModelLoader::NetMeshVertex, int>>, DefaultKeyCompare<NetMeshModelLoader::NetMeshVertex>>::AllocateEntry(void*, void*);
//     void NetMeshEdge, int, BasicSlotPool<AVLTreeEntry<NetMeshModelLoader::NetMeshEdge, int>>, DefaultKeyCompare<NetMeshModelLoader::NetMeshEdge>>::DeleteEntry(AVLTreeEntry<NetMeshModelLoader::NetMeshEdge, int>*);
//     void NetMeshEdge, int, BasicSlotPool<AVLTreeEntry<NetMeshModelLoader::NetMeshEdge, int>>, DefaultKeyCompare<NetMeshModelLoader::NetMeshEdge>>::CompareNodes(AVLTreeNode*, AVLTreeNode*);
//     void NetMeshEdge, int, BasicSlotPool<AVLTreeEntry<NetMeshModelLoader::NetMeshEdge, int>>, DefaultKeyCompare<NetMeshModelLoader::NetMeshEdge>>::CompareKey(void*, AVLTreeNode*);
//     void NetMeshEdge, int, BasicSlotPool<AVLTreeEntry<NetMeshModelLoader::NetMeshEdge, int>>, DefaultKeyCompare<NetMeshModelLoader::NetMeshEdge>>::AllocateEntry(void*, void*);
//     void NetMeshVertex, int, BasicSlotPool<AVLTreeEntry<NetMeshModelLoader::NetMeshVertex, int>>, DefaultKeyCompare<NetMeshModelLoader::NetMeshVertex>>::CompareKey(void*, AVLTreeNode*);
//     void NetMeshVertex, int, BasicSlotPool<AVLTreeEntry<NetMeshModelLoader::NetMeshVertex, int>>, DefaultKeyCompare<NetMeshModelLoader::NetMeshVertex>>::CompareNodes(AVLTreeNode*, AVLTreeNode*);
//     void NetMeshEdge, int, BasicSlotPool<AVLTreeEntry<NetMeshModelLoader::NetMeshEdge, int>>, DefaultKeyCompare<NetMeshModelLoader::NetMeshEdge>>::CastUp(AVLTreeNode*) const;
//     void NetMeshEdge, int, BasicSlotPool<AVLTreeEntry<NetMeshModelLoader::NetMeshEdge, int>>, DefaultKeyCompare<NetMeshModelLoader::NetMeshEdge>>::PostorderTraversal(AVLTreeEntry<NetMeshModelLoader::NetMeshEdge, int>*, void (AVLTreeBase<NetMeshModelLoader::NetMeshEdge, int, BasicSlotPool<AVLTreeEntry<NetMeshModelLoader::NetMeshEdge, int>>, DefaultKeyCompare<NetMeshModelLoader::NetMeshEdge>>::*)(AVLTreeEntry<NetMeshModelLoader::NetMeshEdge, int>*));
//     void NetMeshEdge, int, BasicSlotPool<AVLTreeEntry<NetMeshModelLoader::NetMeshEdge, int>>, DefaultKeyCompare<NetMeshModelLoader::NetMeshEdge>>::DestroyTree(void (AVLTreeBase<NetMeshModelLoader::NetMeshEdge, int, BasicSlotPool<AVLTreeEntry<NetMeshModelLoader::NetMeshEdge, int>>, DefaultKeyCompare<NetMeshModelLoader::NetMeshEdge>>::*)(AVLTreeEntry<NetMeshModelLoader::NetMeshEdge, int>*));
//     void NetMeshEdge, int, BasicSlotPool<AVLTreeEntry<NetMeshModelLoader::NetMeshEdge, int>>, DefaultKeyCompare<NetMeshModelLoader::NetMeshEdge>>::Clear();
//     void NetMeshEdge, int, BasicSlotPool<AVLTreeEntry<NetMeshModelLoader::NetMeshEdge, int>>, DefaultKeyCompare<NetMeshModelLoader::NetMeshEdge>>::~AVLTreeBase();
//     void NetMeshVertex, int, BasicSlotPool<AVLTreeEntry<NetMeshModelLoader::NetMeshVertex, int>>, DefaultKeyCompare<NetMeshModelLoader::NetMeshVertex>>::CastUp(AVLTreeNode*) const;
//     void NetMeshVertex, int, BasicSlotPool<AVLTreeEntry<NetMeshModelLoader::NetMeshVertex, int>>, DefaultKeyCompare<NetMeshModelLoader::NetMeshVertex>>::PostorderTraversal(AVLTreeEntry<NetMeshModelLoader::NetMeshVertex, int>*, void (AVLTreeBase<NetMeshModelLoader::NetMeshVertex, int, BasicSlotPool<AVLTreeEntry<NetMeshModelLoader::NetMeshVertex, int>>, DefaultKeyCompare<NetMeshModelLoader::NetMeshVertex>>::*)(AVLTreeEntry<NetMeshModelLoader::NetMeshVertex, int>*));
//     void NetMeshVertex, int, BasicSlotPool<AVLTreeEntry<NetMeshModelLoader::NetMeshVertex, int>>, DefaultKeyCompare<NetMeshModelLoader::NetMeshVertex>>::DestroyTree(void (AVLTreeBase<NetMeshModelLoader::NetMeshVertex, int, BasicSlotPool<AVLTreeEntry<NetMeshModelLoader::NetMeshVertex, int>>, DefaultKeyCompare<NetMeshModelLoader::NetMeshVertex>>::*)(AVLTreeEntry<NetMeshModelLoader::NetMeshVertex, int>*));
//     void NetMeshVertex, int, BasicSlotPool<AVLTreeEntry<NetMeshModelLoader::NetMeshVertex, int>>, DefaultKeyCompare<NetMeshModelLoader::NetMeshVertex>>::Clear();
//     void NetMeshVertex, int, BasicSlotPool<AVLTreeEntry<NetMeshModelLoader::NetMeshVertex, int>>, DefaultKeyCompare<NetMeshModelLoader::NetMeshVertex>>::~AVLTreeBase();
// };

#endif // _NETMESHMODELLOADER_H_
