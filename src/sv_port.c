#include "str_utils.h"
#include "messages.h"
#include "sv_object.h"
#include "sv_port.h"
#include "sv_range.h"
#include "sv_delay.h"
#include "sv_net.h"

//---------------------------------------------------------------------------
Port::Port(int tag, char* name, Range* dimension, Range* range, Delay* delay) : VerilogObject(tag, name)
{
  this->dimension = dimension;
  this->nets = NULL;
  if (range)
  {
    this->nets = new NetArray(range->getWidth());
    for (int net_index = range->getFrom(); net_index != range->getTo() + range->getInc(); net_index += range->getInc())
    {
      Delay* delay_new = NULL;
      if (delay)
        delay_new = new Delay(*delay);
      Net* net_new = new Net(this->tag, namecopy(this->name), net_index, -1, -1, delay_new, NULL, NULL, this);
      this->addNet(net_new);
    }
  }
  else
  {
    Delay* delay_new = NULL;
    if (delay)
      delay_new = new Delay(*delay);
    Net* net_new = new Net(this->tag, namecopy(this->name), -1, -1, -1, delay_new, NULL, NULL, this);
    this->addNet(net_new);
  }
}

//---------------------------------------------------------------------------
Port::Port(const Port& port) : VerilogObject(port)
{
  this->dimension = NULL;
  if (port.dimension)
    this->dimension = new Range(*port.dimension);

  this->nets = NULL;
  if (port.nets)
  {
    this->nets = new NetArray(port.nets->num);
    for (int net_index = 0; net_index < port.nets->num; net_index ++)
    {
      Net* net_new = new Net(*port.nets->arr[net_index]);
      net_new->setContainer(this);
      this->addNet(net_new);
    }
  }
}

//---------------------------------------------------------------------------
Port::~Port()
{
  this->clean();
  delete this->nets; this->nets = NULL;
  delete this->dimension; this->dimension = NULL;
}

//---------------------------------------------------------------------------
void Port::clean()
{
  if (this->nets) this->nets->removeAll(true);
}

//---------------------------------------------------------------------------
void Port::setTag(int tag)
{
  this->tag = tag;
  if (this->nets)
  for (int net_index = 0; net_index < this->nets->num; net_index++)
    this->nets->arr[net_index]->setTag(tag);
}

//---------------------------------------------------------------------------
void Port::setName(char* name)
{
  VerilogObject::setName(name);
  if (this->nets)
  for (int net_index = 0; net_index < this->nets->num; net_index++)
    this->nets->arr[net_index]->setName(namecopy(this->name));
}

//---------------------------------------------------------------------------
void Port::setDimension(Range* dimension)
{
  delete this->dimension;
  this->dimension = dimension;
}

//---------------------------------------------------------------------------
Range* Port::getDimension()
{
  return this->dimension;
}

//---------------------------------------------------------------------------
char* Port::genFullName()
{
  char* name_full = NULL;
  if (this->nets->num > 1)
  {
    char* name_escape = NULL;
    if (this->isEscape())
      name_escape = name2pattern(PATTERN_FULL_NAME_ESCAPE, this->name);
    else
      name_escape = namecopy(this->name);
    name_full = name2pattern(PATTERN_PORT_FULL_NAME, this->nets->arr[0]->getIndex(), this->nets->arr[this->nets->num-1]->getIndex(), name_escape);
    delete [] name_escape;
  }
  else
    name_full = this->nets->arr[0]->genFullName();
  return name_full;
}

//---------------------------------------------------------------------------
void Port::addNet(Net* net, int ind)
{
  if (!this->nets)
    this->nets = new NetArray(1);
  net->setContainer(this);
  if (ind < 0)
    this->nets->add(net);
  else
    this->nets->addAt(ind, net);
}

//---------------------------------------------------------------------------
Net* Port::getNet(char* net_name, int net_index)
{
  if (this->nets)
  {
    Net* net_mask = new Net(TAG_ALL, namecopy(net_name), net_index);
    int net_cur_index = this->nets->find(net_mask, 0, Net::compareByMask);
    delete net_mask;
    if (net_cur_index >= 0)
      return this->nets->arr[net_cur_index];
  }
  return NULL;
}


//---------------------------------------------------------------------------
void Port::convertToDR(int polarity)
{
  char* name_new = NULL;
  if (strcmp(NAME_NET_VDD, this->name) == 0)
    switch (polarity)
    {
      case 0:
        name_new = namecopy(NAME_NET_GND_DR);
        break;
      case 1:
        name_new = namecopy(NAME_NET_VDD_DR);
        break;
    }
  else
  if (strcmp(NAME_NET_GND, this->name) == 0)
    switch (polarity)
    {
      case 0:
        name_new = namecopy(NAME_NET_VDD_DR);
        break;
      case 1:
        name_new = namecopy(NAME_NET_GND_DR);
        break;
    }
  else
    name_new = name2pattern(PATTERN_NET_DR_RAIL, this->name, polarity);
  this->setName(name_new);
}

