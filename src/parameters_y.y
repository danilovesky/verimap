%{
#include <stdio.h>
#include <stdlib.h>
#include "messages.h"
#include "sv_module.h"
#include "parameters.h"
#include "sv_parameter.h"

//#define DEBUG_YACC
#ifdef DEBUG_YACC
  #define DEBUG_YACC_MESSAGE(msg) fprintf(stderr, msg)
#else
  #define DEBUG_YACC_MESSAGE(msg) // msg
#endif

#define PARAMETER_IGNORING      '-'
#define PARAMETER_ACCUMULATING  '+'
#define PARAMETER_AVERAGING     '*'
#define PARAMETER_MINIMISING    '\\'
#define PARAMETER_MAXIMISING    '/'

void parameters_error(char* message)
{
  Error("%s in line %d in file <%s>", message, parameters_lineno, parameters_filename);
}

ModuleHashTable* parameters_module_hash_table;
StringArray* parameter_names;
int parameter_name_index;
%}

%start source_text

%union
{
  char* string;
  float number;
  StringArray* strings;
  ParameterArray* parameters;
}

%type <strings> names
%type <string> name
%type <parameters> parameters
%type <number> parameter
%token <string> ID
%token <number> PARAMETER
%token <number> EMPTY

%%

source_text
  : names_opt items_opt
    {
      DEBUG_YACC_MESSAGE("source_text : names_opt items_opt\n");
      if (parameter_names) 
        for (int name_index = 0; name_index < parameter_names->num; name_index++)
          delete [] parameter_names->arr[name_index];
      delete parameter_names;
    }	
;

names_opt
  :
    {
      DEBUG_YACC_MESSAGE("names_opt : \n");
    }
  | '[' names ']'
    {
      DEBUG_YACC_MESSAGE("names_opt : '[' names ']'\n");
    }
;

names
  : name
    {
      DEBUG_YACC_MESSAGE("names : name\n");
      parameter_names = new StringArray(1);
      $$ = parameter_names;
      $$->add($1);
    }
  | names ',' name
    {
      DEBUG_YACC_MESSAGE("names : names ',' name\n");
      $$ = $1;
      $$->add($3);
    }
;

name
  :
    {
      DEBUG_YACC_MESSAGE("name : \n");
      $$ = namecopy("-");
    }
  | ID
    {
      DEBUG_YACC_MESSAGE("name : ID\n");
      $$ = name2pattern("%s%c",$1, PARAMETER_IGNORING);
      delete [] $1;
    }
  | ID ':' '-'
    {
      DEBUG_YACC_MESSAGE("name : ID ':' '-'\n");
      $$ = name2pattern("%s%c",$1, PARAMETER_IGNORING);
      delete [] $1;
    }
  | ID ':' '+'
    {
      DEBUG_YACC_MESSAGE("name : ID ':' '+'\n");
      $$ = name2pattern("%s%c",$1, PARAMETER_ACCUMULATING);
      delete [] $1;
    }
  | ID ':' '*'
    {
      DEBUG_YACC_MESSAGE("name : ID ':' '*'\n");
      $$ = name2pattern("%s%c",$1, PARAMETER_AVERAGING);
      delete [] $1;
    }
  | ID ':' '\\'
    {
      DEBUG_YACC_MESSAGE("name : ID ':' '\\'\n");
      $$ = name2pattern("%s%c",$1, PARAMETER_MINIMISING);
      delete [] $1;
    }
  | ID ':' '/'
    {
      DEBUG_YACC_MESSAGE("name : ID ':' '/'\n");
      $$ = name2pattern("%s%c",$1, PARAMETER_MAXIMISING);
      delete [] $1;
    }
;

items_opt
  :
    {
      DEBUG_YACC_MESSAGE("items_opt : \n");
    }
  | items
    {
      DEBUG_YACC_MESSAGE("items_opt : items\n");
    }
;

items
  : item
    {
      DEBUG_YACC_MESSAGE("items : item\n");
    }
  | items item
    {
      DEBUG_YACC_MESSAGE("items : items item\n");
    }
;

