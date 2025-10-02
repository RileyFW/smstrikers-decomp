#ifndef _SCRIPTDEFINES_H_
#define _SCRIPTDEFINES_H_

class cFielder;
class cTeam;

void FuzzyScriptClearGlobals();
void FuzzyScriptSetCurrentTeam(cTeam*);
void FuzzyScriptSetCurrentFielder(cFielder*);

#endif // _SCRIPTDEFINES_H_
