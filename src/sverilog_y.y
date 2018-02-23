%{
#include <stdio.h>
#include <stdlib.h>
#include "messages.h"
#include "str_utils.h"
#include "sv_lib.h"
#include "sv_module.h"
#include "sverilog.h"

#ifdef DEBUG_YACC
  #define DEBUG_YACC_MESSAGE(msg) fprintf(stdout, msg)
#else
  #define DEBUG_YACC_MESSAGE(msg) // msg
#endif

void sverilog_error(char* message)
{
  Error("%s in line %d in file <%s>", message, sverilog_lineno, sverilog_filename);
}

ModuleArray* sverilog_modules;
%}

%start source_text

%union
{
  ModuleArray* modules;
  Module* module;
  Range* range;
  Delay* delay;
  Parameter* parameter;
  ParameterArray* parameters;
  Port* port;
  PortArray* ports;
  Instance* instance;
  InstanceArray* instances;
  Connection* connection;
  ConnectionArray* connections;
  VerilogObjectArray* objects;
  char* string;
  int inumber;
  float rnumber;
}

%token <string> MODULE
%token <string> ENDMODULE
%token <string> PARAMETER
%token <string> INPUT
%token <string> OUTPUT
%token <string> INOUT
%token <string> WIRE
%token <string> REG
%token <string> ID
%token <inumber> INUMBER
%token <rnumber> RNUMBER

%type <modules> source_text
%type <module> module
%type <ports> port_list_opt
%type <ports> port_list                     // creates PortArray
%type <port> port
%type <port> port_expression_opt
%type <port> port_expression
%type <port> port_reference                 // creates Port
%type <range> port_reference_arg            // creates Range
%type <module> module_item_clr              // creates Module
%type <parameters> parameter_declaration    // creates PortArray
%type <ports> port_declaration              // creates PortArray
%type <ports> input_declaration
%type <ports> inout_declaration
%type <ports> output_declaration
%type <ports> reg_declaration
%type <ports> wire_declaration
%type <instances> instance_declaration
%type <instances> instance_list             // creates InstanceArray
%type <instance> instance                   // creates Instance
%type <string> instance_name_opt
%type <inumber> instance_index_opt
%type <connections> connection_list
%type <connections> ordered_connection_list // creates ConnectionArray
%type <connections> named_connection_list   // creates ConnectionArray
%type <connection> named_connection
%type <connection> connection               // creates Connection
%type <objects> variable_list               // creates VerilogObjectArray
%type <range> range_opt
%type <range> range                         // creates Range
%type <delay> delay_opt
%type <delay> delay                         // creates Delay
%type <parameters> assignment_list          // creates ParameterArray
%type <parameter> assignment                // creates Parameter
%type <string> lvalue
%type <rnumber> constant

%%

source_text
  :
    {
      DEBUG_YACC_MESSAGE("source_text : \n");
      $$ = sverilog_modules;
    }
  | source_text module
    {
      DEBUG_YACC_MESSAGE("source_text : source_text module\n");
      $$->add($2);
    }
;

module
  : MODULE ID port_list_opt ';' module_item_clr ENDMODULE
    {
      DEBUG_YACC_MESSAGE("module : MODULE ID port_list_opt ';' module_item_clr ENDMODULE\n");
      $$ = $5;
      $$->setName($2);
      // prepare to sort the ports
      PortArray* ports_sorted = new PortArray($$->ports->num);
      for (int port_index = 0; port_index < $$->ports->num; port_index++)
      {
        Port* port_cur = $$->ports->arr[port_index];
        port_cur->andTag(~TAG_OBJ_PROCESSED);
      }
      // add ports in the order they appear in the header
      for (int port_index = 0; port_index < $3->num; port_index++)
      {
        Port* port_new = $3->arr[port_index];
        if (port_new != NULL)
        {
            Port* port_cur = $$->getPort(port_new->getName());
            if (port_cur)
            {
              ports_sorted->add(port_cur);
              port_cur->orTag(TAG_OBJ_PROCESSED);
            }
            else
              Error("port <%s> of module <%s> in file <%s> is not defined", port_new->getName(), $$->getName(), sverilog_filename);
        }
      }
      // add the rest of the ports
      for (int port_index = 0; port_index < $$->ports->num; port_index++)
      {
        Port* port_cur = $$->ports->arr[port_index];
        if (port_cur->testTag(TAG_OBJ_PROCESSED))
          port_cur->andTag(~TAG_OBJ_PROCESSED);
        else
          ports_sorted->add(port_cur);
      }
      // change the port list in the module
      delete $$->ports;
      $$->ports = ports_sorted;
      $3->removeAll(true);
      delete $3;
    }