item
  : ID parameters
    {
      DEBUG_YACC_MESSAGE("item : ID parameters\n");
      Module* module_mask = new Module(TAG_UNDEFINED, namecopy($1));
      delete [] $1;
      Module* module_cur = parameters_module_hash_table->find(module_mask);
      delete module_mask;
      if (module_cur)
      {
        module_cur->orTag(TAG_OBJ_STATISTICATED);
        module_cur->addParameters($2);
      }
      else
      {
        if ($2) 
          $2->removeAll(true);
      }
      delete $2;
    }
;

parameters
  : parameter
    {
      $$ = new ParameterArray(1);
      parameter_name_index = 0;
      char* parameter_name = NULL;
      int parameter_tag = TAG_PARAMETER_IGNORING;
      if (parameter_names)
      if (parameter_name_index < parameter_names->num)
      {
        parameter_name = namecopy(parameter_names->arr[parameter_name_index]);
        if ( parameter_name)
        {
          int tag_pos = strlen(parameter_name)-1;
          switch (parameter_name[tag_pos])
          {
            case PARAMETER_IGNORING:
              parameter_tag = TAG_OBJ_HIDDEN | TAG_PARAMETER_IGNORING;
              parameter_name[tag_pos] = '\0';
              break;
            case PARAMETER_ACCUMULATING:
              parameter_tag = TAG_OBJ_HIDDEN | TAG_PARAMETER_ACCUMULATING;
              parameter_name[tag_pos] = '\0';
              break;
            case PARAMETER_AVERAGING:
              parameter_tag = TAG_OBJ_HIDDEN | TAG_PARAMETER_AVERAGING;
              parameter_name[tag_pos] = '\0';
              break;
            case PARAMETER_MINIMISING:
              parameter_tag = TAG_OBJ_HIDDEN | TAG_PARAMETER_MINIMISING;
              parameter_name[tag_pos] = '\0';
              break;
            case PARAMETER_MAXIMISING:
              parameter_tag = TAG_OBJ_HIDDEN | TAG_PARAMETER_MAXIMISING;
              parameter_name[tag_pos] = '\0';
              break;
          }
        }
      }
      Parameter* parameter_new = new Parameter(parameter_tag, parameter_name, $1);
      $$->add(parameter_new);
    }
  | parameters ',' parameter
    {
      parameter_name_index++;
      char* parameter_name = NULL;
      int parameter_tag = TAG_PARAMETER_IGNORING;
      if (parameter_names)
      if (parameter_name_index < parameter_names->num)
      {
        parameter_name = namecopy(parameter_names->arr[parameter_name_index]);
        if ( parameter_name)
        {
          int tag_pos = strlen(parameter_name)-1;
          switch (parameter_name[tag_pos])
          {
            case PARAMETER_IGNORING:
              parameter_tag = TAG_OBJ_HIDDEN | TAG_PARAMETER_IGNORING;
              parameter_name[tag_pos] = '\0';
              break;
            case PARAMETER_ACCUMULATING:
              parameter_tag = TAG_OBJ_HIDDEN | TAG_PARAMETER_ACCUMULATING;
              parameter_name[tag_pos] = '\0';
              break;
            case PARAMETER_AVERAGING:
              parameter_tag = TAG_OBJ_HIDDEN | TAG_PARAMETER_AVERAGING;
              parameter_name[tag_pos] = '\0';
              break;
            case PARAMETER_MINIMISING:
              parameter_tag = TAG_OBJ_HIDDEN | TAG_PARAMETER_MINIMISING;
              parameter_name[tag_pos] = '\0';
              break;
            case PARAMETER_MAXIMISING:
              parameter_tag = TAG_OBJ_HIDDEN | TAG_PARAMETER_MAXIMISING;
              parameter_name[tag_pos] = '\0';
              break;
          }
        }
      }
      Parameter* parameter_new = new Parameter(parameter_tag, parameter_name, $3);
      $$->add(parameter_new);
      $$ = $1;
    }
;

parameter
  :
    {
      DEBUG_YACC_MESSAGE("parameter : \n");
      $$ = -1.0;
    }
  | PARAMETER
    {
      DEBUG_YACC_MESSAGE("parameter : PARAMETER\n");
      $$ = $1;
    }
;

%%
