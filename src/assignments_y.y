%{
#include <stdio.h>
#include <stdlib.h>
#include "messages.h"
#include "assignments.h"
#include "sv_assignment.h"

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

void assignments_error(char* message)
{
  Error("%s in line %d in file <%s>", message, assignments_lineno, assignments_filename);
}

AssignmentArray* assignments_assignments;
%}

%start source_text

%union
{
  AssignmentArray* assignments;
  Assignment* assignment;
  char* string;
}

%token <string> ID
%type <assignments> source_text
%type <assignment> item

%%

source_text
  :
    {
      DEBUG_YACC_MESSAGE("source_text : \n");
      $$ = assignments_assignments;
    }
  | source_text item
    {
      DEBUG_YACC_MESSAGE("source_text : source_text item\n");
      $$->add($2);
    }
;

item
  : ID '=' ID
    {
      DEBUG_YACC_MESSAGE("item : ID '=' ID\n");
      $$ = new Assignment(TAG_UNDEFINED, $1, $3);
    }
;

%%


