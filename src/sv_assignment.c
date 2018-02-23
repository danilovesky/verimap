#include "sv_assignment.h"
#include "hash.h"

//---------------------------------------------------------------------------
Assignment::Assignment(int tag, char* name, char* val) : VerilogObject(tag, name)
{
  this->val = NULL;
  this->setVal(val);
}

//---------------------------------------------------------------------------
Assignment::Assignment(const Assignment &assignment) : VerilogObject(assignment)
{
  this->val = NULL;
  this->setVal(namecopy(assignment.val));
}

//---------------------------------------------------------------------------
Assignment::~Assignment()
{
  delete [] this->val;
}

//---------------------------------------------------------------------------
void Assignment::setVal(char* val)
{
  delete [] this->val;
  this->val = val;
}

//---------------------------------------------------------------------------
char* Assignment::getVal()
{
  return this->val;
}

//---------------------------------------------------------------------------
AssignmentArray* Assignment::genDefaults()
{
  AssignmentArray* assignments = new AssignmentArray(ASSIGNMENT_DEFAULT_NUM);
  // PREFIX
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_PREFIX), namecopy(VAL_PREFIX)));
  // SUFFIX
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_SUFFIX), namecopy(VAL_SUFFIX)));
  // DRIVE
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_DRIVE), namecopy(VAL_DRIVE)));
  // FF
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_FF_C),  namecopy(VAL_FF_C)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_FF_D),  namecopy(VAL_FF_D)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_FF_SN), namecopy(VAL_FF_SN)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_FF_RN), namecopy(VAL_FF_RN)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_FF_SE), namecopy(VAL_FF_SE)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_FF_SD), namecopy(VAL_FF_SD)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_FF_E),  namecopy(VAL_FF_E)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_FF_EN), namecopy(VAL_FF_EN)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_FF_Q),  namecopy(VAL_FF_Q)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_FF_QN), namecopy(VAL_FF_QN)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_FF_SP), namecopy(VAL_FF_SP)));
  // BUF
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_BUF),          namecopy(VAL_BUF)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_BUF_IN),       namecopy(VAL_BUF_IN)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_BUF_OUT),      namecopy(VAL_BUF_OUT)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_BUF_MAX_LOAD), namecopy(VAL_BUF_MAX_LOAD)));
  // INV
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_INV),     namecopy(VAL_INV)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_INV_IN),  namecopy(VAL_INV_IN)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_INV_OUT), namecopy(VAL_INV_OUT)));
  // SPINV
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_SPINV),     namecopy(VAL_SPINV)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_SPINV_IN),  namecopy(VAL_SPINV_IN)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_SPINV_OUT), namecopy(VAL_SPINV_OUT)));
  // EMPTY
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_EMPTY),     namecopy(VAL_EMPTY)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_EMPTY_IN),  namecopy(VAL_EMPTY_IN)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_EMPTY_OUT), namecopy(VAL_EMPTY_OUT)));
  // OR2
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_OR2),     namecopy(VAL_OR2)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_OR2_IN1), namecopy(VAL_OR2_IN1)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_OR2_IN2), namecopy(VAL_OR2_IN2)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_OR2_OUT), namecopy(VAL_OR2_OUT)));
  // OR3
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_OR3),     namecopy(VAL_OR3)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_OR3_IN1), namecopy(VAL_OR3_IN1)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_OR3_IN2), namecopy(VAL_OR3_IN2)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_OR3_IN3), namecopy(VAL_OR3_IN3)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_OR3_OUT), namecopy(VAL_OR3_OUT)));
  // NOR2
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_NOR2),     namecopy(VAL_NOR2)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_NOR2_IN1), namecopy(VAL_NOR2_IN1)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_NOR2_IN2), namecopy(VAL_NOR2_IN2)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_NOR2_OUT), namecopy(VAL_NOR2_OUT)));
  // NOR3
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_NOR3),     namecopy(VAL_NOR3)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_NOR3_IN1), namecopy(VAL_NOR3_IN1)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_NOR3_IN2), namecopy(VAL_NOR3_IN2)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_NOR3_IN3), namecopy(VAL_NOR3_IN3)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_NOR3_OUT), namecopy(VAL_NOR3_OUT)));
  // AND2
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_AND2),     namecopy(VAL_AND2)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_AND2_IN1), namecopy(VAL_AND2_IN1)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_AND2_IN2), namecopy(VAL_AND2_IN2)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_AND2_OUT), namecopy(VAL_AND2_OUT)));
  // AND3
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_AND3),     namecopy(VAL_AND3)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_AND3_IN1), namecopy(VAL_AND3_IN1)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_AND3_IN2), namecopy(VAL_AND3_IN2)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_AND3_IN3), namecopy(VAL_AND3_IN3)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_AND3_OUT), namecopy(VAL_AND3_OUT)));
  // NAND2
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_NAND2),     namecopy(VAL_NAND2)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_NAND2_IN1), namecopy(VAL_NAND2_IN1)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_NAND2_IN2), namecopy(VAL_NAND2_IN2)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_NAND2_OUT), namecopy(VAL_NAND2_OUT)));
  // NAND3
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_NAND3),     namecopy(VAL_NAND3)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_NAND3_IN1), namecopy(VAL_NAND3_IN1)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_NAND3_IN2), namecopy(VAL_NAND3_IN2)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_NAND3_IN3), namecopy(VAL_NAND3_IN3)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_NAND3_OUT), namecopy(VAL_NAND3_OUT)));
  // XOR2
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_XOR2),     namecopy(VAL_XOR2)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_XOR2_IN1), namecopy(VAL_XOR2_IN1)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_XOR2_IN2), namecopy(VAL_XOR2_IN2)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_XOR2_OUT), namecopy(VAL_XOR2_OUT)));
  // XNOR2
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_XNOR2),     namecopy(VAL_XNOR2)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_XNOR2_IN1), namecopy(VAL_XNOR2_IN1)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_XNOR2_IN2), namecopy(VAL_XNOR2_IN2)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_XNOR2_OUT), namecopy(VAL_XNOR2_OUT)));
  // C-element with Reset
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_CCx),     namecopy(VAL_CCx)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_CCx_INx), namecopy(VAL_CCx_INx)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_CCx_Q),   namecopy(VAL_CCx_Q)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_CCx_QN),  namecopy(VAL_CCx_QN)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_CCx_RN),  namecopy(VAL_CCx_RN)));
  // C-element with Set
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_CPx),     namecopy(VAL_CPx)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_CPx_INx), namecopy(VAL_CPx_INx)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_CPx_Q),   namecopy(VAL_CPx_Q)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_CPx_QN),  namecopy(VAL_CPx_QN)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_CPx_SN),  namecopy(VAL_CPx_SN)));
  // SR2DR
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_SR2DR),     namecopy(VAL_SR2DR)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_SR2DR_C),   namecopy(VAL_SR2DR_C)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_SR2DR_IN),  namecopy(VAL_SR2DR_IN)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_SR2DR_OUT), namecopy(VAL_SR2DR_OUT)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_SR2DR_SP),  namecopy(VAL_SR2DR_SP)));
  // DR2SR
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_DR2SR),     namecopy(VAL_DR2SR)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_DR2SR_C),   namecopy(VAL_DR2SR_C)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_DR2SR_IN),  namecopy(VAL_DR2SR_IN)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_DR2SR_OUT), namecopy(VAL_DR2SR_OUT)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_DR2SR_SP),  namecopy(VAL_DR2SR_SP)));
  // SPCTRL
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_SPCTRL),     namecopy(VAL_SPCTRL)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_SPCTRL_C),   namecopy(VAL_SPCTRL_C)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_SPCTRL_RN),  namecopy(VAL_SPCTRL_RN)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_SPCTRL_OUT), namecopy(VAL_SPCTRL_OUT)));
  // GOCTRL
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_GOCTRL),      namecopy(VAL_GOCTRL)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_GOCTRL_C),    namecopy(VAL_GOCTRL_C)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_GOCTRL_DONE), namecopy(VAL_GOCTRL_DONE)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_GOCTRL_SN),   namecopy(VAL_GOCTRL_SN)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_GOCTRL_OUT),  namecopy(VAL_GOCTRL_OUT)));
  // ports
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_SPACER), namecopy(VAL_SPACER)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_GO),     namecopy(VAL_GO)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_DONE),   namecopy(VAL_DONE)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_CLOCK),   namecopy(VAL_CLOCK)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_RESET),   namecopy(VAL_RESET)));
  // VDD
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_VDD),     namecopy(VAL_VDD)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_VDD_OUT), namecopy(VAL_VDD_OUT)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_VDD_C),   namecopy(VAL_VDD_C)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_VDD_SP),  namecopy(VAL_VDD_SP)));
  // GND
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_GND),     namecopy(VAL_GND)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_GND_OUT), namecopy(VAL_GND_OUT)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_GND_C),   namecopy(VAL_GND_C)));
  assignments->add(new Assignment(TAG_UNDEFINED, namecopy(VAR_GND_SP),  namecopy(VAL_GND_SP)));

  return assignments;
}

