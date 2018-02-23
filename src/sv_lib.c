#include <stdio.h>
#include "sv_lib.h"
#include "sverilog.h"
#include "rules.h"
#include "parameters.h"
#include "assignments.h"
#include "messages.h"

//---------------------------------------------------------------------------
Lib::Lib(ModuleArray* modules, ModuleArray* gens, RuleArray* rules, AssignmentArray* assignments)
{
  // modules
  this->module_hash_table = new ModuleHashTable();
  this->modules = modules;
  if (this->modules)
  for (int module_index = 0; module_index < this->modules->num; module_index++)
    module_hash_table->add(this->modules->arr[module_index]);
  // gens
  this->gen_hash_table = new GenHashTable();
  this->gens = gens;
  if (this->gens)
  for (int gen_index = 0; gen_index < this->gens->num; gen_index++)
    gen_hash_table->add(this->gens->arr[gen_index]);
  // rules
  this->rule_hash_table = new RuleHashTable();
  this->rules = rules;
  this->trans_hash_table = new TransHashTable();
  this->transs = new TransArray(1);
  if (this->rules)
  for (int rule_index = 0; rule_index < this->rules->num; rule_index++)
  {
  	Rule* rule_cur = this->rules->arr[rule_index];
    rule_hash_table->add(rule_cur);
    Trans* trans_cur = new Trans(rule_cur->getTag(), namecopy(rule_cur->prefix_dr), namecopy(rule_cur->getName()) );
    transs->add(trans_cur);
    trans_hash_table->add(trans_cur);
  }
  // assignments
  this->assignment_hash_table = new AssignmentHashTable();
  this->assignments = assignments;
  if (this->assignments)
  for (int assignment_index = 0; assignment_index < this->assignments->num; assignment_index++)
    assignment_hash_table->add(this->assignments->arr[assignment_index]);
  // parameters
  delay_min_parameters = NULL;
  delay_max_parameters = NULL;  
  
}

//---------------------------------------------------------------------------
Lib::~Lib()
{
  clean();
  delete module_hash_table;
  delete gen_hash_table;
  delete rule_hash_table;
  delete trans_hash_table;
  delete assignment_hash_table;
  delete modules;
  delete gens;
  delete rules;
  delete transs;
  delete assignments;
  delete [] delay_min_parameters;
  delete [] delay_max_parameters;
}

//---------------------------------------------------------------------------
void Lib::clean()
{
  if (this->modules) this->modules->removeAll(true);
  if (this->rules) this->rules->removeAll(true);
  if (this->transs) this->transs->removeAll(true);
  if (this->assignments) this->assignments->removeAll(true);
}

//---------------------------------------------------------------------------
void Lib::readRules(char* file_names)
{
  if (file_names)
  {
    int name_index = 0;
    while (rules_filename = names2name(file_names, name_index++))
    {
      if (strcmp(rules_filename, NAME_STDIO) == 0)
      {
        delete [] rules_filename;
        rules_filename = namecopy("stdin");
        rules_in = stdin;
      }
      else
      if ((rules_in = fopen(rules_filename, "r")) == NULL)
        Error("opening rules for logic transformation file <%s>", rules_filename);

      if (rules_in)
      {
        Message("reading file <%s>", rules_filename);
        rules_rules = new RuleArray(1);
        rules_parse();
        if (rules_in != stdin)
          fclose(rules_in);
        this->addRules(rules_rules);
        delete rules_rules;
      }
      delete [] rules_filename;
    }
    rules_lex_destroy();
  }
  if (this->rules)
    if (this->rules->num <= 0)
      Warning("no rule for logic transformation is loaded");
}

//---------------------------------------------------------------------------
bool Lib::addRule(Rule* rule)
{
  bool result = false;
  if (rule_hash_table->find(rule) == NULL)
  {
    if (!this->rules)
      this->rules = new RuleArray(1);
    rules->add(rule);
    rule_hash_table->add(rule);
    Trans* trans_cur = new Trans(rule->getTag(), namecopy(rule->prefix_dr), namecopy(rule->getName()) );
    transs->add(trans_cur);
    trans_hash_table->add(trans_cur);
    result = true;
  }
  return result;
}

//---------------------------------------------------------------------------
void Lib::addRules(RuleArray* rules)
{
  if (rules)
  for (int rule_index = 0; rule_index < rules->num; rule_index++)
  {
    Rule* rule_cur = rules->arr[rule_index];
    if (!addRule(rule_cur))
    {
      Warning("logic transformation rule for gate <%s> already exists", rule_cur->getName());
      delete rule_cur;
    }
  }
}

//---------------------------------------------------------------------------
Rule* Lib::getRule(char* module_name, int prefix_len_min, int suffix_len_max)
{
  Rule* rule_cur = NULL;
  if (module_name)
  {
    if (this->getLogicTag(module_name) == TAG_UNDEFINED)
    {
      if (prefix_len_min < 1) prefix_len_min = 1;
      if (suffix_len_max < 0) suffix_len_max = 0;
      int prefix_len = strlen(module_name);
      int suffix_len = 0;
      while ((rule_cur == NULL) && (prefix_len >= prefix_len_min) && (suffix_len <= suffix_len_max))
      {
        char* rule_name = namecopy(module_name);
        rule_name[prefix_len] = '\0';
        Rule* rule_mask = new Rule(TAG_UNDEFINED, rule_name);
        rule_cur = rule_hash_table->find(rule_mask);
        delete rule_mask;
        prefix_len--;
        suffix_len++;
      }
    }
  }
  return rule_cur;
}

//---------------------------------------------------------------------------
Rule* Lib::getRuleTrans(char* module_name, int prefix_len_min, int suffix_len_max)
{
  Rule* rule_cur = NULL;
  if (module_name)
  {
    int suffix_len = -1;
    // type of DR suffix
    switch (this->getLogicTag(module_name))
    {
      case TAG_MODULE_PDR:
        suffix_len = strlen(SUFFIX_PDR);
        break;
      case TAG_MODULE_NDR:
        suffix_len = strlen(SUFFIX_PDR);
        break;
      case TAG_MODULE_0DR:
        suffix_len = strlen(SUFFIX_0DR);
        break;
      case TAG_MODULE_1DR:
        suffix_len = strlen(SUFFIX_1DR);
        break;
    }
    // if suffix found then generate SR module name
    if (suffix_len >= 0)
    {
      if (prefix_len_min < 1) prefix_len_min = 1;
      if (suffix_len_max < 0) suffix_len_max = 0;
      int prefix_len = strlen(module_name) - suffix_len;
      Trans* trans_cur = NULL;
      while ((trans_cur == NULL) && (prefix_len >= prefix_len_min) && (suffix_len <= suffix_len_max))
      {
        char* trans_name = namecopy(module_name);
        trans_name[prefix_len] = '\0';
        Trans* trans_mask = new Trans(TAG_UNDEFINED, trans_name);
        trans_cur = trans_hash_table->find(trans_mask);
        delete trans_mask;
        prefix_len--;
        suffix_len++;
      }
      
      if (trans_cur)
      {
        Rule* rule_mask = new Rule(TAG_UNDEFINED, namecopy(trans_cur->getTrans()));
        rule_cur = rule_hash_table->find(rule_mask);
        delete rule_mask;
      }
    }
  }
  return rule_cur;
}

//---------------------------------------------------------------------------
void Lib::modifyRules(int tag_mask, int tag_exclude)
{
  if (this->rules)
  for (int rule_index = 0; rule_index < this->rules->num; rule_index++)
  {
    Rule* rule_cur = this->rules->arr[rule_index];
    if (rule_cur->testTag(tag_mask))
      rule_cur->andTag(~tag_exclude);
  }
}

//---------------------------------------------------------------------------
void Lib::setParameters(char* delay_min_parameters, char* delay_max_parameters)
{
  this->delay_min_parameters = namecopy(delay_min_parameters);
  this->delay_max_parameters = namecopy(delay_max_parameters);
}

