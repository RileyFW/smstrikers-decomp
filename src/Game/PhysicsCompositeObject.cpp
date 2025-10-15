#include "Game/Physics/PhysicsCompositeObject.h"

#include "Game/Physics/PhysicsWorld.h"
#include "Game/Physics/PhysicsObject.h"

#include "NL/nlMemory.h"

/**
 * Offset/Address/Size: 0x0 | 0x801FF6A8 | size: 0xA8
 */
void PhysicsCompositeObject::AdjustTransform(int index, nlMatrix4& transform)
{
    DLListEntry<PhysicsTransform*>* head;
    DLListEntry<PhysicsTransform*>* current = nlDLRingGetStart<DLListEntry<PhysicsTransform*> >(m_Components.m_Head);

    head = m_Components.m_Head;

    u32 i = 0;
    do
    {
        if (nlDLRingIsEnd<DLListEntry<PhysicsTransform*> >(head, current) != 0)
        {
            current = nullptr;
            break;
        }

        if ((nlDLRingIsEnd<DLListEntry<PhysicsTransform*> >(head, current) != 0) || (current == NULL))
        {
            current = NULL;
        }
        else
        {
            current = current->m_next;
        }

        i++;
    } while (i < index);

    PhysicsTransform* transformObj = (PhysicsTransform*)current->m_data;
    transformObj->SetSubObjectTransform(transform, PhysicsObject::RELATIVE_TO_PARENT);
}

/**
 * Offset/Address/Size: 0xA8 | 0x801FF750 | size: 0xBC
 */
int PhysicsCompositeObject::AddObject(PhysicsObject* object)
{
    object->MakeStatic();
    PhysicsTransform* transform = (PhysicsTransform*)nlMalloc(0x30, 8, 0);
    if (transform != nullptr)
    {
        transform = new (transform) PhysicsTransform();
    }

    transform->Attach(object, this);

    DLListEntry<PhysicsTransform*>* entry = (DLListEntry<PhysicsTransform*>*)nlMalloc(0xC, 8, 0);

    if (entry != nullptr)
    {
        entry->m_next = nullptr;
        entry->m_prev = nullptr;
        entry->m_data = &transform;
    }

    nlDLRingAddEnd<DLListEntry<PhysicsTransform*> >(&m_Components.m_Head, entry);

    numComponents++;

    return numComponents - 1;
}

/**
 * Offset/Address/Size: 0x164 | 0x801FF80C | size: 0x110
 */
PhysicsCompositeObject::~PhysicsCompositeObject()
{
    DLListEntry<PhysicsTransform*>* current = nlDLRingGetStart<DLListEntry<PhysicsTransform*> >(m_Components.m_Head);

    while (current != nullptr)
    {
        PhysicsTransform* transform = (PhysicsTransform*)current->m_data;

        // if (transform != nullptr)
        {
            transform->m_parentObject = nullptr;

            delete transform;
        }

        if (nlDLRingIsEnd<DLListEntry<PhysicsTransform*> >(m_Components.m_Head, current))
        {
            current = nullptr;
        }
        else
        {
            current = current->m_next;
        }
    }

    if (m_Components.m_Head != nullptr)
    {
        nlWalkDLRing<DLListEntry<PhysicsTransform*>, DLListContainerBase<PhysicsTransform*, NewAdapter<DLListEntry<PhysicsTransform*> > > >(
            m_Components.m_Head,
            &m_Components,
            &DLListContainerBase<PhysicsTransform*, NewAdapter<DLListEntry<PhysicsTransform*> > >::DeleteEntry);

        m_Components.m_Head = nullptr;
    }
}

/**
 * Offset/Address/Size: 0x274 | 0x801FF91C | size: 0x54
 */
PhysicsCompositeObject::PhysicsCompositeObject(PhysicsWorld* physicsWorld)
    : PhysicsObject(physicsWorld)
{
    m_Components.m_Head = nullptr;
    numComponents = 0;
    dBodySetData(m_bodyID, this);
}

/**
 * Offset/Address/Size: 0x0 | 0x801FF970 | size: 0x8
 */
// int PhysicsCompositeObject::GetObjectType() const
// {
//     return 0x9;
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801FF978 | size: 0x24
//  */
// void DLListContainerBase<PhysicsTransform*, NewAdapter<DLListEntry<PhysicsTransform*>>>::DeleteEntry(DLListEntry<PhysicsTransform*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801FF99C | size: 0x3C
//  */
// void nlWalkDLRing<DLListEntry<PhysicsTransform*>, DLListContainerBase<PhysicsTransform*,
// NewAdapter<DLListEntry<PhysicsTransform*>>>>(DLListEntry<PhysicsTransform*>*, DLListContainerBase<PhysicsTransform*,
// NewAdapter<DLListEntry<PhysicsTransform*>>>*, void (DLListContainerBase<PhysicsTransform*,
// NewAdapter<DLListEntry<PhysicsTransform*>>>::*)(DLListEntry<PhysicsTransform*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x3C | 0x801FF9D8 | size: 0x20
//  */
// void nlDLRingIsEnd<DLListEntry<PhysicsTransform*>>(DLListEntry<PhysicsTransform*>*, DLListEntry<PhysicsTransform*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x5C | 0x801FF9F8 | size: 0x18
//  */
// void nlDLRingGetStart<DLListEntry<PhysicsTransform*>>(DLListEntry<PhysicsTransform*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x74 | 0x801FFA10 | size: 0x3C
//  */
// void nlDLRingAddEnd<DLListEntry<PhysicsTransform*>>(DLListEntry<PhysicsTransform*>**, DLListEntry<PhysicsTransform*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0xB0 | 0x801FFA4C | size: 0x38
//  */
// void nlDLRingAddStart<DLListEntry<PhysicsTransform*>>(DLListEntry<PhysicsTransform*>**, DLListEntry<PhysicsTransform*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801FFA84 | size: 0x60
//  */
// void nlWalkRing<DLListEntry<PhysicsTransform*>, DLListContainerBase<PhysicsTransform*,
// NewAdapter<DLListEntry<PhysicsTransform*>>>>(DLListEntry<PhysicsTransform*>*, DLListContainerBase<PhysicsTransform*,
// NewAdapter<DLListEntry<PhysicsTransform*>>>*, void (DLListContainerBase<PhysicsTransform*,
// NewAdapter<DLListEntry<PhysicsTransform*>>>::*)(DLListEntry<PhysicsTransform*>*))
// {
// }
