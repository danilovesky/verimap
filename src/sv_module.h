#ifndef _SV_MODULE_H_
#define _SV_MODULE_H_

#include "darray.h"
#include "hashtable.h"

class Module;
typedef darray <Module*> ModuleArray;
typedef HashTable <Module> ModuleHashTable;
typedef HashTable <Module> GenHashTable;

#include "sv_object.h"
#include "sv_parameter.h"
#include "sv_port.h"
#include "sv_instance.h"
#include "sv_lib.h"

//---------------------------------------------------------------------------
#define NAME_MODULE_VDD                   "1"
#define NAME_MODULE_GND                   "0"

#define PEARL_READ_GCF_TIMING_LIBRARIES   "ReadGCFTimingLibraries"
#define PEARL_READ_VERILOG                "ReadVerilog"
#define PEARL_TOP_LEVEL_CELL              "TopLevelCell"
#define PEARL_SET_MAX_POSSIBILITIES       "SetMaxPossibilities"
#define PEARL_FIND_PATHS_FROM             "FindPathsFrom"
#define PEARL_SHOW_POSSIBILITY            "ShowPossibility"
#define PEARL_QUIT                        "quit"

//---------------------------------------------------------------------------
class Module : public VerilogObject
{
  protected:
    int depth;
    int width;
    Port* port_clock;
    Port* port_spacer;
    Port* port_reset;
    Port* port_go;
    Port* port_done;
    Port* port_vdd;
    Port* port_gnd;
    PortHashTable* port_hash_table;

    void clean();
    void calcIncidence();
    void findNetHierarchy(Net* net, int depth, int layer);
    void findInstanceHierarchy(Instance* instance, int depth, int layer);
    void findSpacer(Instance* instance);
    void findCD(Net* net_start, NetArray* nets_layer, int completion_delay, int logic_delay, int iteration);
    NetArray* calcNetsCD();
    
    void connectNetsEmpty(Net* net_in, Net* net_out);
    void connectNetsBuffer(Net* net_in, Net* net_out, char* drive = NULL);
    void connectNetsInverter(Net* net_in, Net* net_out, char* drive = NULL);
    void connectNetsSI(Net* net_in, Net* net_out, char* drive = NULL);
    void reuseConnections(Instance* instance, char* connection_name_q, char* connection_name_qn);
    void addReset();
    void connectReset(Instance* instance, char* connection_name, bool propagate, int active_level);
    void addClock();
    void connectClock(Instance* instance, char* connection_name);
    void addSpacer();
    void connectSpacer(Instance* instance, int connection_tag, char* connection_name);
    void addGo();
    void connectGo(Instance* instance, int connection_tag, char* connection_name);
    void addDone();
    void connectDone(Instance* instance, int connection_tag, char* connection_name);

    int getOptimalDR(char* parameter_names);
    void convertInstancesToDR();
    void convertRegisterToDR(Instance* instance);
    void convertToExtraPort(Instance* instance);
    void convertConstantsToDR();
    void mergeNets();
    void removeRedundantNets();
    void bufferPort(Port* port);
    
  public:
    ParameterArray* parameters;
    PortArray* ports;
    InstanceArray* instances;
    InstanceArray* users;
    Lib* lib;
    NetArray* nets_cd_calc;
    NetArray* nets_cd_read; 

    Module(int tag = TAG_UNDEFINED, char* name = NULL, ParameterArray* parameters = NULL, PortArray* ports = NULL, InstanceArray* instances = NULL, Lib* lib = NULL);
    Module(const Module &module);
    ~Module();

    void setDepth(int depth);
    int getDepth();
    void setWidth(int width);
    int getWidth();

    void addUser(Instance* user, int position = -1);
    void addUsers(InstanceArray* users);
    void removeUser(Instance* user);

    void addParameter(Parameter* parameter, int position = -1);
    void addParameters(ParameterArray* parameters);
    void removeParameter(Parameter* parameter);
    Parameter* getParameter(char* parameter_name);

    void addPort(Port* port, int position = -1);
    void addPorts(PortArray* ports);
    void removePort(Port* port);
    Port* getPort(char* port_name);
    int getPortNum(int tag_mask);
    Net* getNet(char* net_name, int net_index);
    Net* getNet(Net* net);

    void addInstance(Instance* instance, int position = -1);
    void addInstances(InstanceArray* instances);
    void removeInstance(Instance* instance);
    Instance* getInstance(char* instance_name, int instance_index = -1);

    bool hasTimingInfo();
    float getMinDelay();
    float getMaxDelay();

    void setPortsInfo(char* port_names, int tag, int tag_mask);
    void calcPortsSR();
    void calcConnections();
    void sortConnections();
    void calcTags();
    void calcHierarchy();
    void calcSpacer();
    void setAllCD();

    void convertPortsToDR();
    void convertToConstants();
    void convertToNL();
    void convertToOP(char* parameter_names);
    void convertToOS();
    void convertToBalanced();
    void convertToDR();
    void convertToCD();
    Module* copyInterface();
    void convertToWrapperSR();

    void simplify();
    void writeWires(FILE* file, char* pattern, char* path, int tag_mask = TAG_PORT_WIRE, int tag_mask_not = TAG_NET_);
    void writeCMD(FILE* file, int path_posibility);
};

#endif
