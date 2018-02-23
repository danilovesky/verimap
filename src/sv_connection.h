#ifndef _SV_CONNECTION_H_
#define _SV_CONNECTION_H_

#include "darray.h"
#include "hashtable.h"

class Connection;
typedef darray <Connection*> ConnectionArray;
typedef HashTable <Connection> ConnectionHashTable;

#include "sv_object.h"
#include "sv_net.h"

// full name
#define PATTERN_CONNECTION_FULL_NAME      ".%s(%s)"
// label name
#define PATTERN_CONNECTION_LABEL_NAME     "%s"

//---------------------------------------------------------------------------
class Connection : public VerilogObject
{
  protected:
    void clean();
    
  public:
    NetArray* nets;
  //
    Connection(int tag = TAG_UNDEFINED, char* name = NULL, NetArray* nets = NULL);
    Connection(const Connection& connection);
    ~Connection();
    char* genFullName();
    Net* getNet(char* net_name, int index = -1);
    bool replaceNet(Net* net_old, Net* net_new, int copy = 0);
    void convertToDR(int polarity);
    void addNet(Net* net, int ind = -1);
};

#endif