//---------------------------------------------------------------------------
float Lib::getMinDelay(const char* assignment_names)
{
  float result = -1.0;
  if (assignment_names)
  {
    int name_index = 0;
    char* assignment_name = NULL;
    while (assignment_name = names2name(assignment_names, name_index++))
    {
      char* module_name = namecopy(getAssignmentVal(assignment_name));
      if (module_name)
      {
        Module* module_cur = getModule(module_name);
        if (module_cur)
        {
          float delay = module_cur->getMinDelay();
          if ( (result < 0) || (delay < result) )
            result = delay;
        }
      }
      delete [] assignment_name;
    }
  }
  return result;
}  

//---------------------------------------------------------------------------
float Lib::getMaxDelay(const char* assignment_names)
{
  float result = -1.0;
  if (assignment_names)
  {
    int name_index = 0;
    char* assignment_name = NULL;
    while (assignment_name = names2name(assignment_names, name_index++))
    {
      char* module_name = namecopy(getAssignmentVal(assignment_name));
      if (module_name)
      {
        Module* module_cur = getModule(module_name);
        if (module_cur)
        {
          float delay = module_cur->getMaxDelay();
          if ( (result < 0) || (delay > result) )
            result = delay;
        }
      }
      delete [] assignment_name;
    }
  }
  return result;
}  

//---------------------------------------------------------------------------
void Lib::readParameters(char* file_names)
{
  if (file_names)
  {
    int name_index = 0;
    while (parameters_filename = names2name(file_names, name_index++))
    {
      if (strcmp(parameters_filename, NAME_STDIO) == 0)
      {
        delete [] parameters_filename;
        parameters_filename = namecopy("stdin");
        parameters_in = stdin;
      }
      else
      if ((parameters_in = fopen(parameters_filename, "r")) == NULL)
        Error("opening modules parameters file <%s>", parameters_filename);

      if (parameters_in)
      {
        parameters_module_hash_table = this->module_hash_table;
        parameters_parse();
        if (parameters_in != stdin)
          fclose(parameters_in);
      }
      delete [] parameters_filename;
    }
    parameters_lex_destroy();
  }
}


//---------------------------------------------------------------------------
void Lib::setModulesWidth(char* width_param)
{
  if (width_param)
  if (this->modules)
  for (int module_index = 0; module_index < this->modules->num; module_index++)
  {
    Module* module_cur = this->modules->arr[module_index];
    Parameter* parameter_cur = module_cur->getParameter(width_param);
    if (parameter_cur)
    {
      int width_cur = (int) parameter_cur->getValue();
      module_cur->setWidth(width_cur);
      module_cur->removeParameter(parameter_cur);
    }
  }
}

//---------------------------------------------------------------------------
char* Lib::getLogicPrefix(char* module_name, int prefix_type)
{
  char* prefix_name = NULL;
  Rule* rule_cur = getRule(module_name);
  if (rule_cur)
  {
    switch (prefix_type)
    {
      case PREFIX_SR:
        prefix_name = rule_cur->getName();
        break;
      case PREFIX_DR:
        prefix_name = rule_cur->prefix_dr;
        break;
      case PREFIX_PD:
        prefix_name = rule_cur->prefix_pd;
        break;
      case PREFIX_PC:
        prefix_name = rule_cur->prefix_pc;
        break;
      case PREFIX_ND:
        prefix_name = rule_cur->prefix_nd;
        break;
      case PREFIX_NC:
        prefix_name = rule_cur->prefix_nc;
        break;
    }
  }
  return prefix_name;
}


//---------------------------------------------------------------------------
int Lib::getLogicTag(char* module_name)
{
  if (module_name)
  {
    int name_len = strlen(module_name);
    int suffix_dr_len = 0;
    // check for PDR suffix
    suffix_dr_len = strlen(SUFFIX_PDR);
    if (suffix_dr_len < name_len)
      if (strcmp(&module_name[name_len - suffix_dr_len], SUFFIX_PDR) == 0)
        return TAG_MODULE_PDR;
    // check for NDR suffix
    suffix_dr_len = strlen(SUFFIX_NDR);
    if (suffix_dr_len < name_len)
      if (strcmp(&module_name[name_len - suffix_dr_len], SUFFIX_NDR) == 0)
        return TAG_MODULE_NDR;
    // check for 0DR suffix
    suffix_dr_len = strlen(SUFFIX_0DR);
    if (suffix_dr_len < name_len)
      if (strcmp(&module_name[name_len - suffix_dr_len], SUFFIX_0DR) == 0)
        return TAG_MODULE_0DR;
    // check for 1DR suffix
    suffix_dr_len = strlen(SUFFIX_1DR);
    if (suffix_dr_len < name_len)
      if (strcmp(&module_name[name_len - suffix_dr_len], SUFFIX_1DR) == 0)
        return TAG_MODULE_1DR;
  }
  return TAG_UNDEFINED;
}

//---------------------------------------------------------------------------
char* Lib::getLogicDrive(char* module_name)
{
  char* drive = NULL;
  Rule* rule_cur = getRule(module_name);
  if (rule_cur)
  {
    int prefix_len = strlen(rule_cur->getName());
    if (prefix_len < strlen(module_name))
      drive = namecopy(&module_name[prefix_len]);
  }
  return drive;
}

//---------------------------------------------------------------------------
char* Lib::getLogic(char* module_name, int prefix_type)
{
  char* logic_name = NULL;
  char* prefix_name = this->getLogicPrefix(module_name, prefix_type);
  if (prefix_name)
  {
    if (strcmp(prefix_name, this->getAssignmentVal(VAR_EMPTY)) == 0)
      logic_name = namecopy(prefix_name);
    else
    if (strcmp(prefix_name, NAME_LOGIC_UNDEFINED) != 0)
    {
      char* drive = getLogicDrive(module_name);
      if (drive == NULL)
        logic_name = namecopy(prefix_name);
      else
        logic_name = name2pattern("%s%s", prefix_name, drive);
      delete [] drive;
    }
  }
  if (logic_name == NULL)
    Error("positive(negative) direct(complementary) logic for module <%s> is undefined", module_name);
  return logic_name;
}

//---------------------------------------------------------------------------
char* Lib::getLogicDR(char* module_name, int tag_mask)
{
  char* prefix_drive_dr = NULL;
  Rule* rule_cur = getRule(module_name);
  if (rule_cur)
  {
    char* drive = this->getLogicDrive(module_name);
    if (drive == NULL)
      prefix_drive_dr = namecopy(rule_cur->prefix_dr);
    else
      prefix_drive_dr = name2pattern("%s%s", rule_cur->prefix_dr, drive);
    delete [] drive;
  }
  else
    prefix_drive_dr = namecopy(module_name);
  char* name_dr = NULL;
  if ((tag_mask & TAG_MODULE_0DR) == TAG_MODULE_0DR)
    name_dr = name2pattern(PATTERN_MODULE_0DR, prefix_drive_dr);
  else
  if ((tag_mask & TAG_MODULE_1DR) == TAG_MODULE_1DR)
    name_dr = name2pattern(PATTERN_MODULE_1DR, prefix_drive_dr);
  else
  if ((tag_mask & TAG_MODULE_PDR) == TAG_MODULE_PDR)
    name_dr = name2pattern(PATTERN_MODULE_PDR, prefix_drive_dr);
  else
  if ((tag_mask & TAG_MODULE_NDR) == TAG_MODULE_NDR)
    name_dr = name2pattern(PATTERN_MODULE_NDR, prefix_drive_dr);
  delete [] prefix_drive_dr;
  return name_dr;
}

//---------------------------------------------------------------------------
bool Lib::getLogicInfo(char* module_name, int tag_mask)
{
  Module* module_cur = this->getModule(module_name);
  if (module_cur)
    return module_cur->testTag(tag_mask);
  else
    return false;
}

