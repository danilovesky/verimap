#include "sv_instance.h"
#include "str_utils.h"
#include "messages.h"

//---------------------------------------------------------------------------
Instance::Instance(int tag, char* name, int index, int depth, int width, int layer, char* module_name, ConnectionArray* connections) : VerilogObject(tag, name)
{
  this->index = index;
  this->depth = depth;
  this->width = width;
  this->layer = layer;
  this->module_name = module_name;
  this->container = NULL;
  this->connections = NULL;
  if (connections)
    this->connections = connections;
}

//---------------------------------------------------------------------------
Instance::Instance(const Instance &instance) : VerilogObject(instance)
{
  this->index = instance.index;
  this->depth = instance.depth;
  this->width = instance.width;
  this->layer = instance.layer;
  this->module_name = namecopy(instance.module_name);
  this->container = instance.container;
  this->connections = NULL;
  if (instance.connections)
  {
    this->connections = new ConnectionArray(instance.connections->num);
    for (int i = 0; i < instance.connections->num; i++)
      this->addConnection(new Connection(*instance.connections->arr[i]));
  }
}

//---------------------------------------------------------------------------
Instance::~Instance()
{
  this->clean();
  delete this->connections; this->connections = NULL;
  delete [] module_name; module_name = NULL;
}

//---------------------------------------------------------------------------
void Instance::clean()
{
  if (this->connections)
  {
    this->connections->removeAll(true);
  }
}

//---------------------------------------------------------------------------
void Instance::setIndex(int index)
{
  this->index = index;
}

//---------------------------------------------------------------------------
int Instance::getIndex()
{
  return this->index;
}

//---------------------------------------------------------------------------
void Instance::setDepth(int depth)
{
  this->depth = depth;
}

//---------------------------------------------------------------------------
int Instance::getDepth()
{
  return this->depth;
}

//---------------------------------------------------------------------------
void Instance::setWidth(int width)
{
  this->width = width;
}

//---------------------------------------------------------------------------
int Instance::getWidth()
{
  return this->width;
}

//---------------------------------------------------------------------------
void Instance::setLayer(int layer)
{
  this->layer = layer;
}

//---------------------------------------------------------------------------
int Instance::getLayer()
{
  return this->layer;
}

//---------------------------------------------------------------------------
void Instance::setModuleName(char* module_name)
{
  delete [] this->module_name;
  this->module_name = module_name;
}

//---------------------------------------------------------------------------
char* Instance::getModuleName()
{
  return this->module_name;
}

//---------------------------------------------------------------------------
void Instance::setContainer(Module* container)
{
  this->container = container;
}

//---------------------------------------------------------------------------
Module* Instance::getContainer()
{
  return this->container;
}

//---------------------------------------------------------------------------
char* Instance::genFullName()
{
  char* name_full = NULL;
  char* name_escape = NULL;

  if (this->isEscape())
    name_escape = name2pattern(PATTERN_FULL_NAME_ESCAPE, this->name);
  else
    name_escape = namecopy(this->name);

  if (this->index < 0)
    name_full = name_escape;
  else
  {
    name_full = name2pattern(PATTERN_INSTANCE_FULL_NAME, name_escape, this->index);
    delete [] name_escape;
  }

  return name_full;
}

//---------------------------------------------------------------------------
char* Instance::genLabelName()
{
  if (this->index < 0)
    return namecopy(this->name);
  else
    return name2pattern(PATTERN_INSTANCE_LABEL, this->name, this->index);
}

//---------------------------------------------------------------------------
void Instance::addConnection(Connection* connection, int ind)
{
  if (!this->connections)
    this->connections = new ConnectionArray(1);
  if (ind < 0)
    this->connections->add(connection);
  else
    this->connections->addAt(ind, connection);
}

//---------------------------------------------------------------------------
void Instance::removeConnection(Connection* connection)
{
  if (this->connections)
  if (connection)
    this->connections->remove(connection, true);
}

//---------------------------------------------------------------------------
Connection* Instance::getConnection(char* connection_name)
{
  if (this->connections)
  {
    Connection* connection_mask = new Connection(TAG_ALL, namecopy(connection_name));
    int connection_ind = connections->find(connection_mask, 0, VerilogObject::compareByMask);
    delete connection_mask;
    if (connection_ind >= 0)
      return connections->arr[connection_ind];
  }
  return NULL;
}

//---------------------------------------------------------------------------
void Instance::connectNet(int connection_tag, char* connection_name, int net_tag, char* net_name, int connection_position)
{
  Connection* connection_new = new Connection(connection_tag, namecopy(connection_name), NULL);
  Net* net_new = new Net(net_tag, namecopy(net_name));
  connection_new->addNet(net_new);
  this->addConnection(connection_new, connection_position);
}

