#ifndef _SV_OBJECT_H_
#define _SV_OBJECT_H_

#include "darray.h"

class VerilogObject;
typedef darray <VerilogObject*> VerilogObjectArray;

#include "object.h"

//---------------------------------------------------------------------------
// Tags
// parameters
#define TAG_PARAMETER_IGNORING            0x00000000
#define TAG_PARAMETER_ACCUMULATING        0x00000001
#define TAG_PARAMETER_AVERAGING           0x00000002
#define TAG_PARAMETER_MINIMISING          0x00000004
#define TAG_PARAMETER_MAXIMISING          0x00000008
#define TAG_PARAMETER_                    (TAG_PARAMETER_IGNORING | TAG_PARAMETER_ACCUMULATING | TAG_PARAMETER_AVERAGING | TAG_PARAMETER_MINIMISING | TAG_PARAMETER_MAXIMISING)

// port, connection, net properties
#define TAG_PORT_INPUT                    0x00000001
#define TAG_PORT_OUTPUT                   0x00000002
#define TAG_PORT_INOUT                    (TAG_PORT_INPUT | TAG_PORT_OUTPUT)
#define TAG_PORT_WIRE                     0x00000004
#define TAG_PORT_REG                      0x00000008
#define TAG_PORT_                         (TAG_PORT_INPUT | TAG_PORT_OUTPUT | TAG_PORT_INOUT | TAG_PORT_REG | TAG_PORT_WIRE)
// module properties
#define TAG_MODULE_CD                     0x00000100
#define TAG_MODULE_PDR                    0x00000200
#define TAG_MODULE_NDR                    0x00000400
#define TAG_MODULE_FF                     0x00000800
#define TAG_MODULE_INITIATOR              0x00001000
#define TAG_MODULE_COMPLEX                0x00002000
#define TAG_MODULE_0DR                    (TAG_MODULE_INITIATOR | TAG_MODULE_PDR)
#define TAG_MODULE_1DR                    (TAG_MODULE_INITIATOR | TAG_MODULE_NDR)
#define TAG_MODULE_                       (TAG_MODULE_CD | TAG_MODULE_PDR | TAG_MODULE_NDR | TAG_MODULE_FF | TAG_MODULE_INITIATOR | TAG_MODULE_COMPLEX)
// instance output ports properties (also applyes to nets)
#define TAG_ITEM_UNDECIDED                0x00010000
#define TAG_ITEM_SR                       0x00020000
#define TAG_ITEM_0DR                      0x00040000
#define TAG_ITEM_1DR                      0x00080000
#define TAG_ITEM_                         (TAG_ITEM_UNDECIDED | TAG_ITEM_SR | TAG_ITEM_0DR | TAG_ITEM_1DR)
// transformation modes
#define TAG_MODE_ALTERNATING_SPACER       0x00100000
#define TAG_MODE_RESET_ACTIVE_1           0x00200000
#define TAG_MODE_ASYNC                    0x00400000
#define TAG_MODE_BUFFER                   0x00800000
#define TAG_MODE_                         (TAG_MODE_ALTERNATING_SPACER | TAG_MODE_RESET_ACTIVE_1 | TAG_MODE_ASYNC | TAG_MODE_BUFFER)
// special nets
#define TAG_NET_CLOCK                     0x01000000
#define TAG_NET_RESET                     0x02000000
#define TAG_NET_VDD                       0x04000000
#define TAG_NET_GND                       0x08000000
#define TAG_NET_                          (TAG_NET_CLOCK | TAG_NET_RESET | TAG_NET_VDD | TAG_NET_GND)
// additional tags
#define TAG_OBJ_PROCESSED                 0x10000000
#define TAG_OBJ_HIDDEN                    0x20000000
#define TAG_OBJ_STATISTICATED             0x40000000
//
#define TAG_OBJ_CD                        0x80000000

// print name for escape sequence
#define PATTERN_FULL_NAME_ESCAPE          "%s "
#define SYMBOL_ESCAPE                     '\\'
#define PATTERN_ESCAPE                    "[]()*+-"
// verilog output
#define LINE_LEN_MAX                      256

//---------------------------------------------------------------------------
class VerilogObject : public Object
{
  protected:

    void escapeName();

  public:

    VerilogObject(int tag = TAG_UNDEFINED, char* name = NULL);
    VerilogObject(const VerilogObject& vobject);
    virtual void setName(char* name);
    bool isEscape();
};

#endif

