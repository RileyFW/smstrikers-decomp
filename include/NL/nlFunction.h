#ifndef _FEFUNCTION_H_
#define _FEFUNCTION_H_

enum Tag
{
    EMPTY = 0,
    FREE_FUNCTION = 1,
    FUNCTOR = 2,
};

struct FunctorBase
{
    virtual ~FunctorBase() { };
    virtual FunctorBase* fnc_0x8() = 0;
    virtual FunctorBase* fnc_0x10() = 0;
};

template <typename ReturnType, typename ParamType>
class Function1
{
public:
    enum Tag mTag; // offset 0x0, size 0x4
    union
    {
        ReturnType (*mFreeFunction)(ParamType); // offset 0x4, size 0x4
        FunctorBase* mFunctor;                  // offset 0x4, size 0x4
    };
}; // total size: 0x8

// template <typename T>
// class Function1
// {
//     enum Tag mTag; // offset 0x0, size 0x4
//     union
//     {                                 // inferred
//         void (*mFreeFunction)(T*);    // offset 0x4, size 0x4
//         struct FunctorBase* mFunctor; // offset 0x4, size 0x4
//     };
// }; // total size: 0x8

template <typename ReturnType>
class Function0
{
public:
    enum Tag mTag; // offset 0x0, size 0x4
    union
    {
        ReturnType (*mFreeFunction)(); // offset 0x4, size 0x4
        FunctorBase* mFunctor;         // offset 0x4, size 0x4
    };

}; // total size: 0x8

template <typename T>
class Function : public Function1<void, T>
{
public:
    ~Function()
    {
        if (mTag == FUNCTOR) {
            delete mFunctor;
        }
        mTag = EMPTY;
    }
}; // total size: 0x8

typedef void FnVoidVoid();

template <>
class Function<FnVoidVoid> : public Function0<void>
{
public:
    ~Function()
    {
        if (mTag == FUNCTOR) {
            delete mFunctor;
        }
        mTag = EMPTY;
    }
}; // total size: 0x8

#endif // _FEFUNCTION_H_
