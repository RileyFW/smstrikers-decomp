#include "Game/PoseAccumulator.h"
#include "NL/nlMemory.h"

#include "math.h"
#include "types.h"

static const nlQuaternion qRotIdentity = { 0, 0, 0, 1 };
static nlVector3 v3ScaleIdentity = { 1.0f, 1.0f, 1.0f };
static nlVector3 v3TransIdentity = { 0.0f, 0.0f, 0.0f };

extern const nlMatrix4 kPose64Template;
extern const RotAccum kRotAccumTemplate;
extern const ScaleAccum kScaleAccumTemplate;
extern const TransAccum kTransAccumTemplate;

/**
 * Offset/Address/Size: 0xCD8 | 0x801EC278 | size: 0x1D74
 */
cPoseAccumulator::cPoseAccumulator(cSHierarchy* h, bool withSecondary)
{
    FORCE_DONT_INLINE;

    m_BaseSHierarchy = h;

    const int n = h->m_nodeCount; // boneCount
    int i;

    {
        const int count = n + 1;
        m_NodeMatrices.mData = (nlMatrix4*)nlMalloc(count * sizeof(nlMatrix4), 8, 0);
        m_NodeMatrices.mSize = count;
        m_NodeMatrices.mCapacity = count;

        for (i = 0; i < count; ++i)
        {
            m_NodeMatrices.mData[i] = kPose64Template; // copy 0x40 bytes template
        }
    }

    {
        const int countB = withSecondary ? (n + 1) : 0;
        m_PrevNodeMatrices.mData = (nlMatrix4*)nlMalloc((unsigned long)(countB * sizeof(nlMatrix4)), 8, 0);
        m_PrevNodeMatrices.mSize = countB;
        m_PrevNodeMatrices.mCapacity = countB;

        for (i = 0; i < countB; ++i)
        {
            m_PrevNodeMatrices.mData[i] = kPose64Template;
        }
    }

    {
        m_rot.mData = (RotAccum*)nlMalloc((unsigned long)(n * sizeof(RotAccum)), 8, 0);
        m_rot.mSize = n;
        m_rot.mCapacity = n;

        for (i = 0; i < n; ++i)
        {
            m_rot.mData[i] = kRotAccumTemplate;
        }
    }

    {
        m_scale.mData = (ScaleAccum*)nlMalloc((unsigned long)(n * sizeof(ScaleAccum)), 8, 0);
        m_scale.mSize = n;
        m_scale.mCapacity = n;
        // m_unk_0x2C = n;
        // m_unk_0x30 = n;

        for (i = 0; i < n; ++i)
        {
            m_scale.mData[i] = kScaleAccumTemplate;
        }
    }

    {
        m_trans.mData = (TransAccum*)nlMalloc((unsigned long)(n * sizeof(TransAccum)), 8, 0);
        m_trans.mSize = n;
        m_trans.mCapacity = n;
        // m_unk_0x38 = n;
        // m_unk_0x3C = n;

        for (i = 0; i < n; ++i)
        {
            m_trans.mData[i] = kTransAccumTemplate; // zero/locked baseline
        }
    }

    {
        void* buffer = nlMalloc(n * sizeof(cBuildNodeMatrixCallbackInfo), 8, 0);
        m_cb.mData = new (buffer) cBuildNodeMatrixCallbackInfo[n];
        m_cb.mSize = n;
        m_cb.mCapacity = n;

        // m_unk_0x44 = n;
        // m_unk_0x48 = n;

        for (i = 0; i < n; ++i)
        {
            new (&m_cb.mData[i]) cBuildNodeMatrixCallbackInfo(); // Call constructor manually
        }
    }

    {
        m_MorphWeights.mData = (float*)nlMalloc((unsigned long)(8 * sizeof(float)), 8, 0);
        m_MorphWeights.mSize = 8;
        // m_floatCount = 8;

        for (i = 0; i < 8; ++i)
        {
            m_MorphWeights.mData[i] = 0.0f;
        }
    }

    for (i = 0; i < n; ++i)
    {
        if (m_BaseSHierarchy->PreserveBoneLength(i))
        {
            const nlVector3* t = m_BaseSHierarchy->GetTranslationOffset(i);
            m_trans.mData[i].t.f.x = t->f.x;
            m_trans.mData[i].t.f.y = t->f.y;
            m_trans.mData[i].t.f.z = t->f.z;
            m_trans.mData[i].fAccumulatedWeight = 1.0f;
            m_trans.mData[i].bIdentity = false;
        }
    }
}

