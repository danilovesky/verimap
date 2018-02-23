#ifndef _SV_TRANS_H_
#define _SV_TRANS_H_

#include "darray.h"
#include "hashtable.h"

class Trans;
typedef darray <Trans*> TransArray;
typedef HashTable <Trans> TransHashTable;

#include "sv_object.h"

//---------------------------------------------------------------------------
class Trans : public VerilogObject
{
  protected:
    char* trans;
  public:
    Trans(int tag = TAG_UNDEFINED, char* name = NULL, char* trans = NULL);
    Trans(const Trans &trans);
    ~Trans();
    void setTrans(char* trans);
    char* getTrans();
};

#endif