//---------------------------------------------------------------------------
void Instance::connectNet(int connection_tag, char* connection_name, Net* net, int connection_position)
{
  Connection* connection_new = new Connection(connection_tag, namecopy(connection_name), NULL);
  connection_new->addNet(net);
  this->addConnection(connection_new, connection_position);
}

//---------------------------------------------------------------------------
bool Instance::replaceNet(Net* net_old, Net* net_new, int copy)
{
  bool result = false;
  for (int connection_ind = 0; connection_ind < this->connections->num; connection_ind++)
  {
    Connection* connection_cur = this->connections->arr[connection_ind];
    if (connection_cur->replaceNet(net_old, net_new, copy))
      result = true;
  }
  return result;
}

//---------------------------------------------------------------------------
void Instance::convertLogicToDR(Lib* lib)
{
  if (!this->testTag(TAG_ITEM_SR))
    this->setModuleName(lib->getLogicDR(this->getModuleName(), this->tag));

  int connection_num = 0;
  if (this->connections)
    connection_num = this->connections->num;

  ConnectionArray* connections_new = new ConnectionArray(connection_num*2);
  for (int connection_ind = 0; connection_ind < connection_num; connection_ind++)
  {
    Connection* connection_cur = this->connections->arr[connection_ind];
    if (connection_cur)
    {
      bool is_sr = 0;
      if (connection_cur->nets)
      for (int net_ind = 0; net_ind < connection_cur->nets->num; net_ind++)
      {
        Net* net_cur = connection_cur->nets->arr[net_ind];
        if (net_cur->testTag(TAG_ITEM_SR))
          is_sr = true;
      }
      if (this->testTag(TAG_ITEM_SR) || is_sr)
      {
        Connection* connection_sr = new Connection(*connection_cur);
        connections_new->add(connection_sr);
      }
      else
      {
        // rail 1
        Connection* connection_1 = new Connection(*connection_cur);
        connection_1->convertToDR(1);
        connections_new->add(connection_1);
        // rail 0
        Connection* connection_0 = new Connection(*connection_cur);
        connection_0->convertToDR(0);
        connections_new->add(connection_0);
      }
    }
  }
  if (this->connections)
    this->connections->removeAll(true);
  delete this->connections;
  this->connections = connections_new;

  Module* module_prot = lib->getModule(this->getModuleName());
  if (module_prot)
    this->orTag(module_prot->getTag() & TAG_MODULE_);
}


//---------------------------------------------------------------------------
void Instance::convertRegisterToMS(Lib* lib)
{
  char* module_name_sr = namecopy(this->module_name);
  this->setModuleName(lib->getLogicDR(this->module_name, this->tag));
  int input_index = 0;
  int output_index = 0;
  int connection_num = 0;
  if (this->connections)
    connection_num = this->connections->num;
  ConnectionArray* connections_new = new ConnectionArray(connection_num*2);
  for (int connection_ind = 0; connection_ind < connection_num; connection_ind++)
  {
    Connection* connection_cur = this->connections->arr[connection_ind];
    int rail_num = -1;
    if (connection_cur->testTag(TAG_PORT_INPUT))
      rail_num = lib->getPortInfo(module_name_sr, input_index++, RAIL_INPUT);
    else
      rail_num = lib->getPortInfo(module_name_sr, output_index++, RAIL_OUTPUT);
    if (rail_num != 0) rail_num = 1;
    if (rail_num == 1)
    {
      // rail 1
      Connection* connection_1 = new Connection(*connection_cur);
      connection_1->convertToDR(1);
      connections_new->add(connection_1);
      // rail 0
      Connection* connection_0 = new Connection(*connection_cur);
      connection_0->convertToDR(0);
      connections_new->add(connection_0);
    }
    else
    {
      // rail SR
      Connection* connection_sr = new Connection(*connection_cur);
      connections_new->add(connection_sr);
    }
  }
  if (this->connections)
  {
    this->connections->removeAll(true);
    delete this->connections;
  }
  this->connections = connections_new;
  delete [] module_name_sr;
}

//---------------------------------------------------------------------------
void Instance::convertToSR()
{
  this->andTag(~TAG_ITEM_);
  this->orTag(TAG_ITEM_SR);
  if (this->connections)
  for (int connection_ind = 0; connection_ind < this->connections->num; connection_ind++)
  {
    Connection* connection_cur = this->connections->arr[connection_ind];
    if (connection_cur->nets)
    for (int net_ind = 0; net_ind < connection_cur->nets->num; net_ind++)
    {
      Net* net_cur = connection_cur->nets->arr[net_ind];
      net_cur->andTag(~TAG_ITEM_);
      net_cur->orTag(TAG_ITEM_SR);
    }
  }
}

