#include <stdio.h>
#include "sv_module.h"
#include "sv_object.h"
#include "sv_parameter.h"
#include "sv_port.h"
#include "sv_instance.h"
#include "sv_lib.h"
#include "messages.h"

//---------------------------------------------------------------------------
Module::Module(int tag, char* name, ParameterArray* parameters, PortArray* ports, InstanceArray* instances, Lib* lib) : VerilogObject(tag, name)
{
  this->depth = -1;
  this->width = 0;
  this->nets_cd_calc = NULL;
  this->nets_cd_read = NULL;

  this->users = NULL;

  this->parameters = NULL;
  this->addParameters(parameters);
  
  this->port_hash_table = new PortHashTable();
  this->ports = NULL;
  this->addPorts(ports);
  this->port_clock = NULL;
  this->port_spacer = NULL;
  this->port_reset = NULL;
  this->port_go = NULL;
  this->port_done = NULL;

  this->port_vdd = new Port(TAG_PORT_WIRE | TAG_NET_VDD | TAG_OBJ_HIDDEN, namecopy(NAME_NET_VDD), NULL, NULL, NULL);
  this->addPort(this->port_vdd);

  this->port_gnd = new Port(TAG_PORT_WIRE | TAG_NET_GND | TAG_OBJ_HIDDEN, namecopy(NAME_NET_GND), NULL, NULL, NULL);
  this->addPort(this->port_gnd);

  this->instances = NULL;
  this->addInstances(instances);

  this->lib = lib;
}

//---------------------------------------------------------------------------
Module::Module(const Module &module) : VerilogObject(module)
{
  this->depth = module.depth;
  this->width = module.width;
  this->nets_cd_calc = NULL;
  this->nets_cd_read = NULL;
  // copy users
  this->users = NULL;
  this->addUsers(module.users);
  // copy parameters
  this->parameters = NULL;
  if (module.parameters)
  {
    this->parameters = new ParameterArray(module.parameters->num);
    for (int parameter_index = 0; parameter_index < module.parameters->num; parameter_index++)
      this->addParameter(new Parameter(*module.parameters->arr[parameter_index]));
  }
  // copy ports
  this->port_hash_table = new PortHashTable();
  this->ports = NULL;
  if (module.ports)
  {
    this->ports = new PortArray(module.ports->num);
    for (int port_index = 0; port_index < module.ports->num; port_index++)
      this->addPort(new Port(*module.ports->arr[port_index]));
  }
  // find clock
  this->port_clock = NULL;
  if (module.port_clock)
    this->port_clock = this->getPort(module.port_clock->getName());
  // find spacer
  this->port_spacer = NULL;
  if (module.port_spacer)
    this->port_spacer = this->getPort(module.port_spacer->getName());
  // find reset
  this->port_reset = NULL;
  if (module.port_reset)
    this->port_reset = this->getPort(module.port_reset->getName());
  // find go
  this->port_go = NULL;
  if (module.port_go)
    this->port_go = this->getPort(module.port_go->getName());
  // find done
  this->port_done = NULL;
  if (module.port_done)
    this->port_done = this->getPort(module.port_done->getName());
  // find vdd
  this->port_vdd = NULL;
  if (module.port_vdd)
    this->port_vdd = this->getPort(module.port_vdd->getName());
  // find gnd
  this->port_gnd = NULL;
  if (module.port_gnd)
    this->port_gnd = this->getPort(module.port_gnd->getName());
  // copy instances
  this->instances = NULL;
  if (module.instances)
  {
    this->instances = new InstanceArray(module.instances->num);
    for (int instance_index = 0; instance_index < module.instances->num; instance_index++)
      this->addInstance(new Instance(*module.instances->arr[instance_index]));
  }
  // copy lib
  this->lib = lib;
  // recalculate connection nets to this module ports
  this->calcConnections();
}

//---------------------------------------------------------------------------
Module::~Module()
{
  clean();
  delete this->users; this->users = NULL;
  delete this->instances; this->instances = NULL;
  delete this->nets_cd_calc; this->nets_cd_calc = NULL;
  delete this->nets_cd_read; this->nets_cd_read = NULL;
  delete this->parameters; this->parameters = NULL;
  delete this->port_hash_table; this->port_hash_table = NULL;
  delete this->ports; this->ports = NULL;
}

//---------------------------------------------------------------------------
void Module::clean()
{
  if (this->instances) this->instances->removeAll(true);
  if (this->nets_cd_calc) this->nets_cd_calc->removeAll(true);
  if (this->nets_cd_read) this->nets_cd_read->removeAll(true);
  if (this->parameters) this->parameters->removeAll(true);
  if (this->ports) this->ports->removeAll(true);
}

//---------------------------------------------------------------------------
void Module::setDepth(int depth)
{
  this->depth = depth;
}

//---------------------------------------------------------------------------
int Module::getDepth()
{
  return this->depth;
}

//---------------------------------------------------------------------------
void Module::setWidth(int width)
{
  this->width = width;
}

//---------------------------------------------------------------------------
int Module::getWidth()
{
  return this->width;
}

//---------------------------------------------------------------------------
void Module::addUser(Instance* user, int position)
{
  if (!this->users)
    this->users = new InstanceArray(1);
  if (position < 0)
    this->users->add(user);
  else
    this->users->addAt(position, user);
}

//---------------------------------------------------------------------------
void Module::addUsers(InstanceArray* users)
{
  if (users)
  for (int user_index = 0; user_index < users->num; user_index++)
  {
    Instance* user_cur = users->arr[user_index];
    this->addUser(user_cur);
  }
}

//---------------------------------------------------------------------------
void Module::removeUser(Instance* user)
{
  this->users->remove(user, false);
}

//---------------------------------------------------------------------------
void Module::addParameter(Parameter* parameter, int position)
{
  if (!this->parameters)
    this->parameters = new ParameterArray(1);
  if (position < 0)
    this->parameters->add(parameter);
  else
    this->parameters->addAt(position, parameter);
}

//---------------------------------------------------------------------------
void Module::addParameters(ParameterArray* parameters)
{
  if (parameters)
  for (int parameter_index = 0; parameter_index < parameters->num; parameter_index++)
  {
    Parameter* parameter_cur = parameters->arr[parameter_index];
    this->addParameter(parameter_cur);
  }
}

//---------------------------------------------------------------------------
void Module::removeParameter(Parameter* parameter)
{
  this->parameters->remove(parameter, true);
}

//---------------------------------------------------------------------------
Parameter* Module::getParameter(char* parameter_name)
{
  if (this->parameters)
  {
    Parameter* parameter_mask = new Parameter(TAG_ALL, namecopy(parameter_name));
    int parameter_index = this->parameters->find(parameter_mask, 0, VerilogObject::compareByMask);
    delete parameter_mask;
    if (parameter_index >= 0)
      return  this->parameters->arr[parameter_index];
  }
  return NULL;
}

//---------------------------------------------------------------------------
void Module::addPort(Port* port, int position)
{
  if (!this->ports)
    this->ports = new PortArray(1);
  if (position < 0)
    this->ports->add(port);
  else
    this->ports->addAt(position, port);
  this->port_hash_table->add(port);
}

//---------------------------------------------------------------------------
void Module::addPorts(PortArray* ports)
{
  if (ports)
  for (int port_index = 0; port_index < ports->num; port_index++)
  {
    Port* port_cur = ports->arr[port_index];
    this->addPort(port_cur);
  }
}

//---------------------------------------------------------------------------
void Module::removePort(Port* port)
{
  this->port_hash_table->remove(port);
  this->ports->remove(port, true);
}
/*
//---------------------------------------------------------------------------
Port* Module::getPort(char* port_name)
{
  if (this->ports)
  {
    Port* port_mask = new Port(TAG_ALL, namecopy(port_name));
    int port_index = this->ports->find(port_mask, 0, VerilogObject::compareByMask);
    delete port_mask;
    if (port_index >= 0)
      return  this->ports->arr[port_index];
  }
  return NULL;
}
*/

//---------------------------------------------------------------------------
Port* Module::getPort(char* port_name)
{
  Port* port_mask = new Port(TAG_ALL, namecopy(port_name));
  Port* port_cur = this->port_hash_table->find(port_mask);
  delete port_mask;
  return port_cur;
}

//---------------------------------------------------------------------------
int Module::getPortNum(int tag_mask)
{
  int port_num = 0;
  if (this->ports)
  for (int port_index = 0; port_index < this->ports->num; port_index++)
  {
     Port* port_cur = this->ports->arr[port_index];
     if (!port_cur->testTag(TAG_OBJ_HIDDEN))
       if (port_cur->testTag(tag_mask))
         port_num++;
  }
  return port_num;
}

//---------------------------------------------------------------------------
Net* Module::getNet(char* net_name, int net_index)
{
  Port* port_cur = getPort(net_name);
  if (port_cur)
    return port_cur->getNet(net_name, net_index);
  else
    return NULL;
}

//---------------------------------------------------------------------------
Net* Module::getNet(Net* net)
{
  return this->getNet(net->getName(), net->getIndex());
}

//---------------------------------------------------------------------------
void Module::addInstance(Instance* instance, int position)
{
  if (!this->instances)
    this->instances = new InstanceArray(1);
  instance->setContainer(this);
  if (position < 0)
    this->instances->add(instance);
  else
    this->instances->addAt(position, instance);
}

//---------------------------------------------------------------------------
void Module::addInstances(InstanceArray* instances)
{
  if (instances)
  for (int instance_index = 0; instance_index < instances->num; instance_index++)
  {
    Instance* instance_cur = instances->arr[instance_index];
    this->addInstance(instance_cur);
  }
}

//---------------------------------------------------------------------------
void Module::removeInstance(Instance* instance)
{
  this->instances->remove(instance, true);
}

//---------------------------------------------------------------------------
Instance* Module::getInstance(char* instance_name, int instance_index)
{
  if (this->instances)
  {
    Instance* instance_mask = new Instance(TAG_ALL, namecopy(instance_name));
    int instance_find_index = this->instances->find(instance_mask, 0, VerilogObject::compareByMask);
    delete instance_mask;
    if (instance_find_index >= 0)
    {
      Instance* instance = this->instances->arr[instance_find_index];
      if (instance_index == instance->getIndex())
        return instance;
    }
  }
  return NULL;
}
    
//---------------------------------------------------------------------------
bool Module::hasTimingInfo()
{
  bool result = true;
  int name_index = 0;
  char* parameter_name = NULL;
  char* parameter_names = NULL;
  if (lib->delay_min_parameters && lib->delay_max_parameters)
    parameter_names = name2pattern("%s,%s", lib->delay_min_parameters, lib->delay_max_parameters);
  while (parameter_name = names2name(parameter_names, name_index++))
  {
    Parameter* parameter_cur = getParameter(parameter_name);
    delete [] parameter_name;
    if (parameter_cur == NULL)
    {
      result = false;
      break;
    }
  }  
  delete [] parameter_names;
  return result;
}

//---------------------------------------------------------------------------
float Module::getMinDelay()
{
  float min_value = 0;
  bool first = true;
  int name_index = 0;
  char* parameter_name = NULL;
  while (parameter_name = names2name(lib->delay_min_parameters, name_index++))
  {
    Parameter* parameter_cur = getParameter(parameter_name);
    delete [] parameter_name;
    if (parameter_cur)
    {
      float cur_value = parameter_cur->getValue();
      if ( first || (cur_value < min_value) )
      {
        min_value = cur_value;
        first = false;
      }
    }
  }
  return min_value;
}

//---------------------------------------------------------------------------
float Module::getMaxDelay()
{
  float max_value = 0;
  bool first = true;
  int name_index = 0;
  char* parameter_name = NULL;
  while (parameter_name = names2name(lib->delay_max_parameters, name_index++))
  {
    Parameter* parameter_cur = getParameter(parameter_name);
    delete [] parameter_name;
    if (parameter_cur)
    {
      float cur_value = parameter_cur->getValue();
      if ( first || (cur_value > max_value) )
      {
        max_value = cur_value;
        first = false;
      }
    }
  }
  return max_value;
}

//---------------------------------------------------------------------------
void Module::setPortsInfo(char* port_names, int tag, int tag_mask)
{
  if (strcmp(port_names, "*") == 0)
  {
    if (this->ports)
    for (int port_index = 0; port_index < this->ports->num; port_index++)
    {
      Port* port_cur = this->ports->arr[port_index];
      if (!port_cur->testTag(TAG_OBJ_HIDDEN))
      if ((port_cur->getTag() & tag_mask) != TAG_UNDEFINED)
      {
        port_cur->andTag(~TAG_ITEM_);
        port_cur->orTag(tag);
      }
    }
  }
  else
  {
    int name_index = 0;
    char* port_name = NULL;
    while (port_name = names2name(port_names, name_index++))
    {
      Port* port_cur = this->getPort(port_name);
      if (port_cur)
      {
        if (!port_cur->testTag(TAG_OBJ_HIDDEN))
        if ((port_cur->getTag() & tag_mask) != TAG_UNDEFINED)
        {
          port_cur->andTag(~TAG_ITEM_);
          port_cur->orTag(tag);
        }
        if (port_cur->testTag(TAG_NET_CLOCK))
        {
          if ( this->port_clock == NULL )
          {
            this->port_clock = port_cur;
            Message ("main clock port of module <%s> is <%s>", this->name, port_name);
          }
          else
            Message ("additional clock port of module <%s> is <%s>", this->name, port_name);
        }
        if (port_cur->testTag(TAG_NET_RESET))
        {
          if ( this->port_reset == NULL )
          {
            this->port_reset = port_cur;
            Message ("main reset port of module <%s> is <%s>", this->name, port_name);
          }
          else
            Message ("additional reset port of module <%s> is <%s>", this->name, port_name);
        }
      }
      delete [] port_name;
    }
  }
}

