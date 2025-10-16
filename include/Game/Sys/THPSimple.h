#ifndef _THPSIMPLE_H_
#define _THPSIMPLE_H_

#include "NL/nlFile.h"

void THPAudioMixCallback();
void MixAudio(short*, short*, unsigned long);
void __THPSimpleDVDCallback(nlFile*, void*, unsigned int, unsigned long);
void __THPAsyncCancelCB(nlFile*, void*, unsigned int, unsigned long, void (*)(nlFile*, void*, unsigned int, unsigned long));
#endif // _THPSIMPLE_H_
