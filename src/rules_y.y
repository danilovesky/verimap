%{
#include <stdio.h>
#include <stdlib.h>
#include "messages.h"
#include "rules.h"
#include "sv_rule.h"

#define FLAG_SYMBOL_YES     'y'
#define FLAG_SYMBOL_NO      'n'
#define FLAG_POS_FF          0
#define FLAG_POS_CD          1
#define FLAG_POS_PDR         2
#define FLAG_POS_NDR         3

#ifdef DEBUG_YACC
  #define DEBUG_YACC_MESSAGE(msg) fprintf(stdout, msg)
#else
  #define DEBUG_YACC_MESSAGE(msg) // msg
#endif

void rules_error(char* message)
{
  Error("%s in line %d in file <%s>", message, rules_lineno, rules_filename);
}

RuleArray* rules_rules;
%}

%start source_text

%union
{
  RuleArray* rules;
  Rule* rule;
  char* string;
}

%token <string> ID
%type <rules> source_text
%type <rule> item

%%

source_text
  :
    {
      DEBUG_YACC_MESSAGE("source_text : \n");
      $$ = rules_rules;
    }
  | source_text item
    {
      DEBUG_YACC_MESSAGE("source_text : source_text item\n");
      $$->add($2);
    }
;

item
  : ID ID ID ID ID ID ID ID
    {
      DEBUG_YACC_MESSAGE("item : ID ID ID ID ID ID ID ID\n");
      Message("  transformation rule \"%s %s %s %s %s %s %s\" is added", $1, $2, $3, $4, $5, $6, $7);
      char* flags = $8;
      int tag = TAG_UNDEFINED;
      int len = strlen(flags);

      if (len > FLAG_POS_FF)
        if (flags[FLAG_POS_FF] == FLAG_SYMBOL_YES)
          tag |= TAG_MODULE_FF;

      if (len > FLAG_POS_CD)
        if (flags[FLAG_POS_CD] == FLAG_SYMBOL_YES)
          tag |= TAG_MODULE_CD;

      if (len > FLAG_POS_PDR)
        if (flags[FLAG_POS_PDR] == FLAG_SYMBOL_YES)
          tag |= TAG_MODULE_PDR;

      if (len > FLAG_POS_NDR)
        if (flags[FLAG_POS_NDR] == FLAG_SYMBOL_YES)
          tag |= TAG_MODULE_NDR;
      delete [] $8;
      $$ = new Rule(tag, $1, $2, $3, $4, $5, $6, $7);
    }
;

%%