//---------------------------------------------------------------------------
int Lib::getPortNum(char* module_name, int port_orig_num, char* flags)
{
  int port_num = port_orig_num;
  Rule* rule_cur = getRule(module_name);
  if (rule_cur)
  {
    char* str_start = rule_cur->polarity;
    int port_cur_num = 0;
    while (str_start[0] != '\0')
    {
      if (strchr(flags, str_start[0]))
        port_cur_num++;
      str_start++;
    }
    if (port_cur_num > port_orig_num)
      port_num = port_cur_num;
  }
  return port_num;
}

//---------------------------------------------------------------------------
int Lib::getPortInd(char* module_name, int port_io_ind, char* flags1, char* flags2)
{
  int port_ind = -1;
  Rule* rule_cur = getRule(module_name);
  if (rule_cur)
  {
    char* str_start = rule_cur->polarity;
    int port_cur_num = 0;
    while ((str_start[0] != '\0') && (port_io_ind >= 0))
    {
      if (strchr(flags1, str_start[0]))
      {
        port_ind++;
        port_io_ind--;
      }
      else
      if (strchr(flags2, str_start[0]))
      {
        port_ind++;
      }
      str_start++;
    }
  }
  return port_ind;
}

//---------------------------------------------------------------------------
int Lib::getPortInfo(char* module_name, int port_index, char* flags)
{
  int result = -1;
  Rule* rule_cur = getRule(module_name);
  if (rule_cur)
  {
    char* str_start = strpbrk(rule_cur->polarity, flags);
    if (str_start)
    {
      char* str_cur = str_start;
      int port_index_cur = 0;
      while (port_index_cur < port_index)
      {
        str_cur++;
        if (str_cur[0] == '\0')
          str_cur = str_start;
        if (strchr(flags, str_cur[0]))
          port_index_cur++;
      }
      result = strchr(flags, str_cur[0]) - flags;
    }
  }
  return result;
}


//===========================================================================

//---------------------------------------------------------------------------
void Lib::readModules(char* file_names)
{
  if (file_names)
  {
    int name_index = 0;
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
        Error("opening library file <%s>", sverilog_filename);

      if (sverilog_in)
      {
        Message("reading file <%s>", sverilog_filename);
        sverilog_modules = new ModuleArray(1);
        sverilog_parse();
        if (sverilog_in != stdin)
          fclose(sverilog_in);
        this->addModules(sverilog_modules);
        delete sverilog_modules;
      }
      delete [] sverilog_filename;
    }
    sverilog_lex_destroy();
    this->calcConnections(this->modules);
    this->sortConnections(this->modules);
  }
}

//---------------------------------------------------------------------------
void Lib::writeModule(FILE* file, Module* module_cur, int tag_ignore)
{
  if (!module_cur->testTag(tag_ignore))
  if (module_cur->instances)
  {
        // module
        fprintf(file, "%s %s", KEY_MODULE, module_cur->getName());
        int line_len = 6 + 2 + 2;
        if (module_cur->getName())
          line_len += strlen(module_cur->getName());

        // port list
        bool port_first = true;
        if (module_cur->ports)
        for (int j=0; j < module_cur->ports->num; j++)
        {
          Port* port_cur = module_cur->ports->arr[j];
          if (!port_cur->testTag(TAG_OBJ_HIDDEN))
          {
            if (port_cur->testTag(TAG_PORT_INPUT) ||
              port_cur->testTag(TAG_PORT_OUTPUT))
            {
              if (port_first)
                fprintf(file, " (");
              else
                fprintf(file, ", ");

              char* port_name = NULL;
              if (port_cur->isEscape())
                port_name = name2pattern("%s ", port_cur->getName());
              else
                port_name = namecopy(port_cur->getName());

              if (line_len + strlen(port_name) > LINE_LEN_MAX)
              {
                line_len = 2;
                fprintf(file, "\n  %s", port_name);
              }
              else
                fprintf(file, "%s", port_name);
              line_len += 2 + strlen(port_name);
              delete [] port_name;
              port_first = false;
            }
          }
        }
        fprintf(file, "); // d=%d w=%d", module_cur->getDepth(), module_cur->getWidth());
        if (module_cur->testTag(TAG_MODULE_COMPLEX))
          fprintf(file, " complex");
        if (module_cur->testTag(TAG_MODULE_INITIATOR))
          fprintf(file, " init");
        if (module_cur->testTag(TAG_MODULE_FF))
          fprintf(file, " ff");

        if (module_cur->testTag(TAG_MODULE_0DR))
          fprintf(file, " 0dr");
        else
        if (module_cur->testTag(TAG_MODULE_1DR))
          fprintf(file, " 1dr");
        else
        if (module_cur->testTag(TAG_MODULE_PDR))
          fprintf(file, " pdr");
        else
        if (module_cur->testTag(TAG_MODULE_NDR))
          fprintf(file, " ndr");

        if (module_cur->testTag(TAG_ITEM_SR))
          fprintf(file, " sr");
        else
        if (module_cur->testTag(TAG_ITEM_1DR))
          fprintf(file, " sp1");
        else
        if (module_cur->testTag(TAG_ITEM_0DR))
          fprintf(file, " sp0");

        if (module_cur->testTag(TAG_MODULE_CD))
          fprintf(file, " cd");
        fprintf(file, "\n");

        // port declaration
        bool port_bl = false;
        if (module_cur->ports)
        for (int j=0; j < module_cur->ports->num; j++)
        {
          Port* port_cur = module_cur->ports->arr[j];
          if (!port_cur->testTag(TAG_OBJ_HIDDEN))
          {
            port_bl = true;
            switch (port_cur->getTag() & TAG_PORT_)
            {
              case TAG_PORT_INPUT:
                fprintf(file, "  %s", KEY_INPUT);
                break;
              case TAG_PORT_OUTPUT:
                fprintf(file, "  %s", KEY_OUTPUT);
                break;
              case TAG_PORT_WIRE:
                fprintf(file, "  %s", KEY_WIRE);
                break;
              default:
                fprintf(file, "  TAG_%X", port_cur->getTag());
            }
            char* port_full_name = port_cur->genFullName();
            fprintf(file, " %s", port_full_name);
            delete [] port_full_name;
            if (port_cur->nets)
            {
              Net* net_cur = port_cur->nets->arr[0];
              fprintf(file, "; // d=%d l=%d", net_cur->getDepth(), net_cur->getLayer());
            }
            if (port_cur->nets->arr[0]->testTag(TAG_ITEM_SR))
              fprintf(file, " sr");
            else
            if (port_cur->nets->arr[0]->testTag(TAG_ITEM_1DR))
              fprintf(file, " dr sp1");
            else
            if (port_cur->nets->arr[0]->testTag(TAG_ITEM_0DR))
              fprintf(file, " dr sp0");
            if (port_cur->nets->arr[0]->testTag(TAG_OBJ_CD))
              fprintf(file, " cd");
            fprintf(file, "\n");
          }
        }
        if (port_bl)
          fprintf(file, "\n");

        // parameters
        bool parameter_bl = false;
        if (module_cur->parameters)
        for (int j=0; j < module_cur->parameters->num; j++)
        {
          Parameter* parameter_cur = module_cur->parameters->arr[j];
          parameter_bl = true;
          if (parameter_cur->testTag(TAG_OBJ_HIDDEN))
            fprintf(file, "//");
          fprintf(file, "  %s %s = %g;\n", KEY_PARAMETER, parameter_cur->getName(), parameter_cur->getValue());
        }
        if (parameter_bl)
          fprintf(file, "\n");

        // instances
        if (module_cur->instances)
        for (int j=0; j < module_cur->instances->num; j++)
        {
          Instance* instance_cur = module_cur->instances->arr[j];
          char* instance_name = instance_cur->genFullName();
          fprintf(file, "  %s", instance_cur->getModuleName());
          if (instance_name)
            fprintf(file, " %s", instance_name);
          int line_len = 2 + 1 + 2;
          if (instance_cur->getModuleName())
            line_len += strlen(instance_cur->getModuleName());
          if (instance_name)
            line_len += strlen(instance_name);
          delete [] instance_name;

          // connection list
          bool connection_first = true;
          if (instance_cur->connections)
          for (int k=0; k < instance_cur->connections->num; k++)
          {
            Connection* connection_cur = instance_cur->connections->arr[k];
            if (connection_first)
              fprintf(file, " (");
            else
              fprintf(file, ", ");
            char* connection_full_name = connection_cur->genFullName();
            if (line_len + strlen(connection_full_name) > LINE_LEN_MAX)
            {
              line_len = 4;
              fprintf(file, "\n    %s", connection_full_name);
            }
            else
              fprintf(file, "%s", connection_full_name);
            line_len += 2 + strlen(connection_full_name);
            delete [] connection_full_name;
            connection_first = false;
          }
          fprintf(file, "); // d=%d w=%d l=%d", instance_cur->getDepth(), instance_cur->getWidth(), instance_cur->getLayer());
          if (instance_cur->testTag(TAG_MODULE_COMPLEX))
            fprintf(file, " complex");
          if (instance_cur->testTag(TAG_MODULE_INITIATOR))
            fprintf(file, " init");
          if (instance_cur->testTag(TAG_MODULE_FF))
            fprintf(file, " ff");

          if (instance_cur->testTag(TAG_MODULE_0DR))
            fprintf(file, " 0dr");
          else
          if (instance_cur->testTag(TAG_MODULE_1DR))
            fprintf(file, " 1dr");
          else
          if (instance_cur->testTag(TAG_MODULE_PDR))
            fprintf(file, " pdr");
          else
          if (instance_cur->testTag(TAG_MODULE_NDR))
            fprintf(file, " ndr");

          if (instance_cur->testTag(TAG_ITEM_SR))
            fprintf(file, " sr");
          else
          if (instance_cur->testTag(TAG_ITEM_1DR))
            fprintf(file, " sp1");
          else
          if (instance_cur->testTag(TAG_ITEM_0DR))
            fprintf(file, " sp0");

          if (instance_cur->testTag(TAG_MODULE_CD))
            fprintf(file, " cd");
          fprintf(file, "\n");
        }
        // endmodule
        fprintf(file, "%s\n\n", KEY_ENDMODULE);
  }
}

