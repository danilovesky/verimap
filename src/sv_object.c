#include "messages.h"
#include "object.h"
#include "sv_object.h"

//---------------------------------------------------------------------------
VerilogObject::VerilogObject(int tag, char* name) : Object(tag, name)
{
  this->escapeName();
}

//---------------------------------------------------------------------------
VerilogObject::VerilogObject(const VerilogObject& vobject) : Object(vobject)
{
  this->escapeName();
}

//---------------------------------------------------------------------------
void VerilogObject::setName(char* name)
{
  Object::setName(name);
  this->escapeName();
}

//---------------------------------------------------------------------------
void VerilogObject::escapeName()
{
  if (this->name)
  for (int i = 0; i < strlen(this->name); i++)
    if (this->name[i] == SYMBOL_ESCAPE)
    {
      for (int j = i; j > 0; j--)
        this->name[j] = this->name[j-1];
      this->name[0] = SYMBOL_ESCAPE;
    }
}

//---------------------------------------------------------------------------
bool VerilogObject::isEscape()
{
  bool result = false;
  if (this->name)
    if (strlen(this->name) > 0)
      result = (this->name[0] == SYMBOL_ESCAPE);
  return result;
}

