#ifndef _JUMBOTRON_H_
#define _JUMBOTRON_H_

void BundleLoad_cb(void*, unsigned long, void*);

class Jumbotron
{
public:
    void Initialize();
    void Uninitialize();
    void Reset();
    void BeginLoad();
    void WaitForLoad();
    void BeginPlaying();
    void StopPlaying();
    void Update(float);
};

#endif // _JUMBOTRON_H_