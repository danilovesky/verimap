#include "sv_circuit.h"
#include "sv_object.h"
#include "sv_module.h"
#include "sv_lib.h"
#include "sverilog.h"
#include "objects.h"
#include "messages.h"

//---------------------------------------------------------------------------
Circuit::Circuit(int tag, char* name, ModuleArray* modules, Lib* lib) : VerilogObject(tag, name)
{
  this->lib = lib;
  this->module_hash_table = new ModuleHashTable();
  this->modules = NULL;
  this->addModules(modules);
}

//---------------------------------------------------------------------------
Circuit::Circuit(const Circuit &circuit) : VerilogObject(circuit)
{
  this->lib = circuit.lib;
  this->module_hash_table = new ModuleHashTable();
  this->modules = NULL;
  this->addModules(circuit.modules);
}

//---------------------------------------------------------------------------
Circuit::~Circuit()
{
  clean();
  delete this->module_hash_table; this->module_hash_table = NULL;
  delete this->modules; this->modules = NULL;
}

//---------------------------------------------------------------------------
void Circuit::clean()
{
  // modules are actualy stored in the library, so there is no need to clean the modules array
}

//---------------------------------------------------------------------------
void Circuit::readModules(char* file_names)
{
  if (file_names)
  {
    int name_index = 0;
    sverilog_modules = new ModuleArray(1);
    while (sverilog_filename = names2name(file_names, name_index++))
    {
      if (strcmp(sverilog_filename, NAME_STDIO) == 0)
      {
        delete [] sverilog_filename;
        sverilog_filename = namecopy("stdin");
        sverilog_in = stdin;
      }
      else
      if ((sverilog_in = fopen(sverilog_filename, "r")) == NULL)
        Error("opening input file <%s>", sverilog_filename);
      sverilog_parse();
      if (sverilog_in != stdin)
        fclose(sverilog_in);
      delete [] sverilog_filename;
    }
    this->addModules(sverilog_modules);
    delete sverilog_modules; sverilog_modules = NULL;
  }
  sverilog_lex_destroy();
  this->lib->calcConnections(this->modules);
  this->lib->sortConnections(this->modules);
}

//---------------------------------------------------------------------------
void Circuit::readCD(char* file_names)
{
  if (this->module_top && (this->getMaxDepth() == 0))
  {
    if (file_names)
    {
      int name_index = 0;
      if (this->module_top->nets_cd_read == NULL)
        this->module_top->nets_cd_read = new NetArray(1);
      objects_objects = (VerilogObjectArray*) this->module_top->nets_cd_read;
      while (objects_filename = names2name(file_names, name_index++))
      {
        if (strcmp(objects_filename, NAME_STDIO) == 0)
        {
          delete [] objects_filename;
          objects_filename = namecopy("stdin");
          objects_in = stdin;
        }
        else
        if ((objects_in = fopen(objects_filename, "r")) == NULL)
          Error("opening input file <%s>", objects_filename);
        objects_parse();
        if (objects_in != stdin)
          fclose(objects_in);
        delete [] objects_filename;
      }
    }
  }
  else
    Warning("cannot read completion nets for hierarchical netlist");
}

//---------------------------------------------------------------------------
void Circuit::writeModules(char* file_name)
{
  this->lib->writeModules(file_name, this->modules);
}

//---------------------------------------------------------------------------
void Circuit::findFullModules(ModuleArray* full_modules, Module* full_module)
{
  for (int instance_index = 0; instance_index < full_module->instances->num; instance_index++)
  {
    Instance* instance_cur = full_module->instances->arr[instance_index];
    char* name_cur = instance_cur->getModuleName();
    if (name_cur)
    {
      Module* module_cur = this->lib->getModule(name_cur);
      if ( module_cur
        && module_cur->testTag(TAG_MODULE_COMPLEX)
        && !module_cur->testTag(TAG_OBJ_PROCESSED) )
      {
        module_cur->orTag(TAG_OBJ_PROCESSED);
        findFullModules(full_modules, module_cur);
        full_modules->add(module_cur);
      }
    }
  }  
}

