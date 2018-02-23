#ifndef _RULES_H_
#define _RULES_H_

#include <stdio.h>
#include "sv_rule.h"

extern char* rules_filename;
extern FILE* rules_in;
extern int rules_lineno;
extern int rules_parse();
extern int rules_lex();
extern int rules_lex_destroy();
extern RuleArray* rules_rules;

#endif
