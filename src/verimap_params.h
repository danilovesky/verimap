#ifndef _VERIMAP_PARAMS_H_
#define _VERIMAP_PARAMS_H_

//=== DEFAULTS
#define _VERIMAP_PROGRAM_NAME             NULL
#define _VERIMAP_INPUT_FILE_NAMES         NULL
#define _VERIMAP_OUTPUT_FILE_NAME         NULL
#define _VERIMAP_FULL_FILE_NAME           NULL
#define _VERIMAP_INCLUDE_FILE_NAMES       NULL
#define _VERIMAP_LIB_FILE_NAME            NULL
#define _VERIMAP_GEN_FILE_NAME            NULL
#define _VERIMAP_RULES_FILE_NAMES         NULL
#define _VERIMAP_PARAMS_FILE_NAMES        NULL
#define _VERIMAP_STATISTICS_FILE_NAME     NULL

#define _VERIMAP_WIRES_FILE_NAME          NULL
#define _VERIMAP_ASSIGNMENTS_FILE_NAMES   NULL
#define _VERIMAP_COMPLETION_FILE_NAMES    NULL

#define _VERIMAP_OPTIMISATION_LEVEL       0
#define _VERIMAP_TRANSFORMATION_LEVEL     0
#define _VERIMAP_CELEMENT_DELAY           0.565
#define _VERIMAP_OPTIMISATION_PARAMS      NULL
#define _VERIMAP_DELAY_MIN_PARAMS         "rise_min,fall_min"
#define _VERIMAP_DELAY_MAX_PARAMS         "rise_max,fall_max"
#define _VERIMAP_SP0_PORT_NAMES           NULL
#define _VERIMAP_SP1_PORT_NAMES           NULL
#define _VERIMAP_CLOCK_PORT_NAMES         "*.clk"
#define _VERIMAP_RESET_PORT_NAMES         "*.rst"
#define _VERIMAP_BUFFER                   0
#define _VERIMAP_RESET_ACTIVE             0

#define _VERIMAP_TOPMOST_MODULE_NAME      NULL
#define _VERIMAP_SINGLE_RAIL_WRAPPER      0
#define _VERIMAP_ALTERNATING_SPACER       0
#define _VERIMAP_STATISTICS_LEVEL         0
#define _VERIMAP_WIRES_LEVEL              0
#define _VERIMAP_WIRES_PATTERN            "always @(?) c=c+1;"

#define _VERIMAP_CMD_FILE_NAME            NULL
#define _VERIMAP_GCF_FILE_NAME            NULL
#define _VERIMAP_PATH_POSSIBILITY         1

//=== FILE OPTIONS
extern char* _verimap_program_name;
extern char* _verimap_input_file_names;
extern char* _verimap_output_file_name;
extern char* _verimap_full_file_name;
extern char* _verimap_include_file_names;
extern char* _verimap_lib_file_name;
extern char* _verimap_gen_file_name;
extern char* _verimap_rules_file_names;
extern char* _verimap_params_file_names;
extern char* _verimap_statistics_file_name;
extern char* _verimap_wires_file_name;
extern char* _verimap_assignments_file_names;
extern char* _verimap_completion_file_names;
//=== GENERAL OPTIONS
extern int _verimap_optimisation_level;
extern int _verimap_transformation_level;
extern float _verimap_celement_delay;
extern char* _verimap_optimisation_params;
extern char* _verimap_delay_min_params;
extern char* _verimap_delay_max_params;
extern char* _verimap_sp0_port_names;
extern char* _verimap_sp1_port_names;
extern char* _verimap_clock_port_names;
extern char* _verimap_reset_port_names;
extern int _verimap_buffer;
extern int _verimap_reset_active;
extern char* _verimap_topmost_module_name;
extern int _verimap_single_rail_wrapper;
extern int _verimap_alternating_spacer;
extern int _verimap_statistics_level;

extern int _verimap_wires_level;
extern char* _verimap_wires_pattern;

extern bool verimap_process_params(int argv, char **argc);
extern void verimap_clear_params();
extern void verimap_correct_params();

extern char* _verimap_cmd_file_name;
extern char* _verimap_gcf_file_name;
extern int _verimap_path_posibility;

#endif

