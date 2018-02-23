#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include <stdio.h>
#include "sv_object.h"

extern char* objects_filename;
extern FILE* objects_in;
extern int objects_lineno;
extern int objects_parse();
extern int objects_lex();
extern int objects_lex_destroy();
extern VerilogObjectArray* objects_objects;

#endif
