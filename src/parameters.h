#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

#include <stdio.h>
#include "sv_module.h"
#include "sv_parameter.h"

extern char* parameters_filename;
extern FILE* parameters_in;
extern int parameters_lineno;
extern int parameters_parse();
extern int parameters_lex();
extern int parameters_lex_destroy();
extern ModuleHashTable* parameters_module_hash_table;

#endif
