#include "Game/Physics/PhysicsNPC.h"
#include "Game/Render/SkinAnimatedMovableNPC.h"

#include "Game/Player.h"

extern CollisionSpace* g_CollisionSpace;

/**
 * Offset/Address/Size: 0x440 | 0x8013B8F8 | size: 0x68
 */
PhysicsNPC::PhysicsNPC(float radius)
    : PhysicsSphere(g_CollisionSpace, (PhysicsWorld*)0, radius)
{
    mpTriggerCallbackFunc = NULL;
    mpAINPC = NULL;

    SetCollide(0x00);
    SetCategory(0xFF);
}

/**
 * Offset/Address/Size: 0x438 | 0x8013B8F0 | size: 0x8
 */
void PhysicsNPC::SetCallbackFunction(CallbackFn cb)
{
    mpTriggerCallbackFunc = cb;
}

enum ContactType
{
    NO_CONTACT = 0,
    ONE_WAY_CONTACT_THIS = 1,
    ONE_WAY_CONTACT_OTHER = 2,
    TWO_WAY_CONTACT = 3,
};

/**
 * Offset/Address/Size: 0xC0 | 0x8013B578 | size: 0x378
 */
int PhysicsNPC::Contact(PhysicsObject* other, dContact* contact, int what)
{
    nlVector3 position;
    GetPosition(&position);

    int objectType = other->GetObjectType();

    switch (objectType - 4)
    {
    case 0: // Object type 4 - PhysicsCharacterBase (0x08)
    {
        // Check if the other object is a player (type 2)
        if (other->m_parentObject != nullptr)
        {
            cPlayer* player = (cPlayer*)(other->m_parentObject);
            if (player->m_eClassType == 2) // Player type
            {
                bool shouldTrigger = true;

                // Check if this NPC is a Chain Chomp (type 3)
                if (mpAINPC != nullptr)
                {
                    SkinAnimatedNPC_Type npcType = mpAINPC->GetSkinAnimatedNPC_Type();
                    if (npcType == SkinAnimatedNPC_CHAIN_CHOMP) // 3
                    {
                        // Check if they're on the same team
                        cPlayer* npcPlayer = (cPlayer*)(mpAINPC);
                        if (!npcPlayer->IsOnSameTeam(player))
                        {
                            shouldTrigger = false;
                        }
                    }
                }

                if (shouldTrigger && mpTriggerCallbackFunc != nullptr)
                {
                    // Call the callback with contact position
                    nlVector3 contactPos;
                    contactPos.f.x = contact->geom.pos[0];
                    contactPos.f.y = contact->geom.pos[1];
                    contactPos.f.z = contact->geom.pos[2];
                    mpTriggerCallbackFunc(this, other, contactPos);
                }

                return shouldTrigger ? 0 : 0;
            }
        }

        // Check if other object is type 3 (some other player type)
        if (other->m_parentObject != nullptr)
        {
            cPlayer* player = (cPlayer*)(other->m_parentObject);
            if (player->m_eClassType == 3)
            {
                // Check if this NPC is Bowser (type 4)
                if (mpAINPC != nullptr)
                {
                    SkinAnimatedNPC_Type npcType = mpAINPC->GetSkinAnimatedNPC_Type();
                    if (npcType == SkinAnimatedNPC_BOWSER) // 4
                    {
                        return 2;
                    }
                }
            }
        }
        break;
    }

    case 1: // Object type 5 - PhysicsBall (0x0A)
    {
        // Get the ball object
        cBall* ball = (cBall*)(other->m_parentObject);
        if (ball != nullptr)
        {
            // Reset some ball state
            // ball->m_bIsSupportedByGround = false;
            // ball->m_bBallPathChangeCount = 0;

            // Check if ball has a parent object (player holding it)
            // if (ball->m_pParentObject != nullptr)
            if (ball != nullptr)
            {
                cPlayer* ballOwner = nullptr;     //(cPlayer*)(ball->m_pParentObject);
                if (ballOwner->m_eClassType == 2) // Player type
                {
                    bool shouldTrigger = true;

                    // Check if this NPC is a Chain Chomp (type 3)
                    if (mpAINPC != nullptr)
                    {
                        SkinAnimatedNPC_Type npcType = mpAINPC->GetSkinAnimatedNPC_Type();
                        if (npcType == SkinAnimatedNPC_CHAIN_CHOMP) // 3
                        {
                            // Check if they're on the same team
                            cPlayer* npcPlayer = (cPlayer*)(mpAINPC);
                            if (!npcPlayer->IsOnSameTeam(ballOwner))
                            {
                                shouldTrigger = false;
                            }
                        }
                    }

                    if (shouldTrigger && mpTriggerCallbackFunc != nullptr)
                    {
                        // Call the callback with contact position
                        nlVector3 contactPos;
                        contactPos.f.x = contact->geom.pos[0];
                        contactPos.f.y = contact->geom.pos[1];
                        contactPos.f.z = contact->geom.pos[2];
                        mpTriggerCallbackFunc(this, other, contactPos);
                    }

                    return shouldTrigger ? 0 : 0;
                }
            }
            else
            {
                // Ball is loose, check if it has a powerup or special state
                // if (ball->m_pPowerupObject != nullptr && ball->m_bHasPowerup)
                if (ball != nullptr)
                {
                    return 0; // Don't trigger if ball has powerup
                }

                if (mpTriggerCallbackFunc != nullptr)
                {
                    // Call the callback with contact position
                    nlVector3 contactPos;
                    contactPos.f.x = contact->geom.pos[0];
                    contactPos.f.y = contact->geom.pos[1];
                    contactPos.f.z = contact->geom.pos[2];
                    mpTriggerCallbackFunc(this, other, contactPos);
                }

                // Reset ball state and invalidate cache
                // other->m_bIsTriggered = false;
                // FakeBallWorld::InvalidateBallCache();
                return 2;
            }
        }
        break;
    }

    case 2: // Object type 6 - PhysicsWall (0x19)
    {
        // Check if wall has a parent object
        if (other->m_parentObject != nullptr)
        {
            if (mpAINPC != nullptr)
            {
                SkinAnimatedNPC_Type npcType = mpAINPC->GetSkinAnimatedNPC_Type();
                if (npcType == SkinAnimatedNPC_BOWSER) // 4
                {
                    // Check if wall has no special state
                    // if (other->m_specialState == 0)
                    {
                        return 0;
                    }
                }
            }
        }

        if (mpTriggerCallbackFunc != nullptr)
        {
            // Call the callback with contact position
            nlVector3 contactPos;
            contactPos.f.x = contact->geom.pos[0];
            contactPos.f.y = contact->geom.pos[1];
            contactPos.f.z = contact->geom.pos[2];
            mpTriggerCallbackFunc(this, other, contactPos);
        }
        break;
    }

    case 3: // Object type 7 - PhysicsFinitePlane (0x7)
    {
        if (other->m_parentObject != nullptr)
        {
            if (mpAINPC != nullptr)
            {
                SkinAnimatedNPC_Type npcType = mpAINPC->GetSkinAnimatedNPC_Type();
                if (npcType == SkinAnimatedNPC_BOWSER) // 4
                {
                    // if (other->m_specialState == 0)
                    {
                        return 0;
                    }
                }
            }
        }

        if (mpTriggerCallbackFunc != nullptr)
        {
            nlVector3 contactPos;
            contactPos.f.x = contact->geom.pos[0];
            contactPos.f.y = contact->geom.pos[1];
            contactPos.f.z = contact->geom.pos[2];
            mpTriggerCallbackFunc(this, other, contactPos);
        }
        break;
    }

    default:
        break;
    }

    if (mpAINPC != nullptr)
    {
        if (mpAINPC->GetSkinAnimatedNPC_Type() == SkinAnimatedNPC_BOWSER)
        {
            return ONE_WAY_CONTACT_OTHER;
        }
    }

    return NO_CONTACT;
}

/**
 * Offset/Address/Size: 0x70 | 0x8013B528 | size: 0x50
 */
bool PhysicsNPC::SetContactInfo(dContact* contact, PhysicsObject* /*other*/, bool first)
{
    if (first)
    {
        SetDefaultContactInfo(contact);
    }

    contact->surface.bounce = 0.01f;
    contact->surface.bounce_vel = 0.0f;
    contact->surface.mu = 5.0f;

    return true;
}
