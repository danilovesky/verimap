#ifndef _SVERILOG_H_
#define _SVERILOG_H_

#include <stdio.h>
#include "sv_module.h"

extern char* sverilog_filename;
extern FILE* sverilog_in;
extern int sverilog_lineno;
extern int sverilog_parse();
extern int sverilog_lex();
extern int sverilog_lex_destroy();
extern ModuleArray* sverilog_modules;

#endif

