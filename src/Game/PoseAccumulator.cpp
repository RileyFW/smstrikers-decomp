#include "Game/PoseAccumulator.h"
#include "NL/nlMemory.h"

#include "math.h"

static const nlQuaternion qRotIdentity = { 0, 0, 0, 1 };
static const nlVector3_ v3ScaleIdentity = { 1.0f, 1.0f, 1.0f };
static const nlVector3_ v3TransIdentity = { 0.0f, 0.0f, 0.0f };

extern const nlMatrix4 kPose64Template;
extern const RotAccum kRotAccumTemplate;
extern const ScaleAccum kScaleAccumTemplate;
extern const TransAccum kTransAccumTemplate;

/**
 * Offset/Address/Size: 0xCD8 | 0x801EC278 | size: 0x1D74
 */
cPoseAccumulator::cPoseAccumulator(cSHierarchy* h, bool withSecondary)
{
    m_hierarchy = h;

    const int n = h->m_nodeCount; // boneCount
    int i;

    {
        const int count = n + 1;
        m_matsA = (nlMatrix4*)nlMalloc((unsigned long)(count * sizeof(nlMatrix4)), 8, 0);
        m_unk_0x08 = count;
        m_unk_0x0C = count;

        for (i = 0; i < count; ++i)
        {
            m_matsA[i] = kPose64Template; // copy 0x40 bytes template
        }
    }

    {
        const int countB = withSecondary ? (n + 1) : 0;
        m_matsB = (nlMatrix4*)nlMalloc((unsigned long)(countB * sizeof(nlMatrix4)), 8, 0);
        m_unk_0x14 = countB;
        m_unk_0x18 = countB;

        for (i = 0; i < countB; ++i)
        {
            m_matsB[i] = kPose64Template;
        }
    }

    {
        m_rot = (RotAccum*)nlMalloc((unsigned long)(n * sizeof(RotAccum)), 8, 0);
        m_unk_0x20 = n;
        m_unk_0x24 = n;

        for (i = 0; i < n; ++i)
        {
            m_rot[i] = kRotAccumTemplate;
        }
    }

    {
        m_scale = (ScaleAccum*)nlMalloc((unsigned long)(n * sizeof(ScaleAccum)), 8, 0);
        m_unk_0x2C = n;
        m_unk_0x30 = n;

        for (i = 0; i < n; ++i)
        {
            m_scale[i] = kScaleAccumTemplate;
        }
    }

    {
        m_trans = (TransAccum*)nlMalloc((unsigned long)(n * sizeof(TransAccum)), 8, 0);
        m_unk_0x38 = n;
        m_unk_0x3C = n;

        for (i = 0; i < n; ++i)
        {
            m_trans[i] = kTransAccumTemplate; // zero/locked baseline
        }
    }

    {
        void* buffer = nlMalloc(n * sizeof(cBuildNodeMatrixCallbackInfo), 8, 0);
        m_cb = new (buffer) cBuildNodeMatrixCallbackInfo[n];

        m_unk_0x44 = n;
        m_unk_0x48 = n;

        for (i = 0; i < n; ++i)
        {
            new (&m_cb[i]) cBuildNodeMatrixCallbackInfo(); // Call constructor manually
        }
    }

    {
        m_floatArray = (float*)nlMalloc((unsigned long)(8 * sizeof(float)), 8, 0);
        m_floatCount = 8;

        for (i = 0; i < 8; ++i)
        {
            m_floatArray[i] = 0.0f;
        }
    }

    for (i = 0; i < n; ++i)
    {
        if (m_hierarchy->PreserveBoneLength(i))
        {
            const nlVector3* t = m_hierarchy->GetTranslationOffset(i);
            m_trans[i].x = t->f.x;
            m_trans[i].y = t->f.y;
            m_trans[i].z = t->f.z;
            m_trans[i].weight = 1.0f;
            m_trans[i].locked = false;
        }
    }
}

/**
 * Offset/Address/Size: 0xB7C | 0x801EC11C | size: 0x15C
 */
