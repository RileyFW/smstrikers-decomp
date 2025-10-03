#ifndef _SHOTMETER_H_
#define _SHOTMETER_H_


class ShotMeter
{
public:
    void Update(float, bool);
    void Abort(cFielder*);
    void CalcOneTimerValue(cFielder*, bool);
    void GetTotalDuration() const;
    void Reset();
    void ShotReleased(cFielder*);
};

#endif // _SHOTMETER_H_