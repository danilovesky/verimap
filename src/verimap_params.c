#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "messages.h"
#include "param.h"
#include "str_utils.h"
#include "verimap_msgs.h"
#include "verimap_params.h"

//=== FILE OPTIONS
char* _verimap_program_name;
char* _verimap_input_file_names;
char* _verimap_output_file_name;
char* _verimap_full_file_name;
char* _verimap_include_file_names;
char* _verimap_lib_file_name;
char* _verimap_gen_file_name;
char* _verimap_rules_file_names;
char* _verimap_params_file_names;
char* _verimap_statistics_file_name;
char* _verimap_wires_file_name;
char* _verimap_assignments_file_names;
char* _verimap_completion_file_names;
//=== GENERAL OPTIONS
int _verimap_optimisation_level;
int _verimap_transformation_level;
float _verimap_celement_delay;
char* _verimap_optimisation_params;
char* _verimap_delay_min_params;
char* _verimap_delay_max_params;
char* _verimap_sp0_port_names;
char* _verimap_sp1_port_names;
char* _verimap_clock_port_names;
char* _verimap_reset_port_names;
int _verimap_buffer;
int _verimap_reset_active;
char* _verimap_topmost_module_name;
int _verimap_single_rail_wrapper;
int _verimap_alternating_spacer;
int _verimap_statistics_level;

int _verimap_wires_level;
char* _verimap_wires_pattern;

char* _verimap_cmd_file_name;
char* _verimap_gcf_file_name;
int _verimap_path_posibility;