//---------------------------------------------------------------------------
void Module::calcPortsSR()
{
  // trace SR wires from FF (clock and reset)
  if (this->instances)
  for (int instance_index = 0; instance_index < this->instances->num; instance_index++)
  {
    Instance* instance_cur = this->instances->arr[instance_index];
    if (instance_cur->testTag(TAG_MODULE_FF))
    {
      int port_input_index = -1;
      int port_output_index = -1;
      for (int connection_index = 0; connection_index < instance_cur->connections->num; connection_index++)
      {
        Connection* connection_cur = instance_cur->connections->arr[connection_index];
        bool port_sr = false;
        // check if it is SR input
        if (!port_sr)
        if (connection_cur->testTag(TAG_PORT_INPUT))
        {
          port_input_index++;
          if (this->lib->getPortInfo(instance_cur->getModuleName(), port_input_index, RAIL_INPUT) == 0)
            port_sr = true;
        }
        // check if it is SR output
        if (!port_sr)
        if (connection_cur->testTag(TAG_PORT_OUTPUT))
        {
          port_output_index++;
          if (this->lib->getPortInfo(instance_cur->getModuleName(), port_output_index, RAIL_OUTPUT) == 0)
            port_sr = true;
        }
        
        if (port_sr)
        if (connection_cur->nets)
        if (connection_cur->nets->num > 0)
        {
          Port* port_cur = this->getPort(connection_cur->nets->arr[0]->getName());
          if ( port_cur )
          if ( !port_cur->testTag(TAG_ITEM_SR) )
          {
            char* port_full_name = port_cur->genFullName();
            char* instance_full_name = instance_cur->genFullName();
            Message("wire <%s> is connected to SR port <%s> of instance <%s> of module <%s> in module <%s>", 
              port_full_name, connection_cur->getName(), instance_full_name, instance_cur->getModuleName(), this->getName());
            delete [] instance_full_name;
            delete [] port_full_name;
            port_cur->andTag(~TAG_ITEM_);
            port_cur->orTag(TAG_ITEM_SR);
          }
        }
      }
    }
  }
  // trace all instances connected to SR wires and tag them as SR
  bool sr_found = true;
  do
  {
    sr_found = false;
    if (this->ports)
    for (int port_index = 0; port_index < this->ports->num; port_index++)
    {
      Port* port_cur = this->ports->arr[port_index];
      if (port_cur->nets)
      for (int net_index = 0; net_index < port_cur->nets->num; net_index++)
      {
        Net* net_cur = port_cur->nets->arr[net_index];
        if (net_cur->testTag(TAG_ITEM_SR))
        {
          // scan preset instances
          if (net_cur->preset)
          for (int instance_index = 0; instance_index < net_cur->preset->num; instance_index++)
          {
            Instance* instance_cur = net_cur->preset->arr[instance_index];
            if (!instance_cur->testTag(TAG_ITEM_SR) &&
                !instance_cur->testTag(TAG_MODULE_FF) &&
                !instance_cur->testTag(TAG_MODULE_COMPLEX))
            {
              sr_found = true;
              instance_cur->convertToSR();
              char* net_full_name = net_cur->genFullName();
              char* instance_full_name = instance_cur->genFullName();
              Message("instance <%s> of module <%s> is connected to SR net <%s> in module <%s>", 
                instance_full_name, instance_cur->getModuleName(), net_full_name, this->getName());
              delete [] instance_full_name;
              delete [] net_full_name;
            }
          }
          // scan postset instances
          if (net_cur->postset)
          for (int instance_index = 0; instance_index < net_cur->postset->num; instance_index++)
          {
            Instance* instance_cur = net_cur->postset->arr[instance_index];
            if (!instance_cur->testTag(TAG_ITEM_SR) &&
                !instance_cur->testTag(TAG_MODULE_FF) &&
                !instance_cur->testTag(TAG_MODULE_COMPLEX))
            {
              sr_found = true;
              instance_cur->convertToSR();
              char* net_full_name = net_cur->genFullName();
              char* instance_full_name = instance_cur->genFullName();
              Message("instance <%s> of module <%s> is connected to SR net <%s> in module <%s>", 
                instance_full_name, instance_cur->getModuleName(), net_full_name, this->getName());
              delete [] instance_full_name;
              delete [] net_full_name;
            }
          }
        }
      }
    }
  }
  while (sr_found);
  // tag SR ports (with all nets SR)
  for (int port_index = 0; port_index < this->ports->num; port_index++)
  {
    Port* port_cur = this->ports->arr[port_index];
    if (port_cur->nets)
    {
      int net_sr_num = 0;
      for (int net_index = 0; net_index < port_cur->nets->num; net_index++)
      {
        Net* net_cur = port_cur->nets->arr[net_index];
        if (net_cur->testTag(TAG_ITEM_SR))
          net_sr_num++;
      }
      if (net_sr_num == port_cur->nets->num)
      {
        port_cur->andTag(~TAG_ITEM_);
        port_cur->orTag(TAG_ITEM_SR);
      }
    }
  }
}

//---------------------------------------------------------------------------
void Module::calcConnections()
{
//Message("module <%s>", this->getName());
  NetArray* nets_tmp = new NetArray(1);
  if (this->instances)
  for (int instance_index = 0; instance_index < this->instances->num; instance_index++)
  {
    Instance* instance_cur = this->instances->arr[instance_index];
    char* instance_full_name = instance_cur->genFullName();
//Message("  instance <%s> of module <%s>", instance_full_name, instance_cur->getModuleName());
    if (instance_cur->connections)
    for (int connection_index = 0; connection_index < instance_cur->connections->num; connection_index++)
    {
      Connection* connection_cur = instance_cur->connections->arr[connection_index];
//Message("    connection <%s>", connection_cur->getName());
      if (connection_cur->nets)
      for (int net_index = 0; net_index < connection_cur->nets->num; net_index++)
      {
        Net* net_cur = connection_cur->nets->arr[net_index];
        if (net_cur)
        {
//char* net_full_name = net_cur->genLabelName();
//Message("      net <%s>", net_full_name);
//delete [] net_full_name;
          bool net_undefined = false;
          Net* net_new = NULL;
          Port* port_cur = this->getPort(net_cur->getName());
          if (!port_cur)
            if (net_cur->getIndex() == -1)
            {
//              Warning("in module <%s> instance <%s> is connected to undeclared net <%s>", 
//                this->name, instance_full_name, net_cur->getName());
              port_cur = new Port(TAG_PORT_WIRE, namecopy(net_cur->getName()), NULL, NULL, NULL);
              this->addPort(port_cur);
            }
          if (port_cur)
          {
            // connection of a bus
            if (net_cur->getIndex() == -1)
            {
              for (int net_new_index = 0; net_new_index < port_cur->nets->num; net_new_index++)
              {
                net_new = port_cur->nets->arr[net_new_index];
                if (net_new != net_cur)
                {
                  if (net_new_index == 0)
                    connection_cur->nets->arr[net_index] = net_new;
                  else
                    connection_cur->nets->addAt(++net_index, net_new);
                }
              }
            }
            // connection of a wire
            else
            {
              net_new = port_cur->getNet(net_cur->getName(), net_cur->getIndex());
              if (net_new != net_cur)
              {
                if (net_new)
                  connection_cur->nets->arr[net_index] = net_new;
                else
                  net_undefined = true;
              }
            }
          }
          else
            net_undefined = true;
          // remember the nets which can be removed in the end  
          if (net_cur != net_new)
          {
//            Message("module <%s> instance <%s> connection <%s> net <%s>", this->name, instance_cur->getName(), connection_cur->getName(), net_cur->getName());
            if ( nets_tmp->locate(net_cur) < 0 )
               nets_tmp->add(net_cur);
          }
 
          if (net_undefined)
          {
            char* net_full_name = net_cur->genFullName();
            Error("in module <%s> instance <%s> is connected to undeclared net <%s> which is in a bus",
              this->name, instance_full_name, net_full_name);
            delete [] net_full_name;
          }
        }
      }
    }
    delete [] instance_full_name;
  }
  if (nets_tmp)
  {
    nets_tmp->removeAll(true);
    delete nets_tmp; nets_tmp = NULL;
  }
}

//---------------------------------------------------------------------------
void Module::sortConnections()
{
  if (this->instances)
  for (int instance_index = 0; instance_index < this->instances->num; instance_index++)
  {
    Instance* instance_cur = this->instances->arr[instance_index];
    char* instance_full_name = instance_cur->genFullName();
    if (instance_full_name)
    {
      if (instance_cur->connections)
      for (int connection_index = 0; connection_index < instance_cur->connections->num; connection_index++)
      {
        Connection* connection_cur = instance_cur->connections->arr[connection_index];
        if (connection_cur->nets)
        for (int net_index = 0; net_index < connection_cur->nets->num; net_index++)
        {
          Net* net_cur = connection_cur->nets->arr[net_index];
          if (net_cur)
          {
            Port* port_prot = this->getPort(net_cur->getName());
            if (port_prot)
              net_cur->setTag(port_prot->getTag());
          }
        }
      }
      //
      Module* module_prot = this->lib->getModule(instance_cur->getModuleName());
      if (module_prot)
      // if prototype is found
      {
        if (instance_cur->connections)
        {
          for (int connection_index = 0; connection_index < instance_cur->connections->num; connection_index++)
          {
            Connection* connection_cur = instance_cur->connections->arr[connection_index];
            if (connection_cur->getName() == NULL)
            {
              if (module_prot->ports)
              {
                int port_index = -1;
                int port_connection_index = port_index;
                while (port_connection_index < connection_index)
                {
                  port_index++;
                  if (port_index < module_prot->ports->num)
                  {
                    Port* port_cur = module_prot->ports->arr[port_index];
                    if (!port_cur->testTag(TAG_PORT_WIRE) &&
                        !port_cur->testTag(TAG_PORT_REG) &&
                        !port_cur->testTag(TAG_OBJ_HIDDEN))
                      port_connection_index++;
                  }
                  else
                    Error("instance <%s> of module <%s> in module <%s> has more connections then ports available",
                      instance_full_name, instance_cur->getModuleName(), this->name);
                }
                if (port_connection_index == connection_index)
                {
                  Port* port_cur = module_prot->ports->arr[port_index];
                  connection_cur->setTag(port_cur->getTag());
                  connection_cur->setName(namecopy(port_cur->getName()));
                }
              }
            }
          }
          // sort connections according to port order
          if (module_prot->ports)
          {
            int connection_index_max = 0;
            for (int port_index = 0; port_index < module_prot->ports->num; port_index++)
            {
              Port* port_cur = module_prot->ports->arr[port_index];
              if (!port_cur->testTag(TAG_PORT_WIRE) &&
                  !port_cur->testTag(TAG_PORT_REG) &&
                  !port_cur->testTag(TAG_OBJ_HIDDEN))
              {
                bool connection_found = false;
                for (int connection_index = connection_index_max; (connection_index < instance_cur->connections->num) && (!connection_found); connection_index++)
                {
                  Connection* connection_cur = instance_cur->connections->arr[connection_index];
                  if (connection_cur->getName())
                  if (strcmp(port_cur->getName(), connection_cur->getName()) == 0)
                  {
                    connection_found = true;
                    instance_cur->connections->arr[connection_index] = instance_cur->connections->arr[connection_index_max];
                    instance_cur->connections->arr[connection_index_max] = connection_cur;
                    connection_cur->setTag(port_cur->getTag());
                    connection_index_max++;
                  }
                }
                if (!connection_found)
                {
                  Connection* connection_new = new Connection(port_cur->getTag(), namecopy(port_cur->getName()));
                  instance_cur->addConnection(connection_new, connection_index_max);
                  connection_index_max++;
                }
              }
            }
          }
        }
      }
      else
        Error("instance <%s> of module <%s> in module <%s> has no prototype", 
          instance_full_name, instance_cur->getModuleName(), this->name);
      
      for (int connection_index = 0; connection_index < instance_cur->connections->num; connection_index++)
      {
        Connection* connection_cur = instance_cur->connections->arr[connection_index];
        if (connection_cur->getName() == NULL)
        {
          Error("some ports of instance <%s> of module <%s> in module <%s> cannot be associated", 
            instance_full_name, instance_cur->getModuleName(), this->name);
          if (connection_index == (instance_cur->connections->num - 1))
            connection_cur->setTag(TAG_PORT_OUTPUT);
          else
            connection_cur->setTag(TAG_PORT_INPUT);
        }
      }
    }
    delete [] instance_full_name;
  }
}

//---------------------------------------------------------------------------
void Module::calcTags()
{
  if (this->testTag(TAG_MODULE_COMPLEX))
  {
    if (!this->testTag(TAG_MODULE_PDR) && !this->testTag(TAG_MODULE_NDR))
      this->orTag(TAG_MODULE_PDR);
    if (this->instances)
    for (int instance_index = 0; instance_index < this->instances->num; instance_index++)
    {
      Instance* instance_cur = this->instances->arr[instance_index];
      Module* module_prot = this->lib->getModule(instance_cur->getModuleName());
      if (module_prot)
      {
        instance_cur->orTag(module_prot->getTag() & TAG_MODULE_);
        if (instance_cur->testTag(TAG_MODULE_PDR))
          instance_cur->andTag(~TAG_MODULE_NDR);
        else
        if (!instance_cur->testTag(TAG_MODULE_NDR))
        {
          char* instance_full_name = instance_cur->genFullName();
          Warning("instance <%s> of module <%s> in module <%s> does not have DR implementation", instance_full_name, module_prot->getName(), this->name);
          delete [] instance_full_name;
        }
        if (instance_cur->testTag(TAG_MODULE_FF))
          this->orTag(TAG_MODULE_INITIATOR);
      }
    }
  }
}

//---------------------------------------------------------------------------
void Module::calcIncidence()
{
  // clean all nets preset and postset
  if (this->ports)
  for (int port_index = 0; port_index < this->ports->num; port_index++)
  {
    Port* port_cur = this->ports->arr[port_index];
    if (port_cur->nets)
    for (int net_index = 0; net_index < port_cur->nets->num; net_index++)
    {
      Net* net_cur = port_cur->nets->arr[net_index];
      delete net_cur->preset; net_cur->preset = NULL;
      delete net_cur->postset; net_cur->postset = NULL;
    }
  }
  // calc new preset and postset
  if (this->instances)
  for (int instance_index = 0; instance_index < this->instances->num; instance_index++)
  {
    Instance* instance_cur = this->instances->arr[instance_index];
    if (instance_cur->connections)
    for (int connection_index = 0; connection_index < instance_cur->connections->num; connection_index++)
    {
      Connection* connection_cur = instance_cur->connections->arr[connection_index];
      if (connection_cur->nets)
      for (int net_index = 0; net_index < connection_cur->nets->num; net_index++)
      {
        Net* net_cur = connection_cur->nets->arr[net_index];
		if (net_cur)
		{
          if (connection_cur->testTag(TAG_PORT_INPUT))
            net_cur->addPostset(instance_cur);
          if (connection_cur->testTag(TAG_PORT_OUTPUT))
            net_cur->addPreset(instance_cur);
        }
      }
    }
  }
}

