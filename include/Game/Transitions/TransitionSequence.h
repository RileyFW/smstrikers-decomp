#ifndef _TRANSITIONSEQUENCE_H_
#define _TRANSITIONSEQUENCE_H_


class TransitionSequence
{
public:
    void CutTime() const;
    TransitionSequence();
    ~TransitionSequence();
    void DoSanityCheck();
    void Update(float);
    void Reset();
    void Render(eGLView);
    void Cancel();
    void GetTransitionLength();
    void Time() const;
    void IsFinished();
    void Initialize(SimpleParser*);
};

#endif // _TRANSITIONSEQUENCE_H_