void cPoseAccumulator::Pose(const cPoseNode& node, const nlMatrix4& mat)
{
    int i;
    for (i = 0; i < m_hierarchy->m_nodeCount; i++)
    {
        RotAccum& r = m_rot[i];
        r.q.f.x = 0.0f;
        r.q.f.y = 0.0f;
        r.q.f.z = 0.0f;
        r.q.f.w = 1.0f;
        r.weight = 0.0f;
        r.angleZ = 0;
        r.weightZ = 0.0f;
        r.locked = true;

        ScaleAccum& s = m_scale[i];
        s.x = 1.0f;
        s.y = 1.0f;
        s.z = 1.0f;
        s.weight = 0.0f;
        s.locked = true;

        if (!m_hierarchy->PreserveBoneLength(i))
        {
            TransAccum& t = m_trans[i];
            t.x = 0.0f;
            t.y = 0.0f;
            t.z = 0.0f;
            t.weight = 0.0f;
            t.locked = true;
        }
    }

    for (i = 0; i < m_floatCount; i++)
    {
        m_floatArray[i] = 0.0f;
    }

    node.V_unk10(this, 1.0f);

    BuildNodeMatrices(mat);
}

/**
 * Offset/Address/Size: 0xA38 | 0x801EBFD8 | size: 0x144
 */
void cPoseAccumulator::InitAccumulators()
{
    for (int i = 0; i < m_hierarchy->m_nodeCount; ++i)
    {
        // --- rotation accum (stride 0x20) ---
        RotAccum& r = m_rot[i];
        r.q.f.x = 0.0f;
        r.q.f.y = 0.0f;
        r.q.f.z = 0.0f;
        r.q.f.w = 1.0f;
        r.weight = 0.0f;
        r.angleZ = 0;
        r.weightZ = 0.0f;
        r.locked = true;

        // --- scale accum (stride 0x14) ---
        ScaleAccum& s = m_scale[i];
        s.x = 1.0f;
        s.y = 1.0f;
        s.z = 1.0f;
        s.weight = 0.0f;
        s.locked = true;

        if (!m_hierarchy->PreserveBoneLength(i))
        {
            TransAccum& t = m_trans[i];
            t.x = 0.0f;
            t.y = 0.0f;
            t.z = 0.0f;
            t.weight = 0.0f;
            t.locked = true;
        }
    }

    for (int k = 0; k < m_floatCount; ++k)
    {
        m_floatArray[k] = 0.0f;
    }
}

/**
 * Offset/Address/Size: 0x644 | 0x801EBBE4 | size: 0x3F4
 */