/**
 * Offset/Address/Size: 0xB7C | 0x801EC11C | size: 0x15C
 */
void cPoseAccumulator::Pose(const cPoseNode& node, const nlMatrix4& mat)
{
    int i;
    for (i = 0; i < m_BaseSHierarchy->m_nodeCount; i++)
    {
        RotAccum& r = m_rot.mData[i];
        r.q.f.x = 0.0f;
        r.q.f.y = 0.0f;
        r.q.f.z = 0.0f;
        r.q.f.w = 1.0f;
        r.quatAccumulatedWeight = 0.0f;
        r.rotAroundZ = 0;
        r.rotAroundZAccumulatedWeight = 0.0f;
        r.bIdentity = true;

        ScaleAccum& s = m_scale.mData[i];
        s.s.f.x = 1.0f;
        s.s.f.y = 1.0f;
        s.s.f.z = 1.0f;
        s.fAccumulatedWeight = 0.0f;
        s.bIdentity = true;

        if (!m_BaseSHierarchy->PreserveBoneLength(i))
        {
            TransAccum& t = m_trans.mData[i];
            t.t.f.x = 0.0f;
            t.t.f.y = 0.0f;
            t.t.f.z = 0.0f;
            t.fAccumulatedWeight = 0.0f;
            t.bIdentity = true;
        }
    }

    for (i = 0; i < m_MorphWeights.mSize; i++)
    {
        m_MorphWeights.mData[i] = 0.0f;
    }

    node.Evaluate(1.0f, this);

    BuildNodeMatrices(mat);
}

/**
 * Offset/Address/Size: 0xA38 | 0x801EBFD8 | size: 0x144
 */
void cPoseAccumulator::InitAccumulators()
{
    for (int i = 0; i < m_BaseSHierarchy->m_nodeCount; ++i)
    {
        RotAccum& r = m_rot.mData[i];
        r.q.f.x = 0.0f;
        r.q.f.y = 0.0f;
        r.q.f.z = 0.0f;
        r.q.f.w = 1.0f;
        r.quatAccumulatedWeight = 0.0f;
        r.rotAroundZ = 0;
        r.rotAroundZAccumulatedWeight = 0.0f;
        r.bIdentity = true;

        ScaleAccum& s = m_scale.mData[i];
        s.s.f.x = 1.0f;
        s.s.f.y = 1.0f;
        s.s.f.z = 1.0f;
        s.fAccumulatedWeight = 0.0f;
        s.bIdentity = true;

        if (!m_BaseSHierarchy->PreserveBoneLength(i))
        {
            TransAccum& t = m_trans.mData[i];
            t.t.f.x = 0.0f;
            t.t.f.y = 0.0f;
            t.t.f.z = 0.0f;
            t.fAccumulatedWeight = 0.0f;
            t.bIdentity = true;
        }
    }

    for (int k = 0; k < m_MorphWeights.mSize; ++k)
    {
        m_MorphWeights.mData[k] = 0.0f;
    }
}

/**
 * Offset/Address/Size: 0x644 | 0x801EBBE4 | size: 0x3F4
 */