//---------------------------------------------------------------------------
void Module::findNetHierarchy(Net* net, int depth, int layer)
{
  if (!net->testTag(TAG_OBJ_PROCESSED))
  {
  	int depth_cur = net->getDepth();
  	int layer_cur = net->getLayer();
    if ((depth > depth_cur) || (layer < layer_cur) || (layer_cur < 0))
    {
      net->orTag(TAG_OBJ_PROCESSED);
      if (depth > depth_cur)
        net->setDepth(depth);
      if ((layer < layer_cur) || (layer_cur < 0))
        net->setLayer(layer);
      if (net->preset)
      {
        if (net->preset->num > 1)
        {
          char* net_name = net->genFullName();
          Error("net <%s> in module <%s> is an output of more then 1 instance", net_name, this->getName());
          delete [] net_name;
        }
        else
        if (net->preset->num == 1)
        {
          Instance* instance_cur = net->preset->arr[0];
          Module* module_prot = this->lib->getModule(instance_cur->getModuleName());
          if (module_prot)
          {
            if (module_prot->testTag(TAG_MODULE_INITIATOR))
            {
              this->orTag(TAG_MODULE_INITIATOR);
              instance_cur->orTag(TAG_MODULE_INITIATOR);
              depth = 0;
              layer = 0;
            }
            instance_cur->setWidth(module_prot->getWidth());
          }
          this->findInstanceHierarchy(instance_cur, depth, layer);
        }
      }
      net->andTag(~TAG_OBJ_PROCESSED);
    }
  }
}


//---------------------------------------------------------------------------
void Module::findInstanceHierarchy(Instance* instance, int depth, int layer)
{
  if (!instance->testTag(TAG_OBJ_PROCESSED))
  {
  	int depth_cur = instance->getDepth();
  	int layer_cur = instance->getLayer();
    if ((depth > depth_cur) || (layer < layer_cur) || (layer_cur < 0))
    {
      instance->orTag(TAG_OBJ_PROCESSED);
      if (depth > depth_cur)
        instance->setDepth(depth);
      if ((layer < layer_cur) || (layer_cur < 0))
        instance->setLayer(layer);
      if (instance->connections)
      for (int connection_index = 0; connection_index < instance->connections->num; connection_index++)
      {
        Connection* connection_cur = instance->connections->arr[connection_index];
        if (connection_cur->testTag(TAG_PORT_INPUT))
          if (connection_cur->nets)
          for (int net_index = 0; net_index < connection_cur->nets->num; net_index++)
          {
            Net* net_cur = connection_cur->nets->arr[net_index];
            depth = instance->getDepth() + instance->getWidth();
            layer = instance->getLayer() + instance->getWidth();
            this->findNetHierarchy(net_cur, depth, layer);
          }
      }
      instance->andTag(~TAG_OBJ_PROCESSED);
    }
  }
}


//---------------------------------------------------------------------------
void Module::calcHierarchy()
{
  this->calcIncidence();
  // initialise instances
  if (this->instances)
  for (int instance_index = 0; instance_index < this->instances->num; instance_index++)
  {
    Instance* instance_cur = this->instances->arr[instance_index];
    instance_cur->andTag(~TAG_OBJ_PROCESSED);
    instance_cur->setDepth(-1);
    instance_cur->setLayer(-1);
    Module* module_prot = this->lib->getModule(instance_cur->getModuleName());
    if (module_prot)
      instance_cur->setWidth(module_prot->getWidth());
  }
  // initialise nets
  if (this->ports)
  for (int port_index = 0; port_index < this->ports->num; port_index++)
  {
    Port* port_cur = this->ports->arr[port_index];
    for (int net_index = 0; net_index < port_cur->nets->num; net_index++)
    {
      Net* net_cur = port_cur->nets->arr[net_index];
      net_cur->andTag(~TAG_OBJ_PROCESSED);
      net_cur->setDepth(-1);
      net_cur->setLayer(-1);
    }
  }

  // calc hierarchy (going from outputs)
  if (this->ports)
  for (int port_index = 0; port_index < this->ports->num; port_index++)
  {
    Port* port_cur = this->ports->arr[port_index];
    if (port_cur->testTag(TAG_PORT_OUTPUT))
    {
      if (port_cur->nets)
      for (int net_index = 0; net_index < port_cur->nets->num; net_index++)
      {
        Net* net_cur = port_cur->nets->arr[net_index];
        this->findNetHierarchy(net_cur, 0, 0);
      }
    }
  }
  // show unused instances
  if (this->instances)
  for (int instance_index = 0; instance_index < this->instances->num; instance_index++)
  {
    Instance* instance_cur = this->instances->arr[instance_index];
    if (instance_cur->getDepth() < 0)
    if (!instance_cur->testTag(TAG_OBJ_HIDDEN))
    {
      char* instance_name = instance_cur->genFullName();
      Warning("instance <%s> of module <%s> in module <%s> does not influence the output", instance_name, instance_cur->getModuleName(), this->getName());
      delete [] instance_name;
    }
  }
  // show unused nets
  if (this->ports)
  for (int port_index = 0; port_index < this->ports->num; port_index++)
  {
    Port* port_cur = this->ports->arr[port_index];
    if (port_cur->nets)
    for (int net_index = 0; net_index < port_cur->nets->num; net_index++)
    {
      Net* net_cur = port_cur->nets->arr[net_index];
      if (net_cur->getDepth() < 0)
      if (!net_cur->testTag(TAG_OBJ_HIDDEN))
      {
        char* net_name = net_cur->genFullName();
        Warning("net <%s> in module <%s> does not influence the output", net_name, this->getName());
        delete [] net_name;
      }
    }
  }
  // calc width of the module
  this->width = -1;
  if (this->instances)
  for (int instance_index = 0; instance_index < this->instances->num; instance_index++)
  {
    Instance* instance_cur = this->instances->arr[instance_index];
    if (instance_cur->getDepth() >= 0)
    {
      int width_cur = instance_cur->getDepth() + instance_cur->getWidth();
      if (width_cur > this->width)
        this->width = width_cur;
    }
  }
}


//---------------------------------------------------------------------------
void Module::findSpacer(Instance* instance)
{
  if (!instance->testTag(TAG_ITEM_SR))
  {
    // set instance spacer according to input nets spacers
    instance->andTag(~(TAG_ITEM_0DR | TAG_ITEM_1DR));
    // variables for input nets spacer statistics
    int in_sp0_num = 0;
    int in_sp1_num = 0;
    int in_num = 0;
    // variables for output nets spacer statistics
    int out_sp0_num = 0;
    int out_sp1_num = 0;
    int out_sp0_critical_num = 0;
    int out_sp1_critical_num = 0;
    int out_num = 0;
    // collect the statistics of input and output spacer (for the nets which are already processed)
    if (instance->connections)
    for (int connection_index = 0; connection_index < instance->connections->num; connection_index++)
    {
      Connection* connection_cur = instance->connections->arr[connection_index];
      // input
      if (connection_cur->testTag(TAG_PORT_INPUT))
      {
        if (connection_cur->nets)
        for (int net_index = 0; net_index < connection_cur->nets->num; net_index++)
        {
          Net* net_cur = connection_cur->nets->arr[net_index];
          if (!net_cur->testTag(TAG_ITEM_SR))
          {
            if (net_cur->testTag(TAG_PORT_INPUT) || net_cur->testTag(TAG_PORT_OUTPUT) ||
               (net_cur->getDepth() <= instance->getDepth() + instance->getWidth()))
            {
              if (net_cur->testTag(TAG_ITEM_0DR))
                in_sp0_num++;
              else
              if (net_cur->testTag(TAG_ITEM_1DR))
                in_sp1_num++;
            }
            in_num++;
          }
        }
      }
      else
      // output
      if (connection_cur->testTag(TAG_PORT_OUTPUT))
      {
        if (connection_cur->nets)
        for (int net_index = 0; net_index < connection_cur->nets->num; net_index++)
        {
          Net* net_cur = connection_cur->nets->arr[net_index];
          if (!net_cur->testTag(TAG_ITEM_SR))
          {
            if (net_cur->testTag(TAG_ITEM_0DR))
            {
              out_sp0_num++;
              // output nets in the critical path
              if (instance->getDepth() == net_cur->getDepth())
                out_sp0_critical_num++;
            }
            else
            if (net_cur->testTag(TAG_ITEM_1DR))
            {
              out_sp1_num++;
              // output nets in the critical path
              if (instance->getDepth() == net_cur->getDepth())
                out_sp1_critical_num++;
            }
            out_num++;
          }
        }
      }
    }

    // choose the spacer for the current instance output
    if (out_sp0_critical_num > out_sp1_critical_num)
      instance->orTag(TAG_ITEM_0DR);
    else
    if (out_sp0_critical_num < out_sp1_critical_num)
      instance->orTag(TAG_ITEM_1DR);
    else
    if (out_sp0_critical_num == out_sp1_critical_num)
      if (out_sp0_num > out_sp1_num)
        instance->orTag(TAG_ITEM_0DR);
      else
        instance->orTag(TAG_ITEM_1DR);

    // instance correction
    Module* module_prot = this->lib->getModule(instance->getModuleName());
    if (module_prot)
    {
      if (instance->testTag(TAG_MODULE_INITIATOR))
      // spacer initiators
      {
        if (module_prot->testTag(TAG_MODULE_0DR) && module_prot->testTag(TAG_MODULE_1DR))
        {
          if (instance->testTag(TAG_ITEM_0DR))
          {
            instance->andTag(~TAG_MODULE_1DR);
            instance->orTag(TAG_MODULE_0DR);
          }
          else
          if (instance->testTag(TAG_ITEM_1DR))
          {
            instance->andTag(~TAG_MODULE_0DR);
            instance->orTag(TAG_MODULE_1DR);
          }
        }
        else
        if (module_prot->testTag(TAG_MODULE_0DR))
        {
          instance->andTag(~(TAG_ITEM_1DR | TAG_MODULE_1DR));
          instance->orTag(TAG_ITEM_0DR | TAG_MODULE_0DR);
        }
        else
        if (module_prot->testTag(TAG_MODULE_1DR))
        {
          instance->andTag(~(TAG_ITEM_0DR | TAG_MODULE_0DR));
          instance->orTag(TAG_ITEM_1DR | TAG_MODULE_1DR);
        }
        else
        {
          char* instance_name = instance->genFullName();
          Error("instance <%s> of module <%s> in module <%s> does not have DR implementation", instance_name, instance->getModuleName(), this->getName());
          delete [] instance_name;
        }
      }
      else
      // combinational logic
      {
        if (module_prot->testTag(TAG_MODULE_NDR) && module_prot->testTag(TAG_MODULE_PDR))
        {
          if ((instance->testTag(TAG_ITEM_0DR) && (2*in_sp0_num > in_num)) ||
              (instance->testTag(TAG_ITEM_1DR) && (2*in_sp1_num > in_num)))
          {
            instance->andTag(~TAG_MODULE_NDR);
            instance->orTag(TAG_MODULE_PDR);
            char* instance_name = instance->genFullName();
            Message("polarity change (NDR->PDR) for instance %s of module %s due to the majority of inputs with opposite spacer",
              instance_name, instance->getModuleName());
            delete [] instance_name;
          }
          else
          if ((instance->testTag(TAG_ITEM_1DR) && (2*in_sp0_num > in_num)) ||
              (instance->testTag(TAG_ITEM_0DR) && (2*in_sp1_num > in_num)))
          {
            instance->andTag(~TAG_MODULE_PDR);
            instance->orTag(TAG_MODULE_NDR);
            char* instance_name = instance->genFullName();
            Message("polarity change (PDR->NDR) for instance %s of module %s due to the majority of inputs with opposite spacer",
              instance_name, instance->getModuleName());
            delete [] instance_name;
          }
        }
      }
    }
    else
    {
      char* instance_name = instance->genFullName();
      Error("instance <%s> of module <%s> in module <%s> does not have prototype", instance_name, instance->getModuleName(), this->getName());
      delete [] instance_name;
    }

    // set input nets spacer according to the instance output spacer and spacer inversion attribute
    if (instance->connections)
    for (int connection_index = 0; connection_index < instance->connections->num; connection_index++)
    {
      Connection* connection_cur = instance->connections->arr[connection_index];
      if (connection_cur->testTag(TAG_PORT_INPUT))
      {
        if (connection_cur->nets)
        for (int net_index = 0; net_index < connection_cur->nets->num; net_index++)
        {
          Net* net_cur = connection_cur->nets->arr[net_index];
          // if the net is neither input nor output of the module,
          // then change its spacer according to the instance it precedes
          if (!net_cur->testTag(TAG_ITEM_SR))
          if (!net_cur->testTag(TAG_PORT_INPUT) && !net_cur->testTag(TAG_PORT_OUTPUT))
//          if (net_cur->getDepth() == instance->getDepth() + instance->getWidth())
          {
            net_cur->andTag(~(TAG_ITEM_0DR | TAG_ITEM_1DR));
            if (instance->testTag(TAG_MODULE_0DR))
              net_cur->orTag(TAG_ITEM_0DR);
            else
            if (instance->testTag(TAG_MODULE_1DR))
              net_cur->orTag(TAG_ITEM_1DR);
            else
            if (instance->testTag(TAG_MODULE_NDR))
            {
              if (instance->testTag(TAG_ITEM_0DR))
                net_cur->orTag(TAG_ITEM_1DR);
              else
                net_cur->orTag(TAG_ITEM_0DR);
            }
            else
            if (instance->testTag(TAG_MODULE_PDR))
            {
              if (instance->testTag(TAG_ITEM_0DR))
                net_cur->orTag(TAG_ITEM_0DR);
              else
                net_cur->orTag(TAG_ITEM_1DR);
            }
            else
            {
              char* instance_full_name = instance->genFullName();
              Error("in module <%s> instance <%s> of module <%s> has insufficient tag information",
                this->name, instance_full_name, instance->getModuleName());
              delete [] instance_full_name;
            }
          }
        }
      }
    }
  }
}

//---------------------------------------------------------------------------
void Module::calcSpacer()
{
  for (int depth_cur = 0; depth_cur < this->getWidth(); depth_cur++)
  {
    if (this->instances)
    for (int instance_index = 0; instance_index < this->instances->num; instance_index++)
    {
      Instance* instance_cur = this->instances->arr[instance_index];
      if (instance_cur->getDepth() == depth_cur)
        this->findSpacer(instance_cur);
    }
  }
}

//---------------------------------------------------------------------------
void Module::setAllCD()
{
  if (this->ports)
  for (int port_index = 0; port_index < this->ports->num; port_index++)
  {
    Port* port_cur = this->ports->arr[port_index];
    if (port_cur->nets)
    for (int net_index = 0; net_index < port_cur->nets->num; net_index++)
    {
      Net* net_cur = port_cur->nets->arr[net_index];
      if ( !net_cur->testTag(TAG_ITEM_SR) && !net_cur->testTag(TAG_OBJ_HIDDEN) )
        net_cur->orTag(TAG_OBJ_CD);
    }
  }
}