//---------------------------------------------------------------------------
void Lib::writeModules(char* file_name, ModuleArray* modules)
{
  if (file_name)
  {
    FILE* file = NULL;
    if (strcmp(file_name, NAME_STDIO) == 0)
      file = stdout;
    else
    {
      if ((file = fopen(file_name, "w")) == NULL)
        Error("opening output file <%s>", file_name);
    }
    if (modules)
    for (int module_index = 0; module_index < modules->num; module_index++)
    {
      Module* module_cur = modules->arr[module_index];
      writeModule(file, module_cur);
    }
    if (file != stdout)
      fclose(file);
  }
}

//---------------------------------------------------------------------------
bool Lib::addModule(Module* module, int position)
{
  bool result = false;
  if (this->module_hash_table->find(module) == NULL)
  {
    if (!this->modules)
      this->modules = new ModuleArray(1);
    module->lib = this;

    // fill module attributes using rules for logic transformation data
    Rule* rule_cur = this->getRule(module->getName());
    module->andTag(~TAG_MODULE_);
    if (rule_cur)
    {
      module->orTag(rule_cur->getTag() & TAG_MODULE_);
      module->setWidth(1);
    }
    else
    {
      char* module_name = module->getName();
      module->orTag(TAG_MODULE_COMPLEX | this->getLogicTag(module_name));
      Rule* rule_trans_cur = this->getRuleTrans(module_name);
      if (rule_trans_cur)
        module->orTag(rule_trans_cur->getTag() & (TAG_MODULE_CD | TAG_MODULE_FF));
    }
    //
    if (module->testTag(TAG_MODULE_FF))
      module->orTag(TAG_MODULE_INITIATOR);
    // add module to the library
    this->modules->add(module);
    this->module_hash_table->add(module);
    result = true;
  }
  return result;
}

//---------------------------------------------------------------------------
void Lib::addModules(ModuleArray* modules)
{
  if (modules)
  for (int module_index = 0; module_index < modules->num; module_index++)
  {
    Module* module_cur = modules->arr[module_index];
    if (!this->addModule(module_cur))
      delete module_cur;
  }
}

//---------------------------------------------------------------------------
Module* Lib::getModule(char* module_name)
{
  Module* module_mask = new Module(TAG_UNDEFINED, namecopy(module_name));
  Module* module_cur = module_hash_table->find(module_mask);
  delete module_mask;
  return module_cur;
}

//---------------------------------------------------------------------------
void Lib::calcConnections(ModuleArray* modules)
{
  if (modules)
  for (int module_index = 0; module_index < modules->num; module_index++)
  {
    Module* module_cur = modules->arr[module_index];
    if (module_cur->testTag(TAG_MODULE_COMPLEX))
      module_cur->calcConnections();
  }
}

//---------------------------------------------------------------------------
void Lib::sortConnections(ModuleArray* modules)
{
  if (modules)
  for (int module_index = 0; module_index < modules->num; module_index++)
  {
    Module* module_cur = modules->arr[module_index];
    if (module_cur->testTag(TAG_MODULE_COMPLEX))
      module_cur->sortConnections();
  }
}


//---------------------------------------------------------------------------
void Lib::findHierarchy(ModuleArray* modules, Module* module, int depth)
{
  if (!module->testTag(TAG_OBJ_PROCESSED))
  if (depth > module->getDepth())
  {
    module->setDepth(depth);
    module->orTag(TAG_OBJ_PROCESSED);
    if (modules)
    for (int module_index = 0; module_index < modules->num; module_index++)
    {
      Module* module_cur = modules->arr[module_index];
      if (module_cur->users)
      for (int user_index = 0; user_index < module_cur->users->num; user_index++)
      {
      	Instance* user_cur = module_cur->users->arr[user_index];
      	if (user_cur->getContainer() == module)
          this->findHierarchy(modules, module_cur, depth+1);
      }
    }
    module->andTag(~TAG_OBJ_PROCESSED);
  }
}


//---------------------------------------------------------------------------
void Lib::calcHierarchy(ModuleArray* modules)
{
  if (modules)
  {
    // clear depth and processed flag
    for (int module_index = 0; module_index < modules->num; module_index++)
    {
      Module* module_cur = modules->arr[module_index];
      module_cur->setDepth(-1);
      module_cur->andTag(~TAG_OBJ_PROCESSED);
    }
    // calc the modules users
    for (int module_index = 0; module_index < modules->num; module_index++)
    {
      Module* module_cur = modules->arr[module_index];
      if (module_cur->instances)
      for (int instance_index = 0; instance_index < module_cur->instances->num; instance_index++)
      {
        Instance* instance_cur = module_cur->instances->arr[instance_index];
        Module* module_prototype = this->getModule(instance_cur->getModuleName());
        if (module_prototype)
          module_prototype->addUser(instance_cur);
      }
    }
    // calc the depth of the modules starting from the top level modules (which are not instantiated)
    for (int module_index = 0; module_index < modules->num; module_index++)
    {
      Module* module_cur = modules->arr[module_index];
      if (module_cur->users == NULL)
        this->findHierarchy(modules, module_cur, 0);
    }
    // calc the depth of instances each module is built of
    for (int depth_cur = this->getMaxDepth(modules); depth_cur >= 0; depth_cur--)
    {
      for (int module_index = 0; module_index < modules->num; module_index++)
      {
        Module* module_cur = modules->arr[module_index];
        if (module_cur->testTag(TAG_MODULE_COMPLEX))
          if (module_cur->getDepth() == depth_cur)
            module_cur->calcHierarchy();
      }
    }
  }
}