;

module_item_clr
  :
    {
      DEBUG_YACC_MESSAGE("module_item_clr : \n");
      $$ = new Module(TAG_UNDEFINED, NULL, NULL, NULL, NULL, NULL);
    }
  | module_item_clr parameter_declaration
    {
      DEBUG_YACC_MESSAGE("module_item_clr : module_item_clr parameter_declaration\n");
      $$ = $1;
      for (int i = 0; i < $2->num; i++)
        $$->addParameter($2->arr[i]);
      delete $2;
    }
  | module_item_clr port_declaration
    {
      DEBUG_YACC_MESSAGE("module_item_clr : module_item_clr port_declaration\n");
      $$ = $1;
      for (int i = 0; i < $2->num; i++)
      {
        Port* port_new = $2->arr[i];
        Port* port_cur = $$->getPort(port_new->getName());
        if (port_cur)
        {
          port_cur->orTag(port_new->getTag());
          delete port_new;
        }
        else
        {
          $$->addPort(port_new);
        }
      }
      delete $2;
    }
  | module_item_clr instance_declaration
    {
      DEBUG_YACC_MESSAGE("module_item_clr : module_item_clr instance_declaration\n");
      $$ = $1;
      for (int i = 0; i < $2->num; i++)
      {
        $2->arr[i]->setContainer($$);
        $$->addInstance($2->arr[i]);
      }
      delete $2;
    }
;

parameter_declaration
  : PARAMETER assignment_list ';'
    {
      DEBUG_YACC_MESSAGE("parameter_declaration : PARAMETER assignment_list ';'\n");
      $$ = $2;
    }
;

port_declaration
  : input_declaration
    {
      DEBUG_YACC_MESSAGE("module_item : input_declaration\n");
      $$ = $1;
    }
  | output_declaration
    {
      DEBUG_YACC_MESSAGE("module_item : output_declaration\n");
      $$ = $1;
    }
  | inout_declaration
    {
      DEBUG_YACC_MESSAGE("module_item : inout_declaration\n");
      $$ = $1;
    }
  | reg_declaration
    {
      DEBUG_YACC_MESSAGE("module_item : reg_declaration\n");
      $$ = $1;
    }
  | wire_declaration
    {
      DEBUG_YACC_MESSAGE("module_item : wire_declaration\n");
      $$ = $1;
    }
;

input_declaration
  : INPUT range_opt variable_list ';'
    {
      DEBUG_YACC_MESSAGE("input_declaration : INPUT range_opt variable_list ';'\n");
      $$ = new PortArray($3->num);
      for (int i = 0; i < $3->num; i++)
      {
        VerilogObject* object_cur = $3->arr[i];
        Port* port_new = new Port(TAG_PORT_INPUT, namecopy(object_cur->getName()), NULL, $2, NULL);
        $$->add(port_new);
      }
      delete $2;
      $3->removeAll(true);
      delete $3;
    }
;

output_declaration
  : OUTPUT range_opt variable_list ';'
    {
      DEBUG_YACC_MESSAGE("output_declaration : OUTPUT range_opt variable_list ';'\n");
      $$ = new PortArray($3->num);
      for (int i = 0; i < $3->num; i++)
      {
        VerilogObject* object_cur = $3->arr[i];
        Port* port_new = new Port(TAG_PORT_OUTPUT, namecopy(object_cur->getName()), NULL, $2, NULL);
        $$->add(port_new);
      }
      delete $2;
      $3->removeAll(true);
      delete $3;
    }
