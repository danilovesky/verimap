#include "sv_delay.h"
#include "sv_net.h"
#include "str_utils.h"
#include "messages.h"

//---------------------------------------------------------------------------
Net::Net(int tag, char* name, int index, int depth, int layer, Delay* delay, 
  InstanceArray* preset, InstanceArray* postset, Port* container) : VerilogObject(tag, name)
{
  this->index = index;
  this->depth = depth;
  this->layer = layer;
  this->delay = delay;
  this->preset = preset;
  this->postset = postset;
  this->container = container;
}

//---------------------------------------------------------------------------
Net::Net(const Net& net) : VerilogObject(net)
{
  this->index = net.index;
  this->depth = net.depth;
  this->layer = net.layer;
  this->delay = NULL;
  if (net.delay)
    this->delay = new Delay(*net.delay);
  this->preset = NULL; // net.preset;
  this->postset = NULL; // net.postset;
  this->container = NULL;
}

//---------------------------------------------------------------------------
Net::~Net()
{
  delete this->delay; this->delay = NULL;
  delete this->preset;  this->preset = NULL;
  delete this->postset;  this->postset = NULL;
}


//---------------------------------------------------------------------------
void Net::setIndex(int index)
{
  this->index = index;
}

//---------------------------------------------------------------------------
int Net::getIndex()
{
  return this->index;
}

//---------------------------------------------------------------------------
void Net::setDepth(int depth)
{
  this->depth = depth;
}

//---------------------------------------------------------------------------
int Net::getDepth()
{
  return this->depth;
}

//---------------------------------------------------------------------------
void Net::setLayer(int layer)
{
  this->layer = layer;
}

//---------------------------------------------------------------------------
int Net::getLayer()
{
  return this->layer;
}

//---------------------------------------------------------------------------
void Net::addPreset(Instance* instance)
{
   if (!this->preset)
     this->preset = new InstanceArray(1);
   if (this->preset->locate(instance) < 0)
     this->preset->add(instance);
}

//---------------------------------------------------------------------------
void Net::removePreset(Instance* instance)
{
  if (this->preset)
    this->preset->remove(instance, false);
}

//---------------------------------------------------------------------------
void Net::addPostset(Instance* instance)
{
   if (!this->postset)
     this->postset = new InstanceArray(1);
   if (this->postset->locate(instance) < 0)
     this->postset->add(instance);
}

//---------------------------------------------------------------------------
void Net::removePostset(Instance* instance)
{
  if (this->postset)
    this->postset->remove(instance, false);
}

//---------------------------------------------------------------------------
void Net::setContainer(Port* container)
{
  this->container = container;
}

//---------------------------------------------------------------------------
Port* Net::getContainer()
{
  return this->container;
}

//---------------------------------------------------------------------------
char* Net::genFullName()
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
    name_full = name2pattern(PATTERN_NET_FULL_NAME, name_escape, this->index);
    delete [] name_escape;
  }
  return name_full;
}

//---------------------------------------------------------------------------
char* Net::genLabelName()
{
  if (this->index < 0)
    return namecopy(this->name);
  else
    return name2pattern(PATTERN_NET_LABEL, this->name, this->index);
}

//---------------------------------------------------------------------------
char* Net::genPearlName()
{
  char* name_pearl = NULL;
  char* name_escape = NULL;

  if (this->isEscape())
  {
    name_escape = new char [2 * strlen(this->name) + 2];
    int j = -1;
    for (int i = 1; i < strlen(this->name); i++)
    {
      if (strchr(PATTERN_ESCAPE, this->name[i]))
      {
        j++;
        name_escape[i+j-1] = SYMBOL_ESCAPE;
        name_escape[i+j] = this->name[i];
      }
      else
      {
        name_escape[i+j] = this->name[i];
      }
      name_escape[i+j+1] = '\0';
    }
  }
  else
    name_escape = namecopy(this->name);

  if (this->index < 0)
    name_pearl = name_escape;
  else
  {
    name_pearl = name2pattern(PATTERN_NET_FULL_NAME, name_escape, this->index);
    delete [] name_escape;
  }

  return name_pearl;
}

//---------------------------------------------------------------------------
void Net::convertToDR(int polarity)
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


//---------------------------------------------------------------------------
void Net::convertToSR()
{
  char* name_new = namecopy(this->name);
  if (name_new)
  {
  	int len = strlen(name_new);
  	if ( (len > 2 ) && (name_new[len-2] == SYMBOL_NET_UNDERSCORE)
  	  && ( (name_new[len-1] == SYMBOL_NET_0) || (name_new[len-1] == SYMBOL_NET_1) ) )
		{
		  name_new[len-2] = '\0';
      this->setName(name_new);
		}
  }	
}

//---------------------------------------------------------------------------
int Net::compareByMask(const void* mask, const void* object)
{
  Net* net_mask = *(Net**) mask;
  Net* net_object = *(Net**) object;
  if (net_mask->testTag(net_object->tag))
    if (net_mask->index == net_object->index)
      if (net_mask->name && net_object->name)
        if (strcmp(net_mask->name, net_object->name) == 0)
          return 0;
  return -1;
}