//---------------------------------------------------------------------------
void Module::convertToConstants()
{
  Port* port_vdd = this->getPort(NAME_NET_VDD);
  Port* port_gnd = this->getPort(NAME_NET_GND);
  if (this->instances)
  for (int instance_index = 0; instance_index < this->instances->num; instance_index++)
  {
    Instance* instance_cur = this->instances->arr[instance_index];
    char* module_name_dr = this->lib->getLogicDR(instance_cur->getModuleName(), instance_cur->getTag());
    if (module_name_dr)
    {
      if ((strncmp(module_name_dr, NAME_MODULE_VDD, strlen(NAME_MODULE_VDD)) == 0) ||
        (strncmp(module_name_dr, NAME_MODULE_GND, strlen(NAME_MODULE_GND)) == 0))
      {
        for (int connection_index = 0; connection_index < instance_cur->connections->num; connection_index++)
        {
          Connection* connection_cur = instance_cur->connections->arr[connection_index];
          for (int net_index = 0; net_index < connection_cur->nets->num; net_index++)
          {
            Net* net_cur = connection_cur->nets->arr[net_index];
            if (strncmp(module_name_dr, NAME_MODULE_VDD, strlen(NAME_MODULE_VDD)) == 0)
              this->connectNetsEmpty(port_vdd->nets->arr[0], net_cur);
            else
              this->connectNetsEmpty(port_gnd->nets->arr[0], net_cur);
          }
        }
        this->removeInstance(instance_cur);
        instance_index--;
      }
    }
    delete [] module_name_dr;
  }
  this->mergeNets();
}

//---------------------------------------------------------------------------
void Module::convertToNL()
{
  if (this->instances)
  for (int instance_index = 0; instance_index < this->instances->num; instance_index++)
  {
    Instance* instance_cur = this->instances->arr[instance_index];
    if (!instance_cur->testTag(TAG_ITEM_SR))
    if (!instance_cur->testTag(TAG_MODULE_FF))
      if (!instance_cur->testTag(TAG_MODULE_NDR))
      {
        Module* module_prot = this->lib->getModule(instance_cur->getModuleName());
        if (module_prot->testTag(TAG_MODULE_NDR))
        {
          instance_cur->andTag(~TAG_MODULE_PDR);
          instance_cur->orTag(TAG_MODULE_NDR);
        }
      }
  }
}

//---------------------------------------------------------------------------
int Module::getOptimalDR(char* parameter_names)
{
  int tag_op = TAG_UNDEFINED;
  if (this->testTag(TAG_MODULE_PDR) && this->testTag(TAG_MODULE_NDR))
  {
    Module* module_pdr = this->lib->genModuleDR(this->getName(), TAG_MODULE_PDR);
    if (!this->lib->getModule(module_pdr->getName()))
    {
      module_pdr->orTag(TAG_OBJ_HIDDEN);
      this->lib->addModule(module_pdr);
      this->lib->addGen(module_pdr);
    }
    this->lib->calcStatistics(module_pdr);

    Module* module_ndr = this->lib->genModuleDR(this->getName(), TAG_MODULE_NDR);
    if (!this->lib->getModule(module_ndr->getName()))
    {
      module_ndr->orTag(TAG_OBJ_HIDDEN);
      this->lib->addModule(module_ndr);
      this->lib->addGen(module_ndr);
    }
    this->lib->calcStatistics(module_ndr);

    // compare parameters
    int name_index = 0;
    char* parameter_name = NULL;
    while (parameter_name = names2name(parameter_names, name_index++))
    {
      if (tag_op == TAG_UNDEFINED)
      {
        Parameter* parameter_pdr = module_pdr->getParameter(parameter_name);
        Parameter* parameter_ndr = module_ndr->getParameter(parameter_name);
        if (parameter_pdr && parameter_ndr)
        if ((parameter_pdr->getValue() >= 0) && (parameter_ndr->getValue() >= 0))
        {
          if (parameter_pdr->getValue() < parameter_ndr->getValue())
            tag_op = TAG_MODULE_PDR;
          else
          if (parameter_pdr->getValue() > parameter_ndr->getValue())
            tag_op = TAG_MODULE_NDR;
        }
        else
          Warning("cannot optimise module <%s> for parameter <%s>", this->getName(), parameter_name);
      }
      delete [] parameter_name;
    }

    if (tag_op == TAG_UNDEFINED)
      tag_op = TAG_MODULE_PDR;
  }
  else
    tag_op = this->getTag() & (TAG_MODULE_PDR | TAG_MODULE_NDR);
  return tag_op;
}

//---------------------------------------------------------------------------
void Module::convertToOP(char* parameter_names)
{
  if (this->instances)
  for (int instance_index = 0; instance_index < this->instances->num; instance_index++)
  {
    Instance* instance_cur = this->instances->arr[instance_index];
    if (!instance_cur->testTag(TAG_ITEM_SR))
    if (!instance_cur->testTag(TAG_MODULE_FF))
    {
      Module* module_prot = this->lib->getModule(instance_cur->getModuleName());
      instance_cur->andTag(~(TAG_MODULE_PDR | TAG_MODULE_NDR));
      int tag_opt_dr = module_prot->getOptimalDR(parameter_names);
      instance_cur->orTag(tag_opt_dr);
    }
  }
}

//---------------------------------------------------------------------------
void Module::convertToOS()
{
  if (this->instances)
  for (int instance_index = 0; instance_index < this->instances->num; instance_index++)
  {
    Instance* instance_cur = this->instances->arr[instance_index];
    if (!instance_cur->testTag(TAG_ITEM_SR) &&
        !instance_cur->testTag(TAG_MODULE_FF) &&
        !instance_cur->testTag(TAG_MODULE_COMPLEX))
    {
      // if the current instance has both positive and negative DR implementations
      Module* module_prot = this->lib->getModule(instance_cur->getModuleName());
      if (module_prot)
      if (module_prot->testTag(TAG_MODULE_PDR) && module_prot->testTag(TAG_MODULE_NDR))
      {
        // count the number of wires in preset which require spacer invertion
        int net_sp0_num = 0;
        int net_sp1_num = 0;
        int net_sp0_critical_num = 0;
        int net_sp1_critical_num = 0;
        if (instance_cur->connections)
        for (int connection_index = 0; connection_index < instance_cur->connections->num; connection_index++)
        {
          Connection* connection_cur = instance_cur->connections->arr[connection_index];
          if (connection_cur->testTag(TAG_PORT_INPUT))
          {
            if (connection_cur->nets)
            for (int net_index = 0; net_index < connection_cur->nets->num; net_index++)
            {
              Net* net_cur = connection_cur->nets->arr[net_index];
              // all preseeding wires
              if (net_cur->testTag(TAG_ITEM_0DR))
                net_sp0_num++;
              else
              if (net_cur->testTag(TAG_ITEM_1DR))
                net_sp1_num++;
              // preceeding wires in critical path
              if (net_cur->getDepth() <= instance_cur->getDepth() + instance_cur->getWidth())
              {
                if (net_cur->testTag(TAG_ITEM_0DR))
                  net_sp0_critical_num++;
                else
                if (net_cur->testTag(TAG_ITEM_1DR))
                  net_sp1_critical_num++;
              }
            }
          }
        }
        // change the spacer inversion of instance if either
        // 1) number of spacer invertors in critical path is decreased
        // or
        // 2) number of spacer invertors in critical path remains the same, but
        //    the total number of spacer invertors is decreased
        bool change_instance_attributes = false;
        if ((instance_cur->testTag(TAG_MODULE_PDR) && instance_cur->testTag(TAG_ITEM_0DR)) ||
            (instance_cur->testTag(TAG_MODULE_NDR) && instance_cur->testTag(TAG_ITEM_1DR)))
        {
          if ((net_sp1_critical_num > net_sp0_critical_num) ||
             ((net_sp1_critical_num == net_sp0_critical_num) && (net_sp1_num > net_sp0_num)))
            change_instance_attributes = true;
        }
        else
        if ((instance_cur->testTag(TAG_MODULE_PDR) && instance_cur->testTag(TAG_ITEM_1DR)) ||
            (instance_cur->testTag(TAG_MODULE_NDR) && instance_cur->testTag(TAG_ITEM_0DR)))
        {
          if ((net_sp0_critical_num > net_sp1_critical_num) ||
             ((net_sp0_critical_num == net_sp1_critical_num) && (net_sp0_num > net_sp1_num)))
            change_instance_attributes = true;
        }
        // change instance attributes
        if (change_instance_attributes)
          if (instance_cur->testTag(TAG_MODULE_PDR))
          {
            instance_cur->andTag(~TAG_MODULE_PDR);
            instance_cur->orTag(TAG_MODULE_NDR);
          }
          else
          if (instance_cur->testTag(TAG_MODULE_NDR))
          {
            instance_cur->andTag(~TAG_MODULE_NDR);
            instance_cur->orTag(TAG_MODULE_PDR);
          }
      }
    }
  }
}

//---------------------------------------------------------------------------
void Module::convertToBalanced()
{
  if (this->ports)
  {
    int port_num = this->ports->num;  // to avoid processing newly inserted ports
    for (int port_index = 0; port_index < port_num; port_index++)
    {
      Port* port_cur = this->ports->arr[port_index];
      if (port_cur->nets)
      for (int net_index = 0; net_index < port_cur->nets->num; net_index++)
      {
        Net* net_cur = port_cur->nets->arr[net_index];
        if (net_cur)
        if (net_cur->testTag(TAG_ITEM_0DR) || net_cur->testTag(TAG_ITEM_1DR))
        {
          char* name_tmp = net_cur->genLabelName();
          Port* port_new = NULL;
          if (net_cur->testTag(TAG_ITEM_0DR))
            port_new = new Port(TAG_PORT_WIRE | TAG_ITEM_1DR, name2pattern(PATTERN_NET_SPINV, name_tmp), NULL, NULL, NULL);
          if (net_cur->testTag(TAG_ITEM_1DR))
            port_new = new Port(TAG_PORT_WIRE | TAG_ITEM_0DR, name2pattern(PATTERN_NET_SPINV, name_tmp), NULL, NULL, NULL);
          delete [] name_tmp;

          bool si_preset_inserted = false;
          bool si_postset_inserted = false;
          int depth_pred = -1;
          int depth_succ = -1;
          int layer_pred = -1;
          int layer_succ = -1;
          char* drive = NULL;
          if (net_cur->preset)
            if (net_cur->preset->num > 0)
            {
              Instance* instance_cur = net_cur->preset->arr[0];
              drive = this->lib->getLogicDrive(instance_cur->getModuleName());
            }

          Net* net_new = port_new->nets->arr[0];
          // instance - net
          if (net_cur->preset)
          for (int instance_index = 0; instance_index < net_cur->preset->num; instance_index++)
          {
            Instance* instance_pred = net_cur->preset->arr[instance_index];
            if ((net_cur->testTag(TAG_ITEM_0DR) && instance_pred->testTag(TAG_ITEM_1DR)) ||
                (net_cur->testTag(TAG_ITEM_1DR) && instance_pred->testTag(TAG_ITEM_0DR)))
            {
              instance_pred->replaceNet(net_cur, net_new);
              net_cur->removePreset(instance_pred);
              net_new->addPreset(instance_pred);
              si_preset_inserted = true;
              int depth_cur = instance_pred->getDepth();
              if ( (depth_pred < 0) || (depth_cur < depth_pred) )
                depth_pred = depth_cur;
              int layer_cur = instance_pred->getLayer();
              if ( (layer_pred < 0) || (layer_cur > layer_pred) )
                layer_pred = layer_cur;
            }
          }
          // net - instance
          if (net_cur->postset)
          for (int instance_index = 0; instance_index < net_cur->postset->num; instance_index++)
          {
            Instance* instance_succ = net_cur->postset->arr[instance_index];
            if (instance_succ->testTag(TAG_MODULE_NDR))
            {
              if ((net_cur->testTag(TAG_ITEM_0DR) && instance_succ->testTag(TAG_ITEM_0DR)) ||
                  (net_cur->testTag(TAG_ITEM_1DR) && instance_succ->testTag(TAG_ITEM_1DR)))
              {
                instance_succ->replaceNet(net_cur, net_new);
                net_cur->removePostset(instance_succ);
                net_new->addPostset(instance_succ);
                instance_index--;
                si_postset_inserted = true;
                int depth_cur = instance_succ->getDepth() + instance_succ->getWidth();
                if ( (depth_succ < 0) || (depth_cur > depth_succ) )
                  depth_succ = depth_cur;
                int layer_cur = instance_succ->getLayer() + instance_succ->getWidth();
                if ( (layer_succ < 0) || (layer_cur < layer_succ) )
                  layer_succ = layer_cur;
              }
            }
            else
            if (instance_succ->testTag(TAG_MODULE_PDR))
            {
              if ( ( net_cur->testTag(TAG_ITEM_0DR) && instance_succ->testTag(TAG_ITEM_1DR) ) ||
                   ( net_cur->testTag(TAG_ITEM_1DR) && instance_succ->testTag(TAG_ITEM_0DR) ) )
              {
                instance_succ->replaceNet(net_cur, net_new);
                net_cur->removePostset(instance_succ);
                net_new->addPostset(instance_succ);
                instance_index--;
                si_postset_inserted = true;
                int depth_cur = instance_succ->getDepth() + instance_succ->getWidth();
                if ( (depth_succ < 0) || (depth_cur > depth_succ) )
                  depth_succ = depth_cur;
                int layer_cur = instance_succ->getLayer() + instance_succ->getWidth();
                if ( (layer_succ < 0) || (layer_cur < layer_succ) )
                  layer_succ = layer_cur;
              }
            }
          }
          // add SI or remove new port
          if (si_preset_inserted || si_postset_inserted)
          {
            this->addPort(port_new);
            int depth_cur = net_cur->getDepth();
            if ( (depth_succ >= 0) && (depth_cur > depth_succ) )
              depth_cur--;
            int layer_cur = net_cur->getLayer();
            if ( (layer_succ >= 0) && (layer_cur > layer_succ) )
              layer_cur--;
            if (si_preset_inserted)
            {
              net_cur->setDepth(depth_cur);
              net_cur->setLayer(layer_cur);
              net_new->setDepth(depth_cur+1);
              net_new->setLayer(layer_cur+1);
              this->connectNetsSI(net_new, net_cur, drive);
            }
            else
            {
              net_new->setDepth(depth_cur);
              net_new->setLayer(layer_cur);
              net_cur->setDepth(depth_cur+1);
              net_cur->setLayer(layer_cur+1);
              this->connectNetsSI(net_cur, net_new, drive);
            }
          }
          else
          {
            delete port_new;
            port_new = NULL;
          }
          delete [] drive;
        }
      }
    }
  }
}

