#ifndef _SV_RULE_H_
#define _SV_RULE_H_

#include "darray.h"
#include "hashtable.h"

class Rule;
typedef darray <Rule*> RuleArray;
typedef HashTable <Rule> RuleHashTable;

#include "sv_object.h"

//---------------------------------------------------------------------------
#define NAME_LOGIC_UNDEFINED              "_"

//---------------------------------------------------------------------------
class Rule : public VerilogObject
{
  public:
    char* prefix_dr;
    char* prefix_pd;
    char* prefix_pc;
    char* prefix_nd;
    char* prefix_nc;
    char* polarity;

    Rule(int tag = TAG_UNDEFINED, char* name = NULL, char* prefix_dr = NULL, char* prefix_pd = NULL, char* prefix_pc = NULL, char* prefix_nd = NULL, char* prefix_nc = NULL, char* polarity = NULL);
    Rule(const Rule &rule);
    ~Rule();
};

#endif

