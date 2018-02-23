#include "cdopt_engine.h"
#include <stdio.h>
#include "messages.h"
#include "example_params.h"
#include "sv_circuit.h"
#include "sv_module.h"

#include <time.h>

#include <string>

using namespace std;

//---------------------------------------------------------------------------
void get23(int n,int &n2,int &n3)
{
	n3 = n/3;
	if (n%3==1) n3--;
	n2 = (n-3*n3)/2;
}

int levelsDelay(int n,int &lev)
{
  	if (n<3) return 0;
  	
  	int n2,n3;

  	int delay = 0;

  	lev = 0;

  	while(n>1)
  	{
	   	get23(n,n2,n3);
	   	n = n2+n3;
	   	lev++;
	   	if (n2) delay += getLibLower("and2"); else delay += getLibLower("and3");
  	}

  	return delay;
}

int main(int argc, char* argv[])
{
  if (example_process_params(argc, argv))
  {
    if (!_example_timefile_name || !_example_celement_delay || !_example_module_name)
    {
    	puts("Not all the needed input parameters specified. Use -h option for help.");
    	example_clear_params();
    	return 0;
    }
    
    Circuit* circuit = new Circuit();
    Module* module = NULL;
    // read library predefined modules
    Progress("Reading library modules");
    circuit->readVerilog(_example_include_file_names, MODULE_TYPE_ELEMENTARY);
    // read circuit
    Progress("Reading input files");
    circuit->readVerilog(_example_input_file_names, MODULE_TYPE_COMPOUND);
    // calc hierarchy of the circuit
    Progress("Calculating circuit hierarchy");
    circuit->calcHierarchy();

    module = circuit->getModule(_example_module_name);
    
    setEcho(true);
    setCircuit(circuit);

    float shrink = 1.0;

    if (_example_shrink_delay) sscanf(_example_shrink_delay,"%lf",&shrink);


    loadTimings(_example_timefile_name, shrink);

    int delay;
    sscanf(_example_celement_delay,"%d",&delay);

    calculateModuleTiming(module);

    int time = clock();

    int a = 2, b = 1024, c, res=1024, rh = -1;

    int runs = 0;

    FILE *pix = fopen("!!!pix_out","w");
    setPixelOut(true, pix);

    while(a!=b-1)
    {
    	c = (a+b)/2;

    	int lev;
    	int dtree = delay + levelsDelay(c,lev);

	    setDeltaCElement(dtree);

    	printf("\n\nRunning analysis with multi-input C-element delay = %d; tree height = %d...\n\n",dtree,lev);

	    int used = cdopt(module);
	    runs++;

    	fprintf(pix, "\n\n\n----------------------------------------------------------------------------------\n\n");

	    if (Error()) { a = c; continue;}

	    if (used > c) { a = c; continue;}

	    b = c;
	     
    	res = used; rh = dtree;
    }

    fclose(pix);

    time = clock()-time;

    printf("Result with %d cd blocks (dtree = %d) was accepted as a final decision.\n",res,rh);
    
    printf("\n\n%d runs finished in %d milliseconds.\n",runs,time);

    printf("Average run time = %d\n",time/runs);

    puts("\n\n\n----------------------------------------------------------------------------------\n");

    puts("CD blocks placement:\n");

    printCDs();

    delete circuit;
  }

  example_clear_params();

  return 0;
}
