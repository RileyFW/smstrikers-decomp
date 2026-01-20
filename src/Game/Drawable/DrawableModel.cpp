#include "Game/Drawable/DrawableModel.h"
#include "Game/Render/RenderShadow.h"
#include "NL/gl/glMatrix.h"

extern bool g_bShadowVolumes;

static float sfCoPlanarZ;
static float sfCoPlanar0Z;
static float sfPlanarShadowOpacity;

/**
 * Offset/Address/Size: 0x0 | 0x8011FE0C | size: 0x3C
 */
void CleanBoundingBoxCache()
{
}

/**
 * Offset/Address/Size: 0x3C | 0x8011FE48 | size: 0x26C
 */
void RenderBoundingBox(const glModel*, const nlMatrix4&)
{
}

/**
 * Offset/Address/Size: 0x2A8 | 0x801200B4 | size: 0x8
 */
float GetCoPlanar0Z()
{
    return sfCoPlanar0Z;
}

/**
 * Offset/Address/Size: 0x2B0 | 0x801200BC | size: 0x8
 */
void SetCoPlanarZ(float z)
{
    sfCoPlanarZ = z;
}

/**
 * Offset/Address/Size: 0x2B8 | 0x801200C4 | size: 0x8
 */
float GetCoPlanarZ()
{
    return sfCoPlanarZ;
}

/**
 * Offset/Address/Size: 0x2C0 | 0x801200CC | size: 0x8
 */
void SetPlanarShadowOpacity(float opacity)
{
    sfPlanarShadowOpacity = opacity;
}

/**
 * Offset/Address/Size: 0x2C8 | 0x801200D4 | size: 0x8
 */
float GetPlanarShadowOpacity()
{
    return sfPlanarShadowOpacity;
}

/**
 * Offset/Address/Size: 0x2D0 | 0x801200DC | size: 0x460
 */
