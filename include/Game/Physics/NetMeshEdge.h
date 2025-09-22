#ifndef _NETMESHEDGE_H_
#define _NETMESHEDGE_H_

#include "NL/nlMath.h"

class NetMeshModelLoader
{
public:
    class NetMeshVertex
    {
    public:
        const nlVector3* GetPosition() const;
        void GetNormal(nlVector3& out) const;
        void GetTextureCoord(nlVector2& out) const;

        /* 0x00 */ NetMeshModelLoader* m_owner;
        /* 0x04 */ u16 m_index;
    };
};

#endif // _NETMESHEDGE_H_