;

inout_declaration
  : INOUT range_opt variable_list ';'
    {
      DEBUG_YACC_MESSAGE("inout_declaration : INOUT range_opt variable_list ';'\n");
      $$ = new PortArray($3->num);
      for (int i = 0; i < $3->num; i++)
      {
        VerilogObject* object_cur = $3->arr[i];
        Port* port_new = new Port(TAG_PORT_OUTPUT, namecopy(object_cur->getName()), NULL, $2, NULL);
        $$->add(port_new);
      }
      delete $2;
      $3->removeAll(true);
      delete $3;
    }
;

reg_declaration
  : REG range_opt variable_list ';'
    {
      DEBUG_YACC_MESSAGE("reg_declaration : REG range_opt variable_list ';'\n");
      $$ = new PortArray($3->num);
      for (int i = 0; i < $3->num; i++)
      {
        VerilogObject* object_cur = $3->arr[i];
        Port* port_new = new Port(TAG_PORT_REG, namecopy(object_cur->getName()), NULL, $2, NULL);
        $$->add(port_new);
      }
      delete $2;
      $3->removeAll(true);
      delete $3;
    }
;

wire_declaration
  : WIRE range_opt delay_opt variable_list ';'
    {
      DEBUG_YACC_MESSAGE("net_declaration : WIRE range_opt delay_opt variable_list ';'\n");
      $$ = new PortArray($4->num);
      for (int i = 0; i < $4->num; i++)
      {
        VerilogObject* object_cur = $4->arr[i];
        // TODO: parse port dimension
        Port* port_new = new Port(TAG_PORT_WIRE, namecopy(object_cur->getName()), NULL, $2, $3);
        $$->add(port_new);
      }
      delete $2;
      delete $3;
      $4->removeAll(true);
      delete $4;
    }
;

instance_declaration
  : ID instance_list ';'
  {
      $$ = $2;
      for (int i = 0; i < $$->num; i++)
        $$->arr[i]->setModuleName($1);
  }

instance_list
  : instance
    {
      DEBUG_YACC_MESSAGE("instance_list : instance\n");
      $$ = new InstanceArray(1);
      $$->add($1);
    }
  | instance_list ',' instance
    {
      DEBUG_YACC_MESSAGE("instance_list : instance_list ',' instance\n");
      $$ = $1;
      $$->add($3);
    }
;

instance
  : instance_name_opt instance_index_opt '(' connection_list ')'
    {
      DEBUG_YACC_MESSAGE("instance : instance_name_opt instance_index_opt '(' connection_list ')'\n");
      $$ = new Instance(TAG_UNDEFINED, $1, $2, -1, -1, -1, NULL, $4);
    }
;

instance_name_opt
  :
    {
      DEBUG_YACC_MESSAGE("instance_name_opt : \n");
      $$ = NULL;
    }
  | ID
    {
      DEBUG_YACC_MESSAGE("instance_name_opt : ID\n");
      $$ = $1;
    }
;

instance_index_opt
  :
    {
      DEBUG_YACC_MESSAGE("instance_index_opt : \n");
      $$ = -1;
    }
  | '[' INUMBER ']'
    {
      DEBUG_YACC_MESSAGE("instance_index_opt : '[' INUMBER ']'\n");
      $$ = $2;
    }

connection_list
  : ordered_connection_list
    {
      DEBUG_YACC_MESSAGE("connection_list : ordered_connection_list\n");
      $$ = $1;
    }
  | named_connection_list
    {
      DEBUG_YACC_MESSAGE("connection_list : named_connection_list\n");
      $$ = $1;
    }
;

