#ifndef _OVERLAYHANDLERSUMMARY_H_
#define _OVERLAYHANDLERSUMMARY_H_

enum eSummaryType
{
    SUMMARY_INVALID = -1,
    SUMMARY_MATCH = 0,
    SUMMARY_CUMULATIVE_MATCH = 1,
    SUMMARY_USER = 2,
    SUMMARY_CUMULATIVE_USER = 3,
    NUM_SUMMARIES = 4,
};

class SummaryOverlay
{
public:
    enum eSummaryContext
    {
        ENDGAME = 0,
        PAUSE = 1,
    };

    SummaryOverlay(SummaryOverlay::eSummaryContext);
    ~SummaryOverlay();
    void SceneCreated();
    void Update(float);
    void DisplayMatchSummary(eSummaryType);
    void DisplayUserSummary(eSummaryType);
};

// class FEFinder<TLComponentInstance, 4>
// {
// public:
//     void _Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
// };

// class FEFinder<TLTextInstance, 3>
// {
// public:
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
// };

#endif // _OVERLAYHANDLERSUMMARY_H_
