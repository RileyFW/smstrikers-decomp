#include "Game/Physics/PhysicsBanana.h"

#include "Game/Game.h"
#include "Game/AI/Powerups.h"
#include "Game/Character.h"
#include "Game/Player.h"

#include "NL/nlMemory.h"

extern CollisionSpace* g_CollisionSpace;
extern PhysicsWorld* g_PhysicsWorld;

// VTable declarations
extern void* CollisionPowerupGroundData_vtable;
extern void* CollisionPowerupWallData_vtable;

/**
 * Offset/Address/Size: 0x75C | 0x80136190 | size: 0x78
 */
PhysicsBanana::PhysicsBanana(float radius)
    : PhysicsSphere(g_CollisionSpace, g_PhysicsWorld, radius)
{
    m_pTriggerCallbackFunc = NULL;
    m_pCallbackParam = NULL;
    m_pPowerupObject = NULL;
    m_bIsSupportedByGround = false;

    SetCollide(0xEF);
    SetCategory(0x20);

    m_gravity = -32.0f;
}

static const nlVector3 v3Zero = { 0.0f, 0.0f, 0.0f };

/**
 * Offset/Address/Size: 0x648 | 0x8013607C | size: 0x114
 */
void PhysicsBanana::PreUpdate()
{
    PhysicsObject::PreUpdate();
    nlVector3 linVel = GetLinearVelocity();

    float len = nlSqrt((linVel.f.x * linVel.f.x) + (linVel.f.y * linVel.f.y) + (linVel.f.z * linVel.f.z), true);

    if ((m_bIsSupportedByGround) || ((len > 15.0f) && (m_pPowerupObject->m_eType == POWER_UP_BANANA)))
    {
        if (((linVel.f.x * linVel.f.x) + (linVel.f.y * linVel.f.y) + (linVel.f.z * linVel.f.z)) > 0.1f)
        {
            float dumping = -g_pGame->m_pGameTweaks->fBananaResistance / len;
            linVel.f.x = dumping * linVel.f.x;
            linVel.f.y = dumping * linVel.f.y;
            linVel.f.z = dumping * linVel.f.z;
            AddForceAtCentreOfMass(linVel);
            return;
        }

        SetLinearVelocity(v3Zero);
    }
}

/**
 * Offset/Address/Size: 0x63C | 0x80136070 | size: 0xC
 */
void PhysicsBanana::PreCollide()
{
    m_bIsSupportedByGround = false;
}

/**
 * Offset/Address/Size: 0xFC | 0x80135B30 | size: 0x540
 */