//---------------------------------------------------------------------------
bool verimap_process_params(int argc, char **argv)
{
  int i;
  int stdout_num = 1;
  bool result = true;

  verimap_clear_params();
  char* program_name = strrchr(argv[0], '/');
  if (program_name == NULL)
    _verimap_program_name = namecopy(argv[0]);
  else
    _verimap_program_name = namecopy(&program_name[1]);

  if (argc < 2)
    i = 0;
  else
    i = 1;

  while (i > 0)
  {
    // [_verimap_input_file_names]
    if (argv[i][0] != '-')
    {
      if (_verimap_input_file_names == NULL)
        _verimap_input_file_names = namecopy(argv[i]);
      else
      {
        char* input_file_name = name2pattern("%s,%s", _verimap_input_file_names, argv[i]);
        delete [] _verimap_input_file_names;
        _verimap_input_file_names = input_file_name;
      }
      i++;
      if (i >= argc) i = 0;
      continue;
    }
    else
    // -o [_verimap_output_file_name] <=> --output [_verimap_output_file_name]
    if (param_string(argc, argv, &i, "o", &_verimap_output_file_name) ||
        param_string(argc, argv, &i, "-output", &_verimap_output_file_name))
    {
    }
    else
    // -f [_verimap_full_file_name] <=> --full [_verimap_full_file_name]
    if (param_string(argc, argv, &i, "f", &_verimap_full_file_name) ||
        param_string(argc, argv, &i, "-full", &_verimap_full_file_name))
    {
    }
    else
    // -i [_verimap_include_file_names] <=> --include [_verimap_include_file_names]
    if (param_string(argc, argv, &i, "i", &_verimap_include_file_names) ||
        param_string(argc, argv, &i, "-include", &_verimap_include_file_names))
    {
    }
    else
    // -l [_verimap_lib_file_name] <=> --library [_verimap_lib_file_name]
    if (param_string(argc, argv, &i, "l", &_verimap_lib_file_name) ||
        param_string(argc, argv, &i, "-library", &_verimap_lib_file_name))
    {
    }
    else
    // -g [_verimap_gen_file_name] <=> --generate [_verimap_gen_file_name]
    if (param_string(argc, argv, &i, "g", &_verimap_gen_file_name) ||
        param_string(argc, argv, &i, "-generate", &_verimap_gen_file_name))
    {
    }
    else
    // -r [_verimap_rules_file_names] <=> --rules [_verimap_rules_file_names]
    if (param_string(argc, argv, &i, "r", &_verimap_rules_file_names) ||
        param_string(argc, argv, &i, "-rules", &_verimap_rules_file_names))
    {
    }
    else
    // -p [_verimap_params_file_names] <=> --params [_verimap_params_file_names]
    if (param_string(argc, argv, &i, "p", &_verimap_params_file_names) ||
        param_string(argc, argv, &i, "-params", &_verimap_params_file_names))
    {
    }
    else
    // -s [_verimap_statistics_file_name] <=> --statistics [_verimap_statistics_file_name]
    if (param_string(argc, argv, &i, "s", &_verimap_statistics_file_name) ||
        param_string(argc, argv, &i, "-statistics", &_verimap_statistics_file_name))
    {
    }
    else
    // -w [_verimap_wires_file_name] <=> --wires [_verimap_wires_file_name]
    if (param_string(argc, argv, &i, "w", &_verimap_wires_file_name) ||
        param_string(argc, argv, &i, "-wires", &_verimap_wires_file_name))
    {
    }
    else
    // -a [_verimap_assignments_file_names] <=> --assignments [_verimap_assignments_file_names]
    if (param_string(argc, argv, &i, "a", &_verimap_assignments_file_names) ||
        param_string(argc, argv, &i, "-assignments", &_verimap_assignments_file_names))
    {
    }
    else
    //=== GENERAL OPTIONS
    // -ol[_verimap_optimisation_level]<=> --optimisation-level[_verimap_optimisation_level]
    if (param_integer(argc, argv, &i, "ol", &_verimap_optimisation_level) ||
        param_integer(argc, argv, &i, "-optimisation-level", &_verimap_optimisation_level))
    {
    }
    else
    // -tl[_verimap_transformation_level] <=> --transformation-level[_verimap_transformation_level]
    if (param_integer(argc, argv, &i, "tl", &_verimap_transformation_level) ||
        param_integer(argc, argv, &i, "-transformation-level", &_verimap_transformation_level))
    {
    }
    else
    // -cd[_verimap_celement_delay] <=> --celement-delay[_verimap_celement_delay]
    if (param_float(argc, argv, &i, "cd", &_verimap_celement_delay) ||
        param_float(argc, argv, &i, "-celement-delay", &_verimap_celement_delay))
    {
    }
    else
    // -op [_verimap_optimisation_params] <=> --optimisation-params [_verimap_optimisation_params]
    if (param_string(argc, argv, &i, "op", &_verimap_optimisation_params) ||
        param_string(argc, argv, &i, "-optimisation-params", &_verimap_optimisation_params))
    {
    }
    else
    // --delay-min-params [_verimap_delay_min_params]
    if (param_string(argc, argv, &i, "-delay-min-params", &_verimap_delay_min_params))
    {
    }
    else
    // --delay-max-params [_verimap_delay_max_params]
    if (param_string(argc, argv, &i, "-delay-max-params", &_verimap_delay_max_params))
    {
    }
    else
    // -tm [_verimap_topmost_module_name] <=> --topmost-module [_verimap_topmost_module_name]
    if (param_string(argc, argv, &i, "tm", &_verimap_topmost_module_name) ||
        param_string(argc, argv, &i, "-topmost-module", &_verimap_topmost_module_name))
    {
    }
    else
    // -sp0 [_verimap_sp0_port_names] <=> --spacer-0 [_verimap_sp0_port_names]
    if (param_string(argc, argv, &i, "sp0", &_verimap_sp0_port_names) ||
        param_string(argc, argv, &i, "-spacer-0", &_verimap_sp0_port_names))
    {
    }
    else
    // -sp1 [_verimap_sp1_port_names] <=> --spacer-1 [_verimap_sp1_port_names]
    if (param_string(argc, argv, &i, "sp1", &_verimap_sp1_port_names) ||
        param_string(argc, argv, &i, "-spacer-1", &_verimap_sp1_port_names))
    {
      if (_verimap_sp0_port_names)
      {
        Warning("\"-sp1 PORT_NAMES\" cannot be used with \"-sp0 PORT_NAMES\" and is ignored");
        delete [] _verimap_sp1_port_names;
        _verimap_sp1_port_names = namecopy(_VERIMAP_SP1_PORT_NAMES);
      }
    }
    else
    // -clk [_verimap_clock_port_names] <=> --clock [_verimap_clock_port_names]
    if (param_string(argc, argv, &i, "clk", &_verimap_clock_port_names) ||
        param_string(argc, argv, &i, "-clock", &_verimap_clock_port_names))
    {
    }
    else
    // -rst [_verimap_reset_port_names] <=> --reset [_verimap_reset_port_names]
    if (param_string(argc, argv, &i, "rst", &_verimap_reset_port_names) ||
        param_string(argc, argv, &i, "-reset", &_verimap_reset_port_names))
    {
    }
    else
    // -buf[_verimap_buffer] <=> --buffer[_verimap_buffer]
    if (param_bool(argc, argv, &i, "buf") ||
        param_bool(argc, argv, &i, "-buffer"))
    {
       _verimap_buffer = 1;
    }
    else
    // -ra[_verimap_reset_active] <=> --reset-active[_verimap_reset_active]
    if (param_integer(argc, argv, &i, "ra", &_verimap_reset_active) ||
        param_integer(argc, argv, &i, "-reset-active", &_verimap_reset_active))
    {
    }
    else
    // -srw <=> --single-rail-wrapper
    if (param_bool(argc, argv, &i, "srw") ||
        param_bool(argc, argv, &i, "-single-rail-wrapper"))
    {
      _verimap_single_rail_wrapper = 1;
    }
    else
    // -as <=> --alternating-spacer
    if (param_bool(argc, argv, &i, "as") ||
        param_bool(argc, argv, &i, "-alternating-spacer"))
    {
      _verimap_alternating_spacer = 1;
    }
    else
    // -sl[_verimap_statistics_level] <=> --statistics-level[_verimap_statistics_level]
    if (param_integer(argc, argv, &i, "sl", &_verimap_statistics_level) ||
        param_integer(argc, argv, &i, "-statistics-level", &_verimap_statistics_level))
    {
      if (_verimap_statistics_level < 0) _verimap_statistics_level = _VERIMAP_STATISTICS_LEVEL;
    }
    else
    // -wl[_verimap_wires_level] <=> --wires-level[_verimap_wires_level]
    if (param_integer(argc, argv, &i, "wl", &_verimap_wires_level) ||
        param_integer(argc, argv, &i, "-wires-level", &_verimap_wires_level))
    {
    }
    else
    // -wp [_verimap_wires_pattern] <=> --wires-pattern [_verimap_wires_pattern]
    if (param_string(argc, argv, &i, "wp", &_verimap_wires_pattern) ||
        param_string(argc, argv, &i, "-wires-pattern", &_verimap_wires_pattern))
    {
    }
    else
    // -cmd [_verimap_cmd_file_name]
    if (param_string(argc, argv, &i, "cmd", &_verimap_cmd_file_name))
    {
    }
    else
    // -gcf [_verimap_gcf_file_name]
    if (param_string(argc, argv, &i, "gcf", &_verimap_gcf_file_name))
    {
    }
    else
    // -pp[_verimap_path_posibility] <=> --path-posibility[_verimap_path_posibility]
    if (param_integer(argc, argv, &i, "pp", &_verimap_path_posibility) ||
        param_integer(argc, argv, &i, "-path-posibility", &_verimap_path_posibility))
    {
      if ( _verimap_path_posibility < 1) _verimap_path_posibility = _VERIMAP_PATH_POSSIBILITY;
    }
    else
    //=== INFO OPTIONS
    // -h <=> --help
    if (param_bool(argc, argv, &i, "h") ||
        param_bool(argc, argv, &i, "-help"))
    {
      if (i != 0)
        Warning("<%s> must be the only flag",argv[i-1]);
      char* _verimap_help = verimap_get_help(_verimap_program_name);
      fprintf(stderr, "%s", _verimap_help);
      delete [] _verimap_help;
      result = false;
    }
    else
    // -v <=> --version
    if (param_bool(argc, argv, &i, "v") ||
        param_bool(argc, argv, &i, "-vesion"))
    {
      if (i != 0)
        Warning("\"%s\" must be the only flag",argv[i-1]);
      char* _verimap_version = verimap_get_version(_verimap_program_name);
      fprintf(stderr, "%s", _verimap_version);
      delete [] _verimap_version;
      result = false;
    }
    else
    // UNRECOGNIZED FLAG
    {
      Error("unrecognized flag \"%s\"", argv[i]);
      result = false;
    }
  }
  verimap_correct_params();
  return result;
}

