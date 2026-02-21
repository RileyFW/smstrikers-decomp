#include "Game/GL/GLRenderBuffer.h"

#include "NL/nlMemory.h"

bool GLRenderBuffer::m_bInstance = false;

u32 glRenderBuffer[4];

// /**
//  * Offset/Address/Size: 0x60 | 0x801E81CC | size: 0x58
//  */
// void 0x8028D548..0x8028D54C | size : 0x4
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801E816C | size: 0x60
//  */
// void nlWalkRing<DLListEntry<GLDrawableData*>, DLListContainerBase<GLDrawableData*, NewAdapter<DLListEntry<GLDrawableData*> > > >(DLListEntry<GLDrawableData*>*, DLListContainerBase<GLDrawableData*, NewAdapter<DLListEntry<GLDrawableData*> > >*, void (DLListContainerBase<GLDrawableData*, NewAdapter<DLListEntry<GLDrawableData*> > >::*)(DLListEntry<GLDrawableData*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x5C | 0x801E8154 | size: 0x18
//  */
// void nlDLRingGetStart<DLListEntry<GLDrawableData*> >(DLListEntry<GLDrawableData*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x3C | 0x801E8134 | size: 0x20
//  */
// void nlDLRingIsEnd<DLListEntry<GLDrawableData*> >(DLListEntry<GLDrawableData*>*, DLListEntry<GLDrawableData*>*)
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x801E80F8 | size: 0x3C
 * TODO: 96% match - compiler instruction scheduling: stw r0,0x24(r1) (LR save)
 * placed immediately after mflr instead of after first lwz from r5.
 * Cannot fix via source code - MWCC scheduler heuristic difference.
 * Implementation is template instantiation from nlDLRing.h:268-273
 */
// void nlWalkDLRing<DLListEntry<GLDrawableData*>, DLListContainerBase<GLDrawableData*, NewAdapter<DLListEntry<GLDrawableData*> > > >(DLListEntry<GLDrawableData*>*, DLListContainerBase<GLDrawableData*, NewAdapter<DLListEntry<GLDrawableData*> > >*, void (DLListContainerBase<GLDrawableData*, NewAdapter<DLListEntry<GLDrawableData*> > >::*)(DLListEntry<GLDrawableData*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801E80D4 | size: 0x24
//  */
// void DLListContainerBase<GLDrawableData*, NewAdapter<DLListEntry<GLDrawableData*> > >::DeleteEntry(DLListEntry<GLDrawableData*>*)
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x801E7FB0 | size: 0x124
 */
GLRenderBuffer::~GLRenderBuffer()
{
    DLListEntry<GLDrawableData*>* current = nlDLRingGetStart<DLListEntry<GLDrawableData*> >(m_drawableData.m_Head);
    DLListEntry<GLDrawableData*>* head = m_drawableData.m_Head;

    while (current != nullptr)
    {
        nlFree(current->m_data);

        if (nlDLRingIsEnd<DLListEntry<GLDrawableData*> >(head, current))
        {
            current = nullptr;
        }
        else
        {
            current = current->m_next;
        }
    }

    m_drawableData.m_Head = nullptr;

    nlWalkDLRing<DLListEntry<GLDrawableData*>, DLListContainerBase<GLDrawableData*, NewAdapter<DLListEntry<GLDrawableData*> > > >(
        m_drawableData.m_Head,
        &m_drawableData,
        &DLListContainerBase<GLDrawableData*, NewAdapter<DLListEntry<GLDrawableData*> > >::DeleteEntry);

    m_drawableData.m_Head = nullptr;
}