//---------------------------------------------------------------------------
ModuleArray* Circuit::calcFullModules()
{
  ModuleArray* full_modules = new ModuleArray(this->modules->num);
  // clean TAG_OBJ_PROCESSED tag
  for (int module_lib_index = 0; module_lib_index < this->lib->modules->num; module_lib_index++)
  {
    Module* module_lib_cur = this->lib->modules->arr[module_lib_index];
    module_lib_cur->andTag(~TAG_OBJ_PROCESSED);
  }
  // add necessary library modules
  for (int module_index = 0; module_index < this->modules->num; module_index++)
  {
    Module* module_cur = this->modules->arr[module_index];
    findFullModules(full_modules, module_cur);
  }
  // add circuit modules
  for (int module_index = 0; module_index < this->modules->num; module_index++)
  {
    Module* module_cur = this->modules->arr[module_index];
    if (!module_cur->testTag(TAG_OBJ_PROCESSED)) {
      full_modules->add(module_cur);
      module_cur->orTag(TAG_OBJ_PROCESSED);
    }
  }
  return full_modules;
}

//---------------------------------------------------------------------------
void Circuit::writeFullModules(char* file_name)
{
  ModuleArray* full_modules = calcFullModules();
  this->lib->writeModules(file_name, full_modules);
  delete full_modules;
}

//---------------------------------------------------------------------------
void Circuit::writeStatistics(char* file_name, char* command_line)
{
  if (this->module_top)
  {
    FILE* file = NULL;
    if (file_name)
    {
      if ((file = fopen(file_name, "a")) == NULL)
        Error("opening statistics output file <%s>", file_name);
    }
    else
      file = stdout;

    this->lib->calcStatistics(this->module_top);

    fprintf(file, "Statistics for module <%s>\n", this->module_top->getName());
    if (command_line)
    fprintf(file, "  command_line: %s\n", command_line);
    if (this->module_top->parameters)
    for (int parameter_index = 0; parameter_index < this->module_top->parameters->num; parameter_index++)
    {
      Parameter* parameter_cur = this->module_top->parameters->arr[parameter_index];
      fprintf(file, "  %s = %g\n", parameter_cur->getName(), parameter_cur->getValue());
    }
    if (file != stdout)
      fclose(file);
  }
}

//---------------------------------------------------------------------------
void Circuit::writeWires(char* file_name, char* pattern)
{
  if (this->module_top)
  {
    FILE* file = NULL;
    if (file_name)
    {
      if ((file = fopen(file_name, "w")) == NULL)
        Error("opening wires output file <%s>", file_name);
    }
    else
      file = stdout;

    this->module_top->writeWires(file, pattern, "", TAG_PORT_, TAG_UNDEFINED);

    if (file != stdout)
      fclose(file);
  }
}

//---------------------------------------------------------------------------
void Circuit::writeCMD(char* cmd_file_name, char* gcf_file_name, char* input_file_names, int path_possibility)
{
  if (cmd_file_name)
  {
    // open CMD file
    FILE* file = NULL;
    if (cmd_file_name)
    {
      if ((file = fopen(cmd_file_name, "w")) == NULL)
        Error("opening Pearl timing analisis command output file <%s>", cmd_file_name);
    }
    else
      file = stdout;
    // tell Pearl to read GCF file
    if (gcf_file_name)
      fprintf(file, "%s %s\n", PEARL_READ_GCF_TIMING_LIBRARIES, gcf_file_name);
    // tell Pearl to read input files
    if (input_file_names)
    {
      char* filename = NULL;
      int name_index = 0;
      while (filename = names2name(input_file_names, name_index++))
      {
        if (strcmp(filename, NAME_STDIO) != 0)
        {
          fprintf(file, "%s %s\n", PEARL_READ_VERILOG, filename);
        }
        delete [] filename;
      }
    }
    fprintf(file, "%s %d\n", PEARL_SET_MAX_POSSIBILITIES, path_possibility);
    // process topmost module
    if (module_top && (this->getMaxDepth() == 0))
      this->module_top->writeCMD(file, path_possibility);
    else
      Warning("cannot generate Pearl timing analisis command file for hierarchical netlist");
    fprintf(file, "%s\n", PEARL_QUIT);
    // close CMD file
    if (file != stdout)
      fclose(file);
  }
}

//---------------------------------------------------------------------------
void Circuit::addModule(Module* module, int position)
{
  if (this->module_hash_table->find(module) == NULL)
  {
    if (!this->modules)
      this->modules = new ModuleArray(1);
    module->lib = this->lib;
    if (position < 0)
      this->modules->add(module);
    else
      this->modules->addAt(position, module);
    this->module_hash_table->add(module);
    this->lib->addModule(module);
  }
  else
  {
    Warning("module <%s> repeats in the circuit", module->getName());
    delete module;
  }
}

