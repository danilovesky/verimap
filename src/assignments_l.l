%{
#include <unistd.h>
#include "messages.h"
#include "str_utils.h"
#include "sv_assignment.h"
#include "assignments_y.h"

#define YY_NO_UNISTD_H

#ifdef DEBUG_LEX
  #include <stdio.h>
  #define DEBUG_LEX_MESSAGE(msg) fprintf(stdout, msg)
#else
  #define DEBUG_LEX_MESSAGE(msg) // msg
#endif

char* assignments_filename = NULL;
%}

%option yylineno

WS                 [\n\r\t\b ]
NWS                [^\n\r\t\b= ]
COMMENT_C_OPEN     "/*"
COMMENT_C_CLOSE    "*/"
COMMENT_CPP_OPEN   "//"
COMMENT_CPP_CLOSE  \n
DIGIT              [0-9]
ALPHA              [a-zA-Z_]
SYMBOL             [%]
ID                 ({DIGIT}*{ALPHA}*{SYMBOL}*)+

%x COMMENT_C
%x COMMENT_CPP

%%
%{
int comment_depth = 0;
%}

{WS}+              {
  /* eat white spaces */
}

{COMMENT_C_OPEN}   {
  DEBUG_LEX_MESSAGE("COMMENT_C_OPEN\n");
  comment_depth = 1;
  BEGIN COMMENT_C;
}

<COMMENT_C>{COMMENT_C_OPEN} {
  DEBUG_LEX_MESSAGE("COMMENT_C_OPEN\n");
  comment_depth++;
}

<COMMENT_C>{COMMENT_C_CLOSE} {
  DEBUG_LEX_MESSAGE("COMMENT_C_CLOSE\n");
  comment_depth--;
  if (comment_depth == 0)
    BEGIN INITIAL;
}

<COMMENT_C>.|\n    {
  /* eat comments */
}

{COMMENT_CPP_OPEN} {
  DEBUG_LEX_MESSAGE("COMMENT_CPP_OPEN\n");
  BEGIN COMMENT_CPP;
}

<COMMENT_CPP>{COMMENT_CPP_CLOSE} {
  DEBUG_LEX_MESSAGE("COMMENT_CPP_CLOSE\n");
  BEGIN INITIAL;
}

<COMMENT_CPP>.     {
  /* eat comments */
}

{ID}               {
  DEBUG_LEX_MESSAGE("ID: "); DEBUG_LEX_MESSAGE(yytext); DEBUG_LEX_MESSAGE("\n");
  assignments_lval.string = namecopy(yytext);
  return ID;
}

.                  {
  DEBUG_LEX_MESSAGE(yytext); DEBUG_LEX_MESSAGE("\n");
  return yytext[0];
}

<<EOF>>            {
  DEBUG_LEX_MESSAGE("<EOF>\n");
  yyterminate();
  return 0;
}

%%

int yywrap()
{
  assignments_lineno = 0;
  return 1;
}

#ifdef FLEX_2_5_4a
  // Free the buffer which remains un-freed due to a bug in flex 2.5.4a (corrected in later versions)
  int assignments_lex_destroy()
  {
    yy_delete_buffer(yy_current_buffer);
    assignments_lineno = 0;
    yy_init = 1;
    return 1;
  }
#endif
