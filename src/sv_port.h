#ifndef _SV_PORT_H_
#define _SV_PORT_H_

#include "darray.h"
#include "hashtable.h"

class Port;
typedef darray <Port*> PortArray;
typedef HashTable <Port> PortHashTable;

#include "sv_object.h"
#include "sv_range.h"
#include "sv_delay.h"
#include "sv_net.h"

// full name
#define PATTERN_PORT_FULL_NAME            "[%d:%d] %s"
// label name
#define PATTERN_PORT_LABEL_NAME           "%s_%d_%d"


//---------------------------------------------------------------------------
class Port : public VerilogObject
{
  protected:
    Range* dimension;

    void clean();

  public:
    NetArray* nets;

    Port(int tag = TAG_UNDEFINED, char* name = NULL, Range* dimension = NULL, Range* range = NULL, Delay* delay = NULL);
    Port(const Port& port);
    ~Port();
    virtual void setTag(int tag);
    virtual void setName(char* name);
    void setDimension(Range* dimension);
    Range* getDimension();
    char* genFullName();
    void addNet(Net* net, int ind = -1);
    Net* getNet(char* net_name, int net_index);
    void convertToDR(int polarity);
};

#endif