ordered_connection_list
  : connection
    {
      DEBUG_YACC_MESSAGE("ordered_connection_list : connection\n");
      $$ = new ConnectionArray(1);
      $$->add($1);
    }
  | ordered_connection_list ',' connection
    {
      DEBUG_YACC_MESSAGE("ordered_connection_list : ordered_connection_list ',' connection\n");
      $$ = $1;
      $$->add($3);
    }
;

named_connection_list
  : named_connection
    {
      DEBUG_YACC_MESSAGE("named_connection_list : named_connection\n");
      $$ = new ConnectionArray(1);
      $$->add($1);
    }
  | named_connection_list ',' named_connection
    {
      DEBUG_YACC_MESSAGE("named_connection_list : named_connection_list ',' named_connection\n");
      $$ = $1;
      $$->add($3);
    }
;

named_connection
  : '.' ID '(' connection ')'
    {
      DEBUG_YACC_MESSAGE("named_connection : '.' ID '(' connection ')'\n");
      $$ = $4;
      $$->setName($2);
    }
;

connection
  : port_expression_opt
    {
      DEBUG_YACC_MESSAGE("connection : port_expression_opt\n");
      NetArray* nets = NULL;
      if ($1)
      {
        nets = new NetArray($1->nets->num);
        for (int net_ind = 0; net_ind < $1->nets->num; net_ind++)
        {
          Net* net_cur = $1->nets->arr[net_ind];
          if (net_cur)
          {
            Net* net_new = new Net(*net_cur);
            nets->add(net_new);
          }
          else
            nets->add(NULL);
        }
        delete $1;
      }
      $$ = new Connection(TAG_UNDEFINED, NULL, nets);
    }
  | '{' port_list '}'
    {
      DEBUG_YACC_MESSAGE("connection : '{' port_list_opt '}'\n");
      NetArray* nets = NULL;
      if ($2)
      {
        nets = new NetArray($2->num);
        for (int port_ind = 0; port_ind < $2->num; port_ind++)
        {
          Port* port_cur = $2->arr[port_ind];
          for (int net_ind = 0; net_ind < port_cur->nets->num; net_ind++)
          {
            Net* net_cur = port_cur->nets->arr[net_ind];
            if (net_cur)
            {
              Net* net_new = new Net(*net_cur);
              nets->add(net_new);
            }
            else
              nets->add(NULL);
          }
          delete port_cur;
        }
        delete $2;
      }
      $$ = new Connection(TAG_UNDEFINED, NULL, nets);
    }
;

port_list_opt
  :
    {
      DEBUG_YACC_MESSAGE("port_list_opt : \n");
      $$ = NULL;
    }
  | '(' port_list ')'
    {
      DEBUG_YACC_MESSAGE("port_list_opt : '(' port_list ')'\n");
      $$ = $2;
    }
;

port_list
  : port
    {
      DEBUG_YACC_MESSAGE("port_list : port\n");
      $$ = new PortArray(2);
      $$->add($1);
    }
  | port_list ',' port
    {
      DEBUG_YACC_MESSAGE("port_list : port_list ',' port\n");
      $$ = $1;
      $$->add($3);
    }
;

port
  : port_expression_opt
    {
      DEBUG_YACC_MESSAGE("port : port_expression_opt\n");
      $$ = $1;
    }
;

port_expression_opt
  :
    {
      DEBUG_YACC_MESSAGE("port_expression_opt : \n");
      $$ = NULL;
    }
  | port_expression
    {
      DEBUG_YACC_MESSAGE("port_expression_opt : port_expression\n");
      $$ = $1;
    }
;

port_expression
  : port_reference
    {
      DEBUG_YACC_MESSAGE("port_expression : port_reference\n");
      $$ = $1;
    }
;

