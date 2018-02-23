#ifndef _SV_PARAMETER_H_
#define _SV_PARAMETER_H_

#include "darray.h"
#include "hashtable.h"

#define PATTERN_PARAMETER_FF       "%s_ff"

class Parameter;
typedef darray <Parameter*> ParameterArray;
typedef HashTable <Parameter> ParameterHashTable;

#include "sv_object.h"

//---------------------------------------------------------------------------
class Parameter : public VerilogObject
{
  private:
    float value;
  public:
    Parameter(int tag = TAG_UNDEFINED, char* name = NULL, float value = 0);
    Parameter(const Parameter& parameter);
    void setValue(float value);
    float getValue();
};

#endif

