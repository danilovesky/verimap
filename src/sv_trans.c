#include "sv_trans.h"
#include "hash.h"

//---------------------------------------------------------------------------
Trans::Trans(int tag, char* name, char* trans) : VerilogObject(tag, name)
{
  this->trans = trans;
}

//---------------------------------------------------------------------------
Trans::Trans(const Trans &trans) : VerilogObject(trans)
{
  this->trans = namecopy(trans.trans);
}

//---------------------------------------------------------------------------
Trans::~Trans()
{
  delete [] trans;
}

//---------------------------------------------------------------------------
void Trans::setTrans(char* trans)
{
  delete [] this->trans;
  this->trans = trans;
}

//---------------------------------------------------------------------------
char* Trans::getTrans()
{
  return this->trans;
}

