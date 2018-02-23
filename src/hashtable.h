#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include "hash.h"
#include "darray.h"

#define DEFAULT_SIZE_POWER 10

//---------------------------------------------------------------------------
// stores TYPE*
template <class TYPE> class HashTable
{
  public:
    ub4 size_power;
    struct HashTableItem
    {
      TYPE* item;
      HashTableItem* next;
      HashTableItem(TYPE* item, HashTableItem* next)
      {
        this->item = item;
        this->next = next;
      }
    }** arr;

    HashTable(ub4 size_power = DEFAULT_SIZE_POWER);
    ~HashTable();
    void clean(int destroy = 0);
    void add(TYPE* key);
    TYPE* find(TYPE* key);
    void remove(TYPE* key);
};

//---------------------------------------------------------------------------
template <class TYPE>
HashTable <TYPE>::HashTable(ub4 size_power)
{
  this->size_power = size_power;
  this->arr = new HashTableItem* [HASH_SIZE(size_power)];
  memset(this->arr, 0, HASH_SIZE(size_power)*sizeof(HashTableItem*));
}

//---------------------------------------------------------------------------
template <class TYPE>
HashTable <TYPE>::~HashTable()
{
  clean();
  delete [] this->arr;
}

//---------------------------------------------------------------------------
template <class TYPE>
void HashTable <TYPE>::clean(int destroy)
{
  ub4 i;
  HashTableItem* buf;

  for (i = 0; i < HASH_SIZE(size_power); i++)
  {
    while (arr[i])
    {
       buf = arr[i];
       this->arr[i] = this->arr[i]->next;
       if (destroy)
         delete buf->item;
       delete buf;
    }
  }
}

//---------------------------------------------------------------------------
template <class TYPE>
void HashTable <TYPE>::add(TYPE* key)
{
  ub4 ind = key->getHashIndex() & HASH_MASK(size_power);
  this->arr[ind] = new HashTableItem(key, this->arr[ind]);
}

//---------------------------------------------------------------------------
template <class TYPE>
TYPE* HashTable <TYPE>::find(TYPE* key)
{
  ub4 ind = key->getHashIndex() & HASH_MASK(size_power);
  HashTableItem* p = this->arr[ind];
  while (p)
  {
    if (*key == *(p->item))
      return p->item;
    else
      p = p->next;
  }
  return NULL;
}

//---------------------------------------------------------------------------
template <class TYPE>
void HashTable <TYPE>::remove(TYPE* key)
{
  ub4 ind = key->getHashIndex() & HASH_MASK(size_power);
  HashTableItem **p = &(this->arr[ind]);
  HashTableItem *buf;
  while (*p)
  {
    if (*key == *((*p)->item))
    {
      buf = *p;
      *p = (*p)->next;
      delete buf;
      return;
    }
    else
      p=&((*p)->next);
  }
}

#endif