void cPoseAccumulator::BuildNodeMatrices(const nlMatrix4& world)
{
    if (m_unk_0x14 == m_unk_0x08)
    {
        s32 tmp = m_unk_0x14;
        m_unk_0x14 = m_unk_0x08;
        m_unk_0x08 = tmp;

        tmp = m_unk_0x18;
        m_unk_0x18 = m_unk_0x0C;
        m_unk_0x0C = tmp;

        nlMatrix4* tmp_mat = m_matsB;
        m_matsB = m_matsA;
        m_matsA = tmp_mat;
    }

    int parentStack[32];
    int parentTop = -1;

    for (int idx = 0; idx < m_hierarchy->m_nodeCount; ++idx)
    {
        nlMatrix4* local = &m_matsA[idx + 1];

        RotAccum* r = &m_rot[idx];
        if (!r->locked)
        {
            if (r->weight == 0.0f)
            {
                nlMakeRotationMatrixZ(*local, 0.0000958738f * r->angleZ);
            }
            else
            {
                if (r->weightZ != 0.0f)
                {
                    float s, c;
                    nlSinCos(&s, &c, r->angleZ);

                    nlQuaternion qz;
                    qz.f.x = 0.0f;
                    qz.f.y = 0.0f;
                    qz.f.z = s;
                    qz.f.w = c;

                    float t = r->weightZ / (r->weight + r->weightZ);
                    nlQuatNLerp(r->q, r->q, qz, t);
                }

                nlQuatToMatrix(*local, r->q);
            }
        }
        else
        {
            local->SetIdentity();
        }

        TransAccum* ta = &m_trans[idx];
        if (!ta->locked)
        {
            local->m[3][0] = ta->x;
            local->m[3][1] = ta->y;
            local->m[3][2] = ta->z;
        }

        int parentIdx = -1;
        if (idx > 0 && parentTop >= 0)
        {
            parentIdx = parentStack[parentTop];
            const ScaleAccum* ps = &m_scale[parentIdx];

            local->m[3][0] *= ps->x;
            local->m[3][1] *= ps->y;
            local->m[3][2] *= ps->z;
        }

        nlMatrix4* out = &m_matsA[idx];
        if (parentIdx >= 0)
        {
            const nlMatrix4* parentWorld = &m_matsA[parentIdx];
            nlMultMatrices(*out, *local, *parentWorld);
        }
        else
        {
            nlMultMatrices(*out, *local, world);
        }

        int delta = m_hierarchy->GetPushPop(idx);
        parentTop += delta;
        if (delta > 0)
        {
            parentStack[parentTop] = idx;
        }

        cBuildNodeMatrixCallbackInfo* cb = &m_cb[idx];
        if (cb->fn)
        {
            int parentForCallback = (parentIdx >= 0) ? parentIdx : -1;
            cb->fn(cb->a, cb->b, this, idx, parentForCallback);
        }
    }

    for (int idx = 0; idx < m_hierarchy->m_nodeCount; ++idx)
    {
        const ScaleAccum* s = &m_scale[idx];
        if (!s->locked)
        {
            nlMatrix4* mtx = &m_matsA[idx];
            mtx->m[0][0] *= s->x;
            mtx->m[0][1] *= s->x;
            mtx->m[0][2] *= s->x;
            mtx->m[1][0] *= s->y;
            mtx->m[1][1] *= s->y;
            mtx->m[1][2] *= s->y;
            mtx->m[2][0] *= s->z;
            mtx->m[2][1] *= s->z;
            mtx->m[2][2] *= s->z;
        }
    }
}

/**
 * Offset/Address/Size: 0x4FC | 0x801EBA9C | size: 0x148
 */
void cPoseAccumulator::BlendRot(int idx, const nlQuaternion* q, float w, bool flip)
{
    if (fabsf(w) < 0.001f)
        return;

    RotAccum* e = m_rot + idx;
    nlQuaternion qtemp;

    if (flip)
    {
        cSHierarchy* h = m_hierarchy;

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

    e->weight += w;

    float t = w / e->weight;

    nlQuaternion tmp = e->q;
    nlQuatNLerp(e->q, tmp, *q, t);

    e = m_rot + idx;
    e->locked = false;
}

/**
 * Offset/Address/Size: 0x468 | 0x801EBA08 | size: 0x94
 */
void cPoseAccumulator::BlendRotAroundZ(int idx, unsigned short angle, float w)
{
    if (fabsf(w) < 0.001f)
        return;

    RotAccum* e = &m_rot[idx];

    e->weightZ += w;
    float t = w / e->weightZ;

    short delta = (short)(angle - e->angleZ);
    delta = (short)(t * delta);

    e->angleZ = e->angleZ + (short)delta;

    e = m_rot + idx;
    e->locked = false;
}

/**
 * Offset/Address/Size: 0x3DC | 0x801EB97C | size: 0x8C
 */
void cPoseAccumulator::BlendScale(int idx, const nlVector3* v, float w, bool /*unused*/)
{
    if (fabsf(w) < 0.001f)
        return;

    ScaleAccum* e = m_scale + idx;
    e->weight += w;

    float t = w / e->weight;
    float inv = 1.0f - t;

    e->x = inv * e->x + t * v->f.x;
    e->y = inv * e->y + t * v->f.y;
    e->z = inv * e->z + t * v->f.z;

    e = m_scale + idx;
    e->locked = false;
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
        cSHierarchy* h = m_hierarchy;

        nlVector3 vtemp;
        if (idx <= h->m_minNode || idx == h->m_maxNode)
        {
            // store: (x, -y, z)
            NL_VECTOR3_SET(vtemp, v->f.x, -v->f.y, v->f.z);
        }
        else
        {
            // store: (x, y, -z)
            NL_VECTOR3_SET(vtemp, v->f.x, v->f.y, -v->f.z);
        }

        v = &vtemp;
    }

    TransAccum* e = m_trans + idx;
    e->weight += w;

    float t = w / e->weight;
    float inv = 1.0f - t;

    e->x = inv * e->x + t * v->f.x;
    e->y = inv * e->y + t * v->f.y;
    e->z = inv * e->z + t * v->f.z;

    e = m_trans + idx;
    e->locked = false;
}