//---------------------------------------------------------------------------
void Circuit::addModules(ModuleArray* modules)
{
  if (modules)
  for (int module_index = 0; module_index < modules->num; module_index++)
  {
    Module* module_cur = modules->arr[module_index];
    this->addModule(module_cur);
  }
}

//---------------------------------------------------------------------------
void Circuit::removeModule(Module* module)
{
  this->module_hash_table->remove(module);
  this->modules->remove(module, false);
}

//---------------------------------------------------------------------------
Module* Circuit::getModule(char* module_name)
{
  Module* module_mask = new Module(TAG_UNDEFINED, namecopy(module_name));
  Module* module_cur = module_hash_table->find(module_mask);
  delete module_mask;
  return module_cur;
}

//---------------------------------------------------------------------------
Module* Circuit::setModuleTop(char* module_name)
{
  // try to find topmost module by name
  this->module_top = this->getModule(module_name);
  if (module_top == NULL)
    Error("unable to find the topmost module <%s>", module_name);
  return this->module_top;
}

//---------------------------------------------------------------------------
Module* Circuit::getModuleTop()
{
  return this->module_top;
}

//---------------------------------------------------------------------------
Module* Circuit::calcModuleTop()
{
  module_top = NULL;
  ModuleArray* modules_internal = new ModuleArray(1);
  if (this->modules)
  for (int module_index = 0; module_index < this->modules->num; module_index++)
  {
    Module* module_cur = this->modules->arr[module_index];
    if (module_cur->instances)
    for (int instance_index = 0; instance_index < module_cur->instances->num; instance_index++)
    {
      Instance* instance_cur = module_cur->instances->arr[instance_index];
      Module* module_internal = this->getModule(instance_cur->getModuleName());
      if (module_internal)
        modules_internal->add(module_internal);
    }
  }
  // if there is at least 1 not internal module
  if (this->modules)
  for (int module_index = 0; module_index < this->modules->num; module_index++)
  {
    Module* module_cur = this->modules->arr[module_index];
    if (modules_internal->locate(module_cur) == -1)
      if (module_top)
      {
        module_top = NULL;
        break;
      }
      else
        module_top = module_cur;
  }
  delete modules_internal; modules_internal = NULL;
  if (module_top)
    Message("the topmost module <%s> detected", module_top->getName());
  else
    Error("unable to detect the topmost module");
  return this->module_top;
}

//---------------------------------------------------------------------------
void Circuit::setPortsInfo(char* port_full_names, int tag, int tag_mask)
{
  if (port_full_names)
  {
    int full_name_ind = 0;
    char* port_full_name = NULL;
    while (port_full_name = names2name(port_full_names, full_name_ind++))
    {
      char* module_name = NULL;
      char* port_name = NULL;
      char* sep_pos = strchr(port_full_name, SYMBOL_NAME_SPACE_SEP);
      if (sep_pos)
      {
        // module name
        int module_name_len = sep_pos - port_full_name;
        module_name = new char [module_name_len + 1];
        memcpy(module_name, port_full_name, module_name_len*sizeof(char));
        module_name[module_name_len] = '\0';
        // port name
        int port_name_len = strlen(port_full_name) - module_name_len - 1;
        port_name = new char [port_name_len + 1];
        memcpy(port_name, &port_full_name[module_name_len+1], port_name_len*sizeof(char));
        port_name[port_name_len] = '\0';
      }
      else
        port_name = namecopy(port_full_name);
      // module name is specified
      if (module_name)
      {
        // all modules
        if (strcmp(module_name, "*") == 0)
        {
          if (this->modules)
          for (int module_ind = 0; module_ind < this->modules->num; module_ind++)
          {
            Module* module_cur = this->modules->arr[module_ind];
            module_cur->setPortsInfo(port_name, tag, tag_mask);
          }
        }
        else
        // one module
        {
          Module* module_cur = this->getModule(module_name);
          if (module_cur)
            module_cur->setPortsInfo(port_name, tag, tag_mask);
          else
            Warning ("unable to find module <%s> containing port <%s>", module_name, port_name);
        }
      }
      else
      // module name is NOT specified -> topmost module
      {
        if (module_top)
          module_top->setPortsInfo(port_name, tag, tag_mask);
        else
          Warning ("unable to find the topmost module containing port <%s>", port_name);
      }
      delete [] port_name;
      delete [] module_name;
      delete [] port_full_name;
    }
  }
}

