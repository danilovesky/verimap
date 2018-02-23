#ifndef _DARRAY_H_
#define _DARRAY_H_

#include <stdlib.h>
#include <string.h>

//---------------------------------------------------------------------------
#define DARRAY_INIT_SIZE 10
//#define INCREASE_SIZE(size) (size = ((size+1)*2))
#define INCREASE_SIZE(size) (size = ((size+1)*4)/3)

//---------------------------------------------------------------------------
template <class TYPE> class darray
{
  protected:
    unsigned size;

    void resize(unsigned new_size);
  public:
    TYPE* arr;
    unsigned num;

    darray();
    darray(unsigned size);
    darray(darray <TYPE>& da);
    ~darray();
    TYPE& operator[](unsigned i);
    void add(TYPE item);
    void addAt(unsigned index, TYPE item);
    void addArr(darray <TYPE>& da);
    void remove(TYPE item, unsigned clear);
    void removeAll(unsigned clear);
    int locate(TYPE item);
    int find(TYPE item, int index, int (*compare)(const void*, const void*));
    void sort(int (*compare)(const void*, const void*));
};

typedef darray <int*> IntArray;
typedef darray <double*> DoubleArray;
typedef darray <char*> StringArray;

//---------------------------------------------------------------------------
template <class TYPE>
darray <TYPE>::darray()
{
  this->size = DARRAY_INIT_SIZE;
  this->arr = this->size ? new TYPE[this->size] : NULL;
  this->num = 0;
}

//---------------------------------------------------------------------------
template <class TYPE>
darray <TYPE>::darray(unsigned size)
{
  this->size = size;
  this->num = 0;
  if (this->size > 0)
    this->arr = new TYPE[this->size];
  else
    this->arr = NULL;
}

//---------------------------------------------------------------------------
template <class TYPE>
darray <TYPE>::darray(darray <TYPE>& da)
{
  this->size = da.size;
  // if size is 0 then memory is not allocated
  this->num = da.num;
  if (size > 0)
    this->arr = new TYPE[size];
  else
    this->arr = NULL;
  memcpy(this->arr, da.arr, this->num*sizeof(TYPE));
}

//---------------------------------------------------------------------------
template <class TYPE>
darray <TYPE>::~darray()
{
  delete [] this->arr;
}

//---------------------------------------------------------------------------
template <class TYPE>
void darray <TYPE>::resize(unsigned size)
{
  this->size = size;
  TYPE* arr_new = NULL;
  if (this->size > 0)
    arr_new = new TYPE[this->size];
  if (this->arr && arr_new)
    memcpy(arr_new, this->arr, this->num*sizeof(TYPE));
  delete [] this->arr;
  this->arr = arr_new;
}

//---------------------------------------------------------------------------
template <class TYPE>
TYPE& darray <TYPE>::operator[](unsigned i)
{
  return this->arr[i];
}

//---------------------------------------------------------------------------
template <class TYPE>
void darray <TYPE>::add(TYPE item)
{
  if (this->num >= this->size)
  {
    INCREASE_SIZE(this->size);
    this->resize(this->size);
  }
  this->arr[this->num] = item;
  this->num++;
}

//---------------------------------------------------------------------------
template <class TYPE>
void darray <TYPE>::addAt(unsigned index, TYPE item)
{
  if (index >= this->num)
    this->add(item);
  else
  {
    if (this->num >= this->size)
    {
      INCREASE_SIZE(this->size);
      this->resize(this->size);
    }
    memmove(this->arr+index+1, this->arr+index, (this->num-index)*sizeof(TYPE));
    this->arr[index] = item;
    this->num++;
  }
}

//---------------------------------------------------------------------------
template <class TYPE>
void darray <TYPE>::remove(TYPE item, unsigned clear)
{
  for (unsigned i = 0; i < this->num; i++)
  {
    if (this->arr[i] == item)
    {
      if (clear != 0)
        delete this->arr[i];
      for (unsigned j = i; j < this->num-1; j++)
        this->arr[j] = this->arr[j+1];
      i--;
      this->num--;
    }
  }
}

//---------------------------------------------------------------------------
template <class TYPE>
void darray <TYPE>::removeAll(unsigned clear)
{
  if (clear != 0)
  for (unsigned i = 0; i < this->num; i++)
  {
    if (this->arr[i])
      delete this->arr[i];
  }
  this->num = 0;
}

//---------------------------------------------------------------------------
template <class TYPE>
void darray <TYPE>::addArr(darray <TYPE>& da)
{
  this->provide(da.num);
  memcpy(this->arr+this->num, da.arr, da.num*sizeof(TYPE));
  this->num += da.num;
}

//---------------------------------------------------------------------------
template <class TYPE>
int darray <TYPE>::locate(TYPE item)
{
  for (unsigned i = 0; i < this->num; i++)
  {
    if (this->arr[i] == item)
      return i;
  }
  return -1;
}

//---------------------------------------------------------------------------
template <class TYPE>
int darray <TYPE>::find(TYPE item, int index, int (*compare)(const void*, const void*))
{
  for (unsigned i = index; i < this->num; i++)
  {
    if (compare (&item, &(this->arr[i])) == 0)
      return i;
  }
  return -1;
}

//---------------------------------------------------------------------------
template <class TYPE>
void darray <TYPE>::sort(int (*compare)(const void*, const void*))
{
  qsort(this->arr, this->num, sizeof(TYPE), compare);
}

#endif


