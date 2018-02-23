#ifndef _PARAM_H_
#define _PARAM_H_

extern "C" int param_bool(int, char **, int *, char *);
extern "C" int param_integer(int, char **, int *, char *, int *);
extern "C" int param_float(int, char **, int *, char *, float *);
extern "C" int param_string(int, char **, int *, char *, char **);

#endif