//---------------------------------------------------------------------------
int Lib::getMaxDepth(ModuleArray* modules)
{
  int depth_max = -1;
  if (modules)
  for (int module_index = 0; module_index < modules->num; module_index++)
  {
    Module* module_cur = modules->arr[module_index];
    int depth_cur = module_cur->getDepth();
    if (depth_cur > depth_max)
      depth_max = depth_cur;
  }
  return depth_max;
}


//---------------------------------------------------------------------------
void Lib::calcTags()
{
  if (this->modules)
  for (int module_index = 0; module_index < this->modules->num; module_index++)
  {
    Module* module_cur = this->modules->arr[module_index];
    if (module_cur->testTag(TAG_MODULE_COMPLEX))
    if (!module_cur->testTag(TAG_MODULE_PDR) && !module_cur->testTag(TAG_MODULE_NDR))
    {
       char* module_name_sr = module_cur->getName();
       char* module_name_dr = NULL;
       // PDR
       module_name_dr = this->getLogicDR(module_name_sr, TAG_MODULE_PDR);
       if (this->getModule(module_name_dr))
         module_cur->orTag(TAG_MODULE_PDR);
       delete [] module_name_dr;
       // NDR
       module_name_dr = this->getLogicDR(module_name_sr, TAG_MODULE_NDR);
       if (this->getModule(module_name_dr))
         module_cur->orTag(TAG_MODULE_NDR);
       delete [] module_name_dr;
       // 0DR
       module_name_dr = this->getLogicDR(module_name_sr, TAG_MODULE_0DR);
       if (this->getModule(module_name_dr))
         module_cur->orTag(TAG_MODULE_0DR);
       delete [] module_name_dr;
       // 1DR
       module_name_dr = this->getLogicDR(module_name_sr, TAG_MODULE_1DR);
       if (this->getModule(module_name_dr))
         module_cur->orTag(TAG_MODULE_1DR);
       delete [] module_name_dr;
    }
  }
}


//===========================================================================
//---------------------------------------------------------------------------
void Lib::readGens(char* file_name)
{
  if (file_name)
  {
    int name_index = 0;
    sverilog_filename = namecopy(file_name);
    if (strcmp(sverilog_filename, NAME_STDIO) == 0)
    {
      delete [] sverilog_filename;
      sverilog_filename = namecopy("stdin");
      sverilog_in = stdin;
    }
    else
    if ((sverilog_in = fopen(sverilog_filename, "r")) == NULL)
      Warning("cannot open generated modules file <%s>", sverilog_filename);

    if (sverilog_in)
    {
      Message("reading file <%s>", sverilog_filename);
      sverilog_modules = new ModuleArray(1);
      sverilog_parse();
      if (sverilog_in != stdin)
        fclose(sverilog_in);
      this->addGens(sverilog_modules);
      delete sverilog_modules;
    }
    delete [] sverilog_filename;
    sverilog_lex_destroy();
    this->calcConnections(this->gens);
    this->sortConnections(this->gens);
  }
}

//---------------------------------------------------------------------------
void Lib::writeGens(char* file_name)
{
  if (file_name)
    this->writeModules(file_name, this->gens);
}

//---------------------------------------------------------------------------
bool Lib::addGen(Module* module, int position)
{
  bool result = false;
  if (this->gen_hash_table->find(module) == NULL)
  {
    if (!this->gens)
      this->gens = new ModuleArray(1);
    module->lib = this;
    if (position < 0)
      this->gens->add(module);
    else
      this->gens->addAt(position, module);
    this->gen_hash_table->add(module);
    // add module to the library
    this->addModule(module);
    result = true;
  }
  return result;
}

//---------------------------------------------------------------------------
void Lib::addGens(ModuleArray* modules)
{
  if (modules)
  for (int module_index = 0; module_index < modules->num; module_index++)
  {
    Module* module_cur = modules->arr[module_index];
    if (!this->addGen(module_cur))
      delete module_cur;
  }
}

//---------------------------------------------------------------------------
Module* Lib::getGen(char* module_name)
{
  Module* module_mask = new Module(TAG_UNDEFINED, namecopy(module_name));
  Module* module_cur = gen_hash_table->find(module_mask);
  delete module_mask;
  return module_cur;
}

//---------------------------------------------------------------------------
Module* Lib::genModuleDR(char* module_name, int tag_mask)
{
  // find SR and DR module prototipes
  char* module_name_dr = this->getLogicDR(module_name, tag_mask);
  if (module_name_dr == NULL)
    Error("cannot generate DR module for SR module <%s>", module_name);

  Module* module_cur = this->getModule(module_name);
  Module* module_new = this->getModule(module_name_dr);

  // if DR module is not created yet
  if (module_cur && !module_new)
  {
    module_new = new Module(tag_mask, namecopy(module_name_dr), NULL, NULL, NULL, module_cur->lib);
    // find the names of direct and complementary modules forming DR
    char* module_name_1 = NULL;
    char* module_name_0 = NULL;
    if ((tag_mask & TAG_MODULE_NDR) == TAG_MODULE_NDR)
    {
      module_name_1 = this->getLogic(module_name, PREFIX_ND);
      module_name_0 = this->getLogic(module_name, PREFIX_NC);
    }
    else
    if ((tag_mask & TAG_MODULE_PDR) == TAG_MODULE_PDR)
    {
      module_name_1 = this->getLogic(module_name, PREFIX_PD);
      module_name_0 = this->getLogic(module_name, PREFIX_PC);
    }

    Module* module_1 = this->getModule(module_name_1);
    if (module_1 == NULL)
      Error("module <%s> required to build dual-rail module <%s> is undefined", module_name_1, module_name_dr);
    Module* module_0 = this->getModule(module_name_0);
    if (module_0 == NULL)
      Error("module <%s> required to build dual-rail module <%s> is undefined", module_name_0, module_name_dr);
    // create instances of direct and complementary modules
    Instance* instance_1 = new Instance(TAG_ITEM_SR, name2pattern(PATTERN_INSTANCE_DR_RAIL, 1), -1, 0, module_1->getWidth(), 0, module_name_1, NULL);
    Instance* instance_0 = new Instance(TAG_ITEM_SR, name2pattern(PATTERN_INSTANCE_DR_RAIL, 0), -1, 0, module_0->getWidth(), 0, module_name_0, NULL);

    // look through the ports of SR module
    int port_index_input = -1;
    int port_index_output = -1;
    if (module_cur->ports)
    for (int port_ind = 0; port_ind < module_cur->ports->num; port_ind++)
    {
      Port* port_cur = module_cur->ports->arr[port_ind];
      // create rail_1 and rail_0 ports in DR module unless the corresponding port is hidden in SR module
      if (!port_cur->testTag(TAG_OBJ_HIDDEN))
      {
        // rail 1
        Port* port_1 = new Port(*port_cur);
        port_1->convertToDR(1);
        module_new->addPort(port_1);
        // rail 0
        Port* port_0 = new Port(*port_cur);
        port_0->convertToDR(0);
        module_new->addPort(port_0);

        // find polarity of the port
        int polarity = -1;
        if (port_cur->testTag(TAG_PORT_INPUT))
        {
          port_index_input++;
          polarity = this->getPortInfo(module_name, port_index_input, POLARITY_INPUT);
        }
        if (port_cur->testTag(TAG_PORT_OUTPUT))
        {
          port_index_output++;
          polarity = this->getPortInfo(module_name, port_index_output, POLARITY_OUTPUT);
          int polarity_1 = this->getPortInfo(module_name_1, port_index_output, POLARITY_OUTPUT);
          int polarity_0 = this->getPortInfo(module_name_0, port_index_output, POLARITY_OUTPUT);
          if (polarity_1 != polarity_0)
            Warning("complementary modules <%s> and <%s> comprising dual-rail module <%s> have different output polarity",
              module_name_1, module_name_0, module_new->getName());
          if (polarity != polarity_1)
            polarity = 0;
          else
            polarity = 1;
        }

        // create connections and assign nets to them according to the polarity
        Connection* connection_1 = new Connection(port_cur->getTag() & TAG_PORT_, NULL, NULL);
        Connection* connection_0 = new Connection(port_cur->getTag() & TAG_PORT_, NULL, NULL);
        if (port_cur->nets)
        for (int net_ind = 0; net_ind < port_cur->nets->num; net_ind++)
        {
          Net* net_cur = port_cur->nets->arr[net_ind];
          char* net_name = NULL;
          // rail 1
          net_name = name2pattern(PATTERN_NET_DR_RAIL, net_cur->getName(), polarity);
          Net* net_1 = module_new->getNet(net_name, net_cur->getIndex());
          delete [] net_name;
          connection_1->addNet(net_1);
          // rail 0
          net_name = name2pattern(PATTERN_NET_DR_RAIL, net_cur->getName(), 1 - polarity);
          Net* net_0 = module_new->getNet(net_name, net_cur->getIndex());
          delete [] net_name;
          connection_0->addNet(net_0);
        }
        instance_1->addConnection(connection_1);
        instance_0->addConnection(connection_0);
      }
    }
    module_new->addInstance(instance_1);
    module_new->addInstance(instance_0);
    // calculate module width
    int module_width = instance_1->getWidth();
    if (module_width != instance_0->getWidth())
    {
      Warning("complementary modules <%s> and <%s> comprising dual-rail module <%s> have different width (%d and %d respectively)",
        instance_1->getModuleName(), instance_0->getModuleName(), module_new->getName(),  
        instance_1->getWidth(), instance_0->getWidth());
      if (module_width < instance_0->getWidth())
        module_width = instance_0->getWidth();
    }
    module_new->setWidth(module_width);
    if (module_new->getWidth() != module_cur->getWidth())
      Warning("dual-rail module <%s> and single-rail module <%s> have different width (%d and %d respectively)", 
        module_new->getName(), module_cur->getName(), module_new->getWidth(), module_cur->getWidth()); 
//    module_new->calcConnections(); // not necessary here
    module_new->sortConnections();
  }
  else
  {
    if (module_new)
      module_new->orTag(tag_mask);
    else
      Error("cannot generate DR module <%s> because SR module <%s> is not found", module_name_dr, module_name);
  }
  delete [] module_name_dr;
  return module_new;
}