//---------------------------------------------------------------------------
void Module::connectNetsEmpty(Net* net_in, Net* net_out)
{
  if (net_in && net_out)
  {
    char* module_name = namecopy(this->lib->getAssignmentVal(VAR_EMPTY));
    Module* module_prot = this->lib->getModule(module_name);
    if (module_prot)
    {
      char* name_tmp = net_out->genLabelName();
      Instance* instance_empty = new Instance(TAG_ITEM_SR | TAG_MODULE_PDR, name2pattern(PATTERN_INSTANCE, name_tmp), -1, 
        net_out->getDepth(), module_prot->getWidth(), net_out->getLayer(), module_name, NULL);
      delete [] name_tmp;
      instance_empty->connectNet(TAG_PORT_INPUT, this->lib->getAssignmentVal(VAR_EMPTY_IN), net_in);
      instance_empty->connectNet(TAG_PORT_OUTPUT, this->lib->getAssignmentVal(VAR_EMPTY_OUT), net_out);
      this->addInstance(instance_empty);
      net_in->addPostset(instance_empty);
      net_out->addPreset(instance_empty);
    }
    else
    {
      Error("empty module <%s> is undefined", module_name);
      delete [] module_name;
    }
  }
}

//---------------------------------------------------------------------------
void Module::connectNetsBuffer(Net* net_in, Net* net_out, char* drive)
{
  if (net_in && net_out)
  {
    char* module_name = namecopy(this->lib->getAssignmentVal(VAR_BUF));
    Module* module_prot = this->lib->getModule(module_name);
    if (module_prot)
    {
      char* name_tmp = net_out->genLabelName();
      Instance* instance_buf = new Instance(TAG_ITEM_SR | TAG_MODULE_PDR, name2pattern(PATTERN_INSTANCE, name_tmp), -1, 
        net_out->getDepth(), module_prot->getWidth(), net_out->getLayer(), module_name, NULL);
      delete [] name_tmp;
      instance_buf->connectNet(TAG_PORT_INPUT, this->lib->getAssignmentVal(VAR_BUF_IN), net_in);
      instance_buf->connectNet(TAG_PORT_OUTPUT, this->lib->getAssignmentVal(VAR_BUF_OUT), net_out);
      this->addInstance(instance_buf);
      net_in->addPostset(instance_buf);
      net_out->addPreset(instance_buf);
    }
    else
    {
      Error("buffer module <%s> is undefined", module_name);
      delete [] module_name;
    }
  }
}

//---------------------------------------------------------------------------
void Module::connectNetsInverter(Net* net_in, Net* net_out, char* drive)
{
  if (net_in && net_out)
  {
    char* module_name = namecopy(this->lib->getAssignmentVal(VAR_INV));
    Module* module_prot = this->lib->getModule(module_name);
    if (module_prot)
    {
      char* name_tmp = net_out->genLabelName();
      Instance* instance_inv = new Instance(TAG_ITEM_SR | TAG_MODULE_PDR, name2pattern(PATTERN_INSTANCE, name_tmp), -1, 
        net_out->getDepth(), module_prot->getWidth(), net_out->getLayer(), module_name, NULL);
      delete [] name_tmp;
      instance_inv->connectNet(TAG_PORT_INPUT, this->lib->getAssignmentVal(VAR_INV_IN), net_in);
      instance_inv->connectNet(TAG_PORT_OUTPUT, this->lib->getAssignmentVal(VAR_INV_OUT), net_out);
      this->addInstance(instance_inv);
      net_in->addPostset(instance_inv);
      net_out->addPreset(instance_inv);
    }
    else
    {
      Error("inverter module <%s> is undefined", module_name);
      delete [] module_name;
    }
  }
}

//---------------------------------------------------------------------------
void Module::connectNetsSI(Net* net_in, Net* net_out, char* drive)
{
  if (net_in && net_out)
  {
    char* module_name = NULL;
    if (drive)
      module_name = name2pattern("%s%s", this->lib->getAssignmentVal(VAR_SPINV), drive);
    else
      module_name = name2pattern("%s%s", this->lib->getAssignmentVal(VAR_SPINV), this->lib->getAssignmentVal(VAR_DRIVE));
    Module* module_prot = this->lib->getModule(module_name);
    if (module_prot)
    {
      char* name_tmp = net_out->genLabelName();
      Instance* instance_si = new Instance(net_out->getTag() & (TAG_ITEM_0DR | TAG_ITEM_1DR) | TAG_MODULE_NDR, 
        name2pattern(PATTERN_INSTANCE, name_tmp), -1, net_out->getDepth(), 1, net_out->getLayer(), module_name, NULL);
      delete [] name_tmp;
      instance_si->connectNet(TAG_PORT_INPUT, this->lib->getAssignmentVal(VAR_SPINV_IN), net_in);
      instance_si->connectNet(TAG_PORT_OUTPUT, this->lib->getAssignmentVal(VAR_SPINV_OUT), net_out);
      this->addInstance(instance_si);
      net_in->addPostset(instance_si);
      net_out->addPreset(instance_si);
    }
    else
    {
      Error("spacer inverter module <%s> is undefined", module_name);
      delete [] module_name;
    }
  }
}

//---------------------------------------------------------------------------
void Module::reuseConnections(Instance* instance, char* connection_name_q, char* connection_name_qn)
{
  Net* net_qn = NULL;
  Connection* connection_qn = instance->getConnection(connection_name_qn);
  if (connection_qn)
  {
    if (connection_qn->nets)
      if (connection_qn->nets->num == 1)
        net_qn = connection_qn->nets->arr[0];
  }

  Net* net_q = NULL;
  Connection* connection_q = instance->getConnection(connection_name_q);
  if (connection_q)
  {
    if (connection_q->nets)
      if (connection_q->nets->num == 1)
        net_q = connection_q->nets->arr[0];
  }

  if (connection_qn)
  {
    if (net_q && net_qn)
    {
      this->connectNetsEmpty(new Net(*net_q), new Net(*net_qn));
      instance->removeConnection(connection_qn);
    }
    else
    if (net_qn)
    {
      connection_qn->setName(namecopy(connection_name_q));
      instance->removeConnection(connection_q);
    }
    else
      instance->removeConnection(connection_qn);
  }
}

//---------------------------------------------------------------------------
void Module::convertRegisterToDR(Instance* instance)
{
  instance->convertRegisterToMS(this->lib);
  // simplify connections
  {
    char* connection_q_1_name = name2pattern(PATTERN_NET_DR_RAIL, this->lib->getAssignmentVal(VAR_FF_Q), 1);
    char* connection_qn_0_name = name2pattern(PATTERN_NET_DR_RAIL, this->lib->getAssignmentVal(VAR_FF_QN), 0);
    this->reuseConnections(instance, connection_q_1_name, connection_qn_0_name);
    delete [] connection_q_1_name;
    delete [] connection_qn_0_name;
  }
  {
    char* connection_q_0_name = name2pattern(PATTERN_NET_DR_RAIL, this->lib->getAssignmentVal(VAR_FF_Q), 0);
    char* connection_qn_1_name = name2pattern(PATTERN_NET_DR_RAIL, this->lib->getAssignmentVal(VAR_FF_QN), 1);
    this->reuseConnections(instance, connection_q_0_name, connection_qn_1_name);
    delete [] connection_q_0_name;
    delete [] connection_qn_1_name;
  }
}

//---------------------------------------------------------------------------
void Module::addReset()
{
  if (this->port_reset == NULL)
  {
    char* net_reset_name = namecopy(this->lib->getAssignmentVal(VAR_RESET));
    this->port_reset = this->getPort(net_reset_name);
    if (this->port_reset == NULL)
    {
      this->port_reset = new Port(TAG_PORT_INPUT | TAG_ITEM_SR | TAG_NET_RESET, namecopy(net_reset_name), NULL, NULL, NULL);
      this->addPort(this->port_reset);
      this->orTag(TAG_NET_RESET);
      Message("reset port <%s> is added to module <%s>", net_reset_name, this->getName());
    }
    delete [] net_reset_name;
  }
}

//---------------------------------------------------------------------------
void Module::connectReset(Instance* instance, char* connection_name, bool propagate, int active_level)
{
  if (instance->getConnection(connection_name) == NULL)
  {
    // add reset net (if it does not exist)
    this->addReset();
    Net* net_reset = this->port_reset->nets->arr[0];
    if (propagate)
      instance->connectNet(TAG_PORT_INPUT, connection_name, net_reset);
    else
    {
      Net* net_reset_not = NULL;
      if ((this->testTag(TAG_MODE_RESET_ACTIVE_1) && (active_level == 0)) ||
         (!this->testTag(TAG_MODE_RESET_ACTIVE_1) && (active_level == 1)))
      {
        char* port_reset_not_name = name2pattern(PATTERN_NET_RESET_NOT, this->port_reset->getName());
        Port* port_reset_not = this->getPort(port_reset_not_name);
        if (port_reset_not == NULL)
        {
          port_reset_not = new Port(TAG_PORT_WIRE | TAG_ITEM_SR, namecopy(port_reset_not_name));
          this->addPort(port_reset_not);
          net_reset_not = port_reset_not->nets->arr[0];    
          this->connectNetsInverter(net_reset, net_reset_not);
        }
        else
          net_reset_not = port_reset_not->nets->arr[0];    
        delete [] port_reset_not_name;
        instance->connectNet(TAG_PORT_INPUT, connection_name, net_reset_not);
      }
      else
        instance->connectNet(TAG_PORT_INPUT, connection_name, net_reset);
    }
  }
}

//---------------------------------------------------------------------------
void Module::addClock()
{
  if (this->port_clock == NULL)
  {
    char* net_clock_name = namecopy(this->lib->getAssignmentVal(VAR_CLOCK));
    this->port_clock = this->getPort(net_clock_name);
    if (this->port_clock == NULL)
    {
      this->port_clock = new Port(TAG_PORT_INPUT | TAG_ITEM_SR | TAG_NET_CLOCK, namecopy(net_clock_name), NULL, NULL, NULL);
      this->addPort(this->port_clock);
      this->orTag(TAG_NET_CLOCK);
      Message("clock port <%s> is added to module <%s>", net_clock_name, this->getName());
    }
    delete [] net_clock_name;
  }
}

//---------------------------------------------------------------------------
void Module::connectClock(Instance* instance, char* connection_name)
{
  if (instance->getConnection(connection_name) == NULL)
  {
    // add clock net (if it does not exist)
    this->addClock();
    Net* net_clock =  this->port_clock->nets->arr[0];
    instance->connectNet(TAG_PORT_INPUT, connection_name, net_clock);
  }
}

//---------------------------------------------------------------------------
void Module::addSpacer()
{
  if (this->port_spacer == NULL)
  {
    char* net_spacer_name = namecopy(this->lib->getAssignmentVal(VAR_SPACER));
    this->port_spacer = this->getPort(net_spacer_name);
    if (this->port_spacer == NULL)
    {
      this->port_spacer = new Port(TAG_PORT_INPUT | TAG_ITEM_SR, namecopy(net_spacer_name), NULL, NULL, NULL);
      this->addPort(this->port_spacer);
      Message("spacer port <%s> is added to module <%s>", net_spacer_name, this->getName());
    }
    delete [] net_spacer_name;
  }
}

//---------------------------------------------------------------------------
void Module::connectSpacer(Instance* instance, int connection_tag, char* connection_name)
{
  if (instance->getConnection(connection_name) == NULL)
  {
    // add spacer net (if it does not exist)
    this->addSpacer();
    Net* net_spacer = this->port_spacer->nets->arr[0];
    instance->connectNet(connection_tag, connection_name, net_spacer);
  }
}

//---------------------------------------------------------------------------
void Module::addGo()
{
  if (this->port_go == NULL)
  {
    char* net_go_name = namecopy(this->lib->getAssignmentVal(VAR_GO));
    this->port_go = this->getPort(net_go_name);
    if (this->port_go == NULL)
    {
      this->port_go = new Port(TAG_PORT_INPUT | TAG_ITEM_SR, namecopy(net_go_name), NULL, NULL, NULL);
      this->addPort(this->port_go);
      Message("go port <%s> is added to module <%s>", net_go_name, this->getName());
    }
    delete [] net_go_name;
  }
}

//---------------------------------------------------------------------------
void Module::connectGo(Instance* instance, int connection_tag, char* connection_name)
{
  if (instance->getConnection(connection_name) == NULL)
  {
    this->addGo();
    instance->connectNet(connection_tag, connection_name, this->port_go->nets->arr[0]);
  }
}


//---------------------------------------------------------------------------
void Module::addDone()
{
  if (this->port_done == NULL)
  {
    char* net_done_name = namecopy(this->lib->getAssignmentVal(VAR_DONE));
    this->port_done = this->getPort(net_done_name);
    if (this->port_done == NULL)
    {
      this->port_done = new Port(TAG_PORT_OUTPUT | TAG_ITEM_SR, namecopy(net_done_name), NULL, NULL, NULL);
      this->addPort(this->port_done);
      Message("done port <%s> is added to module <%s>", net_done_name, this->getName());
    }
    delete [] net_done_name;
  }
}
//---------------------------------------------------------------------------
void Module::connectDone(Instance* instance, int connection_tag, char* connection_name)
{
  if (instance->getConnection(connection_name) == NULL)
  {
    this->addDone();
    instance->connectNet(connection_tag, connection_name, this->port_done->nets->arr[0]);
  }
}

//---------------------------------------------------------------------------
void Module::convertToExtraPort(Instance* instance)
{
  Module* module_prot = this->lib->getModule(instance->getModuleName());
  if (module_prot)
  {
    // if reset extra input should be added
    if (module_prot->testTag(TAG_NET_RESET))
    {
      if (module_prot->testTag(TAG_MODULE_FF))
        this->connectReset(instance, this->lib->getAssignmentVal(VAR_FF_RN), false, 0);
      else
      if (module_prot->testTag(TAG_MODULE_COMPLEX))
        this->connectReset(instance, this->lib->getAssignmentVal(VAR_RESET), true, 0);
    }

    // if clock extra input should be added
    if (module_prot->testTag(TAG_NET_CLOCK))
    {
      char* connection_clock_name = NULL;
      if (module_prot->testTag(TAG_MODULE_FF))
        connection_clock_name = this->lib->getAssignmentVal(VAR_FF_C);
      else
      if (module_prot->testTag(TAG_MODULE_COMPLEX))
        connection_clock_name = this->lib->getAssignmentVal(VAR_CLOCK);
      if (module_prot->getPort(connection_clock_name))
        this->connectClock(instance, connection_clock_name);
    }

    // if spacer extra port should be added
    if (this->testTag(TAG_MODE_ALTERNATING_SPACER))
    {
      char* connection_spacer_name = NULL;
      if (module_prot->testTag(TAG_MODULE_FF))
        connection_spacer_name = this->lib->getAssignmentVal(VAR_FF_SP);
      else
      if (module_prot->testTag(TAG_MODULE_COMPLEX))
        connection_spacer_name = this->lib->getAssignmentVal(VAR_SPACER);
      if (connection_spacer_name  && module_prot->getPort(connection_spacer_name) )
        this->connectSpacer(instance, TAG_PORT_INPUT, connection_spacer_name);
    }
  }
}

