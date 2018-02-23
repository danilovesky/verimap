// Andrey Mokhov
//
// School of EECE
// University of Newcastle upon Tyne
//
// April 2006
//
// Email: Andrey.Mokhov@ncl.ac.uk, Andrey.Mokhov@gmail.com

#ifndef _CD_ENIGNE_H_
#define _CD_ENIGNE_H_

#include "sv_net.h"
#include "sv_module.h"
#include "sv_circuit.h"

#include <string>
#include <cstdio>
#include <string>
#include <queue>
#include <vector>
#include <map>

using namespace std;

#ifdef LINUX
  #include <ext/algorithm>
  #include <ext/hash_map>
  #include <ext/hash_set>

  namespace __gnu_cxx
  {
    template<class T> struct hash<T*>
    { size_t operator()(T*  const & x) const { return (size_t)x; } };
  }

  using namespace __gnu_cxx;
#else //if WIN32
  #include <algorithm>
  #include <hash_map>
  #include <hash_set>

  using namespace stdext;
#endif

//---------------------------------------------------------------------------
void setTimings(Circuit *circuit, float shrink = 1.0);
bool optimiseCD(Module *module, float celement2_min_delay, float tree2_min_delay, float tree3_min_delay);

#endif
