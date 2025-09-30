#ifndef _TRANSLIGHT_H_
#define _TRANSLIGHT_H_


class TransitionLight
{
public:
    TransitionLight();
    void ApplyLight(float);
    void LoadFromParser(SimpleParser*);
    void AttachToModel(glModel*);
    void DetachFromModel(glModel*);
};

#endif // _TRANSLIGHT_H_