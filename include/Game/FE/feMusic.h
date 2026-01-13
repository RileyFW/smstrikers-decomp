#ifndef _FEMUSIC_H_
#define _FEMUSIC_H_

namespace FEMusic {
    void ResetCurrentFEStreamHash();
    void StopStream();
    void StartStreamIfDifferent(int);
}

#endif // _FEMUSIC_H_