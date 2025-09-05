#ifndef _DRAWABLEBALL_H_
#define _DRAWABLEBALL_H_

#include "Game/Drawable/DrawableObj.h"

// void BallLightingCB(glModel*, eGLView&, unsigned long&);
// void BallBlurCB(glModel*, eGLView&, unsigned long&);
// void Replayable<1, SaveFrame, char>(SaveFrame&, char&);
// void Replayable<1, LoadFrame, char>(LoadFrame&, char&);
// void Replayable<1, SaveFrame, FloatCompressor<-127, 127, 7>>(SaveFrame&, const FloatCompressor<-127, 127, 7>&);
// void Replayable<1, SaveFrame, FloatCompressor<-1, 1, 13>>(SaveFrame&, const FloatCompressor<-1, 1, 13>&);
// void Replayable<1, SaveFrame, FloatCompressor<-127, 127, 5>>(SaveFrame&, const FloatCompressor<-127, 127, 5>&);
// void Replayable<1, LoadFrame, FloatCompressor<-127, 127, 7>>(LoadFrame&, const FloatCompressor<-127, 127, 7>&);
// void Replayable<1, LoadFrame, FloatCompressor<-1, 1, 13>>(LoadFrame&, const FloatCompressor<-1, 1, 13>&);
// void Replayable<1, LoadFrame, FloatCompressor<-127, 127, 5>>(LoadFrame&, const FloatCompressor<-127, 127, 5>&);

class LoadFrame;
class SaveFrame;

class DrawableCharacter;

class DrawableBall
{
public:
    void EvaluateFrom(DrawableCharacter&);
    void Blend(const float*, const DrawableBall&, const DrawableBall&);
    void Render() const;
    void Grab();
    void IndexToPlayer(int) const;
    // void Replay<LoadFrame>(LoadFrame&);
    // void Replay<SaveFrame>(SaveFrame&);
};

#endif // _DRAWABLEBALL_H_
