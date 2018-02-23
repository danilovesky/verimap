#ifndef _SV_INSTANCE_H_
#define _SV_INSTANCE_H_

#include "darray.h"
#include "hashtable.h"

class Instance;
typedef darray <Instance*> InstanceArray;
typedef HashTable <Instance> InstanceHashTable;

#include "sv_object.h"
#include "sv_net.h"
#include "sv_connection.h"
#include "sv_lib.h"

// full name
#define PATTERN_INSTANCE_FULL_NAME        "%s[%d]"
// label name
#define PATTERN_INSTANCE_LABEL            "%s_%d"

#define PATTERN_INSTANCE                  "inst_%s"
#define PATTERN_INSTANCE_DR_RAIL          "inst_rail_%d"

#define PATTERN_INSTANCE_CD               "inst_%s_cd"
#define PATTERN_INSTANCE_LAYER            "inst_layer_%d"

// sr
#define SUFFIX_SR                         "_sr"
#define PATTERN_MODULE_SR                 "%s_sr"

// dr
#define SUFFIX_PDR                        "_pdr"
#define PATTERN_MODULE_PDR                "%s_pdr"

#define SUFFIX_NDR                        "_ndr"
#define PATTERN_MODULE_NDR                "%s_ndr"

#define SUFFIX_0DR                        "_0dr"
#define PATTERN_MODULE_0DR                "%s_0dr"

#define SUFFIX_1DR                        "_1dr"
#define PATTERN_MODULE_1DR                "%s_1dr"

//---------------------------------------------------------------------------
class Instance : public VerilogObject
{
  private:
    int depth;
    int layer;
    int width;
    int index;
    char* module_name;
    Module* container;

    void clean();

  public:
    ConnectionArray* connections;
  //
    Instance(int tag, char* name, int index = -1, int depth = -1, int width = 0,  int layer = -1, char* module_name = NULL, ConnectionArray* connections = NULL);
    Instance(const Instance &instance);
    ~Instance();
    void setIndex(int index);
    int getIndex();
    void setDepth(int depth);
    int getDepth();
    void setWidth(int width);
    int getWidth();
    void setLayer(int layer);
    int getLayer();
    void setModuleName(char* module_name);
    char* getModuleName();
    void setContainer(Module* container);
    Module* getContainer();
    char* genFullName();
    char* genLabelName();
    void addConnection(Connection* connection, int ind = -1);
    void removeConnection(Connection* connection);
    Connection* getConnection(char* connection_name);
    void connectNet(int connection_tag, char* connection_name, int net_tag, char* net_name, int connection_position = -1);
    void connectNet(int connection_tag, char* connection_name, Net* net, int connection_position = -1);
    bool replaceNet(Net* net_old, Net* net_new, int copy = 0);
    void convertLogicToDR(Lib* lib);
    void convertRegisterToMS(Lib* lib);
    void convertRegisterToLC(Lib* lib);
    void convertToSR();
};

#endif

