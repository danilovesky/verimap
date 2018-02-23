#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <string.h>
#include "str_utils.h"
#include "darray.h"
#include "hash.h"

class Object;
typedef darray <Object*> ObjectArray;

#define TAG_UNDEFINED         0x00000000
#define TAG_ALL               0xFFFFFFFF

//---------------------------------------------------------------------------
class Object
{
  protected:
    unsigned int tag;
    char* name;

  public:
    Object(int tag = TAG_UNDEFINED, char* name = NULL)
    {
      this->setTag(tag);
      this->name = NULL;
      this->setName(name);
    }

    Object(const Object& object)
    {
      this->setTag(object.tag);
      this->name = NULL;
      this->setName(namecopy(object.name));
    }

    ~Object()
    {
      delete [] this->name; this->name = NULL;
    }

    virtual inline void setTag(int tag)
    {
      this->tag = tag;
    }

    inline int getTag()
    {
      return tag;
    }

    inline void orTag(int tag)
    {
      this->setTag(this->tag | tag);
    }

    inline void andTag(int tag)
    {
      this->setTag(this->tag & tag);
    }

    inline bool testTag(int tag)
    {
      return ((this->tag & tag) == tag);
    }

    virtual inline void setName(char* name)
    {
      delete [] this->name;
      this->name = name;
    }

    inline char* getName()
    {
      return this->name;
    }

    inline int operator==(Object& object)
    {
      return (strcmp(this->name, object.getName()) == 0);
    }

    static int compareByMask(const void* mask, const void* object)
    {
      Object* obj_mask = *(Object**) mask;
      Object* obj_object = *(Object**) object;
      if (obj_mask->testTag(obj_object->tag))
        if (obj_mask->name && obj_object->name)
          if (strcmp(obj_mask->name, obj_object->name) == 0)
            return 0;
      return -1;
    }

    unsigned getHashIndex()
    {
      return hash_string(this->name, 0);
    }
};

#endif
