#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "param.h"
#include "messages.h"

int param_bool(int argc, char **argv, int *i, char *s)
{
  if (strcmp(s, &argv[*i][1]))
    return 0;
  (*i)++;
  if (*i >= argc)
    *i = 0;
  return 1;
}

int param_integer(int argc, char **argv, int *i, char *s, int *value)
{
  int n, tmp;
  char *p;
  n = strlen(s);
  if (strncmp(&argv[*i][1], s, n))
    return 0;
  if (strlen(argv[*i]) == (n + 1))
  {
    *value = -1;
    (*i)++;
    if (*i >= argc)
      *i = 0;
    return 1;
  }
  if (!isdigit(argv[*i][n + 1]))
    return 0;
  tmp = (int) strtol(&argv[*i][n + 1], &p, 10);
  if ((*p) != '\0')
    return 0;
  (*i)++;
  if (*i >= argc)
    *i = 0;
  *value = tmp;
  return 1;
}

int param_float(int argc, char **argv, int *i, char *s, float *value)
{
  int n;
  char *p;
  float tmp;

  n = strlen(s);
  if (strncmp(&argv[*i][1], s, n))
    return 0;
  if (strlen(argv[*i]) == (n + 1))
  {
    *value = -1.0;
    (*i)++;
    if (*i >= argc)
      *i = 0;
    return 1;
  }
  if (!isdigit(argv[*i][n + 1]) && (argv[*i][n + 1] != '.'))
    return 0;
  tmp = (float) strtod(&argv[*i][n + 1], &p);
  if ((*p) != '\0')
    return 0;
  (*i)++;
  if (*i >= argc)
    *i = 0;
  *value = tmp;
  return 1;
}

int param_string(int argc, char **argv, int *i, char *s, char **str)
{
  if (strcmp(s, &argv[*i][1]))
    return 0;
  (*i)++;
  if ((*i >= argc) || ((argv[*i][0] == '-') && (strlen(argv[*i]) > 1)))
  {
    Error("expected string for option -%s", s);
  }
  delete [] (*str);
  *str = new char[strlen(argv[*i])+1];
  strcpy(*str, argv[*i]);

  (*i)++;
  if (*i >= argc)
    *i = 0;
  return 1;
}