//---------------------------------------------------------------------------
void verimap_clear_params()
{
  delete [] _verimap_program_name; _verimap_program_name = NULL;
  delete [] _verimap_input_file_names; _verimap_input_file_names = NULL;
  delete [] _verimap_output_file_name; _verimap_output_file_name = NULL;
  delete [] _verimap_full_file_name; _verimap_full_file_name = NULL;
  delete [] _verimap_include_file_names; _verimap_include_file_names = NULL;
  delete [] _verimap_lib_file_name; _verimap_lib_file_name = NULL;
  delete [] _verimap_gen_file_name; _verimap_gen_file_name = NULL;
  delete [] _verimap_rules_file_names; _verimap_rules_file_names = NULL;
  delete [] _verimap_params_file_names; _verimap_rules_file_names = NULL;
  delete [] _verimap_statistics_file_name; _verimap_statistics_file_name = NULL;
  delete [] _verimap_wires_file_name; _verimap_wires_file_name = NULL;
  delete [] _verimap_assignments_file_names; _verimap_assignments_file_names = NULL;
  delete [] _verimap_completion_file_names; _verimap_completion_file_names = NULL;
  _verimap_optimisation_level = -1;
  _verimap_transformation_level = -1;
  _verimap_celement_delay = -1.0;
  delete [] _verimap_optimisation_params; _verimap_optimisation_params = NULL;
  delete [] _verimap_delay_min_params; _verimap_delay_min_params = NULL;
  delete [] _verimap_delay_max_params; _verimap_delay_max_params = NULL;
  delete [] _verimap_sp0_port_names; _verimap_sp0_port_names = NULL;
  delete [] _verimap_sp1_port_names; _verimap_sp1_port_names = NULL;
  delete [] _verimap_clock_port_names; _verimap_clock_port_names = NULL;
  delete [] _verimap_reset_port_names; _verimap_reset_port_names = NULL;
  _verimap_buffer = -1;
  _verimap_reset_active = -1;
  delete [] _verimap_topmost_module_name; _verimap_topmost_module_name = NULL;
  _verimap_single_rail_wrapper = -1;
  _verimap_alternating_spacer = -1;
  _verimap_statistics_level = -1;

  delete [] _verimap_wires_pattern; _verimap_wires_pattern = NULL;
  delete [] _verimap_cmd_file_name; _verimap_cmd_file_name = NULL;
  delete [] _verimap_gcf_file_name; _verimap_gcf_file_name = NULL;
  _verimap_path_posibility = -1;
}

