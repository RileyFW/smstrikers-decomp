#include "Game/Sys/THPSimple.h"
#include "NL/nlFileGC.h"

/**
 * Offset/Address/Size: 0x17E4 | 0x801CD748 | size: 0x4
 */
void __THPAsyncCancelCB(nlFile*, void*, unsigned int, unsigned long, void (*)(nlFile*, void*, unsigned int, unsigned long))
{
}

/**
 * Offset/Address/Size: 0xD0C | 0x801CCC70 | size: 0x160
 * TODO: 99.49% match - remaining register swap in readIdx/nextSize update (lwzx/andc temp assignment)
 */
void __THPSimpleDVDCallback(nlFile* file, void* buffer, unsigned int bytesRead, unsigned long offset) {
    SimpleControl.dvdBusy = 0;

    SimpleControl.readBuffers[SimpleControl.readIdx].mFrameNumber = SimpleControl.frameCount;
    SimpleControl.frameCount++;
    SimpleControl.readBuffers[SimpleControl.readIdx].mIsValid = TRUE;

    SimpleControl.totalRead += SimpleControl.nextSize;
    SimpleControl.nextSize = *(u32*)SimpleControl.readBuffers[SimpleControl.readIdx].mPtr;

    {
        register s32 readIdx = SimpleControl.readIdx;
        readIdx = (readIdx + 1 >= NumReadBuffers) ? 0 : readIdx + 1;
        SimpleControl.readIdx = readIdx;
    }

    if (SimpleControl.readBuffers[SimpleControl.readIdx].mIsValid != 0) {
        return;
    }

    if (SimpleControl.unk74 != 0) {
        return;
    }

    if (SimpleControl.playing != 1) {
        return;
    }

    if (SimpleControl.frameCount > SimpleControl.numFrames - 1) {
        if (SimpleControl.loop != 1) {
            return;
        }
        SimpleControl.frameCount = 0;
        SimpleControl.totalRead = SimpleControl.movieDataOffsets;
        SimpleControl.nextSize = SimpleControl.firstFrameSize;
    }

    SimpleControl.dvdBusy = 1;
    nlSeek(SimpleControl.file, SimpleControl.totalRead, 0);
    nlReadAsync(SimpleControl.file, SimpleControl.readBuffers[SimpleControl.readIdx].mPtr, SimpleControl.nextSize, __THPSimpleDVDCallback, 0);
}

/**
 * Offset/Address/Size: 0x31C | 0x801CC280 | size: 0x368
 */
void MixAudio(short*, short*, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x138 | 0x801CC09C | size: 0x178
 */
void THPAudioMixCallback()
{
}