//---------------------------------------------------------------------------
int Lib::findModuleC_width(int input_num)
{
  int width = 2; 
  if (input_num > 2)
  {
    int x = input_num;
    int x2 = -1;
    int x3 = -1;
    do
    {
  	  this->findModuleC_x2x3(x, x2, x3);
  	  width++;
  	  x = x2 + x3;
    }
    while (x > 1);
  }
  return width;
}

//---------------------------------------------------------------------------
void Lib::findModuleC_x2x3(int input_num, int &x2, int &x3)
{
  if (input_num % 3 == 1)
    x3 = (input_num-2) / 3;
  else
    x3 = input_num / 3;
  x2 = (input_num - x3*3) / 2;
}

//---------------------------------------------------------------------------
Module* Lib::genModuleC(int input_num)
{
  char* module_c_name = name2pattern(this->getAssignmentVal(VAR_CPx), input_num);
  Module* module_c = NULL;
  // if DR module is not created yet
  if ( (this->getModule(module_c_name) == NULL) && (input_num > 2) )
  {
    module_c = new Module(TAG_ITEM_SR, module_c_name, NULL, NULL, NULL, this);
    // create input ports
    for (int input_index = 0; input_index < input_num; input_index++)
    {
      char* port_in_name = name2pattern(this->getAssignmentVal(VAR_CPx_INx), input_index+1);
      Port* port_in = new Port(TAG_PORT_INPUT, port_in_name, NULL, NULL, NULL);
      module_c->addPort(port_in);
    }
    // create 2-input C-element
    char* instance_c2_name = name2pattern(PATTERN_INSTANCE, this->getAssignmentVal(VAR_CPx_Q));
    Instance* instance_c2 = new Instance(TAG_ITEM_SR, instance_c2_name, -1, 0, 1, 0, NULL);
    module_c->addInstance(instance_c2);
    int layer_num = -1;
    // create trees
    for (int tree_index = 0; tree_index < 2; tree_index++)
    {
      char* tree_name = NULL;
      if (tree_index == 0)
        tree_name = "t1";
      else
        tree_name = "t2";
      Net* net_tree_out = NULL;
      int layer_input_num = input_num;
      int layer_index = -1;
      // create layers of the tree
      do
      {
        layer_index++;
        int layer_gate2_num = 0;
        int layer_gate3_num = 0;
        this->findModuleC_x2x3(layer_input_num, layer_gate2_num, layer_gate3_num);
        // create gates of the layer
        int layer_input_index = -1;
        int layer_gate_index = -1;
        for (int layer_gate_type = 0; layer_gate_type < 2; layer_gate_type++)
        {
          int gate_num = 0;
          int gate_input_num = 0;
          char* module_gate_name = NULL;
          char* connection_gate_out_name = NULL;
          char* connection_in_name[3];
          // choose the module parameters depending on the current layer and the tree index
          if (layer_gate_type == 0)
          {
            gate_num = layer_gate2_num;
            gate_input_num = 2;
            if (((tree_index + layer_index)  % 2) == 0)
            {
              module_gate_name = this->getAssignmentVal(VAR_NAND2);
              connection_gate_out_name = this->getAssignmentVal(VAR_NAND2_OUT);
              connection_in_name[0] = this->getAssignmentVal(VAR_NAND2_IN1);
              connection_in_name[1] = this->getAssignmentVal(VAR_NAND2_IN2);
              connection_in_name[2] = NULL;
            }
            else
            {
              module_gate_name = this->getAssignmentVal(VAR_NOR2);
              connection_gate_out_name = this->getAssignmentVal(VAR_NOR2_OUT);
              connection_in_name[0] = this->getAssignmentVal(VAR_NOR2_IN1);
              connection_in_name[1] = this->getAssignmentVal(VAR_NOR2_IN2);
              connection_in_name[2] = NULL;
            }
          }
          else
          {
            gate_num = layer_gate3_num;
            gate_input_num = 3;
            if (((tree_index + layer_index)  % 2) == 0)
            {
              module_gate_name = this->getAssignmentVal(VAR_NAND3);
              connection_gate_out_name = this->getAssignmentVal(VAR_NAND3_OUT);
              connection_in_name[0] = this->getAssignmentVal(VAR_NAND3_IN1);
              connection_in_name[1] = this->getAssignmentVal(VAR_NAND3_IN2);
              connection_in_name[2] = this->getAssignmentVal(VAR_NAND3_IN3);
            }
            else
            {
              module_gate_name = this->getAssignmentVal(VAR_NOR3);
              connection_gate_out_name = this->getAssignmentVal(VAR_NOR3_OUT);
              connection_in_name[0] = this->getAssignmentVal(VAR_NOR3_IN1);
              connection_in_name[1] = this->getAssignmentVal(VAR_NOR3_IN2);
              connection_in_name[2] = this->getAssignmentVal(VAR_NOR3_IN3);
            }
          }
          // go through all the gates in the layer
          for (int gate_index = 0; gate_index < gate_num; gate_index++)
          {
            layer_gate_index++;
            // create gate output wire
            char* port_gate_out_name = name2pattern(PATTERN_NET_TREE, tree_name, layer_index, layer_gate_index);
            Port* port_gate_out = new Port(TAG_PORT_WIRE, port_gate_out_name, NULL, NULL, NULL);
            Net* net_gate_out = port_gate_out->nets->arr[0];
            net_tree_out = net_gate_out;
            module_c->addPort(port_gate_out);
            // create gate instance
            char* instance_gate_name = name2pattern(PATTERN_INSTANCE, port_gate_out_name);
            Instance* instance_gate = new Instance(TAG_ITEM_SR, instance_gate_name, -1, -1, 1, -1, namecopy(module_gate_name), NULL);
            module_c->addInstance(instance_gate);
            // connect gate output wire to the output connection of the gate
            instance_gate->connectNet(TAG_PORT_OUTPUT, connection_gate_out_name, net_gate_out);
            // connect inputs
            for (int connection_gate_in_index = 0; connection_gate_in_index < gate_input_num; connection_gate_in_index++)
            {
              layer_input_index++;
              // find input port
              char* port_gate_in_name = NULL;
              if (layer_index > 0)
                port_gate_in_name = name2pattern(PATTERN_NET_TREE, tree_name, layer_index-1, layer_input_index);
              else
                port_gate_in_name = name2pattern(this->getAssignmentVal(VAR_CPx_INx), layer_input_index+1);
              Port* port_gate_in = module_c->getPort(port_gate_in_name);
              delete [] port_gate_in_name;
              // if the input port is found, then create input connection and connect the net
              if (port_gate_in)
              {
                Net* net_gate_in = port_gate_in->nets->arr[0];
                instance_gate->connectNet(TAG_PORT_INPUT, connection_in_name[connection_gate_in_index], net_gate_in);
              }
              else
                Error("cannot construct %d-input C-element <%s>", input_num, module_c_name);
            } // for (int connection_gate_in_index = 0; connction_gate_in_index < gate_input_num; connction_gate_in_index++)
          } // for (int gate_index = 0; gate_index < gate_num; gate_index++)
        } // for (int layer_gate_type = 0; layer_gate_type < 2; layer_gate_type++)
        layer_input_num = layer_gate2_num + layer_gate3_num;
      }
      while (layer_input_num > 1);
      layer_num = layer_index+1;
      // connect the tree output to the input of C-element
      char* connection_in_x_name = name2pattern(this->getAssignmentVal(VAR_CPx_INx), tree_index+1);
      instance_c2->connectNet(TAG_PORT_INPUT, connection_in_x_name, net_tree_out);
      delete [] connection_in_x_name;
    }

    // create Q output port
    char* port_q_name = namecopy(this->getAssignmentVal(VAR_CPx_Q));
    Port* port_q = new Port(TAG_PORT_OUTPUT, port_q_name, NULL, NULL, NULL);
    Net* net_q = port_q->nets->arr[0];
    module_c->addPort(port_q);
    // create QN output port
    char* port_qn_name = namecopy(this->getAssignmentVal(VAR_CPx_QN));
    Port* port_qn = new Port(TAG_PORT_OUTPUT, port_qn_name, NULL, NULL, NULL);
    Net* net_qn = port_qn->nets->arr[0];
    module_c->addPort(port_qn);
    // check if reset input should be added
    char* port_sn_name = namecopy(this->getAssignmentVal(VAR_CPx_SN));
    Port* port_sn= new Port(TAG_PORT_INPUT, port_sn_name, NULL, NULL, NULL);
    Net* net_sn = port_sn->nets->arr[0];
    module_c->addPort(port_sn);

    if ((layer_num % 2) == 0)
    {
      char* module_c2_name = name2pattern(this->getAssignmentVal(VAR_CPx), 2);
      instance_c2->setModuleName(module_c2_name);
      instance_c2->connectNet(TAG_PORT_OUTPUT, this->getAssignmentVal(VAR_CPx_Q), net_q);
      instance_c2->connectNet(TAG_PORT_OUTPUT, this->getAssignmentVal(VAR_CPx_QN), net_qn);
      instance_c2->connectNet(TAG_PORT_INPUT, this->getAssignmentVal(VAR_CPx_SN), net_sn);
    }
    else
    {
      char* module_c2_name = name2pattern(this->getAssignmentVal(VAR_CCx), 2);
      instance_c2->setModuleName(module_c2_name);
      instance_c2->connectNet(TAG_PORT_OUTPUT, this->getAssignmentVal(VAR_CCx_Q), net_qn);
      instance_c2->connectNet(TAG_PORT_OUTPUT, this->getAssignmentVal(VAR_CCx_QN), net_q);
      instance_c2->connectNet(TAG_PORT_INPUT, this->getAssignmentVal(VAR_CCx_RN), net_sn);
    }
//    module_c->calcConnections(); // not necessary here
    module_c->sortConnections();
  }
  else
    delete [] module_c_name;
  return module_c;
}


