#ifndef _GOALIELOOSEBALL_H_
#define _GOALIELOOSEBALL_H_

void LooseBallCallback(float, float, unsigned long, float, void*);

class LooseBallAnims
{
public:
    void Init(cPlayer*);
    void Destroy();
    void FindLooseBallAnim(const nlVector3&, bool);
    void GetSwatSTSInfo(int);
    void GetDesperationInfo(unsigned int);
};

#endif // _GOALIELOOSEBALL_H_