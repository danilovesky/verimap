#ifndef _SV_CIRCUIT_H_
#define _SV_CIRCUIT_H_

class Circuit;

#include <stdio.h>
#include "sv_object.h"
#include "sv_module.h"
#include "sv_lib.h"

#define FORMAT_OUTPUT_UNDEFINED        0x00000000
#define FORMAT_OUTPUT_PROTOTYPES       0x00000001

//---------------------------------------------------------------------------
class Circuit : public VerilogObject
{
  protected:
    ModuleHashTable* module_hash_table;
    ModuleArray* modules;
    Module* module_top;

    void clean();
    void findHierarchy(Module* module, int depth);
    int getMaxDepth();
    void findTags(Module* module_top);
    void findFullModules(ModuleArray* full_modules, Module* full_module);
    ModuleArray* calcFullModules();

  public:
    Circuit(int tag = TAG_UNDEFINED, char* name = NULL, ModuleArray* modules = NULL, Lib* lib = NULL);
    Circuit(const Circuit &circuit);
    ~Circuit();

    Lib* lib;

    void readModules(char* file_names);
    void readCD(char* file_names);
    void writeModules(char* file_name);
    void writeFullModules(char* file_name);
    void writeStatistics(char* file_name, char* command_line = NULL);
    void writeWires(char* file_name, char* pattern);
    void writeCMD(char* cmd_file_name, char* gcf_file_name, char* input_file_names, int path_possibility);

    void addModule(Module* module, int position = -1);
    void addModules(ModuleArray* modules);
    void removeModule(Module* module);
    Module* getModule(char* module_name);

    Module* setModuleTop(char* module_name);
    Module* getModuleTop();
    Module* calcModuleTop();

    void setPortsInfo(char* port_names, int tag, int tag_mask = (TAG_PORT_INPUT | TAG_PORT_OUTPUT));
    void calcPortsSR();
    void calcHierarchy();
    void calcTags();
    void calcSpacer();
    bool isHierarchical();
    bool isBranchingHierarchical();
    void setAllCD();

    void convertToConstants();
    void convertToNL();
    void convertToOP(char* parameter_names);
    void convertToOS();
    void convertToBalanced();
    void convertToDR(); //(Module* module_top, int tag_mask);
    void convertToCD();

    void simplify();
};

#endif