//---------------------------------------------------------------------------
float Lib::calcParameter(float value_cur, float value_prot)
{
  float value_new = 0;
  if (value_cur < 0)
    value_new -= value_cur;
  else
    value_new += value_cur;

  if (value_prot < 0)
    value_new -= value_prot;
  else
    value_new += value_prot;

  if ((value_cur < 0) || (value_prot < 0))
    value_new = -value_new;

  return value_new;
}

//---------------------------------------------------------------------------
void Lib::calcStatistics(Module* module)
{
  if (module)
  if (!module->testTag(TAG_OBJ_STATISTICATED))
  {
    module->orTag(TAG_OBJ_STATISTICATED);
    ParameterArray* parameters = new ParameterArray(1);
    // summ up all instances parameters
    if (module->instances)
    for (int instance_ind = 0; instance_ind < module->instances->num; instance_ind++)
    {
      Instance* instance_cur = module->instances->arr[instance_ind];
      Module* module_prot = this->getModule(instance_cur->getModuleName());
      if (module_prot)
      {
        // calc parameters of the instance prototipe
        if (module_prot->testTag(TAG_MODULE_COMPLEX))
          this->calcStatistics(module_prot);

        int parameter_ind = -1;
        // module_prot  module  operation
        //          CL      CL       CL++
        //          FF      CL       FF++
        //          CL      FF       CL++
        //          FF      FF       CL++
        // add up the current instance parameters to a temp parameters array
        if (module_prot->parameters)
        for (int parameter_index = 0; parameter_index < module_prot->parameters->num; parameter_index++)
        {
          Parameter* parameter_prot = module_prot->parameters->arr[parameter_index];
          if ( parameter_prot->testTag(TAG_OBJ_HIDDEN)
            && parameter_prot->testTag(TAG_PARAMETER_ACCUMULATING))
          {
            parameter_ind++;
            if (parameter_ind < parameters->num)
            {
              if (module->testTag(TAG_MODULE_FF) || !module_prot->testTag(TAG_MODULE_FF))
              {
                Parameter* parameter_cur = parameters->arr[parameter_ind];
                float value_new = this->calcParameter(parameter_prot->getValue(), parameter_cur->getValue());
                parameter_cur->setValue(value_new);
              }
            }
            else
            {
              Parameter* parameter_new = NULL;
              if (module->testTag(TAG_MODULE_FF) || !module_prot->testTag(TAG_MODULE_FF))
                parameter_new = new Parameter(TAG_OBJ_HIDDEN, namecopy(parameter_prot->getName()), parameter_prot->getValue());
              else
                parameter_new = new Parameter(TAG_OBJ_HIDDEN, namecopy(parameter_prot->getName()), 0);
              parameters->add(parameter_new);
            }
          }
        }

        // create new parameters for flip-flops
        if (!module->testTag(TAG_MODULE_FF) && module_prot->testTag(TAG_MODULE_FF))
        if (module_prot->parameters)
        for (int parameter_index = 0; parameter_index < module_prot->parameters->num; parameter_index++)
        {
          Parameter* parameter_prot = module_prot->parameters->arr[parameter_index];
          if (parameter_prot->testTag(TAG_OBJ_HIDDEN))
          {
            parameter_ind++;
            if (parameter_ind < parameters->num)
            {
              Parameter* parameter_cur = parameters->arr[parameter_ind];
              float value_new = this->calcParameter(parameter_prot->getValue(), parameter_cur->getValue());
              parameter_cur->setValue(value_new);
            }
            else
            {
              Parameter* parameter_new = new Parameter(TAG_OBJ_HIDDEN, name2pattern(PATTERN_PARAMETER_FF, parameter_prot->getName()), parameter_prot->getValue());
              parameters->add(parameter_new);
            }
          }
        }
      }
    }

    // remove old hidden parameters of the module
    if (module->parameters)
    for (int parameter_index = 0; parameter_index < module->parameters->num; parameter_index++)
    {
      Parameter* parameter_cur = module->parameters->arr[parameter_index];
      if (parameter_cur->testTag(TAG_OBJ_HIDDEN))
      {
        module->removeParameter(parameter_cur);
        parameter_index--;
      }
    }
    // add newly calculated parameters
    module->addParameters(parameters);
    delete parameters;
  }
}

