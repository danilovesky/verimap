%{
#include <unistd.h>
#include "messages.h"
#include "str_utils.h"
#include "sv_circuit.h"
#include "sverilog_y.h"

#define YY_NO_UNISTD_H

#ifdef DEBUG_LEX
  #include <stdio.h>
  #define DEBUG_LEX_MESSAGE(msg) fprintf(stdout, msg)
#else
  #define DEBUG_LEX_MESSAGE(msg) // msg
#endif

char* sverilog_filename;
%}

%option yylineno

WS                 [\n\r\t\b ]
NWS                [^\n\r\t\b ]
COMMENT_C_OPEN     "/*"
COMMENT_C_CLOSE    "*/"
COMMENT_CPP        "//"
DIGIT              [0-9]
ALPHA              [a-zA-Z_]
ALPHANUM           [a-zA-Z_0-9]
INUMBER            {DIGIT}{DIGIT}*
RNUMBER1           {DIGIT}*\.{DIGIT}+
RNUMBER2           {DIGIT}+\.{DIGIT}*
RNUMBER            {RNUMBER1}|{RNUMBER2}
VDD                "1'b1"
GND                "1'b0"
ID_STANDART        {ALPHA}+({DIGIT}*{ALPHA}*)*
ID_ESCAPE          "\\"{NWS}+
ID                 {ID_STANDART}|{ID_ESCAPE}|{VDD}|{GND}
KEY_MODULE         module
KEY_ENDMODULE      endmodule
KEY_INPUT          input
KEY_OUTPUT         output
KEY_INOUT          inout
KEY_REG            reg
KEY_WIRE           wire
KEY_TRIREG         trireg
KEY_PARAMETER      parameter
KEY_ASSIGN         assign
KEY_IF             if
KEY_ELSE           else

KEY_SPECIFY        specify
KEY_ENDSPECIFY     endspecify

PRE_DEFINE         \`define
PRE_TIMESCALE      \`timescale
PRE_CELLDEFINE     \`celldefine
PRE_ENDCELLDEFINE  \`endcelldefine
PRE_DELAY_MODE_PATH \`delay_mode_path
PRE_IFDEF          \`ifdef
PRE_ENDIF          \`endif


%x COMMENT_C
%x IGNORE_LINE
%x IFDEF
%x SPECIFY

%%
%{
int comment_depth = 0;
int ifdef_depth = 0;
int specify_depth = 0;
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

{COMMENT_CPP}      {
  DEBUG_LEX_MESSAGE("COMMENT_CPP\n");
  BEGIN IGNORE_LINE;
}

<IGNORE_LINE>.     {
  /* eat line */
}

<IGNORE_LINE>\n    {
  DEBUG_LEX_MESSAGE("IGNORE_LINE\n");
  BEGIN INITIAL;
}

{KEY_IF}           {
  BEGIN IGNORE_LINE;
}

{KEY_ELSE}         {
  BEGIN IGNORE_LINE;
}

{KEY_ASSIGN}       {
  BEGIN IGNORE_LINE;
}

{PRE_TIMESCALE}    {
  BEGIN IGNORE_LINE;
}

{PRE_CELLDEFINE}   {
  BEGIN IGNORE_LINE;
}

{PRE_ENDCELLDEFINE} {
  BEGIN IGNORE_LINE;
}

{PRE_DEFINE}       {
  BEGIN IGNORE_LINE;
}

{PRE_DELAY_MODE_PATH} {
  BEGIN IGNORE_LINE;
}

{KEY_TRIREG}       {
  BEGIN IGNORE_LINE;
}

{PRE_IFDEF}        {
  DEBUG_LEX_MESSAGE("PRE_IFDEF\n");
  ifdef_depth = 1;
  BEGIN IFDEF;
}

<IFDEF>{PRE_IFDEF} {
  DEBUG_LEX_MESSAGE("PRE_IFDEF\n");
  ifdef_depth++;
  fprintf(stdout, "dpeth=%d", ifdef_depth);
}

<IFDEF>{PRE_ENDIF} {
  DEBUG_LEX_MESSAGE("PRE_ENDIF\n");
  ifdef_depth--;
  if (ifdef_depth == 0)
    BEGIN INITIAL;
}

<IFDEF>.|\n        {
  /* eat ifdef */
}



{KEY_SPECIFY}        {
  DEBUG_LEX_MESSAGE("KEY_SPECIFY\n");
  specify_depth = 1;
  BEGIN SPECIFY;
}

<SPECIFY>{KEY_SPECIFY} {
  DEBUG_LEX_MESSAGE("KEY_SPECIFY\n");
  specify_depth++;
}

<SPECIFY>{KEY_ENDSPECIFY} {
  DEBUG_LEX_MESSAGE("KEY_ENDSPECIFY\n");
  specify_depth--;
  if (specify_depth == 0)
    BEGIN INITIAL;
}

<SPECIFY>.|\n        {
  /* eat ifdef */
}


{KEY_MODULE}       {
  DEBUG_LEX_MESSAGE("KEY_MODULE\n");
  return MODULE;
}

{KEY_ENDMODULE}    {
  DEBUG_LEX_MESSAGE("KEY_ENDMODULE\n");
  return ENDMODULE;
}

{KEY_INPUT}        {
  DEBUG_LEX_MESSAGE("KEY_INPUT\n");
  return INPUT;
}

{KEY_OUTPUT}       {
  DEBUG_LEX_MESSAGE("KEY_OUTPUT\n");
  return OUTPUT;
}

{KEY_INOUT}        {
  DEBUG_LEX_MESSAGE("KEY_INOUT\n");
  return INOUT;
}

{KEY_REG}          {
  DEBUG_LEX_MESSAGE("KEY_REG\n");
  return REG;
}

{KEY_WIRE}         {
  DEBUG_LEX_MESSAGE("KEY_WIRE\n");
  return WIRE;
}

{ID}               {
  DEBUG_LEX_MESSAGE("ID: "); DEBUG_LEX_MESSAGE(yytext); DEBUG_LEX_MESSAGE("\n");
  sverilog_lval.string = namecopy(yytext);
  return ID;
}

{INUMBER}          {
  DEBUG_LEX_MESSAGE("INUMBER: "); DEBUG_LEX_MESSAGE(yytext); DEBUG_LEX_MESSAGE("\n");
  sverilog_lval.inumber = atoi(yytext);
  return INUMBER;
}

{RNUMBER}          {
  DEBUG_LEX_MESSAGE("RNUMBER: "); DEBUG_LEX_MESSAGE(yytext); DEBUG_LEX_MESSAGE("\n");
  sverilog_lval.rnumber = atof(yytext);
  return RNUMBER;
}

.                  {
  DEBUG_LEX_MESSAGE(yytext); DEBUG_LEX_MESSAGE("\n");
  return(yytext[0]);
}

<<EOF>>            {
  DEBUG_LEX_MESSAGE("<EOF>\n");
  yyterminate();
  return 0;
}

%%

int yywrap()
{
  sverilog_lineno = 0;
  return 1;
}

#ifdef FLEX_2_5_4a
  // Free the buffer which remains un-freed due to a bug in flex 2.5.4a (corrected in later versions)
  int sverilog_lex_destroy()
  {
    yy_delete_buffer(yy_current_buffer);
    sverilog_lineno = 0;
    yy_init = 1;
    return 1;
  }
#endif