//---------------------------------------------------------------------------
void Module::convertInstancesToDR()
{
  if (this->instances)
  for (int instance_index = 0; instance_index < this->instances->num; instance_index++)
  {
    Instance* instance_cur = this->instances->arr[instance_index];
    char* module_prot_name_sr = namecopy(instance_cur->getModuleName());

    Rule* rule_cur = this->lib->getRule(module_prot_name_sr);
    if (rule_cur && instance_cur->testTag(TAG_MODULE_FF))
      this->convertRegisterToDR(instance_cur);
    else
      instance_cur->convertLogicToDR(this->lib);

    Module* module_prot = lib->getModule(instance_cur->getModuleName());
    if (module_prot)
    {
      // check if extra reset is required
      if (this->lib->getPortNum(module_prot_name_sr, 0, EXTRA_INPUT_RESET) > 0)
        module_prot->orTag(TAG_NET_RESET);
      // check if extra clock is required
      if (this->lib->getPortNum(module_prot_name_sr, 0, EXTRA_INPUT_CLOCK) > 0)
        module_prot->orTag(TAG_NET_CLOCK);

      this->convertToExtraPort(instance_cur);
    }
    delete [] module_prot_name_sr;
  }
}

//---------------------------------------------------------------------------
void Module::convertPortsToDR()
{
  int port_num = 1;
  if (this->ports)
    port_num = this->ports->num;
  PortArray* ports_new = new PortArray(port_num*2);
  for (int port_index = 0; port_index < port_num; port_index++)
  {
    Port* port_cur = this->ports->arr[port_index];
    if (!port_cur->testTag(TAG_ITEM_SR) && !port_cur->testTag(TAG_OBJ_HIDDEN))
    {
      // rail 1
      Port* port_1 = new Port(*port_cur);
      port_1->convertToDR(1);
      ports_new->add(port_1);
      // rail 0
      Port* port_0 = new Port(*port_cur);
      port_0->convertToDR(0);
      ports_new->add(port_0);
    }
    else
    {
      ports_new->add(port_cur);
      this->ports->arr[port_index] = NULL;
    }
  }
  if (this->ports)
  {
    this->ports->removeAll(true);
    this->port_hash_table->clean();
  }
  this->addPorts(ports_new);
  delete ports_new;
}

//---------------------------------------------------------------------------
void Module::convertConstantsToDR()
{
  if (this->instances)
  {
    bool bl_vdd = false;
    bool bl_gnd = false;
    Net* net_vdd = this->port_vdd->nets->arr[0];
    Net* net_gnd = this->port_gnd->nets->arr[0];
    for (int instance_index = 0; instance_index < this->instances->num; instance_index++)
    {
      Instance* instance_cur = this->instances->arr[instance_index];
      for (int connection_index = 0; connection_index < instance_cur->connections->num; connection_index++)
      {
        Connection* connection_cur = instance_cur->connections->arr[connection_index];
        if ( connection_cur->nets )
        {
          if ( !bl_vdd )
            if ( connection_cur->nets->locate(net_vdd) >= 0 )
              bl_vdd = true;

          if ( !bl_gnd )
            if ( connection_cur->nets->locate(net_gnd) >= 0 )
              bl_gnd = true;
        }
      }
    }
    
    if ( bl_vdd )
    {
      // modify vdd net
      this->port_hash_table->remove(port_vdd);
      this->port_vdd->andTag(~TAG_OBJ_HIDDEN);
      char* port_vdd_name = name2pattern(PATTERN_NET_CONST, this->lib->getAssignmentVal(VAR_VDD));
      this->port_vdd->setName(port_vdd_name);
      this->port_hash_table->add(port_vdd);
      // add vdd instance
      char* module_vdd_name = namecopy(this->lib->getAssignmentVal(VAR_VDD));
      char* instance_vdd_name = name2pattern(PATTERN_INSTANCE, module_vdd_name);
      Instance* instance_vdd = new Instance(TAG_MODULE_0DR, instance_vdd_name, -1, 0, 1, 0, module_vdd_name, NULL);
      instance_vdd->connectNet(TAG_PORT_OUTPUT, this->lib->getAssignmentVal(VAR_VDD_OUT), net_vdd, -1);
      this->addInstance(instance_vdd);
    }

    if ( bl_gnd     )
    {
      // modify gnd net
      this->port_hash_table->remove(port_gnd);
      this->port_gnd->andTag(~TAG_OBJ_HIDDEN);
      char* port_gnd_name = name2pattern(PATTERN_NET_CONST, this->lib->getAssignmentVal(VAR_GND));
      this->port_gnd->setName(port_gnd_name);
      this->port_hash_table->add(port_gnd);
      // add gnd instance
      char* module_gnd_name = namecopy(this->lib->getAssignmentVal(VAR_GND));
      char* instance_gnd_name = name2pattern(PATTERN_INSTANCE, module_gnd_name);
      Instance* instance_gnd = new Instance(TAG_MODULE_0DR, instance_gnd_name, -1, 0, 1, 0, module_gnd_name, NULL);
      instance_gnd->connectNet(TAG_PORT_OUTPUT, this->lib->getAssignmentVal(VAR_GND_OUT), net_gnd, -1);
      this->addInstance(instance_gnd);
    }
  }
}

//---------------------------------------------------------------------------
void Module::mergeNets()
{
  if (this->instances)
  for (int instance_empty_index = 0; instance_empty_index < this->instances->num; instance_empty_index++)
  {
    Instance* instance_empty = this->instances->arr[instance_empty_index];
    if (strcmp(instance_empty->getModuleName(), this->lib->getAssignmentVal(VAR_EMPTY)) == 0)
    {
      Net* net_in = NULL;
      Net* net_out = NULL;
      Connection* connection_in = instance_empty->getConnection(this->lib->getAssignmentVal(VAR_EMPTY_IN));
      if (connection_in)
        if (connection_in->nets->num == 1)
          net_in = connection_in->nets->arr[0];
      Connection* connection_out = instance_empty->getConnection(this->lib->getAssignmentVal(VAR_EMPTY_OUT));
      if (connection_out)
        if (connection_out->nets->num == 1)
          net_out = connection_out->nets->arr[0];
      // replace net_in by net_out
      if (net_in->testTag(TAG_PORT_WIRE) && 
//!!         !net_in->testTag(TAG_OBJ_CD) &&
         (net_in->getIndex() == -1))
      {
        if (this->instances)
        for (int instance_index = 0; instance_index < this->instances->num; instance_index++)
        {
          Instance* instance_cur = this->instances->arr[instance_index];
          instance_cur->replaceNet(net_in, net_out);
        }
        this->removeInstance(instance_empty);
        instance_empty_index--;
        net_in->orTag(TAG_OBJ_PROCESSED); //!!
      }
      else
      // replace net_out by net_in
      if (net_out->testTag(TAG_PORT_WIRE) && 
//!!     !net_out->testTag(TAG_OBJ_CD) &&
         (net_out->getIndex() == -1))
      {
        if (this->instances)
        for (int instance_index = 0; instance_index < this->instances->num; instance_index++)
        {
          Instance* instance_cur = this->instances->arr[instance_index];
          instance_cur->replaceNet(net_out, net_in);
        }
        this->removeInstance(instance_empty);
        instance_empty_index--;
        net_out->orTag(TAG_OBJ_PROCESSED); //!!
      }
      else
      {
        char* net_in_full_name = net_in->genFullName();
        char* net_out_full_name = net_out->genFullName();
        Warning("nets <%s> and <%s> cannot be merged in module <%s>", net_in_full_name, net_out_full_name, this->name);
        delete [] net_in_full_name;
        delete [] net_out_full_name;
      }
    }
  }
}

//---------------------------------------------------------------------------
void Module::removeRedundantNets()
{
  // first, tag all nets of a module as hidden
  if (this->ports)
  for (int port_index = 0; port_index < this->ports->num; port_index++)
  {
    Port* port_cur = this->ports->arr[port_index];
    if (port_cur->nets)
    for (int net_index = 0; net_index < port_cur->nets->num; net_index++)
    {
      Net* net_cur = port_cur->nets->arr[net_index];
      net_cur->orTag(TAG_OBJ_HIDDEN);
    }
  }
  // then, tag connected nets as not hidden
  if (this->instances)
  for (int instance_index = 0; instance_index < this->instances->num; instance_index++)
  {
    Instance* instance_cur = this->instances->arr[instance_index];
    if (instance_cur->connections)
    for (int connection_index = 0; connection_index < instance_cur->connections->num; connection_index++)
    {
      Connection* connection_cur = instance_cur->connections->arr[connection_index];
      if (connection_cur->nets)
      for (int net_index = 0; net_index < connection_cur->nets->num; net_index++)
      {
        Net* net_cur = connection_cur->nets->arr[net_index];
        if (net_cur)
          net_cur->andTag(~TAG_OBJ_HIDDEN);
      }
    }
  }
  // finally, remove not connected WIRES which do not belong to a bus
  if (this->ports)
  {
    int port_num = this->ports->num;
    for (int port_index = 0; port_index < port_num; port_index++)
    {
      Port* port_cur = this->ports->arr[port_index];
      if (port_cur->testTag(TAG_PORT_WIRE))
      {
        if (port_cur->nets)
        if (port_cur->nets->num == 1)
        {
          Net* net_cur = port_cur->nets->arr[0];
          if (net_cur->testTag(TAG_OBJ_HIDDEN))
          {
            this->removePort(port_cur);
            port_cur = NULL;
            port_index--;
            port_num--;
          }
        }
      }
    }
  }
}

//---------------------------------------------------------------------------
void Module::convertToDR()
{
  this->andTag(~TAG_OBJ_STATISTICATED);
  this->setName(this->lib->getLogicDR(this->name, this->tag));
  this->convertConstantsToDR();
  this->convertInstancesToDR();
  this->convertPortsToDR();
  this->calcConnections();
  this->mergeNets(); //!!
  if (this->testTag(TAG_MODE_BUFFER))
  {
    this->bufferPort(this->port_spacer);
  }
}

//---------------------------------------------------------------------------
NetArray* Module::calcNetsCD()
{
  NetArray* nets_cd = new NetArray(10);
  NetHashTable* nets_cd_hash_table = new NetHashTable();
  if (this->ports)
  for (int port_index = 0; port_index < this->ports->num; port_index++)
  {
  	Port* port_cur = this->ports->arr[port_index];
  	if (port_cur->nets) 
    for (int net_index = 0; net_index < port_cur->nets->num; net_index++)
    {
      Net* net_cur = port_cur->nets->arr[net_index];
      if (net_cur->testTag(TAG_OBJ_CD))
      {
      	Net* net_new = new Net(*net_cur);
      	net_new->convertToSR();
      	if (nets_cd_hash_table->find(net_new))
      	  delete net_new;
      	else
      	{
          nets_cd->add(net_new);
          nets_cd_hash_table->add(net_new);
      	}
      }
    }
  }
  delete nets_cd_hash_table;
  return nets_cd;
}

