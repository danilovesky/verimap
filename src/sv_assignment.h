#ifndef _SV_ASSIGNMENT_H_

#define _SV_ASSIGNMENT_H_

#include "darray.h"
#include "hashtable.h"

class Assignment;
typedef darray <Assignment*> AssignmentArray;
typedef HashTable <Assignment> AssignmentHashTable;

#include "sv_object.h"

//---------------------------------------------------------------------------
#define ASSIGNMENT_DEFAULT_NUM    32
// PREFIX
#define VAR_PREFIX        "PREFIX"
#define VAL_PREFIX        ""
// SUFFIX
#define VAR_SUFFIX        "SUFFIX"
#define VAL_SUFFIX        ""
// DRIVE
#define VAR_DRIVE         "DRIVE"
#define VAL_DRIVE         "1"
// FF
#define VAR_FF_C          "FF_C"
#define VAL_FF_C          "C"
#define VAR_FF_D          "FF_D"
#define VAL_FF_D          "D"
#define VAR_FF_SN         "FF_SN"
#define VAL_FF_SN         "SN"
#define VAR_FF_RN         "FF_RN"
#define VAL_FF_RN         "RN"
#define VAR_FF_SE         "FF_SE"
#define VAL_FF_SE         "SE"
#define VAR_FF_SD         "FF_SD"
#define VAL_FF_SD         "SD"
#define VAR_FF_E          "FF_E"
#define VAL_FF_E          "E"
#define VAR_FF_EN         "FF_EN"
#define VAL_FF_EN         "EN"
#define VAR_FF_Q          "FF_Q"
#define VAL_FF_Q          "Q"
#define VAR_FF_QN         "FF_QN"
#define VAL_FF_QN         "QN"
#define VAR_FF_SP         "FF_SP"
#define VAL_FF_SP         "SP"
// BUF
#define VAR_BUF           "BUF"
#define VAL_BUF           "BU4"
#define VAR_BUF_IN        "BUF_IN"
#define VAL_BUF_IN        "A"
#define VAR_BUF_OUT       "BUF_OUT"
#define VAL_BUF_OUT       "Q"
#define VAR_BUF_MAX_LOAD  "BUF_MAX_LOAD"
#define VAL_BUF_MAX_LOAD  "16"
// INV
#define VAR_INV           "INV"
#define VAL_INV           "IN1"
#define VAR_INV_IN        "INV_IN"
#define VAL_INV_IN        "A"
#define VAR_INV_OUT       "INV_OUT"
#define VAL_INV_OUT       "Q"
// SPINV
#define VAR_SPINV         "SPINV"
#define VAL_SPINV         "spinv"
#define VAR_SPINV_IN      "SPINV_IN"
#define VAL_SPINV_IN      "i"
#define VAR_SPINV_OUT     "SPINV_OUT"
#define VAL_SPINV_OUT     "z"
// EMPTY
#define VAR_EMPTY         "EMPTY"
#define VAL_EMPTY         "empty"
#define VAR_EMPTY_IN      "EMPTY_IN"
#define VAL_EMPTY_IN      "i"
#define VAR_EMPTY_OUT     "EMPTY_OUT"
#define VAL_EMPTY_OUT     "z"
// OR2
#define VAR_OR2           "OR2"
#define VAL_OR2           "OR2"
#define VAR_OR2_IN1       "OR2_IN1"
#define VAL_OR2_IN1       "A"
#define VAR_OR2_IN2       "OR2_IN2"
#define VAL_OR2_IN2       "B"
#define VAR_OR2_OUT       "OR2_OUT"
#define VAL_OR2_OUT       "Q"
// OR3
#define VAR_OR3           "OR3"
#define VAL_OR3           "OR3"
#define VAR_OR3_IN1       "OR3_IN1"
#define VAL_OR3_IN1       "A"
#define VAR_OR3_IN2       "OR3_IN2"
#define VAL_OR3_IN2       "B"
#define VAR_OR3_IN3       "OR3_IN3"
#define VAL_OR3_IN3       "C"
#define VAR_OR3_OUT       "OR3_OUT"
#define VAL_OR3_OUT       "Q"
// NOR2
#define VAR_NOR2          "NOR2"
#define VAL_NOR2          "NOR2"
#define VAR_NOR2_IN1      "NOR2_IN1"
#define VAL_NOR2_IN1      "A"
#define VAR_NOR2_IN2      "NOR2_IN2"
#define VAL_NOR2_IN2      "B"
#define VAR_NOR2_OUT      "NOR2_OUT"
#define VAL_NOR2_OUT      "Q"
// NOR3
#define VAR_NOR3          "NOR3"
#define VAL_NOR3          "NOR3"
#define VAR_NOR3_IN1      "NOR3_IN1"
#define VAL_NOR3_IN1      "A"
#define VAR_NOR3_IN2      "NOR3_IN2"
#define VAL_NOR3_IN2      "B"
#define VAR_NOR3_IN3      "NOR3_IN3"
#define VAL_NOR3_IN3      "C"
#define VAR_NOR3_OUT      "NOR3_OUT"
#define VAL_NOR3_OUT      "Q"
// AND2
#define VAR_AND2          "AND2"
#define VAL_AND2          "AND2"
#define VAR_AND2_IN1      "AND2_IN1"
#define VAL_AND2_IN1      "A"
#define VAR_AND2_IN2      "AND2_IN2"
#define VAL_AND2_IN2      "B"
#define VAR_AND2_OUT      "AND2_OUT"
#define VAL_AND2_OUT      "Q"
// AND3
#define VAR_AND3          "AND3"
#define VAL_AND3          "AND3"
#define VAR_AND3_IN1      "AND3_IN1"
#define VAL_AND3_IN1      "A"
#define VAR_AND3_IN2      "AND3_IN2"
#define VAL_AND3_IN2      "B"
#define VAR_AND3_IN3      "AND3_IN3"
#define VAL_AND3_IN3      "C"
#define VAR_AND3_OUT      "AND3_OUT"
#define VAL_AND3_OUT      "Q"
// NAND2
#define VAR_NAND2         "NAND2"
#define VAL_NAND2         "NAND2"
#define VAR_NAND2_IN1     "NAND2_IN1"
#define VAL_NAND2_IN1     "A"
#define VAR_NAND2_IN2     "NAND2_IN2"
#define VAL_NAND2_IN2     "B"
#define VAR_NAND2_OUT     "NAND2_OUT"
#define VAL_NAND2_OUT     "Q"
// AND3
#define VAR_NAND3          "NAND3"
#define VAL_NAND3          "NAND3"
#define VAR_NAND3_IN1      "NAND3_IN1"
#define VAL_NAND3_IN1      "A"
#define VAR_NAND3_IN2      "NAND3_IN2"
#define VAL_NAND3_IN2      "B"
#define VAR_NAND3_IN3      "NAND3_IN3"
#define VAL_NAND3_IN3      "C"
#define VAR_NAND3_OUT      "NAND3_OUT"
#define VAL_NAND3_OUT      "Q"
// XOR2
#define VAR_XOR2          "XOR2"
#define VAL_XOR2          "XOR2"
#define VAR_XOR2_IN1      "XOR2_IN1"
#define VAL_XOR2_IN1      "A"
#define VAR_XOR2_IN2      "XOR2_IN2"
#define VAL_XOR2_IN2      "B"
#define VAR_XOR2_OUT      "XOR2_OUT"
#define VAL_XOR2_OUT      "Q"
// XNOR2
#define VAR_XNOR2         "XNOR2"
#define VAL_XNOR2         "XNOR2"
#define VAR_XNOR2_IN1     "XNOR2_IN1"
#define VAL_XNOR2_IN1     "A"
#define VAR_XNOR2_IN2     "XNOR2_IN2"
#define VAL_XNOR2_IN2     "B"
#define VAR_XNOR2_OUT     "XNOR2_OUT"
#define VAL_XNOR2_OUT     "Q"
// C-element with Reset
#define VAR_CCx           "CCx"
#define VAL_CCx           "cc0%dd1"
#define VAR_CCx_INx       "CC_INx"
#define VAL_CCx_INx       "a%d"
#define VAR_CCx_Q         "CC_Q"
#define VAL_CCx_Q         "q"
#define VAR_CCx_QN        "CC_QN"
#define VAL_CCx_QN        "qn"
#define VAR_CCx_RN        "CCx_RN"
#define VAL_CCx_RN        "cdn"
// C-element with Set
#define VAR_CPx           "CPx"
#define VAL_CPx           "cp0%dd1"
#define VAR_CPx_INx       "CP_INx"
#define VAL_CPx_INx       "a%d"
#define VAR_CPx_Q         "CP_Q"
#define VAL_CPx_Q         "q"
#define VAR_CPx_QN        "CP_QN"
#define VAL_CPx_QN        "qn"
#define VAR_CPx_SN        "CPx_RN"
#define VAL_CPx_SN        "sdn"
// SR2DR
#define VAR_SR2DR         "SR2DR"
#define VAL_SR2DR         "SR2DR"
#define VAR_SR2DR_C       "SR2DR_C"
#define VAL_SR2DR_C       "C"
#define VAR_SR2DR_IN      "SR2DR_IN"
#define VAL_SR2DR_IN      "A"
#define VAR_SR2DR_OUT     "SR2DR_OUT"
#define VAL_SR2DR_OUT     "Q"
#define VAR_SR2DR_SP      "SR2DR_SP"
#define VAL_SR2DR_SP      "SP"
// DR2SR
#define VAR_DR2SR         "DR2SR"
#define VAL_DR2SR         "DR2SR"
#define VAR_DR2SR_C       "DR2SR_C"
#define VAL_DR2SR_C       "C"
#define VAR_DR2SR_IN      "DR2SR_IN"
#define VAL_DR2SR_IN      "A"
#define VAR_DR2SR_OUT     "DR2SR_OUT"
#define VAL_DR2SR_OUT     "Q"
#define VAR_DR2SR_SP      "DR2SR_SP"
#define VAL_DR2SR_SP      "SP"
// SPCTRL
#define VAR_SPCTRL        "SPCTRL"
#define VAL_SPCTRL        "spctrl"
#define VAR_SPCTRL_C      "SPCTRL_C"
#define VAL_SPCTRL_C      "C"
#define VAR_SPCTRL_RN     "SPCTRL_RN"
#define VAL_SPCTRL_RN     "RN"
#define VAR_SPCTRL_OUT    "SPCTRL_OUT"
#define VAL_SPCTRL_OUT    "Q"
// GOCTRL
#define VAR_GOCTRL        "GOCTRL"
#define VAL_GOCTRL        "goctrl"
#define VAR_GOCTRL_C      "GOCTRL_C"
#define VAL_GOCTRL_C      "C"
#define VAR_GOCTRL_DONE   "GOCTRL_DONE"
#define VAL_GOCTRL_DONE   "DONE"
#define VAR_GOCTRL_SN     "GOCTRL_SN"
#define VAL_GOCTRL_SN     "SN"
#define VAR_GOCTRL_OUT    "GOCTRL_OUT"
#define VAL_GOCTRL_OUT    "GO"
// SPAER / GO / DONE / CLOCK / RESET
#define VAR_SPACER        "SPACER"
#define VAL_SPACER        "spacer"
#define VAR_GO            "GO"
#define VAL_GO            "go"
#define VAR_DONE          "DONE"
#define VAL_DONE          "done"
#define VAR_CLOCK         "CLOCK"
#define VAL_CLOCK         "clock"
#define VAR_RESET         "RESET"
#define VAL_RESET         "reset"
// VDD 
#define VAR_VDD           "VDD"
#define VAL_VDD           "vdd"
#define VAR_VDD_OUT       "VDD_OUT"
#define VAL_VDD_OUT       "Q"
#define VAR_VDD_C         "VDD_C"
#define VAL_VDD_C         "C"
#define VAR_VDD_SP        "VDD_SP"
#define VAL_VDD_SP        "SP"
// GND
#define VAR_GND           "GND"
#define VAL_GND           "gnd"
#define VAR_GND_OUT       "GND_OUT"
#define VAL_GND_OUT       "Q"
#define VAR_GND_C         "GND_C"
#define VAL_GND_C         "C"
#define VAR_GND_SP        "GND_SP"
#define VAL_GND_SP        "SP"

// Tree 2-input gates
#define VAR_TREE_2_INPUT  VAR_AND2","VAR_OR2","VAR_NAND2","VAR_NOR2
#define VAR_TREE_3_INPUT  VAR_AND3","VAR_OR3","VAR_NAND3","VAR_NOR3

//---------------------------------------------------------------------------
class Assignment : public VerilogObject
{
  public:
    char* val;

    Assignment(int tag = TAG_UNDEFINED, char* name = NULL, char* val = NULL);
    Assignment(const Assignment &assignment);
    ~Assignment();
    void setVal(char* val);
    char* getVal();
    static AssignmentArray* genDefaults();
};

#endif

