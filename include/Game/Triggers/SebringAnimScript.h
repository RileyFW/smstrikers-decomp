#ifndef _SEBRINGANIMSCRIPT_H_
#define _SEBRINGANIMSCRIPT_H_

class SebringAnimTagScriptInterpreter : public AnimTagScriptInterpreter
{
public:
    void DoFunctionCall(unsigned int);
    void TriggerFired(unsigned long);

    /* 0xC0 */ bool m_FireTriggers;
}; // total size: 0xC4

#endif // _SEBRINGANIMSCRIPT_H_
