///////////////////////////////////////////////////////////////////////////////
//
// FNTPcallback.h
//
// TBC
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef FNTPCALLBACK_H_
#define FNTPCALLBACK_H_

class CallbackBase
{
public:
    CallbackBase() {}

    virtual ~CallbackBase() {}

    virtual void Call(void) = 0;
    // add other methods here

};

template<class C>
class FNTPcallback: public CallbackBase
{
public:
    FNTPcallback()
    {
        m_pClass = 0;
        m_pCallback = 0;
    }

    ~ FNTPcallback() {}

    typedef void (C::*Callback)(void);

    void SetInstance(C* pClass) { m_pClass = pClass; }
    void SetMethod(Callback pMethod) { m_pCallback = pMethod; }

    void Call(void)
    {
        if (m_pClass && m_pCallback)
        {
            (m_pClass->*m_pCallback)();
        }
    }

private:
    C* m_pClass;
    Callback m_pCallback;
};

#endif /*FNTPCALLBACK_H_*/