//---------------------------------------------------------------------------
void Module::convertToCD()
{
  int c_in_num = 0;
  char* instance_c_name = name2pattern(PATTERN_INSTANCE, this->lib->getAssignmentVal(VAR_DONE));
  Instance* instance_c = new Instance(TAG_ITEM_SR, instance_c_name, -1, 0, 1, 0, NULL, NULL);
  // intersect read and calculated completion net sets
  // build completion logic
  NetArray* nets_cd = this->calcNetsCD();
  if (nets_cd)
  {
    for (int net_index = 0; net_index < nets_cd->num; net_index++)
    {
      Net* net_cur = nets_cd->arr[net_index];
      char* net_cur_label = net_cur->genLabelName();
      // find rail 1
      char* net_cd_in_1_name = name2pattern(PATTERN_NET_DR_RAIL, net_cur->getName(), 1);
      Net* net_cd_in_1 = this->getNet(net_cd_in_1_name, net_cur->getIndex());
      delete [] net_cd_in_1_name;
      if (!net_cd_in_1 || net_cd_in_1->testTag(TAG_OBJ_PROCESSED)) continue;
      // find rail 0
      char* net_cd_in_0_name = name2pattern(PATTERN_NET_DR_RAIL, net_cur->getName(), 0);
      Net* net_cd_in_0 = this->getNet(net_cd_in_0_name, net_cur->getIndex());
      delete [] net_cd_in_0_name;
      if (!net_cd_in_0 || net_cd_in_0->testTag(TAG_OBJ_PROCESSED)) continue;

      // create CD gate
      char* instance_cd_name = name2pattern(PATTERN_INSTANCE_CD, net_cur_label);
      char* module_cd_name = NULL;
      char* connection_in1_name = NULL;
      char* connection_in2_name = NULL;
      char* connection_out_name = NULL;

      if (testTag(TAG_MODE_ALTERNATING_SPACER))
      {
        module_cd_name = namecopy(this->lib->getAssignmentVal(VAR_XOR2));
        connection_in1_name = this->lib->getAssignmentVal(VAR_XOR2_IN1);
        connection_in2_name = this->lib->getAssignmentVal(VAR_XOR2_IN2);
        connection_out_name = this->lib->getAssignmentVal(VAR_XOR2_OUT);
      }
      else
      {
        if ( net_cd_in_1->testTag(TAG_ITEM_0DR) && net_cd_in_0->testTag(TAG_ITEM_0DR))
        {
          module_cd_name = namecopy(this->lib->getAssignmentVal(VAR_OR2));
          connection_in1_name = this->lib->getAssignmentVal(VAR_OR2_IN1);
          connection_in2_name = this->lib->getAssignmentVal(VAR_OR2_IN2);
          connection_out_name = this->lib->getAssignmentVal(VAR_OR2_OUT);
        }
        else
        if ( net_cd_in_1->testTag(TAG_ITEM_1DR) && net_cd_in_0->testTag(TAG_ITEM_1DR))
        {
          module_cd_name = namecopy(this->lib->getAssignmentVal(VAR_NAND2));
          connection_in1_name = this->lib->getAssignmentVal(VAR_NAND2_IN1);
          connection_in2_name = this->lib->getAssignmentVal(VAR_NAND2_IN2);
          connection_out_name = this->lib->getAssignmentVal(VAR_NAND2_OUT);
        }
        else
        {
          char* net_full_name = net_cur->genFullName();
          Warning("inconsistent spacer on net <%s> in module <%s>", net_full_name, this->getName());
          delete [] net_full_name;
          module_cd_name = namecopy(this->lib->getAssignmentVal(VAR_XOR2));
        }
      }
      Instance* instance_cd = new Instance(TAG_UNDEFINED, instance_cd_name, -1, net_cur->getDepth()-1, 1, net_cur->getLayer()-1, module_cd_name, NULL);
      this->addInstance(instance_cd);
      // create CD output wire
      char* net_cd_name = name2pattern(PATTERN_NET_CD, net_cur_label);
      Port* port_cd = new Port(TAG_PORT_WIRE, net_cd_name, NULL, NULL, NULL);
      this->addPort(port_cd);
      Net* net_cd = port_cd->nets->arr[0];
      net_cd->setDepth(net_cur->getDepth()-1);
      net_cd->setLayer(net_cur->getLayer()-1);
      delete [] net_cur_label;
      // add rail_1 connections to CD gate
      instance_cd->connectNet(TAG_PORT_INPUT, connection_in1_name, net_cd_in_1);
      // add rail_0 connections to CD gate
      instance_cd->connectNet(TAG_PORT_INPUT, connection_in2_name, net_cd_in_0);
      // add output connections to CD gate
      instance_cd->connectNet(TAG_PORT_OUTPUT, connection_out_name, net_cd);
      // connect CD output wire to C-element
      c_in_num++;
      char* connection_in_x_name = name2pattern(this->lib->getAssignmentVal(VAR_CPx_INx), c_in_num);
      instance_c->connectNet(TAG_PORT_INPUT, connection_in_x_name, net_cd);
      delete [] connection_in_x_name;
    }
    nets_cd->removeAll(true);
    delete nets_cd; nets_cd = NULL;
  }
  // go port
  char* port_go_name = this->lib->getAssignmentVal(VAR_GO);
  this->port_go = new Port(TAG_PORT_INPUT, namecopy(port_go_name), NULL, NULL, NULL);
  Net* net_go = port_go->nets->arr[0];
  this->addPort(this->port_go);

  // done port
  char* port_done_name = this->lib->getAssignmentVal(VAR_DONE);
  this->port_done = new Port(TAG_PORT_OUTPUT, namecopy(port_done_name), NULL, NULL, NULL);
  Net* net_done = port_done->nets->arr[0];
  this->addPort(this->port_done);
  this->addDone();

  // connect complex instances with go-done ports
  for (int instance_index = 0; instance_index < this->instances->num; instance_index++)
  {
    Instance* instance_cur =  this->instances->arr[instance_index];
    Module* module_prot = this->lib->getModule(instance_cur->getModuleName());
    if (module_prot)
    {
      // connect go to complex module
      if (module_prot->getPort(port_go_name))
        instance_cur->connectNet(TAG_PORT_INPUT, port_go_name, net_go);

      // connect done to complex module
      if (module_prot->getPort(port_done_name))
      {
        // create done output wire
        char* instance_cur_label = instance_cur->genLabelName();
        Port* port_cd = new Port(TAG_PORT_WIRE, name2pattern(PATTERN_NET_CD, instance_cur_label), NULL, NULL, NULL);
        delete [] instance_cur_label;
        Net* net_cd = port_cd->nets->arr[0];
        net_cd->setDepth(instance_cur->getDepth());
        net_cd->setLayer(instance_cur->getLayer());
        this->addPort(port_cd);
        instance_cur->connectNet(TAG_PORT_OUTPUT, port_done_name, net_cd);
        
        // connect done to C-element
        c_in_num++;
        char* connection_in_x_name = name2pattern(this->lib->getAssignmentVal(VAR_CPx_INx), c_in_num);
        instance_c->connectNet(TAG_PORT_INPUT, connection_in_x_name, net_cd);
        delete [] connection_in_x_name;
      }
      // reset      
      char* connection_reset_name = this->lib->getAssignmentVal(VAR_RESET);
      if (module_prot->getPort(connection_reset_name))
        this->connectReset(instance_cur, connection_reset_name, true, 0);
    }
  }

  // C-element
  if (c_in_num > 0)
  {
    this->addInstance(instance_c);
    c_in_num++;
    instance_c->setModuleName(name2pattern(this->lib->getAssignmentVal(VAR_CPx), c_in_num));
    // add go input
    char* connection_in_x_name = name2pattern(this->lib->getAssignmentVal(VAR_CPx_INx), c_in_num);
    instance_c->connectNet(TAG_PORT_INPUT, connection_in_x_name, net_go);
    delete [] connection_in_x_name;
    // output of the C-element
    instance_c->connectNet(TAG_PORT_OUTPUT, this->lib->getAssignmentVal(VAR_CPx_Q), net_done);
    instance_c->connectNet(TAG_PORT_OUTPUT, this->lib->getAssignmentVal(VAR_CPx_QN), NULL);
    // chack if reset input should be added
    char* connection_reset_name = this->lib->getAssignmentVal(VAR_CPx_SN);
    if (strcmp(connection_reset_name, "") != 0)
      this->connectReset(instance_c, connection_reset_name, false, 0);
    // generate C-element module
    Message("generate %d-input C-element", c_in_num);
    Module* module_c = this->lib->genModuleC(c_in_num);
    if (module_c)
      this->lib->addGen(module_c);
  }
  else
  {
    delete instance_c;
    this->connectNetsBuffer(net_go, net_done);
  }
}

//---------------------------------------------------------------------------
Module* Module::copyInterface()
{
  // create interface copy
  Module* module_new = new Module(this->getTag(), namecopy(this->getName()), NULL, NULL, NULL, this->lib);
  // copy parameters
  if (this->parameters)
  for (int parameter_index = 0; parameter_index < this->parameters->num; parameter_index++)
    module_new->addParameter(new Parameter(*this->parameters->arr[parameter_index]));
  // copy input-output ports
  if (this->ports)
  {
    for (int port_index = 0; port_index < this->ports->num; port_index++)
    {
      Port* port_cur = this->ports->arr[port_index];
      if (port_cur->testTag(TAG_PORT_INPUT) || port_cur->testTag(TAG_PORT_OUTPUT))
        module_new->addPort(new Port(*port_cur));
    }
  }
  // find clock
  module_new->port_clock = NULL;
  if (this->port_clock)
    module_new->port_clock = module_new->getPort(this->port_clock->getName());
  // find spacer
  module_new->port_spacer = NULL;
  if (this->port_spacer)
    module_new->port_spacer = module_new->getPort(this->port_spacer->getName());
  // find reset
  module_new->port_reset = NULL;
  if (this->port_reset)
    module_new->port_reset = module_new->getPort(this->port_reset->getName());
  // find vdd
  module_new->port_vdd = NULL;
  if (this->port_vdd)
    module_new->port_vdd = module_new->getPort(this->port_vdd->getName());
  // find gnd
  module_new->port_gnd = NULL;
  if (this->port_gnd)
    module_new->port_gnd = module_new->getPort(this->port_gnd->getName());

  return module_new;
}