//===========================================================================

//---------------------------------------------------------------------------
void Lib::writeLibItem(FILE* file, Module* module, char* parameter_names)
{
  if (module)
  {
    Rule* rule_cur = this->getRule(module->getName());
    if (rule_cur)
    {
      Module* module_pdr = NULL;
      Module* module_ndr = NULL;
      int tag_init = TAG_UNDEFINED;
      if (rule_cur->testTag(TAG_MODULE_FF))
        tag_init |= TAG_MODULE_INITIATOR;
      // PDR
      if (rule_cur->testTag(TAG_MODULE_PDR))
      {
        module_pdr = this->genModuleDR(module->getName(), (tag_init | TAG_MODULE_PDR));
        if (!this->getModule(module_pdr->getName()))
        {
          module_pdr->orTag(TAG_OBJ_HIDDEN);
          this->addModule(module_pdr);
          this->addGen(module_pdr);
        }
        this->calcStatistics(module_pdr);
      }
      // NDR
      if (rule_cur->testTag(TAG_MODULE_NDR))
      {
        module_ndr = this->genModuleDR(module->getName(), (tag_init | TAG_MODULE_NDR));
        if (!this->getModule(module_ndr->getName()))
        {
          module_ndr->orTag(TAG_OBJ_HIDDEN);
          this->addModule(module_ndr);
          this->addGen(module_ndr);
        }
        this->calcStatistics(module_ndr);
      }

      // output parameters
      int name_index = 0;
      char* parameter_name = NULL;
      while (parameter_name = names2name(parameter_names, name_index++))
      {
        // SR
        float value_sr = -1;
        Parameter* parameter_sr = module->getParameter(parameter_name);
        if (parameter_sr)
          value_sr = parameter_sr->getValue();
        // PDR
        float value_pdr = -1;
        if (module_pdr)
        {
          Parameter* parameter_pdr = module_pdr->getParameter(parameter_name);
          if (parameter_pdr)
            value_pdr = parameter_pdr->getValue();
        }
        // NDR
        float value_ndr = -1;
        if (module_ndr)
        {
          Parameter* parameter_ndr = module_ndr->getParameter(parameter_name);
          if (parameter_ndr)
            value_ndr = parameter_ndr->getValue();
        }
        fprintf(file, "// %-14s %-19s %9.0f %9.0f %9.0f     ", module->getName(), parameter_name, value_sr, value_pdr, value_ndr);

        if ( ((value_pdr < 0) && (value_ndr < 0)) ||
             ((value_pdr > 0) && (2*value_sr >= value_pdr)) ||
             ((value_ndr > 0) && (2*value_sr >= value_ndr)) )
          fprintf(file, "\n");
        else
        {
          float value_cur = -1;
          if ((value_pdr > 0) && (value_ndr > 0))
            if (value_pdr < value_ndr)
              value_cur = value_pdr;
            else
              value_cur = value_ndr;
          else
          if (value_pdr > 0)
            value_cur = value_pdr;
          else
          if (value_ndr > 0)
            value_cur = value_ndr;
          fprintf(file, "!!! +%.0f\n", (value_cur - 2*value_sr));
        }
        delete [] parameter_name;
      }
    }
  }
}

//---------------------------------------------------------------------------
void Lib::writeLib(char* file_name, char* parameter_names)
{
  if (file_name)
  {
    FILE* file = NULL;
    if (strcmp(file_name, NAME_STDIO) == 0)
      file = stdout;
    else
    {
      if ((file = fopen(file_name, "w")) == NULL)
        Error("opening library output file <%s>", file_name);
    }
    // header
    if (this->modules)
    {
      fprintf(file, "// module         parameter                  SR       PDR       NDR\n");
      fprintf(file, "// name           name                     area      area      area\n");
      for (int module_index = 0; module_index < this->modules->num; module_index++)
      {
        Module* module_cur = this->modules->arr[module_index];
        this->writeLibItem(file, module_cur, parameter_names);
      }
    }
    // library
    if (this->modules)
    {
      fprintf(file, "\n");
      for (int module_index = 0; module_index < this->modules->num; module_index++)
      {
        Module* module_cur = this->modules->arr[module_index];
        this->writeModule(file, module_cur, TAG_ALL);
      }
    }
  }
}

//===========================================================================

//---------------------------------------------------------------------------
void Lib::readAssignments(char* file_names)
{
  if (file_names)
  {
    int name_index = 0;
    while (assignments_filename = names2name(file_names, name_index++))
    {
      if (strcmp(assignments_filename, NAME_STDIO) == 0)
      {
        delete [] assignments_filename;
        assignments_filename = namecopy("stdin");
        assignments_in = stdin;
      }
      else
      if ((assignments_in = fopen(assignments_filename, "r")) == NULL)
        Error("opening input file <%s>", assignments_filename);

      if (assignments_in)
      {
        Message("reading file <%s>", assignments_filename);
        assignments_assignments = new AssignmentArray(1);
        assignments_parse();
        if (assignments_in != stdin)
          fclose(assignments_in);
        this->addAssignments(assignments_assignments);
        delete assignments_assignments;
      }
      delete [] assignments_filename;
    }
    assignments_lex_destroy();
  }
}

//---------------------------------------------------------------------------
bool Lib::addAssignment(Assignment* assignment)
{
  bool result = false;
  if (!this->assignments)
    this->assignments = new AssignmentArray(1);
  Assignment* assignment_old = assignment_hash_table->find(assignment);
  if (assignment_old)
  {
    if (strcmp(assignment_old->getVal(),  assignment->getVal()) != 0)
    {
      Message("assignment <%s=%s> is replaced by <%s=%s>", 
        assignment_old->getName(), assignment_old->getVal(), assignment->getName(), assignment->getVal());
      assignment_old->setVal(namecopy(assignment->getVal()));
    }
  }
  else
  {
    assignments->add(assignment);
    assignment_hash_table->add(assignment);
    result = true;
  }
  return result;
}

//---------------------------------------------------------------------------
void Lib::addAssignments(AssignmentArray* assignments)
{
  if (assignments)
  for (int assignment_index = 0; assignment_index < assignments->num; assignment_index++)
  {
    Assignment*  assignment_cur = assignments->arr[assignment_index];
//    Message(">>> name=%s val=%s", assignment_cur->getName(), assignment_cur->getVal());
    if (!this->addAssignment(assignment_cur))
      delete assignment_cur;
  }
}

//---------------------------------------------------------------------------
Assignment* Lib::getAssignment(char* var_name)
{
  Assignment* assignment_mask = new Assignment(TAG_UNDEFINED, namecopy(var_name), NULL);
  Assignment* assignment_cur = assignment_hash_table->find(assignment_mask);
  delete assignment_mask;
  return assignment_cur;
}


//---------------------------------------------------------------------------
char* Lib::getAssignmentVal(char* var_name)
{
  Assignment* assignment_cur = this->getAssignment(var_name);
  if (assignment_cur)
    return assignment_cur->getVal();
  else
    return NULL;
}

//---------------------------------------------------------------------------
void Lib::printAssignments()
{
  if (this->assignments)
  for (int assignment_index = 0; assignment_index < this->assignments->num; assignment_index++)
  {
    Assignment*  assignment_cur = this->assignments->arr[assignment_index];
    fprintf(stderr, "%s=%s\n", assignment_cur->getName(), assignment_cur->getVal());
  }
}