//---------------------------------------------------------------------------
void Circuit::calcPortsSR()
{
  for (int module_index = 0; module_index < modules->num; module_index++)
  {
    Module* module_cur = modules->arr[module_index];
    module_cur->calcPortsSR();
  }
}

//---------------------------------------------------------------------------
void Circuit::calcHierarchy()
{
  this->lib->calcHierarchy(this->modules);
}

//---------------------------------------------------------------------------
int Circuit::getMaxDepth()
{
  return this->lib->getMaxDepth(this->modules);
}

//---------------------------------------------------------------------------
void Circuit::findTags(Module* module)
{
  if (module)
  if (module->testTag(TAG_OBJ_HIDDEN))
  {
    char* module_name_pdr = this->lib->getLogicDR(module->getName(), TAG_MODULE_PDR);
    Module* module_pdr = this->lib->getModule(module_name_pdr);
    delete [] module_name_pdr; 

    char* module_name_ndr = this->lib->getLogicDR(module->getName(), TAG_MODULE_NDR);
    Module* module_ndr = this->lib->getModule(module_name_ndr);
    delete [] module_name_ndr; 

    char* module_name_1dr = this->lib->getLogicDR(module->getName(), TAG_MODULE_1DR);
    Module* module_1dr = this->lib->getModule(module_name_1dr);
    delete [] module_name_1dr; 

    char* module_name_0dr = this->lib->getLogicDR(module->getName(), TAG_MODULE_0DR);
    Module* module_0dr = this->lib->getModule(module_name_0dr);
    delete [] module_name_0dr; 

    if (!module_pdr && !module_ndr && !module_1dr && !module_0dr)
    {
      module->andTag(~TAG_OBJ_HIDDEN);
      if (module->testTag(TAG_MODULE_COMPLEX))
      {
        if (module->instances)
        for (int instance_index = 0; instance_index < module->instances->num; instance_index++)
        {
          Instance* instance_cur = module->instances->arr[instance_index];
          if (!instance_cur->testTag(TAG_ITEM_SR))
          {
            Module* module_prot = this->lib->getModule(instance_cur->getModuleName());
            this->findTags(module_prot);
          }
        }
      }
    }
  }
}
//---------------------------------------------------------------------------
void Circuit::calcTags()
{
  this->lib->calcTags();

  if (this->modules)
  for (int depth_cur = this->getMaxDepth(); depth_cur >= 0; depth_cur--)
    for (int module_index = 0; module_index < this->modules->num; module_index++)
    {
      Module* module_cur = this->modules->arr[module_index];
      if (!module_cur->testTag(TAG_OBJ_HIDDEN))
        if (module_cur->getDepth() == depth_cur)
          module_cur->calcTags();
    }

  for (int module_index = 0; module_index < this->modules->num; module_index++)
  {
    Module* module_cur = this->modules->arr[module_index];
    module_cur->orTag(TAG_OBJ_HIDDEN);
  }
  this->findTags(this->module_top);
}

//---------------------------------------------------------------------------
void Circuit::calcSpacer()
{
  if (this->modules)
  for (int module_index = 0; module_index < this->modules->num; module_index++)
  {
    Module* module_cur = this->modules->arr[module_index];
    if (!module_cur->testTag(TAG_OBJ_HIDDEN))
      module_cur->calcSpacer();
  }
}

//---------------------------------------------------------------------------
bool Circuit::isHierarchical()
{
  return (this->getMaxDepth() > 0);
}

//---------------------------------------------------------------------------
bool Circuit::isBranchingHierarchical()
{
  if (this->modules)
  for (int module_index = 0; module_index < this->modules->num; module_index++)
  {
  	Module* module_cur = this->modules->arr[module_index];
  	if (module_cur->users)
  	  if (module_cur->users->num > 1)
  	    return true;
  }
  return false;
}

//---------------------------------------------------------------------------
void Circuit::setAllCD()
{
  if (this->modules)
  for (int depth_cur = this->getMaxDepth(); depth_cur >= 0; depth_cur--)
  {
    for (int module_index = 0; module_index < this->modules->num; module_index++)
    {
      Module* module_cur = this->modules->arr[module_index];
      if (!module_cur->testTag(TAG_OBJ_HIDDEN))
        if (module_cur->getDepth() == depth_cur)
          module_cur->setAllCD();
    }
  }
}