port_reference
  : ID port_reference_arg
    {
      DEBUG_YACC_MESSAGE("port_reference : ID port_reference_arg\n");
      $$ = new Port(TAG_UNDEFINED, $1, NULL, $2, NULL);
      delete $2;
    }
  | INUMBER
    {
      DEBUG_YACC_MESSAGE("port_reference : INUMBER\n");
      switch ($1)
      {
        case 0:
          $$ = new Port(TAG_UNDEFINED, namecopy(NAME_NET_GND), NULL, NULL, NULL);
          break;
        case 1:
          $$ = new Port(TAG_UNDEFINED, namecopy(NAME_NET_VDD), NULL, NULL, NULL);
          break;
      }
    }
;

port_reference_arg
  :
    {
      DEBUG_YACC_MESSAGE("port_reference_arg : \n");
      $$ = NULL;
    }
  | '[' INUMBER ']'
    {
      DEBUG_YACC_MESSAGE("port_reference_arg : '[' INUMBER ']'\n");
      $$ = new Range($2, $2);
    }
  | '[' INUMBER ':' INUMBER ']'
    {
      DEBUG_YACC_MESSAGE("port_reference_arg : '[' INUMBER ':' INUMBER ']'\n");
      $$ = new Range($2, $4);
    }
;

variable_list
  : ID
    {
      DEBUG_YACC_MESSAGE("variable_list : ID\n");
      $$ = new VerilogObjectArray(1);
      VerilogObject* object_new = new VerilogObject(TAG_UNDEFINED, $1);
      $$->add(object_new);
    }
  | variable_list ',' ID
    {
      DEBUG_YACC_MESSAGE("variable_list : variable_list ',' ID\n");
      $$ = $1;
      VerilogObject* object_new = new VerilogObject(TAG_UNDEFINED, $3);
      $$->add(object_new);
    }
 ;

range_opt
  :
    {
      DEBUG_YACC_MESSAGE("range_opt : \n");
      $$ = NULL;
    }
  | range
    {
      DEBUG_YACC_MESSAGE("range_opt : range\n");
      $$ = $1;
    }
;

range
  : '[' INUMBER ':' INUMBER ']'
    {
      DEBUG_YACC_MESSAGE("range : '[' INUMBER ':' INUMBER ']'\n");
      $$ = new Range($2, $4);
    }
;

assignment_list
  : assignment
    {
      DEBUG_YACC_MESSAGE("assignment_list : assignment\n");
      $$ = new ParameterArray(1);
      $$->add($1);
    }
  | assignment_list ',' assignment
    {
      DEBUG_YACC_MESSAGE("assignment_list : assignment_list ',' assignment\n");
      $$ = $1;
      $$->add($3);
    }
;

assignment
  : lvalue '=' constant
    {
      DEBUG_YACC_MESSAGE("assignment : lvalue '=' constant\n");
      $$ = new Parameter(TAG_UNDEFINED, $1, $3);
    }
;

lvalue
  : ID
    {
      DEBUG_YACC_MESSAGE("lvalue : ID\n");
      $$= $1;
    }
;

delay_opt
  :
    {
      DEBUG_YACC_MESSAGE("delay_opt : \n");
      $$ = NULL;
    }
  | delay
    {
      DEBUG_YACC_MESSAGE("delay_opt : delay\n");
      $$ = $1;
  }
;

delay
  : '#' constant
    {
      DEBUG_YACC_MESSAGE("delay : '#' constant\n");
      $$ = new Delay($2, $2);
    }
  | '#' '(' constant ')'
    {
      DEBUG_YACC_MESSAGE("delay : '#' '(' constant ')'\n");
      $$ = new Delay($3, $3);
    }
  | '#' '(' constant ',' constant ')'
    {
      DEBUG_YACC_MESSAGE("delay : '#' '(' constant ',' constant ')'\n");
      $$ = new Delay($3, $5);
    }
;

constant
  : INUMBER
    {
      DEBUG_YACC_MESSAGE("constant : INUMBER\n");
      $$ = $1;
    }
  | RNUMBER
    {
      DEBUG_YACC_MESSAGE("constant : RNUMBER\n");
      $$ = $1;
    }
;

%%


