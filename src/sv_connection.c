#include "messages.h"
#include "sv_connection.h"
#include "sv_object.h"
#include "sv_port.h"

//---------------------------------------------------------------------------
Connection::Connection(int tag, char* name, NetArray* nets) : VerilogObject(tag, name)
{
  this->nets = nets;
}

//---------------------------------------------------------------------------
Connection::Connection(const Connection& connection) : VerilogObject(connection)
{
  this->nets = NULL;
  if (connection.nets)
  {
    this->nets = new NetArray(connection.nets->num);
    for (int net_index = 0; net_index < connection.nets->num; net_index++)
    {
      Net* net_new = new Net(*connection.nets->arr[net_index]);
      this->addNet(net_new);
    }
  }
}

//---------------------------------------------------------------------------
Connection::~Connection()
{
  this->clean();
  delete this->nets; this->nets = NULL;
}

//---------------------------------------------------------------------------
void Connection::clean()
{
  if (this->nets)
  for (int net_index = 0; net_index < this->nets->num; net_index++)
  {
    Net* net_cur = this->nets->arr[net_index];
    if (net_cur)
      if (net_cur->getContainer() == NULL)
      {
        delete net_cur; 
        this->nets->arr[net_index] = NULL;
      }
  }
}

//---------------------------------------------------------------------------
char* Connection::genFullName()
{
  char* connection_full_name = NULL;
  char* net_names = NULL;
  if (this->nets)
  if (this->nets->num > 0)
  {
    for (int net_ind = 0; net_ind < this->nets->num; net_ind++)
    {
      Net* net_cur = this->nets->arr[net_ind];
      if (net_names)
      {
        char* net_names_old = net_names;
        char* net_name = NULL;
        if (net_cur)
          net_name = net_cur->genFullName();
        else
          net_name = namecopy("");
        net_names = name2pattern("%s, %s", net_names_old, net_name);
        delete [] net_name;
        delete [] net_names_old;
      }
      else
      {
        if (net_cur)
          net_names = net_cur->genFullName();
        else
          net_names = namecopy("");
      }
    }
    if (this->nets->num > 1)
    {
      char* net_names_old = net_names;
      net_names = name2pattern("{%s}", net_names_old);
      delete [] net_names_old;
    }
  }
  if (!net_names)
    net_names = namecopy(" ");
  if (this->name)
  {
    connection_full_name = name2pattern(PATTERN_CONNECTION_FULL_NAME, this->name, net_names);
    delete [] net_names;
  }
  else
    connection_full_name = net_names;
  return connection_full_name;
}

//---------------------------------------------------------------------------
Net* Connection::getNet(char* net_name, int net_index)
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
bool Connection::replaceNet(Net* net_old, Net* net_new, int copy)
{
  bool result = false;
  if (this->nets)
  for (int net_ind = 0; net_ind < this->nets->num; net_ind++)
  {
  	if (copy == 0)
  	{
      if (this->nets->arr[net_ind] == net_old)
      {
        this->nets->arr[net_ind] = net_new;
        result = true;
      }
    }
    else
    {
      if (strcmp(this->nets->arr[net_ind]->getName(), net_old->getName()) == 0)
      {
      	delete this->nets->arr[net_ind];
        this->nets->arr[net_ind] = net_new;
        result = true;
      }
    }
  }
  return result;
}

//---------------------------------------------------------------------------
void Connection::convertToDR(int polarity)
{
  this->setName(name2pattern(PATTERN_NET_DR_RAIL, this->name, polarity));
  if (this->nets)
  for (int net_ind = 0; net_ind < this->nets->num; net_ind++)
  {
    Net* net_cur = this->nets->arr[net_ind];
    if (net_cur)
      net_cur->convertToDR(polarity);
  }
}

//---------------------------------------------------------------------------
void Connection::addNet(Net* net, int ind)
{
  if (!this->nets)
    this->nets = new NetArray(1);
  if (ind < 0)
    this->nets->add(net);
  else
    this->nets->addAt(ind, net);
}

