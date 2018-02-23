#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "str_utils.h"

//---------------------------------------------------------------------------
char* namecopy(char* name)
{
  char* name_copy = NULL;
  if (name)
  {
    int size = strlen(name) + 1;
    name_copy = new char[size];
    memcpy(name_copy, name, size*sizeof(char));
  }
  return name_copy;
}

//---------------------------------------------------------------------------
char* nameresize(char*& name, int size)
{
  char* name_new = new char[size+1];
  int len = strlen(name);
  if (len > size) len = size;
  memcpy(name_new, name, len*sizeof(char));
  name_new[len] = '\0';
  if (name)
  {
    delete [] name;
    name = name_new;
  }
  return name_new;
}

//---------------------------------------------------------------------------
char* name2pattern(const char* pattern, ...)
{
  va_list args;
  va_start(args, pattern);
  char* s = new char[10240*sizeof(char)];
  vsprintf(s, pattern, args);
  va_end(args);
  char* name_new = namecopy(s);
  delete [] s;
  return name_new;
}

//---------------------------------------------------------------------------
char* name2name_(char* name)
{
  char* s = namecopy(name);
  int i = 0;
  while (s[i] != '\0')
  {
    if ((s[i] == ' ') || (s[i] == '\t') || (s[i] == '\n') || (s[i] == '\r'))
      s[i] = SYMBOL_UNDERSCORE;
    i++;
  }
  return name;
}

//---------------------------------------------------------------------------
int indent(char*& str, int dir, int delta, char symbol)
{
  int len = 0;
  if (str != NULL) len = strlen(str);
  len = len + dir*delta;
  delete [] str;
  str = new char[len + 1];
  memset (str, symbol, len);
  str[len] = '\0';
  return len;
}

//---------------------------------------------------------------------------
int namesnum(const char* names)
{
  int count = 0;
  const char* name_start = names;
  while (name_start)
  {
    count++;
    name_start = strchr(name_start, SYMBOL_NAME_SEP);
    if (name_start) name_start++;
  }
  return count;
}

//---------------------------------------------------------------------------
char* names2name(const char* names, int index)
{
  int count = 0;
  char* name = NULL;
  const char* name_start = names;
  while (name_start && (count < index))
  {
    count++;
    name_start = strchr(name_start, SYMBOL_NAME_SEP);
    if (name_start) name_start++;
  }
  if (name_start)
  {
    int len = 0;
    const char* name_end = strchr(name_start, SYMBOL_NAME_SEP);
    if (name_end)
      len = name_end - name_start;
    else
      len = strlen(name_start);
    name = new char[len + 1];
    memcpy(name, name_start, len*sizeof(char));
    name[len] = '\0';
  }
  return name;
}

//---------------------------------------------------------------------------
int namesnamenum(const char* names, char* name)
{
  int count = 0;
  int name_index = 0;
  char* name_cur = NULL;
  while (name_cur = names2name(names, name_index++))
  {
    if (strcmp(name_cur, name) == 0)
      count++;
    delete [] name_cur;
  }
  return count;
}