/**
 * Offset/Address/Size: 0x258 | 0x801EB7F8 | size: 0x8C
 */
void cPoseAccumulator::BlendRotIdentity(int idx, float w)
{
    if (fabsf(w) < 0.001f)
        return;

    RotAccum* a = &m_rot[idx];
    a->weight += w;

    if (a->locked)
        return;

    const float t = w / a->weight;

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

    ScaleAccum* a = &m_scale[idx];
    a->weight += w;

    if (a->locked)
        return;

    const float t = w / a->weight;
    const float inv = 1.0f - t;

    a->x = inv * a->x + t * v3ScaleIdentity.f[0];
    a->y = inv * a->y + t * v3ScaleIdentity.f[1];
    a->z = inv * a->z + t * v3ScaleIdentity.f[2];
}

/**
 * Offset/Address/Size: 0x140 | 0x801EB6E0 | size: 0x8C
 */
void cPoseAccumulator::BlendTransIdentity(int idx, float w)
{
    if (fabsf(w) < 0.001f)
        return;

    TransAccum* e = &m_trans[idx];
    e->weight += w;

    if (e->locked)
        return;

    const float f3 = w / e->weight;
    const float f2 = 1.0f - f3;

    e->x = f2 * e->x + f3 * v3TransIdentity.f[0];
    e->y = f2 * e->y + f3 * v3TransIdentity.f[1];
    e->z = f2 * e->z + f3 * v3TransIdentity.f[2];
}

/**
 * Offset/Address/Size: 0x130 | 0x801EB6D0 | size: 0x10
 */
nlMatrix4* cPoseAccumulator::GetNodeMatrix(int i) const
{
    return &m_matsA[i];
}

/**
 * Offset/Address/Size: 0xB0 | 0x801EB650 | size: 0x80
 */
nlMatrix4* cPoseAccumulator::GetNodeMatrixByHashID(unsigned int hash) const
{
    cSHierarchy* hierarchy = m_hierarchy; // r3->0x00
    int index = 0;                        // r30 = 0

    // Loop through all nodes in the hierarchy
    while (index < hierarchy->m_nodeCount)
    { // r31->0x08
        unsigned int nodeID = hierarchy->GetNodeID(index);
        if (hash == nodeID)
        {
            break;
        }
        index++;
    }

    return (nlMatrix4*)((char*)m_matsA + (index << 6));
}

/**
 * Offset/Address/Size: 0xA4 | 0x801EB644 | size: 0xC
 */
s32 cPoseAccumulator::GetNumNodes() const
{
    return m_hierarchy->m_nodeCount;
}

/**
 * Offset/Address/Size: 0x28 | 0x801EB5C8 | size: 0x7C
 */
void cPoseAccumulator::MultNodeMatrices(const nlMatrix4* arg0)
{
    for (int i = 0; i < m_hierarchy->m_nodeCount; i++)
    {
        nlMatrix4* temp_r3 = m_matsA + i;
        nlMultMatrices(*temp_r3, *temp_r3, *arg0);
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x801EB5A0 | size: 0x28
 */
void cPoseAccumulator::SetBuildNodeMatrixCallback(int idx, BuildNodeMatrixFn fn, unsigned int a, unsigned int b)
{
    cBuildNodeMatrixCallbackInfo& cb = m_cb[idx];
    cb.fn = fn;
    cb.a = a;
    cb.b = b;
}
