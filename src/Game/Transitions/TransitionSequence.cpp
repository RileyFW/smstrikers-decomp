#include "Game/Transitions/TransitionSequence.h"

/**
 * Offset/Address/Size: 0xB0C | 0x80208ED4 | size: 0x38
 */
TransitionSequence::TransitionSequence()
{
    m_pTransitions = NULL;
    m_nNumTransitions = 0;
    m_pPlaying = NULL;
    m_pSound = NULL;
    m_CutAt = -1.0f;
}

/**
 * Offset/Address/Size: 0x9EC | 0x80208DB4 | size: 0x120
 */
TransitionSequence::~TransitionSequence()
{
    if (m_pTransitions != nullptr)
    {
        for (int i = 0; i < m_nNumTransitions; i++)
        {
            delete m_pTransitions[i];
            m_pTransitions[i] = nullptr;

            delete[] m_pSound[i].soundStr;
            m_pSound[i].soundStr = nullptr;
        }

        delete[] m_pTransitions;
        m_pTransitions = nullptr;

        delete[] m_pPlaying;
        m_pPlaying = nullptr;

        delete[] m_pEarly;
        m_pEarly = nullptr;

        delete[] m_pSound;
        m_pSound = nullptr;
    }
}

/**
 * Offset/Address/Size: 0x974 | 0x80208D3C | size: 0x78
 */
void TransitionSequence::DoSanityCheck()
{
    for (int i = 0; i < m_nNumTransitions; i++)
    {
        if (m_pTransitions[i] != nullptr)
        {
            m_pTransitions[i]->DoSanityCheck();
        }
    }
}

/**
 * Offset/Address/Size: 0x718 | 0x80208AE0 | size: 0x25C
 */
void TransitionSequence::Update(float)
{
}

/**
 * Offset/Address/Size: 0x650 | 0x80208A18 | size: 0xC8
 */
void TransitionSequence::Reset()
{
}

/**
 * Offset/Address/Size: 0x5BC | 0x80208984 | size: 0x94
 */
void TransitionSequence::Render(eGLView)
{
}

/**
 * Offset/Address/Size: 0x518 | 0x802088E0 | size: 0xA4
 */
void TransitionSequence::Cancel()
{
}

/**
 * Offset/Address/Size: 0x480 | 0x80208848 | size: 0x98
 */
float TransitionSequence::GetTransitionLength()
{
    float totalLength = 0.0f;

    for (int i = 0; i < m_nNumTransitions; i++)
    {
        float transitionLength = m_pTransitions[i]->GetTransitionLength();
        totalLength += transitionLength;

        totalLength -= m_pEarly[i];
    }

    return totalLength;
}

/**
 * Offset/Address/Size: 0x478 | 0x80208840 | size: 0x8
 */
float TransitionSequence::Time() const
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x438 | 0x80208800 | size: 0x40
 */
bool TransitionSequence::IsFinished()
{
    for (int i = 0; i < m_nNumTransitions; i++)
    {
        if (m_pPlaying[i] != 2)
        {
            return false;
        }
    }

    return true;
}

/**
 * Offset/Address/Size: 0x0 | 0x802083C8 | size: 0x438
 */
void TransitionSequence::Initialize(SimpleParser*)
{
}