void cPoseAccumulator::BuildNodeMatrices(const nlMatrix4& world)
{
    if (m_PrevNodeMatrices.mSize == m_NodeMatrices.mSize)
    {
        s32 tmp = m_PrevNodeMatrices.mSize;
        m_PrevNodeMatrices.mSize = m_NodeMatrices.mSize;
        m_NodeMatrices.mSize = tmp;

        tmp = m_PrevNodeMatrices.mCapacity;
        m_PrevNodeMatrices.mCapacity = m_NodeMatrices.mCapacity;
        m_NodeMatrices.mCapacity = tmp;

        nlMatrix4* tmp_mat = m_PrevNodeMatrices.mData;
        m_PrevNodeMatrices.mData = m_NodeMatrices.mData;
        m_NodeMatrices.mData = tmp_mat;
    }

    int parentStack[32];
    int parentTop = -1;

    for (int idx = 0; idx < m_BaseSHierarchy->m_nodeCount; ++idx)
    {
        nlMatrix4* local = &m_NodeMatrices.mData[idx + 1];

        RotAccum* r = &m_rot.mData[idx];
        if (!r->bIdentity)
        {
            if (r->quatAccumulatedWeight == 0.0f)
            {
                nlMakeRotationMatrixZ(*local, 0.0000958738f * r->rotAroundZ);
            }
            else
            {
                if (r->rotAroundZAccumulatedWeight != 0.0f)
                {
                    float s, c;
                    nlSinCos(&s, &c, r->rotAroundZ);

                    nlQuaternion qz;
                    qz.f.x = 0.0f;
                    qz.f.y = 0.0f;
                    qz.f.z = s;
                    qz.f.w = c;

                    float t = r->rotAroundZAccumulatedWeight / (r->quatAccumulatedWeight + r->rotAroundZAccumulatedWeight);
                    nlQuatNLerp(r->q, r->q, qz, t);
                }

                nlQuatToMatrix(*local, r->q);
            }
        }
        else
        {
            local->SetIdentity();
        }

        TransAccum* ta = &m_trans.mData[idx];
        if (!ta->bIdentity)
        {
            local->m[3][0] = ta->t.f.x;
            local->m[3][1] = ta->t.f.y;
            local->m[3][2] = ta->t.f.z;
        }

        int parentIdx = -1;
        if (idx > 0 && parentTop >= 0)
        {
            parentIdx = parentStack[parentTop];
            const ScaleAccum* ps = &m_scale.mData[parentIdx];

            local->m[3][0] *= ps->s.f.x;
            local->m[3][1] *= ps->s.f.y;
            local->m[3][2] *= ps->s.f.z;
        }

        nlMatrix4* out = &m_NodeMatrices.mData[idx];
        if (parentIdx >= 0)
        {
            const nlMatrix4* parentWorld = &m_NodeMatrices.mData[parentIdx];
            nlMultMatrices(*out, *local, *parentWorld);
        }
        else
        {
            nlMultMatrices(*out, *local, world);
        }

        int delta = m_BaseSHierarchy->GetPushPop(idx);
        parentTop += delta;
        if (delta > 0)
        {
            parentStack[parentTop] = idx;
        }

        cBuildNodeMatrixCallbackInfo* cb = &m_cb.mData[idx];
        if (cb->fn)
        {
            int parentForCallback = (parentIdx >= 0) ? parentIdx : -1;
            cb->fn(cb->a, cb->b, this, idx, parentForCallback);
        }
    }

    for (int idx = 0; idx < m_BaseSHierarchy->m_nodeCount; ++idx)
    {
        const ScaleAccum* s = &m_scale.mData[idx];
        if (!s->bIdentity)
        {
            nlMatrix4* mtx = &m_NodeMatrices.mData[idx];
            mtx->m[0][0] *= s->s.f.x;
            mtx->m[0][1] *= s->s.f.x;
            mtx->m[0][2] *= s->s.f.x;
            mtx->m[1][0] *= s->s.f.y;
            mtx->m[1][1] *= s->s.f.y;
            mtx->m[1][2] *= s->s.f.y;
            mtx->m[2][0] *= s->s.f.z;
            mtx->m[2][1] *= s->s.f.z;
            mtx->m[2][2] *= s->s.f.z;
        }
    }
}

/**
 * Offset/Address/Size: 0x4FC | 0x801EBA9C | size: 0x148
 */
