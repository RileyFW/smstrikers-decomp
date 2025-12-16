#ifndef _GLXSWAP_H_
#define _GLXSWAP_H_

void DrawLoadingIndicator();
void BlitImage(int, int, float, float, bool);
void hitz_Post(bool);
void hitz_Pre(bool);
void hitz_SwapBuffers();
void hitz_AdvanceFrame();
void simple_Post(bool);
void simple_Pre(bool);
void glxSwapPost(bool);
void glxSwapPre(bool);
void glxInitSwap(void*, void*);
void glxSwapWaitDrawDone();
void vi_post_cb(unsigned long);
void vi_pre_cb(unsigned long);
void loading_indicator();
void glxLoadRestoreState();
void glxLoadSaveState();
void glxSwapLoading(bool bLoadingIndicator, bool bLoadOtherPosition);
void* glxGetBackBuffer();
void* glxGetDisplayedBuffer();
void glx_ScreenCapture(bool);
void glxSwapSetBlack(bool);

// class Config
// {
// public:
//     void Get<BasicString<char, Detail::TempStringAllocator>>(const char*, BasicString<char, Detail::TempStringAllocator>);
//     void TagValuePair::Get<BasicString<char, Detail::TempStringAllocator>>() const;
// };

#endif // _GLXSWAP_H_
