#ifndef _SV_LIB_H_
#define _SV_LIB_H_

class Lib;

#include <stdio.h>
#include "sv_object.h"
#include "sv_module.h"
#include "sv_rule.h"
#include "sv_trans.h"
#include "sv_assignment.h"

//---------------------------------------------------------------------------
// polarity
#define PREFIX_SR                         0x00000100
#define PREFIX_DR                         0x00000200
#define PREFIX_POSITIVE_                  0x00000001
#define PREFIX_NEGATIVE_                  0x00000002
#define PREFIX_DIRECT_                    0x00000010
#define PREFIX_COMPLEMENTARY_             0x00000020
#define PREFIX_PD                         (PREFIX_POSITIVE_ | PREFIX_DIRECT_)
#define PREFIX_PC                         (PREFIX_POSITIVE_ | PREFIX_COMPLEMENTARY_)
#define PREFIX_ND                         (PREFIX_NEGATIVE_ | PREFIX_DIRECT_)
#define PREFIX_NC                         (PREFIX_NEGATIVE_ | PREFIX_COMPLEMENTARY_)

// polarity
#define POLARITY_INPUT                    "np"
#define POLARITY_OUTPUT                   "NP"
#define POLARITY_INPUT_POSITIVE           'p'
#define POLARITY_INPUT_NEGATIVE           'n'
#define POLARITY_OUTPUT_POSITIVE          'P'
#define POLARITY_OUTPUT_NEGATIVE          'N'
// rails
#define RAIL_INPUT                        "sd"
#define RAIL_OUTPUT                       "SD"
#define RAIL_INPUT_SINGLE                 's'
#define RAIL_INPUT_DUAL                   'd'
#define RAIL_OUTPUT_SINGLE                'S'
#define RAIL_OUTPUT_DUAL                  'D'
// extra ports
#define EXTRA_INPUT_CLOCK                 "c"
#define EXTRA_INPUT_RESET                 "r"
#define EXTRA_OUTPUT_CLOCK                "C"
#define EXTRA_OUTPUT_RESET                "R"

// key words of verilog netlist
#define KEY_MODULE                        "module"
#define KEY_ENDMODULE                     "endmodule"
#define KEY_INPUT                         "input"
#define KEY_OUTPUT                        "output"
#define KEY_INOUT                         "inout"
#define KEY_REG                           "reg"
#define KEY_WIRE                          "wire"
#define KEY_PARAMETER                     "parameter"
#define KEY_DELAY                         "#"

//---------------------------------------------------------------------------
class Lib
{
  protected:
    RuleHashTable* rule_hash_table;
    TransHashTable* trans_hash_table;
    GenHashTable* gen_hash_table;
    AssignmentHashTable* assignment_hash_table;
    ModuleArray* gens;
    RuleArray* rules;
    TransArray* transs;
    AssignmentArray* assignments;

    void clean();
    float calcParameter(float value_cur, float value_prot);
    void findHierarchy(ModuleArray* modules, Module* module, int depth);
    void writeModule(FILE* file, Module* module_cur, int tag_ignore = TAG_OBJ_HIDDEN);
    void writeLibItem(FILE* file, Module* module, char* parameter_names);

  public:
    ModuleArray* modules;
    ModuleHashTable* module_hash_table;
    char* delay_min_parameters;
    char* delay_max_parameters;

    Lib(ModuleArray* modules = NULL, ModuleArray* gens = NULL, RuleArray* rules = NULL, AssignmentArray* assignments = NULL);
    ~Lib();

    void readRules(char* file_names);
    bool addRule(Rule* rule);
    void addRules(RuleArray* rules);
    Rule* getRule(char* module_name, int prefix_len_min = 2, int suffix_len_max = 255);
    Rule* getRuleTrans(char* module_name, int prefix_len_min = 2, int suffix_len_max = 255);
    void modifyRules(int tag_mask = TAG_MODULE_FF, int tag_exclude = TAG_MODULE_NDR);

    void setParameters(char* delay_min_parameters, char* delay_max_parameters);
    void readParameters(char* file_names);
    void setModulesWidth(char* width_param);
    float getMinDelay(const char* assignment_names);
    float getMaxDelay(const char* assignment_names);

    char* getLogicPrefix(char* module_name, int prefix_type);
    int getLogicTag(char* module_name);
    char* getLogicDrive(char* module_name);
    char* getLogic(char* module_name, int prefix_type);
    char* getLogicDR(char* module_name, int tag_mask);
    bool getLogicInfo(char* module_name, int tag_mask);

    int getPortNum(char* module_name, int port_orig_num, char* flags);
    int getPortInd(char* module_name, int port_io_ind, char* flags1, char* flags2);
    int getPortInfo(char* module_name, int port_index, char* flags);

    void readModules(char* file_names);
    void writeModules(char* file_name, ModuleArray* modules);
    bool addModule(Module* module, int position = -1);
    void addModules(ModuleArray* modules);
    Module* getModule(char* module_name);
    void calcConnections(ModuleArray* modules);
    void sortConnections(ModuleArray* modules);
    void calcHierarchy(ModuleArray* modules);
    int getMaxDepth(ModuleArray* modules);
    void calcTags();

    void readGens(char* file_name);
    void writeGens(char* file_name);
    bool addGen(Module* module, int position = -1);
    void addGens(ModuleArray* modules);
    Module* getGen(char* module_name);
    Module* genModuleDR(char* module_name, int tag_mask);
    int findModuleC_width(int input_num);
    void findModuleC_x2x3(int input_num, int &x2, int &x3);
    Module* genModuleC(int input_num);
    void calcStatistics(Module* module_top);
    
    void writeLib(char* file_name, char* parameter_names);

    void readAssignments(char* file_names);
    bool addAssignment(Assignment* assignment);
    void addAssignments(AssignmentArray* assignments);
    Assignment* getAssignment(char* var_name);
    char* getAssignmentVal(char* var_name);
    void printAssignments();
};

#endif

