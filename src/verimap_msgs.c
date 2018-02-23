#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "verimap_msgs.h"

const char *_verimap_fmt_help =
  "VeriMap is a direct mapping tool for data path\n"
  "Usage: %s [OPTIONS] [INPUT_FILE_NAMES]\n"
  "FILE OPTIONS:\n"
  "  -o,  --output OUTPUT_FILE_NAME  netlist output file [STDOUT]\n"
  "  -f,  --full FULL_FILE_NAME      full netlist output file []\n"
  "  -i,  --include INC_FILE_NAMES   library input files [STDIN]\n"
  "  -l,  --library LIB_FILE_NAME    library output file []\n"
  "  -g,  --generate GEN_FILE_NAME   generated modules input-output file [STDOUT]\n"
  "  -r,  --rules RULES_FILE_NAMES   rules for gate transformation input files []\n"
  "  -p,  --params PARAMS_FILE_NAMES parameters of modules input files []\n"
  "  -a,  --assignments ASSIGNMENTS_FILE_NAMES assignments input files []\n"
  "       *_FILE_NAMES is a coma separated list of files for reading\n"
  "TRANSFORMATION OPTIONS:\n"
  "  -tl, --transformation-level[TL] transformation level (TL=[0],1,2,3)\n"
  "       0 = no circuit transformation, the netlist is re-formatted only\n"
  "       1 = calculate the optimisation possibilities only, the output circuit\n"
  "           is still single-rail\n"
  "       2 = convert the circuit into dual-rail\n"
  "       3 = build completion detection logic, add go input and done output\n"
  "  -cd, --celement-delay[DELAY]    2-input C-element delay, ns (DELAY=[0.565])\n"
  "  -as, --alternating-spacer       optimise for alternating spacer protocol\n"
  "  -srw,--single-rail-wrapper      build a single-rail wrapper\n"
  "OPTIMISATION OPTIONS:\n"
  "  -ol, --optimisation-level[OL]    optimisation level (OL=[0],1,2)\n"
  "       0 = no optimisation (positive gates)\n"
  "       1 = optimisation for negative gates or for specified parameters given\n"
  "           by --optimisation-params option\n"
  "       2 = optimisation of spacer converters distribution\n"
  "       3 = optimisation of completion detection logic\n"
  "  -op, --optimisation-params PARAM_NAMES optimisation parameters []\n"
  "  --delay-min-params PARAM_NAMES    minimum delay parameters [rise_min,fall_min]\n"
  "  --delay-max-params PARAM_NAMES    maximum delay parameters [rise_max,fall_max]\n"
  "       PARAM_NAMES is a coma separated list of PARAM_NAME\n"
  "       PARAM_NAME is a parameter name specified in the PARAMS_FILE_NAMES files\n"
  "STRUCTURE OPTIONS:\n"
  "  -tm, --topmost-module MODULE_NAME name of the topmost module\n"
  "  -buf,--buffer                   buffer SPACER and DONE signals\n"
  "  -ra, --reset-active[RA]         reset active level (RA=[0],1)\n"
  "       0 = active-0 reset, 1 = active-1 reset\n"
  "  -rst,--reset PORT_NAMES         names of reset ports [*.rst]\n"
  "  -clk,--clock PORT_NAMES         names of clock ports [*.clk]\n"
  "  -sp0,--spacer-0 PORT_NAMES      spacer-0 ports [*.*]\n"
  "  -sp1,--spacer-1 PORT_NAMES      spacer-1 ports []\n"
  "       PORT_NAMES is a comma-separated list of MODULE_NAME.PORT_NAME\n"
  "         MODULE_NAME.* = all ports of the MODULE_NAME module\n"
  "         *.PORT_NAME   = port PORT_NAME of all modules\n"
  "         *.*           = all ports of all modules\n"
  "         PORT_NAME     = port PORT_NAME of the topmost module\n"
  "STATISTICS OPTIONS:\n"
  "  -s,  --statistics STAT_FILE_NAME statistics output file [STDOUT]\n"
  "  -sl, --statistics-level[SL]     statistics output level (SL=[0],1,2,3)\n"
  "       0 = no statistics is collected\n"
  "       1 = statistics is collected for single-rail circuit only\n"
  "       2 = statistics is collected for dual-rail circuit only\n"
  "       3 = statistics is collected for both single- and dual-rail circuits\n"
  "SWITCHING ACTIVITY OPTIONS:\n"
  "  -w,  --wires WIRES_FILE_NAME    wires switching output file [STDOUT]\n"
  "  -wl, --wires-level[WL]          wires switching output level (WL=[0],1,2,3)\n"
  "       0 = no wires switching analysis\n"
  "       1 = wires switching is analysed for single-rail circuit only\n"
  "       2 = wires switching is analysed for dual-rail circuit only\n"
  "       3 = wires switching is analysed for both single- and dual-rail circuits\n"
  "  -wp, --wires-pattern PATTERN    wires output pattern [always @(?) c=c+1;]\n"
  "       Question mark ? in the PATTERN is replaced by the wires full names\n"
  "TIMING ANALYSIS OPTIONS:\n"
  "  -cmd CMD_FILE_NAME              Pearl timing analysis command file\n"
  "  -gcf GCF_FILE_NAME              GCF file for timing analysis\n"
  "  -pp, --path-possibility[N]      consider top-N path possibilities (N=[1],2...)\n"
  "INFORMATION OPTIONS:\n"
  "  -h,  --help                     print this help only\n"
  "  -v,  --version                  print version only\n";
const char *_verimap_fmt_version =
  "Version %d.%d\n"
  "Last changed at %s\n"
  "Created by Danil Sokolov (E-mail: danil.sokolov@ncl.ac.uk, ICQ#: 30193190)\n"
  "Copyright (c), 2003, University of Newcastle upon Tyne. Newcastle upon Tyne. United Kingdom\n";

const int _verimap_version_major = 1;
const int _verimap_version_minor = 2;
const char *_verimap_version_date = "27 October 2006";

char *verimap_get_help(char *name)
{
  char *help = NULL;
  int len = strlen (_verimap_fmt_help) + 2 * strlen (name);
  help = new char [len+1];
  sprintf (help, _verimap_fmt_help, name, name);
  return help;
}

char *verimap_get_version (char *name)
{
  char *version = NULL;
  int len = strlen (_verimap_fmt_version) + strlen (_verimap_version_date);
  version = new char [len+1];
  (void) sprintf (version, _verimap_fmt_version, _verimap_version_major, _verimap_version_minor, _verimap_version_date);
  return version;
}