void cPoseAccumulator::BlendRot(int idx, const nlQuaternion* q, float w, bool flip)
{
    if ((float)fabsf(w) < 0.001f)
        return;

    RotAccum* e = m_rot.mData + idx;
    nlQuaternion qtemp;

    if (flip)
    {
        cSHierarchy* h = m_BaseSHierarchy;

        if (idx == h->m_maxNode || idx == h->m_minNode)
        {
            // store: (-x, -w, y, z)
            qtemp.f.x = -q->f.x;
            qtemp.f.y = q->f.y;
            qtemp.f.z = q->f.z;
            qtemp.f.w = -q->f.w;
        }
        else if (idx < h->m_minNode)
        {
            // store: (-x, y, -z, w)
            qtemp.f.x = -q->f.x;
            qtemp.f.y = q->f.y;
            qtemp.f.z = -q->f.z;
            qtemp.f.w = q->f.w;
        }
        else
        {
            // store: (-x, -y, z, w)
            qtemp.f.x = -q->f.x;
            qtemp.f.y = -q->f.y;
            qtemp.f.z = q->f.z;
            qtemp.f.w = q->f.w;
        }

        q = &qtemp;
    }

    e->quatAccumulatedWeight += w;

    float t = w / e->quatAccumulatedWeight;

    nlQuaternion tmp = e->q;
    nlQuatNLerp(e->q, tmp, *q, t);

    e = m_rot.mData + idx;
    e->bIdentity = false;
}

static inline RotAccum* GetRotAccum(RotAccum* data, int idx)
{
    return data + idx;
}

/**
 * Offset/Address/Size: 0x468 | 0x801EBA08 | size: 0x94
 */
void cPoseAccumulator::BlendRotAroundZ(int idx, unsigned short angle, float w)
{
    if (fabsf(w) < 0.001f)
        return;

    RotAccum* e = GetRotAccum(m_rot.mData, idx);

    e->rotAroundZAccumulatedWeight += w;
    float t = w / e->rotAroundZAccumulatedWeight;

    short delta = (short)(angle - e->rotAroundZ);
    delta = (short)(t * delta);

    e->rotAroundZ = e->rotAroundZ + (short)delta;

    e = GetRotAccum(m_rot.mData, idx);
    e->bIdentity = false;
}

static inline ScaleAccum* GetScaleAccum(ScaleAccum* data, int idx)
{
    return data + idx;
}

/**
 * Offset/Address/Size: 0x3DC | 0x801EB97C | size: 0x8C
 */
void cPoseAccumulator::BlendScale(int idx, const nlVector3* v, float w, bool)
{
    if (fabsf(w) < 0.001f)
        return;

    ScaleAccum* e = GetScaleAccum(m_scale.mData, idx);
    e->fAccumulatedWeight += w;

    float t = w / e->fAccumulatedWeight;
    float inv = 1.0f - t;

    e->s.f.x = inv * e->s.f.x + t * v->f.x;
    e->s.f.y = inv * e->s.f.y + t * v->f.y;
    e->s.f.z = inv * e->s.f.z + t * v->f.z;

    e = GetScaleAccum(m_scale.mData, idx);
    e->bIdentity = false;
}

/**
 * Offset/Address/Size: 0x2E4 | 0x801EB884 | size: 0xF8
 */
void cPoseAccumulator::BlendTrans(int idx, const nlVector3* v, float w, bool flip)
{
    if (fabsf(w) < 0.001f)
        return;

    if (flip)
    {
        cSHierarchy* h = m_BaseSHierarchy;

        nlVector3 vtemp;
        if (idx <= h->m_minNode || idx == h->m_maxNode)
        {
            // store: (x, -y, z)
            nlVec3Set(vtemp, v->f.x, -v->f.y, v->f.z);
        }
        else
        {
            // store: (x, y, -z)
            nlVec3Set(vtemp, v->f.x, v->f.y, -v->f.z);
        }

        v = &vtemp;
    }

    TransAccum* e = m_trans.mData + idx;
    e->fAccumulatedWeight += w;

    float t = w / e->fAccumulatedWeight;
    float inv = 1.0f - t;

    e->t.f.x = inv * e->t.f.x + t * v->f.x;
    e->t.f.y = inv * e->t.f.y + t * v->f.y;
    e->t.f.z = inv * e->t.f.z + t * v->f.z;

    e = m_trans.mData + idx;
    e->bIdentity = false;
}

/**
 * Offset/Address/Size: 0x258 | 0x801EB7F8 | size: 0x8C
 */
