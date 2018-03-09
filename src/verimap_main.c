/*
Algorithm:
  + process command line
  + read input data
    + read rules for logic transformation
    + read library modules from include files
    + read previously generated modules from generated file
    + read circuit modules from input files
    + read parameters of modules
  + calculate hierarchy
    + calculate modules hierarchy
    + calculate instances hierarchy
  + calc topmost module
  + calc rail structure of the circuit
    + tag all ports as DR_SP0
    + tag specified ports as DR_SP1
    + tag specified ports as SR
    + expand SR ports
  + generate wrapper to interface single-rail environment
  + process advanced options for original circuit
    + output statistics into statistics file
    + output wires into wires file
  + convert data
    + apply negative logic optimisation
    + convert circuit into DR
    + optimise spacer converters
    + add CD
    + simplify circuit
  + process advanced options for modified circuit
    + output statistics into statistics file
    + output wires for into wires file
  + write generated modules into gen file
  + write circuit modules into output file
  + clean up
*/

#include <stdio.h>
#include "messages.h"
#include "verimap_params.h"
#include "sv_circuit.h"
#include "sv_lib.h"
#include "sv_module.h"
#include "cd_engine.h"

//---------------------------------------------------------------------------
void setPortsInfo(Circuit* circuit)
{
  circuit->setPortsInfo("*.*", TAG_ITEM_UNDECIDED, TAG_PORT_);
  circuit->setPortsInfo("*.*", TAG_ITEM_0DR, (TAG_PORT_INPUT | TAG_PORT_OUTPUT));
  if (_verimap_sp0_port_names)
  {
    circuit->setPortsInfo("*", TAG_ITEM_1DR, (TAG_PORT_INPUT | TAG_PORT_OUTPUT));
    circuit->setPortsInfo(_verimap_sp0_port_names, TAG_ITEM_0DR, (TAG_PORT_INPUT | TAG_PORT_OUTPUT));
  }
  else
  if (_verimap_sp1_port_names)
  {
    circuit->setPortsInfo("*", TAG_ITEM_0DR, (TAG_PORT_INPUT | TAG_PORT_OUTPUT));
    circuit->setPortsInfo(_verimap_sp1_port_names, TAG_ITEM_1DR, (TAG_PORT_INPUT | TAG_PORT_OUTPUT));
  }
  // define single rail wires
  circuit->setPortsInfo(_verimap_clock_port_names, TAG_ITEM_SR | TAG_NET_CLOCK, (TAG_PORT_INPUT | TAG_PORT_OUTPUT));
  circuit->setPortsInfo(_verimap_reset_port_names, TAG_ITEM_SR | TAG_NET_RESET, (TAG_PORT_INPUT | TAG_PORT_OUTPUT));
  circuit->calcPortsSR();
}