void DrawPlanarShadow(const glModel*, const nlMatrix4&, float, bool, bool, bool, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x730 | 0x8012053C | size: 0x234
 */
void DrawCoPlanarReference(eGLView, const glModel&, const nlMatrix4&, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x964 | 0x80120770 | size: 0x290
 */
void GetShadowBoundingSquare(const glModel*, const nlMatrix4&, float&, float&, float&, float&, unsigned long)
{
}

/**
 * Offset/Address/Size: 0xBF4 | 0x80120A00 | size: 0x84
 */
void DrawableModel::DrawPlanarShadow()
{
    glModel* model = glModelDupNoStreams(m_pModel, true, false);
    f32 opacity = sfPlanarShadowOpacity;
    const nlMatrix4& worldMtx = GetWorldMatrix();
    ::DrawPlanarShadow(model, worldMtx, opacity * m_translucency, true, false, true, (unsigned long)this);
}

/**
 * Offset/Address/Size: 0xC78 | 0x80120A84 | size: 0x78
 */
void DrawableShadow::Draw()
{
    if (g_bShadowVolumes) {
        u32 mtx;
        nlMatrix4& worldMtx = GetWorldMatrix();
        mtx = glAllocMatrix();
        if (mtx + 0x10000 != 0xFFFF) {
            glSetMatrix(mtx, worldMtx);
        }
        RenderShadowModel(2, m_pModel, mtx);
    }
}

/**
 * Offset/Address/Size: 0xCF0 | 0x80120AFC | size: 0x28
 */
void DrawableModel::GetAABBDimensions(AABBDimensions&, bool) const
{
}

/**
 * Offset/Address/Size: 0xD18 | 0x80120B24 | size: 0x38C
 */
void GetAABBDimensions(const glModel*, AABBDimensions&, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x10A4 | 0x80120EB0 | size: 0x1C8
 */
bool DrawableModel::Clone() const
{
    return false;
}

/**
 * Offset/Address/Size: 0x126C | 0x80121078 | size: 0x38
 */
void DrawableModel::Draw()
{
}

/**
 * Offset/Address/Size: 0x12A4 | 0x801210B0 | size: 0x598
 */
void DrawableModel::DrawModel(const nlMatrix4&)
{
}

/**
 * Offset/Address/Size: 0x183C | 0x80121648 | size: 0x598
 */
void Fresnelify(glModelPacket*, eGLView)
{
}

/**
 * Offset/Address/Size: 0x1DD4 | 0x80121BE0 | size: 0x214
 */
void DrawBallShadow(const nlVector3&, const BallShadowParams&, bool)
{
}

/**
 * Offset/Address/Size: 0x1FE8 | 0x80121DF4 | size: 0x60
 */
DrawableModel::~DrawableModel()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80121E54 | size: 0x60
 */
DrawableShadow::~DrawableShadow()
{
}

/**
 * Offset/Address/Size: 0x60 | 0x80121EB4 | size: 0x60
 */
// void nlAVLTreeSlotPool<unsigned long, AABBDimensions, DefaultKeyCompare<unsigned long>>::~nlAVLTreeSlotPool()
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x80121F14 | size: 0x58
 */
// void AVLTreeBase<unsigned long, AABBDimensions, BasicSlotPool<AVLTreeEntry<unsigned long, AABBDimensions>>, DefaultKeyCompare<unsigned long>>::Clear()
// {
// }

/**
 * Offset/Address/Size: 0x58 | 0x80121F6C | size: 0x64
 */
// void AVLTreeBase<unsigned long, AABBDimensions, BasicSlotPool<AVLTreeEntry<unsigned long, AABBDimensions>>, DefaultKeyCompare<unsigned long>>::DestroyTree(void (AVLTreeBase<unsigned long, AABBDimensions, BasicSlotPool<AVLTreeEntry<unsigned long, AABBDimensions>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, AABBDimensions>*))
// {
// }

/**
 * Offset/Address/Size: 0xBC | 0x80121FD0 | size: 0x758
 */
// void AVLTreeBase<unsigned long, AABBDimensions, BasicSlotPool<AVLTreeEntry<unsigned long, AABBDimensions>>, DefaultKeyCompare<unsigned long>>::PostorderTraversal(AVLTreeEntry<unsigned long, AABBDimensions>*, void (AVLTreeBase<unsigned long, AABBDimensions, BasicSlotPool<AVLTreeEntry<unsigned long, AABBDimensions>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, AABBDimensions>*))
// {
// }

/**
 * Offset/Address/Size: 0x814 | 0x80122728 | size: 0x8
 */
// void AVLTreeBase<unsigned long, AABBDimensions, BasicSlotPool<AVLTreeEntry<unsigned long, AABBDimensions>>, DefaultKeyCompare<unsigned long>>::CastUp(AVLTreeNode*) const
// {
// }

/**
 * Offset/Address/Size: 0x81C | 0x80122730 | size: 0x10
 */
// void AVLTreeBase<unsigned long, AABBDimensions, BasicSlotPool<AVLTreeEntry<unsigned long, AABBDimensions>>, DefaultKeyCompare<unsigned long>>::DeleteEntry(AVLTreeEntry<unsigned long, AABBDimensions>*)
// {
// }

/**
 * Offset/Address/Size: 0x958 | 0x8012286C | size: 0x7C
 */
// void AVLTreeBase<unsigned long, AABBDimensions, BasicSlotPool<AVLTreeEntry<unsigned long, AABBDimensions>>, DefaultKeyCompare<unsigned long>>::~AVLTreeBase()
// {
// }

/**
 * Offset/Address/Size: 0x9D4 | 0x801228E8 | size: 0x2C
 */
// void AVLTreeBase<unsigned long, AABBDimensions, BasicSlotPool<AVLTreeEntry<unsigned long, AABBDimensions>>, DefaultKeyCompare<unsigned long>>::CompareNodes(AVLTreeNode*, AVLTreeNode*)
// {
// }

/**
 * Offset/Address/Size: 0xA00 | 0x80122914 | size: 0x2C
 */
// void AVLTreeBase<unsigned long, AABBDimensions, BasicSlotPool<AVLTreeEntry<unsigned long, AABBDimensions>>, DefaultKeyCompare<unsigned long>>::CompareKey(void*, AVLTreeNode*)
// {
// }

/**
 * Offset/Address/Size: 0xA2C | 0x80122940 | size: 0xE0
 */
// void AVLTreeBase<unsigned long, AABBDimensions, BasicSlotPool<AVLTreeEntry<unsigned long, AABBDimensions>>, DefaultKeyCompare<unsigned long>>::AllocateEntry(void*, void*)
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x80122A20 | size: 0x8
 */
bool DrawableModel::IsDrawableModel()
{
    return true;
}

/**
 * Offset/Address/Size: 0x8 | 0x80122A28 | size: 0x4
 */
DrawableModel* DrawableModel::AsDrawableModel()
{
    return NULL;
}
