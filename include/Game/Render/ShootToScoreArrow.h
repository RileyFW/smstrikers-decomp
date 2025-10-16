#ifndef _SHOOTTOSCOREARROW_H_
#define _SHOOTTOSCOREARROW_H_

// void 0x8028D310..0x8028D314 | size: 0x4;

class WorldDarkening
{
public:
    void Instance();
    void Fade(float, float);
    void UpdateAndRender(float);
};

#endif // _SHOOTTOSCOREARROW_H_
