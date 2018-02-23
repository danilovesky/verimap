#ifndef _SV_NET_H_
#define _SV_NET_H_

#include "darray.h"
#include "hashtable.h"

class Net;
typedef darray <Net*> NetArray;
typedef HashTable <Net> NetHashTable;

#include "sv_object.h"
#include "sv_delay.h"
#include "sv_port.h"
#include "sv_instance.h"

//---------------------------------------------------------------------------
// vdd, gnd
#define NAME_NET_GND                     "1'b0"
#define NAME_NET_VDD                     "1'b1"
#define NAME_NET_GND                     "1'b0"
#define NAME_NET_VDD_DR                  "1'b1"
#define NAME_NET_GND_DR                  "1'b0"
#define PATTERN_NET_NOT                  "not_%s"
#define PATTERN_NET_SPINV                "spinv_%s"
#define PATTERN_NET_DR_RAIL              "%s_%d"
#define PATTERN_NET_CONST                "const_%s"
// full name
#define PATTERN_NET_FULL_NAME            "%s[%d]"
// label name
#define PATTERN_NET_RESET_NOT            "%s_not"
#define PATTERN_NET_LABEL                "%s_%d"
#define PATTERN_NET_TREE                 "%s_l%d_n%d"
#define PATTERN_NET_CD                   "%s_cd"
#define PATTERN_NET_LAYER                "layer_%d"
#define SYMBOL_NET_0                     '0'
#define SYMBOL_NET_1                     '1'
#define SYMBOL_NET_UNDERSCORE            '_'

//---------------------------------------------------------------------------
class Net : public VerilogObject
{
  protected:
    int index;
    int depth;
    int layer;
    Delay* delay;
    Port* container;

  public:
    InstanceArray* preset;
    InstanceArray* postset;

    Net(int tag = TAG_UNDEFINED, char* name = NULL, int index = -1, int depth = -1, int layer = -1, Delay* delay = NULL, 
      InstanceArray* preset = NULL, InstanceArray* postset = NULL, Port* container = NULL);
    Net(const Net& incidence);
    ~Net();
    void setIndex(int index);
    int getIndex();
    void setDepth(int depth);
    int getDepth();
    void setLayer(int layer);
    int getLayer();
    void setDelay(Delay* delay);
    Delay* getDelay();
    void addPreset(Instance* instance);
    void removePreset(Instance* instance);
    void addPostset(Instance* instance);
    void removePostset(Instance* instance);
    void setContainer(Port* container);
    Port* getContainer();
    char* genFullName();
    char* genLabelName();
    char* genPearlName();
    void convertToDR(int polarity);
    void convertToSR();
    static int compareByMask(const void* mask, const void* object);
};

#endif