void cPoseAccumulator::BlendRotIdentity(int idx, float w)
{
    if (fabsf(w) < 0.001f)
        return;

    RotAccum* a = &m_rot.mData[idx];
    a->quatAccumulatedWeight += w;

    if (a->bIdentity)
        return;

    const float t = w / a->quatAccumulatedWeight;

    nlQuaternion tmp = a->q;
    nlQuatNLerp(a->q, tmp, qRotIdentity, t);
}

/**
 * Offset/Address/Size: 0x1CC | 0x801EB76C | size: 0x8C
 */
void cPoseAccumulator::BlendScaleIdentity(int idx, float w)
{
    if (fabsf(w) < 0.001f)
        return;

    ScaleAccum* e = &m_scale.mData[idx];
    e->fAccumulatedWeight += w;

    if (e->bIdentity)
        return;

    float f3 = w / e->fAccumulatedWeight;
    float f2 = 1.0f - f3;

    e->s.f.x = f2 * e->s.f.x + f3 * v3ScaleIdentity.f.x;
    e->s.f.y = f2 * e->s.f.y + f3 * v3ScaleIdentity.f.y;
    e->s.f.z = f2 * e->s.f.z + f3 * v3ScaleIdentity.f.z;
}

/**
 * Offset/Address/Size: 0x140 | 0x801EB6E0 | size: 0x8C
 */
void cPoseAccumulator::BlendTransIdentity(int idx, float w)
{
    if (fabsf(w) < 0.001f)
        return;

    TransAccum* e = &m_trans.mData[idx];
    e->fAccumulatedWeight += w;

    if (e->bIdentity)
        return;

    const float f3 = w / e->fAccumulatedWeight;
    const float f2 = 1.0f - f3;

    e->t.f.x = f2 * e->t.f.x + f3 * v3TransIdentity.f.x;
    e->t.f.y = f2 * e->t.f.y + f3 * v3TransIdentity.f.y;
    e->t.f.z = f2 * e->t.f.z + f3 * v3TransIdentity.f.z;
}

/**
 * Offset/Address/Size: 0x130 | 0x801EB6D0 | size: 0x10
 */
nlMatrix4& cPoseAccumulator::GetNodeMatrix(int i) const
{
    return m_NodeMatrices.mData[i];
}

/**
 * Offset/Address/Size: 0xB0 | 0x801EB650 | size: 0x80
 */
nlMatrix4& cPoseAccumulator::GetNodeMatrixByHashID(unsigned int hash) const
{
    cSHierarchy* hierarchy = m_BaseSHierarchy; // r3->0x00
    int index = 0;                             // r30 = 0

    while (index < hierarchy->m_nodeCount)
    {
        unsigned int nodeID = hierarchy->GetNodeID(index);
        if (hash == nodeID)
        {
            break;
        }
        index++;
    }

    return m_NodeMatrices.mData[index];
}

/**
 * Offset/Address/Size: 0xA4 | 0x801EB644 | size: 0xC
 */
s32 cPoseAccumulator::GetNumNodes() const
{
    return m_BaseSHierarchy->m_nodeCount;
}

/**
 * Offset/Address/Size: 0x28 | 0x801EB5C8 | size: 0x7C
 */
void cPoseAccumulator::MultNodeMatrices(const nlMatrix4* arg0)
{
    for (int i = 0; i < m_BaseSHierarchy->m_nodeCount; i++)
    {
        nlMatrix4* temp_r3 = &m_NodeMatrices.mData[i];
        nlMultMatrices(*temp_r3, *temp_r3, *arg0);
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x801EB5A0 | size: 0x28
 */
void cPoseAccumulator::SetBuildNodeMatrixCallback(int idx, BuildNodeMatrixFn fn, unsigned int a, unsigned int b)
{
    int offset = idx * (int)sizeof(cBuildNodeMatrixCallbackInfo);
    *(BuildNodeMatrixFn*)((char*)m_cb.mData + offset) = fn;
    *(unsigned int*)((char*)m_cb.mData + offset + 4) = a;
    *(unsigned int*)((char*)m_cb.mData + offset + 8) = b;
}
