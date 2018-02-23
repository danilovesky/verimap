%{
#include <stdio.h>
#include <stdlib.h>
#include "messages.h"
#include "objects.h"
#include "sv_object.h"

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

void objects_error(char* message)
{
  Error("%s in line %d in file <%s>", message, objects_lineno, objects_filename);
}

VerilogObjectArray* objects_objects;
%}

%start source_text

%union
{
  VerilogObjectArray* objects;
  VerilogObject* object;
  char* string;
}

%token <string> ID
%type <objects> source_text
%type <object> object

%%

source_text
  :
    {
      DEBUG_YACC_MESSAGE("source_text : \n");
      $$ = objects_objects;
    }
  | source_text object
    {
      DEBUG_YACC_MESSAGE("source_text : source_text object\n");
      $$->add($2);
    }
;

object
  : ID
    {
      DEBUG_YACC_MESSAGE("object : ID\n");
      $$ = new VerilogObject(TAG_UNDEFINED, $1);
    }
;

%%