//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  Progress("Reading command line parameters");
  if (verimap_process_params(argc, argv))
  {
    Progress("Creating library object");
    Lib* lib = new Lib(NULL, NULL, NULL, Assignment::genDefaults());
    Progress("Creating circuit object");
    Circuit* circuit = new Circuit(TAG_UNDEFINED, NULL, NULL, lib);
    Module* module_top = NULL;
    Module* module_srw = NULL;

    // set assignments
    Progress("Reading assignments");
    lib->readAssignments(_verimap_assignments_file_names);

    // read library transformation rules
    Progress("Reading transformation rules");
    lib->readRules(_verimap_rules_file_names);

    // read library predefined modules
    Progress("Reading library modules");
    lib->readModules(_verimap_include_file_names);

    // read previously generated modules
    Progress("Reading generated modules");
    lib->readGens(_verimap_gen_file_name);
    
    // read parameters
    Progress("Reading parameters");
    lib->readParameters(_verimap_params_file_names);

    // calculate library modules parameters
    Progress("Setting library modules parameters");
//    lib->setModulesWidth(_verimap_gate_delay_param); // not needed?
    lib->setParameters(_verimap_delay_min_params, _verimap_delay_max_params);

    // calc hierarchy of the circuit
    Progress("Calculating library modules hierarchy");
    lib->calcHierarchy(lib->modules);

    // if it was required by a comand-line parameter, then write library information
    Progress("Generating the library");
    lib->writeLib(_verimap_lib_file_name, _verimap_optimisation_params);

    // read circuit
    Progress("Reading input files");
    circuit->readModules(_verimap_input_file_names);

    // converting the behavioural Verilog constants into vdd and gnd instances
    Progress("Converting constants");
    circuit->convertToConstants();

    // calc hierarchy of the circuit
    Progress("Calculating circuit hierarchy");
    circuit->calcHierarchy();

    // find the topmost module
    Progress("Calculating the topmost module");
    if (_verimap_topmost_module_name)
      module_top = circuit->setModuleTop(_verimap_topmost_module_name);
    else
      module_top = circuit->calcModuleTop();
    
    // calc tags
    Progress("Calculating tags");
    circuit->calcTags();

    // set ports properties DR_SP0, DR_SP1, SR
    Progress("Setting port attributes");
    setPortsInfo(circuit);

    // prepare to generate single-rail wrapper
    if (_verimap_single_rail_wrapper > 0)
      if (module_top)
        module_srw = module_top->copyInterface();
      else
        Error("topmost module name should be specified to build a single-rail wrapper");

    // output statistics for original circuit
    if ((_verimap_statistics_level & 1) == 1)
    {
      Progress("Collecting statistics for original circuit");
      circuit->writeStatistics(_verimap_statistics_file_name);
    }

    // output wires for original circuit
    if ((_verimap_wires_level & 1) == 1)
      circuit->writeWires(_verimap_wires_file_name, _verimap_wires_pattern);
    // spacer alternation mode
    if (_verimap_alternating_spacer > 0)
    {
      circuit->orTag(TAG_MODE_ALTERNATING_SPACER);
    }
    // active-1 reset
    if (_verimap_reset_active > 0)
    {
      circuit->orTag(TAG_MODE_RESET_ACTIVE_1);
    }
    // buffering done and spacer_polarity nets
    if (_verimap_buffer)
    {
      circuit->orTag(TAG_MODE_BUFFER);
      if (module_srw) module_srw->orTag(TAG_MODE_BUFFER);
    }
    // create the Pearl timing analisis command file
    if (_verimap_cmd_file_name)
      circuit->writeCMD(_verimap_cmd_file_name, _verimap_gcf_file_name, _verimap_input_file_names, _verimap_path_posibility);
    // convert circuit to DR
    if (_verimap_transformation_level >= 1)
    {
      // optimisation for specified parameters
      if (_verimap_optimisation_params)
      {
        Progress("Optimising for specified parameters");
        circuit->convertToOP(_verimap_optimisation_params);
      }
      else
      // optimise for negative gates
      if (_verimap_optimisation_level >= 1)
      {
        Progress("Optimising for negative logic");
        circuit->convertToNL();
      }
      // calc spacer distribution
      Progress("Calculating spacer distribution");
      circuit->calcSpacer();

      // optimisation of spacer distribution
      if (_verimap_optimisation_level >= 2)
      {
        Progress("Optimising spacer distribution");
        circuit->convertToOS();
      }
      // balance the spacer
      Progress("Balancing spacer");
      circuit->convertToBalanced();

      // actual transformation
      if (_verimap_transformation_level >= 2)
      {
        Progress("Converting to DR");
        circuit->convertToDR();
        if (_verimap_transformation_level >= 3)
        {
          // calc completion nets
          if (_verimap_optimisation_level >= 3)
          {
            Progress("Calculating completion nets");
            if (circuit->isBranchingHierarchical() || !module_top)
            {
              if (circuit->isBranchingHierarchical())
                Warning("cannot optimise completion detection logic in hierarchical netlist");
              if (!module_top)
                Warning("topmost module is needed to optimise completion detection logic");
              circuit->setAllCD();
            }
            else
            {
              // otpimise completion logic
              Progress("Setting library gates timing characteristics");
              setTimings(circuit, 1.0);
              float tree2_min_delay = lib->getMinDelay(VAR_TREE_2_INPUT);
              float tree3_min_delay = lib->getMinDelay(VAR_TREE_3_INPUT);
              Progress("Optimising completion detectors distribution %f, %f, %f", _verimap_celement_delay, tree2_min_delay, tree3_min_delay);
              if ( !optimiseCD(module_top, _verimap_celement_delay, tree2_min_delay, tree3_min_delay) )
              {
                Warning("cannot optimise completion detection logic");
                circuit->setAllCD();
              }
            }
          }
          else
            circuit->setAllCD();

          // add completion detection logic
          Progress("Adding completion");
          circuit->convertToCD();
        }
      }
    }

    // generate single-rail wrapper
    if (module_srw)
    {
      Progress("Generating single-rail wrapper");
      module_srw->setTag(module_top->getTag());
      module_srw->convertToWrapperSR();
      circuit->addModule(module_srw);
      circuit->setModuleTop(module_srw->getName());
    }

    // simplify the circuit (remove unattached wires, etc.)
    Progress("Removing redundant wires and gates");
    circuit->simplify();
    // statistics for transformed circuit
    if ((_verimap_statistics_level & 2) == 2)
    {
      Progress("Collecting statistics for resultant circuit");
      char* command_line = namecopy(argv[0]);
      for (int i = 1; i < argc; i++)
      {
        char* command_line_tmp = command_line;
        command_line = name2pattern("%s %s", command_line_tmp, argv[i]);
        delete [] command_line_tmp;
      }
      circuit->writeStatistics(_verimap_statistics_file_name, command_line);
      delete [] command_line;
    }

    // output wires for transformed circuit
    if ((_verimap_wires_level & 2) == 2)
      circuit->writeWires(_verimap_wires_file_name, _verimap_wires_pattern);

    // write generated modules into gen file
    Progress("Writing generated modules");
    lib->writeGens(_verimap_gen_file_name);

    // write the resultunt circuit into the output file
    Progress("Writing output file");
    circuit->writeModules(_verimap_output_file_name);

    // write full circuit output (required library DR modules and the circuit itself)
    if (_verimap_full_file_name)
    {
      Progress("Writing full output file");
      circuit->writeFullModules(_verimap_full_file_name);
    }

    // clean up
    Progress("Cleaning up circuit object");
    delete circuit;
    Progress("Cleaning up library object");
    delete lib;
  }
  Progress("Cleaning up command line parameters");
  verimap_clear_params();
  Progress("Done");
  return 0;
}