//---------------------------------------------------------------------------
void Circuit::convertToConstants()
{
  if (this->modules)
  for (int module_index = 0; module_index < this->modules->num; module_index++)
  {
    Module* module_cur = this->modules->arr[module_index];
    if (!module_cur->testTag(TAG_OBJ_HIDDEN))
      module_cur->convertToConstants();
  }
}

//---------------------------------------------------------------------------
void Circuit::convertToNL()
{
  if (this->modules)
  for (int module_index = 0; module_index < this->modules->num; module_index++)
  {
    Module* module_cur = this->modules->arr[module_index];
    if (!module_cur->testTag(TAG_OBJ_HIDDEN))
      module_cur->convertToNL();
  }
}

//---------------------------------------------------------------------------
void Circuit::convertToOP(char* parameter_names)
{
  if (this->modules)
  for (int module_index = 0; module_index < this->modules->num; module_index++)
  {
    Module* module_cur = this->modules->arr[module_index];
    if (!module_cur->testTag(TAG_OBJ_HIDDEN))
      module_cur->convertToOP(parameter_names);
  }
}

//---------------------------------------------------------------------------
void Circuit::convertToOS()
{
  if (this->modules)
  for (int module_index = 0; module_index < this->modules->num; module_index++)
  {
    Module* module_cur = this->modules->arr[module_index];
    if (!module_cur->testTag(TAG_OBJ_HIDDEN))
      module_cur->convertToOS();
  }
}

//---------------------------------------------------------------------------
void Circuit::convertToBalanced()
{
  if (this->modules)
  for (int module_index = 0; module_index < this->modules->num; module_index++)
  {
    Module* module_cur = this->modules->arr[module_index];
    if (!module_cur->testTag(TAG_OBJ_HIDDEN))
      module_cur->convertToBalanced();
  }
}

//---------------------------------------------------------------------------
void Circuit::convertToDR()
{
  if (this->modules)
  for (int depth_cur = this->getMaxDepth(); depth_cur >= 0; depth_cur--)
  {
    for (int module_index = 0; module_index < this->modules->num; module_index++)
    {
      Module* module_cur = this->modules->arr[module_index];
      if ( !module_cur->testTag(TAG_OBJ_HIDDEN) )
      {
        if ( module_cur->getDepth() == depth_cur )
        {
          if (module_cur->instances)
          for (int instance_ind = 0; instance_ind < module_cur->instances->num; instance_ind++)
          {
            Instance* instance_cur = module_cur->instances->arr[instance_ind];
            if ( !instance_cur->testTag(TAG_ITEM_SR)
              && !instance_cur->testTag(TAG_MODULE_COMPLEX) )
            {
              Module* module_new = this->lib->genModuleDR(instance_cur->getModuleName(), instance_cur->getTag());
              // add the DR module to the array of generated modules and to the library
              module_new->andTag(~TAG_OBJ_HIDDEN);
              if (!this->lib->getModule(module_new->getName()))
              {
                this->lib->addModule(module_new);
                this->lib->addGen(module_new);
              }
            }
          }
          module_cur->orTag(this->getTag() & TAG_MODE_);
          this->module_hash_table->remove(module_cur);
          this->lib->module_hash_table->remove(module_cur);
          module_cur->convertToDR();
          this->module_hash_table->add(module_cur);
          this->lib->module_hash_table->add(module_cur);
        }
      }
    }
  }
}

//---------------------------------------------------------------------------
void Circuit::convertToCD()
{
  if (this->modules)
  for (int depth_cur = this->getMaxDepth(); depth_cur >= 0; depth_cur--)
    for (int module_index = 0; module_index < this->modules->num; module_index++)
      {
        Module* module_cur = this->modules->arr[module_index];
        if (!module_cur->testTag(TAG_OBJ_HIDDEN))
          if (module_cur->getDepth() == depth_cur)
          {
            module_cur->orTag(TAG_MODE_ASYNC);
            module_cur->orTag(tag & TAG_MODE_ALTERNATING_SPACER);
            module_cur->convertToCD();
          }
      }
}

//---------------------------------------------------------------------------
void Circuit::simplify()
{
  if (this->modules)
  for (int depth_cur = this->getMaxDepth(); depth_cur >= 0; depth_cur--)
    for (int module_index = 0; module_index < this->modules->num; module_index++)
    {
      Module* module_cur = this->modules->arr[module_index];
      if (!module_cur->testTag(TAG_OBJ_HIDDEN))
        if (module_cur->getDepth() == depth_cur)
          module_cur->simplify();
    }
}