//---------------------------------------------------------------------------
void Module::convertToWrapperSR()
{
  this->andTag(~TAG_OBJ_STATISTICATED);

  // create an instance of DR module (for which the wrapper is being generated)
  char* module_dr_name = this->lib->getLogicDR(this->getName(), this->getTag());
  char* instance_name = name2pattern(PATTERN_INSTANCE, module_dr_name);
  Instance* instance_dr = new Instance(TAG_ITEM_0DR | TAG_MODULE_COMPLEX, instance_name, -1, -1, -1, -1, module_dr_name, NULL);
  this->addInstance(instance_dr);

  // add go-controller
  if (this->testTag(TAG_MODE_ASYNC))
  {
    char* module_goctrl_name = namecopy(this->lib->getAssignmentVal(VAR_GOCTRL));
    char* instance_goctrl_name = name2pattern(PATTERN_INSTANCE, module_goctrl_name);
    Instance* instance_goctrl = new Instance(TAG_ITEM_SR | TAG_MODULE_COMPLEX, instance_goctrl_name, -1, -1, -1, -1, module_goctrl_name, NULL);
    this->addInstance(instance_goctrl);
    // clk
    this->connectClock(instance_goctrl, this->lib->getAssignmentVal(VAR_GOCTRL_C));
    // done
    this->connectDone(instance_goctrl, TAG_PORT_INPUT, this->lib->getAssignmentVal(VAR_GOCTRL_DONE));
    this->port_done->setTag(TAG_PORT_WIRE | TAG_ITEM_SR);
    // rst
    this->connectReset(instance_goctrl, this->lib->getAssignmentVal(VAR_GOCTRL_SN), false, 0);
    // go
    this->connectGo(instance_goctrl, TAG_PORT_OUTPUT, this->lib->getAssignmentVal(VAR_GOCTRL_OUT));
    this->port_go->setTag(TAG_PORT_WIRE | TAG_ITEM_SR);
  }

  // add toggle
  if (this->testTag(TAG_MODE_ALTERNATING_SPACER))
  {
    // generate spacer signal
    char* module_spacer_name = namecopy(this->lib->getAssignmentVal(VAR_SPCTRL));
    char* instance_spacer_name = name2pattern(PATTERN_INSTANCE, this->lib->getAssignmentVal(VAR_SPACER));
    Instance* instance_spacer = new Instance(TAG_ITEM_SR | TAG_MODULE_COMPLEX, instance_spacer_name, -1, -1, -1, -1, module_spacer_name, NULL);
    this->addInstance(instance_spacer);
    // rst
    this->connectReset(instance_spacer, this->lib->getAssignmentVal(VAR_SPCTRL_RN), false, 0);
    // clk
    if (this->testTag(TAG_MODE_ASYNC))
      this->connectDone(instance_spacer, TAG_PORT_INPUT, this->lib->getAssignmentVal(VAR_SPCTRL_C));
    else
      this->connectClock(instance_spacer, this->lib->getAssignmentVal(VAR_SPCTRL_C));
    // spacer
    this->connectSpacer(instance_spacer, TAG_PORT_OUTPUT, this->lib->getAssignmentVal(VAR_SPCTRL_OUT));
    this->port_spacer->setTag(TAG_PORT_WIRE | TAG_ITEM_SR);
  }

  // create converters around this DR module to interface the SR environment
  int port_num = 0;
  if (this->ports)
    port_num = this->ports->num;  // to avoid processing newly inserted ports
  for (int port_index = 0; port_index < port_num; port_index++)
  {
    Port* port_cur = this->ports->arr[port_index];
    if (!port_cur->testTag(TAG_OBJ_HIDDEN))
    if (port_cur->testTag(TAG_PORT_INPUT) || port_cur->testTag(TAG_PORT_OUTPUT))
    {
      // process SR ports
      if (port_cur->testTag(TAG_ITEM_SR))
      {
        if ((port_cur == this->port_clock) && this->testTag(TAG_MODE_ASYNC))
          this->connectDone(instance_dr, TAG_PORT_INPUT, port_cur->getName());
        else
        {
          Connection* connection_sr = new Connection(port_cur->getTag(), namecopy(port_cur->getName()), NULL);
          if (port_cur->nets)
          for (int net_index = 0; net_index < port_cur->nets->num; net_index++)
          {
            Net* net_cur = port_cur->nets->arr[net_index];
            connection_sr->addNet(new Net(*net_cur));
          }
          instance_dr->addConnection(connection_sr);
	      }
      } // end of "if (port_cur->testTag(TAG_ITEM_SR))"
      else
      // process DR ports
      if (port_cur->testTag(TAG_ITEM_0DR) || port_cur->testTag(TAG_ITEM_1DR))
      {
        // add DR_1 port to DR instance
        Port* port_dr_1 = new Port(*port_cur);
        port_dr_1->setName(name2pattern(PATTERN_NET_DR_RAIL, port_cur->getName(), 1));
        port_dr_1->setTag(TAG_PORT_WIRE | TAG_ITEM_0DR);
        this->addPort(port_dr_1);
        Connection* connection_dr_1 = new Connection(port_cur->getTag(), namecopy(port_dr_1->getName()), NULL);
        if (port_dr_1->nets)
        for (int net_index = 0; net_index < port_dr_1->nets->num; net_index++)
        {
          Net* net_cur = port_dr_1->nets->arr[net_index];
          connection_dr_1->addNet(new Net(*net_cur));
        }
        instance_dr->addConnection(connection_dr_1);
        // add DR_0 port to DR instance
        Port* port_dr_0 = new Port(*port_cur);
        port_dr_0->setName(name2pattern(PATTERN_NET_DR_RAIL, port_cur->getName(), 0));
        port_dr_0->setTag(TAG_PORT_WIRE | TAG_ITEM_0DR);
        this->addPort(port_dr_0);
        Connection* connection_dr_0 = new Connection(port_cur->getTag(), namecopy(port_dr_0->getName()), NULL);
        if (port_dr_0->nets)
        for (int net_index = 0; net_index < port_dr_0->nets->num; net_index++)
        {
          Net* net_cur = port_dr_0->nets->arr[net_index];
          connection_dr_0->addNet(new Net(*net_cur));
        }
        instance_dr->addConnection(connection_dr_0);
        // generate converters for DR ports
        if (port_cur->nets)
        for (int net_index = 0; net_index < port_cur->nets->num; net_index++)
        {
          Net* net_cur = port_cur->nets->arr[net_index];
          Net* net_dr_1 = port_dr_1->nets->arr[net_index];
          Net* net_dr_0 = port_dr_0->nets->arr[net_index];
          char* name_tmp = net_cur->genLabelName();
          Instance* instance_cnv = NULL;
          // SR to DR converter
          if (net_cur->testTag(TAG_PORT_INPUT))
          {
            char* module_sr2dr_name = NULL;
            if (port_cur->testTag(TAG_ITEM_0DR))
              module_sr2dr_name = this->lib->getLogicDR(this->lib->getAssignmentVal(VAR_SR2DR), TAG_MODULE_0DR);
            else
              module_sr2dr_name = this->lib->getLogicDR(this->lib->getAssignmentVal(VAR_SR2DR), TAG_MODULE_1DR);
            Module* module_sr2dr = this->lib->getModule(module_sr2dr_name);
            if (module_sr2dr)
            {
              char* instance_sr2dr_name = name2pattern(PATTERN_INSTANCE, name_tmp);
              instance_cnv = new Instance(TAG_ITEM_SR | TAG_MODULE_COMPLEX, instance_sr2dr_name, -1, -1, -1, -1, module_sr2dr_name, NULL);

              // input CLOCK or DONE
              char* connection_clock_name = this->lib->getAssignmentVal(VAR_SR2DR_C);
              if (module_sr2dr->getPort(connection_clock_name))
              {
                if ( this->testTag(TAG_MODE_ASYNC) )
                  instance_cnv->connectNet(TAG_PORT_INPUT | TAG_ITEM_SR, connection_clock_name, this->port_done->nets->arr[0]);
                else
                  instance_cnv->connectNet(TAG_PORT_INPUT | TAG_ITEM_SR, connection_clock_name, this->port_clock->nets->arr[0]);
              }

              // input A
              char* connection_in_name = this->lib->getAssignmentVal(VAR_SR2DR_IN);
              if (module_sr2dr->getPort(connection_in_name))
                instance_cnv->connectNet(TAG_PORT_INPUT | TAG_ITEM_SR, connection_in_name, net_cur);

              // output Q_1
              char* connection_out_1_name = name2pattern(PATTERN_NET_DR_RAIL, this->lib->getAssignmentVal(VAR_SR2DR_OUT), 1);
              if (module_sr2dr->getPort(connection_out_1_name))
                instance_cnv->connectNet(TAG_PORT_OUTPUT | TAG_ITEM_0DR, connection_out_1_name, net_dr_1);
              delete [] connection_out_1_name;

              // output Q_0
              char* connection_out_0_name = name2pattern(PATTERN_NET_DR_RAIL, this->lib->getAssignmentVal(VAR_SR2DR_OUT), 0);
              if (module_sr2dr->getPort(connection_out_0_name))
                instance_cnv->connectNet(TAG_PORT_OUTPUT | TAG_ITEM_0DR, connection_out_0_name, net_dr_0);
              delete [] connection_out_0_name;

              // if spacer should be added
              if (this->testTag(TAG_MODE_ALTERNATING_SPACER))
              {
                char* connection_spacer_name =  this->lib->getAssignmentVal(VAR_FF_SP);
                if (module_sr2dr->getPort(connection_spacer_name))
                  instance_cnv->connectNet(TAG_PORT_INPUT | TAG_ITEM_SR, connection_spacer_name, this->port_spacer->nets->arr[0]);
              }
            }
            else
            {
              Error("module <%s> is required to biud a single-rail wrapper", module_sr2dr_name);
              delete [] module_sr2dr_name;
            }
          } // if (net_cur->testTag(TAG_PORT_INPUT))
          else
          // DR to SR converter
          if (port_cur->testTag(TAG_PORT_OUTPUT))
          {
            char* module_dr2sr_name = NULL;
            if (port_cur->testTag(TAG_ITEM_0DR))
              module_dr2sr_name = this->lib->getLogicDR(this->lib->getAssignmentVal(VAR_DR2SR), TAG_MODULE_0DR);
            else
              module_dr2sr_name = this->lib->getLogicDR(this->lib->getAssignmentVal(VAR_DR2SR), TAG_MODULE_1DR);
            Module* module_dr2sr = this->lib->getModule(module_dr2sr_name);
            if (module_dr2sr)
            {
              char* instance_dr2sr_name = name2pattern(PATTERN_INSTANCE, name_tmp);
              instance_cnv = new Instance(TAG_ITEM_SR | TAG_MODULE_COMPLEX, instance_dr2sr_name, -1, -1, -1, -1, module_dr2sr_name, NULL);
              // input C
              char* connection_clock_name = this->lib->getAssignmentVal(VAR_DR2SR_C);
              if (module_dr2sr->getPort(connection_clock_name))
              {
                if ( this->testTag(TAG_MODE_ASYNC) )
                  instance_cnv->connectNet(TAG_PORT_INPUT | TAG_ITEM_SR, connection_clock_name, this->port_done->nets->arr[0]);
                else
                  instance_cnv->connectNet(TAG_PORT_INPUT | TAG_ITEM_SR, connection_clock_name, this->port_clock->nets->arr[0]);
              }

              // input A_1
              char* connection_in_1_name = name2pattern(PATTERN_NET_DR_RAIL, this->lib->getAssignmentVal(VAR_DR2SR_IN), 1);
              if (module_dr2sr->getPort(connection_in_1_name))
                instance_cnv->connectNet(TAG_PORT_INPUT | TAG_ITEM_0DR, connection_in_1_name, net_dr_1);
              delete [] connection_in_1_name;

              // input A_0
              char* connection_in_0_name = name2pattern(PATTERN_NET_DR_RAIL, this->lib->getAssignmentVal(VAR_DR2SR_IN), 0);
              if (module_dr2sr->getPort(connection_in_0_name))
                instance_cnv->connectNet(TAG_PORT_INPUT | TAG_ITEM_0DR, connection_in_0_name, net_dr_0);
              delete [] connection_in_0_name;

              // output Q
              char* connection_out_name = this->lib->getAssignmentVal(VAR_DR2SR_OUT);
              if (module_dr2sr->getPort(connection_out_name))
                instance_cnv->connectNet(TAG_PORT_OUTPUT | TAG_ITEM_SR, connection_out_name, net_cur);

              // if spacer should be added
              if (this->testTag(TAG_MODE_ALTERNATING_SPACER))
              {
                char* connection_spacer_name =  this->lib->getAssignmentVal(VAR_FF_SP);
                if (module_dr2sr->getPort(connection_spacer_name))
                  instance_cnv->connectNet(TAG_PORT_INPUT | TAG_ITEM_SR, connection_spacer_name, this->port_spacer->nets->arr[0]);
              }
            }
            else
            {
              Error("module <%s> is required to biud a single-rail wrapper", module_dr2sr_name);
              delete [] module_dr2sr_name;
            }
          } // end of "if (port_cur->testTag(TAG_PORT_OUTPUT))"

          // add converter
          if (instance_cnv)
            this->addInstance(instance_cnv);
          else
            Warning("cannot generate a converter for net <%s> of module <%s>", name_tmp, this->getName());
          delete [] name_tmp;
        } // end of "for (int net_index = 0; net_index < port_cur->nets->num; net_index++)"
      } // end of "if (port_cur->testTag(TAG_ITEM_0DR) || port_cur->testTag(TAG_ITEM_1DR))"
    } // end of "if (port_cur->testTag(TAG_PORT_INPUT) || port_cur->testTag(TAG_PORT_OUTPUT))"
  } // end of "for (int port_index = 0; port_index < this->ports->num; port_index++)"

  if ( this->testTag(TAG_MODE_ASYNC) )
  {
    this->connectGo(instance_dr, TAG_PORT_INPUT, this->lib->getAssignmentVal(VAR_GO));
    this->connectDone(instance_dr, TAG_PORT_OUTPUT, this->lib->getAssignmentVal(VAR_DONE));
  }
  // if required, connect spacer to DR instance
  Module* module_dr_prot = this->lib->getModule(module_dr_name);
  if (module_dr_prot)
  {
    char* port_spacer_name = this->lib->getAssignmentVal(VAR_SPACER);
    if (module_dr_prot->getPort(port_spacer_name))
      instance_dr->connectNet(TAG_PORT_INPUT, port_spacer_name, TAG_PORT_WIRE, port_spacer_name);
  }
  // recalculate connection nets to this module ports
  this->calcConnections();
  if (this->testTag(TAG_MODE_BUFFER))
    this->bufferPort(this->port_spacer);
}


//---------------------------------------------------------------------------
void Module::simplify()
{
  this->removeRedundantNets();
}

//---------------------------------------------------------------------------
void Module::bufferPort(Port* port)
{
if (port)
if (port->nets)
{
  int buf_max_load = atoi(this->lib->getAssignmentVal(VAR_BUF_MAX_LOAD));
  for (int net_index = 0; net_index < port->nets->num; net_index++)
  {
    Net* net_cur = port->nets->arr[net_index];
    int buffer_level = -1;
    int buffer_num = -1;
    //
    do
    {
      int instance_count = 0;
      Port* port_new = NULL;
      //
      buffer_level++;
      buffer_num = 0;
      if (this->instances)
      {
        int instances_num = this->instances->num;
        for (int instance_index = 0; instance_index < instances_num; instance_index++)
        {
          Instance* instance_cur = this->instances->arr[instance_index];
          //
          if (instance_count > buf_max_load)
          {
            instance_count = 0;
            buffer_num++;
            port_new = NULL;
          }
          //
          bool instance_connected = false;
          if (instance_cur->connections)
          for (int connection_index = 0; connection_index < instance_cur->connections->num; connection_index++)
          {
            Connection* connection_cur = instance_cur->connections->arr[connection_index];
            if (connection_cur->testTag(TAG_PORT_INPUT))
            {
              Net* net_old = connection_cur->getNet(net_cur->getName(), net_cur->getIndex());
              if (net_old)
              {
                // create a new port if it has not been created yet
                if (!port_new)
                {
                  char* net_full_name = net_cur->genFullName();
                  char* port_new_name = name2pattern(PATTERN_NET_TREE, net_full_name, buffer_level, buffer_num);
                  delete [] net_full_name;
                  port_new = new Port(TAG_PORT_WIRE, port_new_name);
                  this->addPort(port_new);
                  connectNetsBuffer(net_old, port_new->nets->arr[0]);
                }
                // change the net
                connection_cur->replaceNet(net_old, port_new->nets->arr[0]);
                instance_connected = true;
              }
            }
          }
          //
          if (instance_connected)
            instance_count++;
        }
      }
    }
    while (buffer_num > 0);
  }
}
}

//---------------------------------------------------------------------------
void Module::writeWires(FILE* file, char* pattern, char* path, int tag_mask, int tag_mask_not)
{
  // ports
  if (this->ports)
  for (int potr_ind = 0; potr_ind < this->ports->num; potr_ind++)
  {
    Port* port_cur = this->ports->arr[potr_ind];
    if (!port_cur->testTag(TAG_OBJ_HIDDEN))
    if ((port_cur->getTag() & tag_mask_not) == TAG_UNDEFINED)
    if ((port_cur->getTag() & tag_mask) != TAG_UNDEFINED)
    {
      if (port_cur->nets)
      for (int net_ind = 0; net_ind < port_cur->nets->num; net_ind++)
      {
        Net* net_cur = port_cur->nets->arr[net_ind];
        if (!net_cur->testTag(TAG_OBJ_HIDDEN))
        {
          char* net_full_name = net_cur->genFullName();
          if (pattern)
          {
            for (int i = 0; i < strlen(pattern); i++)
              if (pattern[i] == SYMBOL_WIRE_META)
                fprintf(file, "%s%s", path, net_full_name);
              else
                fprintf(file, "%c", pattern[i]);
            fprintf(file, "\n");
          }
          else
          {
            fprintf(file, "%s%s\n", path, net_full_name);
          }
          delete [] net_full_name;
        }
      }
    }
  }
  // instances
  if (this->instances)
  for (int instance_ind = 0; instance_ind < this->instances->num; instance_ind++)
  {
    Instance* instance_cur = this->instances->arr[instance_ind];
    if (!instance_cur->testTag(TAG_OBJ_HIDDEN))
    {
      Module* module_prot = this->lib->getModule(instance_cur->getModuleName());
      if (module_prot)
        if (module_prot->testTag(TAG_MODULE_COMPLEX) &&
           !module_prot->testTag(TAG_MODULE_FF))
        {
          char* instance_full_name = instance_cur->genFullName();
          char* path_cur = path_cur = name2pattern("%s%s.", path, instance_full_name);
          delete [] instance_full_name;
          module_prot->writeWires(file, pattern, path_cur, TAG_PORT_WIRE, TAG_UNDEFINED);
          delete [] path_cur;
        }
    }
  }
}

//---------------------------------------------------------------------------
void Module::writeCMD(FILE* file, int path_posibility)
{
  int possibility_from = 1;
  int possibility_to = path_posibility;
  // tell Pearl the topmost module name
  fprintf(file, "%s %s\n", PEARL_TOP_LEVEL_CELL, this->getName());
  // tell Pearl the input ports
  if (this->ports)
  for (int port_index = 0; port_index < this->ports->num; port_index++)
  {
    Port* port_cur = this->ports->arr[port_index];
    if ( !port_cur->testTag(TAG_OBJ_HIDDEN) &&
         !port_cur->testTag(TAG_ITEM_SR) &&
          port_cur->testTag(TAG_PORT_INPUT) )
    {
      if (port_cur->nets)
      for (int net_index = 0; net_index < port_cur->nets->num; net_index++)
      {
        Net* net_cur = port_cur->nets->arr[net_index];
        char* net_pearl_name = net_cur->genPearlName();
        fprintf(file, "%s %s\n", PEARL_FIND_PATHS_FROM, net_pearl_name);
        delete [] net_pearl_name;
        fprintf(file, "%s %d %d\n",PEARL_SHOW_POSSIBILITY, possibility_from, possibility_to);
      }
    }
  }
  // tell Pearl the outputs of flip-flops
  if (this->instances)
  for (int instance_index = 0; instance_index < this->instances->num; instance_index++)
  {
    Instance* instance_cur = this->instances->arr[instance_index];
    if ( !instance_cur->testTag(TAG_OBJ_HIDDEN) &&
         !instance_cur->testTag(TAG_ITEM_SR) &&
          instance_cur->testTag(TAG_MODULE_INITIATOR) )
    {
      if (instance_cur->connections)
      for (int connection_index = 0; connection_index < instance_cur->connections->num; connection_index++)
      {
        Connection* connection_cur = instance_cur->connections->arr[connection_index];
        if ( connection_cur->testTag(TAG_PORT_OUTPUT))
        {
          if (connection_cur->nets)
          for (int net_index = 0; net_index < connection_cur->nets->num; net_index++)
          {
            Net* net_cur = connection_cur->nets->arr[net_index];
            if ( !net_cur->testTag(TAG_OBJ_HIDDEN) &&
                 !net_cur->testTag(TAG_PORT_INPUT) )
            {
              char* net_pearl_name = net_cur->genPearlName();
              fprintf(file, "%s %s\n", PEARL_FIND_PATHS_FROM, net_pearl_name);
              delete [] net_pearl_name;
              fprintf(file, "%s %d %d\n",PEARL_SHOW_POSSIBILITY, possibility_from, possibility_to);
            }
          }
        }
      }
    }
  }
}
