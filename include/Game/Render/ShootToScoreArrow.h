#ifndef _SHOOTTOSCOREARROW_H_
#define _SHOOTTOSCOREARROW_H_

// void 0x8028D310..0x8028D314 | size: 0x4;

class WorldDarkening
{
public:
    WorldDarkening()
    {
        mRate = 0.f;
        mPos = 0.f;
        mTo = 0.f;
        mActive = 0;
    };
    // ~WorldDarkening();

    static WorldDarkening& Instance();
    void Fade(float, float);
    void UpdateAndRender(float);

    /* 0x0 */ float mRate;
    /* 0x4 */ float mPos;
    /* 0x8 */ float mTo;
    /* 0xC */ bool mActive;
}; // total size: 0x10

#endif // _SHOOTTOSCOREARROW_H_
