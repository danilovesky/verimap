#include "sv_parameter.h"
#include "sv_object.h"

//---------------------------------------------------------------------------
Parameter::Parameter(int tag, char* name, float value) : VerilogObject(tag, name)
{
  this->value = value;
}

//---------------------------------------------------------------------------
Parameter::Parameter(const Parameter& parameter) : VerilogObject(parameter)
{
  this->value = parameter.value;
}

//---------------------------------------------------------------------------
void Parameter::setValue(float value)
{
  this->value = value;
}

//---------------------------------------------------------------------------
float Parameter::getValue()
{
  return value;
}

