#ifndef _CUPTICKERMANAGER_H_
#define _CUPTICKERMANAGER_H_

#include "Game/FE/tlTextInstance.h"

class FEScrollText;

class CupTickerManager
{
public:
    CupTickerManager();
    ~CupTickerManager();
    void SetTickerTextInstance(TLTextInstance*);
    void CreateNewMessage();
    void Update(float);
    // void BuildGoalTotalTickerMessage(BasicString<unsigned short, Detail::TempStringAllocator>&, bool);

    /* 0x00 */ FEScrollText* m_pScrollText;
};

// class BasicString<unsigned short, Detail
// {
// public:
//     void TempStringAllocator>::AppendInPlace<Detail::TempStringAllocator>(const BasicString<unsigned short, Detail::TempStringAllocator>&);
//     void TempStringAllocator>::Append<Detail::TempStringAllocator>(const BasicString<unsigned short, Detail::TempStringAllocator>&) const;
// };

// class Function0<void>
// {
// public:
//     void FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (CupTickerManager::*)()>, CupTickerManager*>>::~FunctorImpl();
//     void FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (CupTickerManager::*)()>, CupTickerManager*>>::operator()();
//     void FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (CupTickerManager::*)()>, CupTickerManager*>>::Clone() const;
// };

// class MemFun<CupTickerManager, void>(void (CupTickerManager
// {
// public:
//     void *)());
// };

// class Format<BasicString<unsigned short, Detail
// {
// public:
//     void TempStringAllocator>, const unsigned short*, const unsigned short*>(const BasicString<unsigned short, Detail::TempStringAllocator>&, const unsigned short* const&, const unsigned short* const&);
//     void TempStringAllocator>, BasicString<unsigned short, Detail::TempStringAllocator>, BasicString<unsigned short, Detail::TempStringAllocator>>(const BasicString<unsigned short, Detail::TempStringAllocator>&, const BasicString<unsigned short, Detail::TempStringAllocator>&, const BasicString<unsigned short, Detail::TempStringAllocator>&);
//     void TempStringAllocator>, const unsigned short*, const unsigned short*, unsigned short[16], unsigned short[16]>(const BasicString<unsigned short, Detail::TempStringAllocator>&, const unsigned short* const&, const unsigned short* const&, const unsigned short(&)[16], const unsigned short(&)[16]);
// };

// class FormatImpl<BasicString<unsigned short, Detail
// {
// public:
//     void TempStringAllocator>>::operator%<BasicString<unsigned short, Detail::TempStringAllocator>>(const BasicString<unsigned short, Detail::TempStringAllocator>&);
//     void TempStringAllocator>>::operator%<const unsigned short*>(const unsigned short* const&);
// };

// class Bind<void, Detail
// {
// public:
//     void MemFunImpl<void, void (CupTickerManager::*)()>, CupTickerManager*>(Detail::MemFunImpl<void, void (CupTickerManager::*)()>, CupTickerManager* const&);
// };

#endif // _CUPTICKERMANAGER_H_