ContactType PhysicsBanana::Contact(PhysicsObject* other, dContact* contact, int numContacts)
{
    nlVector3 bananaPos;
    GetPosition(&bananaPos);

    // Check if colliding with ground (object type 0x11)
    if (other->GetObjectType() == 0x11) // PhysicsGroundPlane
    {
        // Loop through all contact points
        for (int i = 0; i < numContacts; i++)
        {
            // Check if contact point is below banana position and has positive depth
            if ((contact[i].geom.pos[1] <= bananaPos.f.y) && (contact[i].geom.depth > 0.0f))
            {
                // Mark banana as supported by ground
                if (!m_bIsSupportedByGround)
                {
                    m_bIsSupportedByGround = true;
                }

                // Get banana's linear velocity
                nlVector3 linVel;
                GetLinearVelocity(&linVel);

                // Check if banana is moving downward (negative Y velocity)
                if (linVel.f.y < 0.0f)
                {
                    // Create collision event for banana hitting ground
                    Event* event = g_pEventManager->CreateValidEvent(0x22, 0x2C);
                    // if (event != nullptr)
                    {
                        CollisionPowerupGroundData* eventData = (CollisionPowerupGroundData*)(&event->m_data);

                        eventData = new (eventData) CollisionPowerupGroundData();

                        // Set banana position
                        GetPosition(&eventData->m_position);
                        eventData->m_velocityY = linVel.f.y;

                        // Set powerup object reference
                        eventData->m_pPowerupObject = m_pPowerupObject;
                    }
                }

                // Call trigger callback if set
                if (m_pTriggerCallbackFunc != nullptr)
                {
                    nlVector3 contactPos;
                    contactPos.f.x = contact[i].geom.pos[0];
                    contactPos.f.y = contact[i].geom.pos[1];
                    contactPos.f.z = contact[i].geom.pos[2];

                    m_pTriggerCallbackFunc(this, other, contactPos, m_pCallbackParam);
                }

                return TWO_WAY_CONTACT; // Contact handled
            }
        }
    }

    // Handle other object types
    int objectType = other->GetObjectType();

    // Switch on object type (0x0D to 0x19 range)
    switch (objectType)
    {
    case 0x0D: // Player
    {
        // Check if player is in possession state
        cPlayer* player = (cPlayer*)other->m_parentObject;
        if (player->m_eClassType == FIELDER)
        {
            cFielder* fielder = (cFielder*)player;
            if (fielder->m_eMovementState == MOVEMENT_FROM_ANIM)
            {
                // Check if banana is already assigned to this player
                if (m_pPowerupObject != nullptr && m_pPowerupObject->m_pThrower == fielder)
                {
                    return NO_CONTACT; // Ignore collision
                }

                // Call trigger callback
                if (m_pTriggerCallbackFunc != nullptr)
                {
                    nlVector3 contactPos;
                    contactPos.f.x = contact[0].geom.pos[0];
                    contactPos.f.y = contact[0].geom.pos[1];
                    contactPos.f.z = contact[0].geom.pos[2];

                    m_pTriggerCallbackFunc(this, other, contactPos, m_pCallbackParam);
                }
            }
        }
        return NO_CONTACT; // Contact handled
    }

    case 0x0E: // Fielder
    {
        cFielder* fielder = (cFielder*)other->m_parentObject;

        // Check if fielder is in possession state
        if (fielder->m_eMovementState == MOVEMENT_FROM_ANIM)
        {
            // Check if banana is already assigned to this fielder
            if (m_pPowerupObject != nullptr && m_pPowerupObject->m_pThrower == fielder)
            {
                return NO_CONTACT; // Ignore collision
            }

            // Check if fielder is away from ball carrier
            if (fielder->IsBallAwayFromCarrier())
            {
                return NO_CONTACT; // Ignore collision
            }

            // Check if fielder has ball
            if (fielder->m_pBall != nullptr /*&& fielder->m_bHasBall*/)
            {
                // Mark powerup as collected
                if (m_pPowerupObject != nullptr)
                {
                    m_pPowerupObject->m_bShouldDestroy = true;
                }
                return NO_CONTACT; // Contact handled
            }

            // Call trigger callback
            if (m_pTriggerCallbackFunc != nullptr)
            {
                nlVector3 contactPos;
                contactPos.f.x = contact[0].geom.pos[0];
                contactPos.f.y = contact[0].geom.pos[1];
                contactPos.f.z = contact[0].geom.pos[2];

                m_pTriggerCallbackFunc(this, other, contactPos, m_pCallbackParam);
            }
        }
        return NO_CONTACT; // Contact handled
    }

    case 0x0F: // Goalie
    {
        // Check if banana is already assigned to this goalie
        if (m_pPowerupObject != nullptr /*&& m_pPowerupObject->m_pThrower == other->m_parentObject*/)
        {
            return NO_CONTACT; // Ignore collision
        }

        // Call trigger callback
        if (m_pTriggerCallbackFunc != nullptr)
        {
            nlVector3 contactPos;
            contactPos.f.x = contact[0].geom.pos[0];
            contactPos.f.y = contact[0].geom.pos[1];
            contactPos.f.z = contact[0].geom.pos[2];

            m_pTriggerCallbackFunc(this, other, contactPos, m_pCallbackParam);
        }
        return NO_CONTACT; // Contact handled
    }

    case 0x10: // Ball
    {
        // Check if banana is already assigned to this ball
        if (m_pPowerupObject != nullptr /*&& m_pPowerupObject->m_pThrower == other->m_parentObject*/)
        {
            return NO_CONTACT; // Ignore collision
        }

        // Call trigger callback
        if (m_pTriggerCallbackFunc != nullptr)
        {
            nlVector3 contactPos;
            contactPos.f.x = contact[0].geom.pos[0];
            contactPos.f.y = contact[0].geom.pos[1];
            contactPos.f.z = contact[0].geom.pos[2];

            m_pTriggerCallbackFunc(this, other, contactPos, m_pCallbackParam);
        }
        return NO_CONTACT; // Contact handled
    }

    case 0x11: // Wall
    {
        // Check if banana is already assigned to this wall
        if (m_pPowerupObject != nullptr /*&& m_pPowerupObject->m_pThrower == other->m_parentObject*/)
        {
            return NO_CONTACT; // Ignore collision
        }

        // Call trigger callback
        if (m_pTriggerCallbackFunc != nullptr)
        {
            nlVector3 contactPos;
            contactPos.f.x = contact[0].geom.pos[0];
            contactPos.f.y = contact[0].geom.pos[1];
            contactPos.f.z = contact[0].geom.pos[2];

            m_pTriggerCallbackFunc(this, other, contactPos, m_pCallbackParam);
        }
        return NO_CONTACT; // Contact handled
    }

    default:
        break;
    }

    // Check for wall collision with high velocity
    bool hasWallContact = false;
    for (int i = 0; i < numContacts; i++)
    {
        if (contact[i].geom.depth < 0.0f)
        {
            hasWallContact = true;
            break;
        }
    }

    if (hasWallContact)
    {
        // Get banana's linear velocity magnitude
        nlVector3 linVel = GetLinearVelocity();
        float velocitySquared = (linVel.f.x * linVel.f.x) + (linVel.f.y * linVel.f.y) + (linVel.f.z * linVel.f.z);

        // Check if velocity is above threshold
        if (velocitySquared > 225.0f) // 15.0f squared
        {
            // Check if colliding with wall (object type 0x19)
            if (other->GetObjectType() == 0x19) // PhysicsWall
            {
                // Create collision event for banana hitting wall
                Event* event = g_pEventManager->CreateValidEvent(0x21, 0x3C);
                // if (event != nullptr)
                // {
                CollisionPowerupWallData* eventData = (CollisionPowerupWallData*)(&event->m_data);
                eventData = new (eventData) CollisionPowerupWallData();

                // Set powerup object references
                eventData->m_pPowerupObject = m_pPowerupObject;
                eventData->m_pThrower = m_pPowerupObject->m_pThrower;

                // Set contact position
                eventData->m_contactPos.f.x = contact[0].geom.pos[0];
                eventData->m_contactPos.f.y = contact[0].geom.pos[1];
                eventData->m_contactPos.f.z = contact[0].geom.pos[2];

                // Set contact normal
                eventData->m_contactNormal.f.x = contact[0].geom.normal[0];
                eventData->m_contactNormal.f.y = contact[0].geom.normal[1];
                eventData->m_contactNormal.f.z = contact[0].geom.normal[2];
                // }
            }
        }
    }

    return TWO_WAY_CONTACT; // Contact handled
}

/**
 * Offset/Address/Size: 0x70 | 0x80135AA4 | size: 0x8C
 */
bool PhysicsBanana::SetContactInfo(dContact* contact, PhysicsObject* other, bool first)
{
    if (first)
    {
        SetDefaultContactInfo(contact);
    }

    if (other->GetObjectType() == 0x11)
    {
        contact->surface.bounce = g_pGame->m_pGameTweaks->fShellBounceGround;
    }
    else
    {
        contact->surface.bounce = 0.01f;
    }
    contact->surface.bounce_vel = 0.0f;
    contact->surface.mu = 10.0f;

    return true;
}

/**
 * Offset/Address/Size: 0x0 | 0x80135A34 | size: 0x70
 */
PhysicsBanana::~PhysicsBanana()
{
}
