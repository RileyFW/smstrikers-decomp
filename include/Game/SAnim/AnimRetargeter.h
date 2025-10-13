#ifndef _ANIMRETARGETER_H_
#define _ANIMRETARGETER_H_


class AnimRetargetList
{
public:
    void Initialize(nlChunk*);
    void GetAnimRetargetWithSignature(const cSAnim*);
};

#endif // _ANIMRETARGETER_H_