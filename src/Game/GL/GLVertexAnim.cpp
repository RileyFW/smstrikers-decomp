#include "Game/GL/GLVertexAnim.h"

/**
 * Offset/Address/Size: 0x198 | 0x801E7E30 | size: 0x40
 */
GLVertexAnim::GLVertexAnim()
{
    m_unk_0x00 = -1;
    m_unk_0x04 = 0;
    m_unk_0x08 = 0;
    m_unk_0x0C = 30.0f;
    m_unk_0x10 = 0;
    m_unk_0x14 = false;
    m_unk_0x1C = 0.0f;
    m_unk_0x18 = 1.0f;
    m_frames = NULL;
    m_unk_0x24 = NULL;
}

/**
 * Offset/Address/Size: 0xBC | 0x801E7D54 | size: 0xDC
 */
void GLVertexAnim::GetModel(int frameIndex)
{
    int actualFrame = (frameIndex < 0) ? (int)m_unk_0x1C : frameIndex;

    glModel* model = glModelDup(m_unk_0x24, true);
    FrameVertexData* frameVertexData = m_frames + actualFrame * m_unk_0x08;

    for (glModelPacket* packet = model->packets; packet < model->packets + model->numPackets; packet++)
    {
        VertexData* packetVertexData = packet->m_vertexData;
        VertexData* endVertexData = packetVertexData + packet->numStreams;
        while (packetVertexData < endVertexData)
        {
            if (packetVertexData->m_unk_0x04 == 0)
            {
                packetVertexData->m_unk_0x00 = frameVertexData;
                break;
            }
            packetVertexData++;
        }
    }
}

/**
 * Offset/Address/Size: 0x1C | 0x801E7CB4 | size: 0xA0
 */
void GLVertexAnim::Update(float arg0)
{
    if (m_unk_0x14)
    {
        return; // Early return if animation is stopped
    }

    // Update animation progress
    m_unk_0x1C += m_unk_0x0C * (m_unk_0x18 * arg0);

    // Check if animation has completed
    if (m_unk_0x1C >= m_unk_0x04)
    {
        if (m_unk_0x10 == 1)
        {
            // Stop animation at the end
            m_unk_0x14 = true;
            m_unk_0x1C = m_unk_0x04 - 1;
        }
        else
        {
            // Loop animation
            m_unk_0x1C = 0.0f;
        }
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x801E7C98 | size: 0x1C
 */
void GLVertexAnim::Reset()
{
    m_unk_0x18 = 1.0f;
    m_unk_0x1C = 0.0f;
    m_unk_0x14 = false;
}
