#ifndef _ASSIGNMENTS_H_
#define _ASSIGNMENTS_H_

#include <stdio.h>
#include "sv_assignment.h"

extern char* assignments_filename;
extern FILE* assignments_in;
extern int assignments_lineno;
extern int assignments_parse();
extern int assignments_lex();
extern int assignments_lex_destroy();
extern AssignmentArray* assignments_assignments;

#endif