//---------------------------------------------------------------------------
void verimap_correct_params()
{
  if (_verimap_program_name == NULL)
    _verimap_program_name = namecopy(_VERIMAP_PROGRAM_NAME);
  if (_verimap_input_file_names == NULL)
    _verimap_input_file_names = namecopy(_VERIMAP_INPUT_FILE_NAMES);
  if (_verimap_output_file_name == NULL)
    _verimap_output_file_name = namecopy(_VERIMAP_OUTPUT_FILE_NAME);
  if (_verimap_full_file_name == NULL)
    _verimap_full_file_name = namecopy(_VERIMAP_FULL_FILE_NAME);
  if (_verimap_include_file_names == NULL)
    _verimap_include_file_names = namecopy(_VERIMAP_INCLUDE_FILE_NAMES);
  if (_verimap_lib_file_name == NULL)
    _verimap_lib_file_name = namecopy(_VERIMAP_LIB_FILE_NAME);
  if (_verimap_gen_file_name == NULL)
    _verimap_gen_file_name = namecopy(_VERIMAP_GEN_FILE_NAME);
  if (_verimap_rules_file_names == NULL)
    _verimap_rules_file_names = namecopy(_VERIMAP_RULES_FILE_NAMES);
  if (_verimap_params_file_names == NULL)
    _verimap_params_file_names = namecopy(_VERIMAP_PARAMS_FILE_NAMES);
  if (_verimap_statistics_file_name == NULL)
    _verimap_statistics_file_name = namecopy(_VERIMAP_STATISTICS_FILE_NAME);
  if (_verimap_wires_file_name == NULL)
    _verimap_wires_file_name = namecopy(_VERIMAP_WIRES_FILE_NAME);
  if (_verimap_assignments_file_names == NULL)
    _verimap_assignments_file_names = namecopy(_VERIMAP_ASSIGNMENTS_FILE_NAMES);
  if (_verimap_completion_file_names == NULL)
    _verimap_completion_file_names = namecopy(_VERIMAP_COMPLETION_FILE_NAMES);

  if (_verimap_optimisation_level < 0)
    _verimap_optimisation_level = _VERIMAP_OPTIMISATION_LEVEL;
  if (_verimap_transformation_level < 0)
    _verimap_transformation_level = _VERIMAP_TRANSFORMATION_LEVEL;
  if (_verimap_celement_delay < 0)
    _verimap_celement_delay = _VERIMAP_CELEMENT_DELAY;
  if (_verimap_optimisation_params == NULL)
    _verimap_optimisation_params = _VERIMAP_OPTIMISATION_PARAMS;

  if (_verimap_delay_min_params == NULL)
    _verimap_delay_min_params = namecopy(_VERIMAP_DELAY_MIN_PARAMS);
  if (_verimap_delay_max_params == NULL)
    _verimap_delay_max_params = namecopy(_VERIMAP_DELAY_MAX_PARAMS);

  if (_verimap_sp0_port_names == NULL && _verimap_sp1_port_names == NULL)
    _verimap_sp0_port_names = namecopy(_VERIMAP_SP0_PORT_NAMES);
  if (_verimap_sp0_port_names != NULL && _verimap_sp1_port_names != NULL)
  {
     Warning("\"-sp1 PORT_NAMES\" cannot be used with \"-sp0 PORT_NAMES\" and is ignored");
     delete [] _verimap_sp1_port_names;
     _verimap_sp1_port_names = NULL;
  }
  if (_verimap_clock_port_names == NULL)
    _verimap_clock_port_names = namecopy(_VERIMAP_CLOCK_PORT_NAMES);
  if (_verimap_reset_port_names == NULL)
    _verimap_reset_port_names = namecopy(_VERIMAP_RESET_PORT_NAMES);
  if (_verimap_topmost_module_name == NULL)
    _verimap_topmost_module_name = namecopy(_VERIMAP_TOPMOST_MODULE_NAME);
  if (_verimap_buffer < 0)
    _verimap_buffer = _VERIMAP_BUFFER;
  if (_verimap_buffer < 0)
    _verimap_reset_active = _VERIMAP_RESET_ACTIVE;
  if (_verimap_single_rail_wrapper < 0)
    _verimap_single_rail_wrapper = _VERIMAP_SINGLE_RAIL_WRAPPER;
  if (_verimap_alternating_spacer < 0)
    _verimap_alternating_spacer = _VERIMAP_ALTERNATING_SPACER;
  if (_verimap_statistics_level < 0)
    _verimap_statistics_level = _VERIMAP_STATISTICS_LEVEL;
  if (_verimap_wires_level < 0)
    _verimap_wires_level = _VERIMAP_WIRES_LEVEL;

  if (_verimap_wires_pattern == NULL)
    _verimap_wires_pattern = namecopy(_VERIMAP_WIRES_PATTERN);

  if (_verimap_cmd_file_name == NULL)
    _verimap_cmd_file_name = namecopy(_VERIMAP_CMD_FILE_NAME);
  if (_verimap_gcf_file_name == NULL)
    _verimap_gcf_file_name = namecopy(_VERIMAP_GCF_FILE_NAME);

  if (_verimap_path_posibility < 0)
    _verimap_path_posibility = _VERIMAP_PATH_POSSIBILITY;

  // if no input file specified read it from standard input
  if (_verimap_input_file_names == NULL)
    _verimap_input_file_names = namecopy(NAME_STDIO);
  // if no output file specified write it to standard output
  if (_verimap_output_file_name == NULL)
    _verimap_output_file_name = namecopy(NAME_STDIO);

  // count the number of files read from standard input and written to standard output
  int stdin_num = 0;
  int stdout_num = 0;

  stdin_num += namesnamenum(_verimap_input_file_names, NAME_STDIO);
  stdin_num += namesnamenum(_verimap_include_file_names, NAME_STDIO);
  stdin_num += namesnamenum(_verimap_gen_file_name, NAME_STDIO);
  stdin_num += namesnamenum(_verimap_rules_file_names, NAME_STDIO);
  stdin_num += namesnamenum(_verimap_params_file_names, NAME_STDIO);

  stdout_num += namesnamenum(_verimap_output_file_name, NAME_STDIO);
  stdout_num += namesnamenum(_verimap_full_file_name, NAME_STDIO);
  stdout_num += namesnamenum(_verimap_lib_file_name, NAME_STDIO);
  stdout_num += namesnamenum(_verimap_gen_file_name, NAME_STDIO);
  stdout_num += namesnamenum(_verimap_statistics_file_name, NAME_STDIO);
  stdout_num += namesnamenum(_verimap_wires_file_name, NAME_STDIO);
  stdout_num += namesnamenum(_verimap_cmd_file_name, NAME_STDIO);
  stdin_num += namesnamenum(_verimap_gcf_file_name, NAME_STDIO);

  if (stdin_num > 1)
    Warning("%d files will be read from standard input", stdin_num);
  if (stdout_num > 1)
    Warning("%d files will be written to standard output", stdout_num);
}
