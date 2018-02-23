// Andrey Mokhov
//
// School of EECE
// University of Newcastle upon Tyne
//
// April 2006
//
// Email: Andrey.Mokhov@ncl.ac.uk, Andrey.Mokhov@gmail.com

#include <stdio.h>
#include "cd_engine.h"
#include "messages.h"

//===========================================================================
Circuit* cd_circuit;
int cd_indent = 0;
map<string,int> gatesCount; // number of primitive gates in module
const int inf = 2147483647;
const int nanosecond = 1000; // so int can hold up to 10^6 nanoseconds
int dC = nanosecond; // deltaC is equal to 1 nanosecond (default value)
int celement2_min_delay_ps;
int tree2_min_delay_ps;
int tree3_min_delay_ps;
map<Module*, int> cdCount;    // number of cd blocks used
map<Module*, int> layersCount;  // number of layers
hash_set<Net*> cds;       // set of nets with completion detection   !!!! hash_set is NOT ANSI
hash_map<Instance*,Module*> itom; // !!!! hash_map is NOT ANSI

//---------------------------------------------------------------------------
struct TimeInterval
{
  int lower, upper;
  TimeInterval() : lower(0), upper(0) {}
  TimeInterval(int lower, int upper) : lower(lower), upper(upper) {}
};

map<string,TimeInterval> libModuleTimeInterval;
hash_map<Module*,TimeInterval> moduleTimeInterval; // !!!! hash_map is NOT ANSI

//---------------------------------------------------------------------------
void calcLayer23(int n,int &n2,int &n3)
{
   n3 = n/3;
   if (n%3 == 1) n3--;
   n2 = (n-3*n3)/2;
}

//---------------------------------------------------------------------------
int calcTree23Delay(int n, int &lev)
{
  if (n < 3) return 0;
  int n2,n3;
  int delay = 0;
  lev = 0;
  while(n > 1)
  {
    calcLayer23(n, n2, n3);
    n = n2 + n3;
    lev++;
    
    if (tree2_min_delay_ps <= tree3_min_delay_ps)
    {
      if (n2) delay += tree2_min_delay_ps; 
      else delay += tree3_min_delay_ps;
    }
    else
    {
      if (n3) delay += tree3_min_delay_ps; 
      else delay += tree2_min_delay_ps;
    }
  }
  return delay;
}

//---------------------------------------------------------------------------
void setCelementDelay(int delay)
{
  dC = delay;
}

//---------------------------------------------------------------------------
int inline getLower(Module *module)
{
  if (!moduleTimeInterval.count(module)) return -1;
  return moduleTimeInterval[module].lower;
}

//---------------------------------------------------------------------------
int inline getUpper(Module *module)
{
  if (!moduleTimeInterval.count(module)) return -1;
  return moduleTimeInterval[module].upper;
}

//---------------------------------------------------------------------------
void inline setModuleTimeInterval(Module *module, TimeInterval ti)
{
  moduleTimeInterval[module] = ti;
}

//---------------------------------------------------------------------------
int getLibLower(string name)
{
  int i;
  if (!libModuleTimeInterval.count(name)) return -1;
  return libModuleTimeInterval[name].lower;
}

//---------------------------------------------------------------------------
int getLibUpper(string name)
{
  int i;
  if (!libModuleTimeInterval.count(name)) return -1;
  return libModuleTimeInterval[name].upper;
}

//===========================================================================
struct Vertex
{
  Instance *inst;    // instance
  int f;             // f-funcion for the current layer
  int f_lo;          // f-funcion for the current layer (lower estimation)
  vector<int> g;     // array for g-function evaluation
                     // g[i] represents shortest distance to output i of the Layer #1
  int delta;         // delta = f - max(g)
                     // redundant, introduced for optimisation purposes only
  int cnt;           // number of outputs to process
  bool operator<(const Vertex &v) const
  {
    if (cnt!=v.cnt) return cnt<v.cnt;
    return delta<v.delta;
  }
};


//===========================================================================
struct PriorityQueue
{
  Vertex *heap;
  int size;
  int n;
  hash_map<Instance*, int> pos; // position of instance in heap   !!!! hash_map is NOT ANSI

  PriorityQueue() : heap(NULL), size(0), n(0) 
  {
  }
  
  PriorityQueue(int size)
  {
    heap = new Vertex[size+1];
    this->size = size;
    heap[0].cnt = -1;
    n = 0;
  }
  
  ~PriorityQueue()  
  {  
    if (heap) delete [] heap; 
  }

  bool empty()   
  {  
    return (n == 0);
  }

  int count()  
  {  
    return n;  
  }

  void push(Vertex &v)
  {
    n++;
    int k = n, up = k/2;
    while(v < heap[up])
    {
      heap[k] = heap[up];
      pos[heap[k].inst] = k;
      k = up;
      up/=2;
    }
    heap[k] = v;
    pos[v.inst] = k;
  }

  void rebuildHeap()
  {
    int i;
    for(i=n/2; i>=1; i--)
    {
      int k = i, down = 2*i;
      Vertex v = heap[k];
      while(down<=n)
      {
        if (down<n && heap[down+1] < heap[down]) down++;
        if (heap[down] < v)
        {
          heap[k] = heap[down];
          pos[heap[k].inst] = k;
          k = down;
          down*=2;
        }
        else break;
      }
      heap[k] = v;
      pos[v.inst] = k;
    }
  }

  Vertex top()
  {
    return heap[1];
  }

  void pop()
  {
    pos[heap[1].inst] = 0;
    Vertex v = heap[n--];

    int k = 1, down = 2;
    while(down<=n)
    {
      if (down<n && heap[down+1] < heap[down]) down++;
      if (heap[down] < v)
      {
        heap[k] = heap[down];
        pos[heap[k].inst] = k;
        k = down;
        down*=2;
      }
      else break;
    }
    heap[k] = v;
    pos[v.inst] = k;
  }

  Vertex getVertex(Instance *inst)
  {
    return heap[pos[inst]];
  }

  bool contains(Instance *inst)
  {
    return (pos[inst] != 0);
  }

  void update(Vertex &v)
  {
    int k = pos[v.inst];
    if (!k) return;
    int up = k/2, down = 2*k;

    if (v < heap[up]) // should sift up
    {
      while(v < heap[up])
      {
        heap[k] = heap[up];
        pos[heap[k].inst] = k;
        k = up;
        up/=2;
      }
      heap[k] = v;
      pos[v.inst] = k;
    }

    // sift down if needed

    while(down<=n)
    {
      if (down<n && heap[down+1] < heap[down]) down++;
      if (heap[down] < v)
      {
        heap[k] = heap[down];
        pos[heap[k].inst] = k;
        k = down;
        down*=2;
      }
      else break;
    }

    heap[k] = v;
    pos[v.inst] = k;
  }

  int place_cd(int x=1) // place cd blocks on instances' outputs with cnt==0
  {
    if (x<0 || x>n || heap[x].cnt != 0) return 0;
    int added = -cds.size();
    Instance *inst = heap[x].inst;
    int n = inst->connections->num;
    for(int i=0; i<n; i++)
    {
      Connection *conn = (*(inst->connections))[i];
      if ( conn->testTag(TAG_PORT_OUTPUT) )
            {
        int m = conn->nets->num;
        for(int j=0; j<m; j++) cds.insert((*(conn->nets))[j]);
            }
    }
    added += cds.size();
    return added + place_cd(x*2) + place_cd(x*2+1);
  }

  void print()
  {
    string out="";
    char t[100];
    sprintf(t,"%d vertices:",n); out+=t;
    for(int i=1; i<=n; i++)
    {
      if (i>1) out+=",";
      out+=" ";
      char* instance_full_name = heap[i].inst->genFullName();
      sprintf(t,"<%s>(cnt=%d,delta=%d)", instance_full_name, heap[i].cnt, heap[i].delta);
      delete [] instance_full_name;
      out+=t;
    }
    Message(out.c_str());
  }
};


//===========================================================================

//---------------------------------------------------------------------------
Module *getModule(Instance *instance)
{
  if (itom.count(instance)) return itom[instance];
  Module * mo = cd_circuit->lib->getModule(instance->getModuleName());
  itom[instance] = mo;
  return mo;
}
//---------------------------------------------------------------------------
void calculateModuleTiming(Module *mo)
{

  if (mo == NULL || getLower(mo) != -1) return; // already calculated
  string name = mo->getName();
  
  if (getLibLower(name)!=-1) // is library gate
  {
    cdCount[mo] = 0;
    layersCount[mo] = 0;
    setModuleTimeInterval(mo, TimeInterval(getLibLower(name), getLibUpper(name)) );
    return;
  }
  
  cd_indent+=2;
  hash_map<Instance*, int> cnt;   // !!!! hash_map is NOT ANSI
  hash_map<Instance*, int> lower; // !!!! hash_map is NOT ANSI
  hash_map<Instance*, int> upper; // !!!! hash_map is NOT ANSI

  hash_set<Instance*> seen; // !!!! hash_set is NOT ANSI
  
  int i,j,k,n,m,l;
  int gatesCounter = 0;
  queue<Instance*> ready;
  Connection *conn;
  Instance   *inst;
  Module     *modu;
  Port       *port;
  Net        *net;

  n = mo->instances->num;
  for(i=0; i<n; i++)
  {
    inst = (*(mo->instances))[i];
    modu = getModule(inst);
    if (modu == NULL) continue; //!!!
    calculateModuleTiming(modu);
    gatesCounter += gatesCount[modu->getName()];
    m = inst->connections->num;
    seen.clear();

    for(j=0; j<m; j++)
    {
      conn = (*(inst->connections))[j];
      if ( conn->testTag(TAG_PORT_OUTPUT) && conn->nets)
      {
        l = conn->nets->num;
        for(k=0; k<l; k++)
        {
          net = (*(conn->nets))[k];
          if (net)
          {
            if (net->postset)
            { 
              int nn = net->postset->num;
              for(int z=0; z<nn; z++) seen.insert((*(net->postset))[z]);
            }
          }
        }
      }
    }
    cnt[inst] = seen.size();
    if (!cnt[inst]) ready.push(inst);
  }
  // ready contains instances whose outputs are connected to the module outputs only
  int L = 0, U = 0;
  while(!ready.empty())
  {
    inst = ready.front();
    ready.pop();

    int lo = lower[inst] + getLower(getModule(inst));
    int up = upper[inst] + getUpper(getModule(inst));
    n = inst->connections->num;
    seen.clear();

    for(i=0; i<n; i++)
    {
      conn = (*(inst->connections))[i];
      if ( conn->testTag(TAG_PORT_INPUT) )
      {
        m = conn->nets->num;
        for(j=0; j<m; j++)
        {
          net = (*(conn->nets))[j];
          if (net)
          {
            if ( net->preset && net->preset->num )
            {
              l = net->preset->num;
              for(k=0; k<l; k++)
              {
                Instance *inst = (*(net->preset))[k];
                if (seen.count(inst)) continue;
                seen.insert(inst);
                cnt[inst]--;
                if (lower[inst] < lo) lower[inst] = lo;
                if (upper[inst] < up) upper[inst] = up;
                if (!cnt[inst]) ready.push(inst);
              }
            }
            else
            {
              if (L < lo) L = lo;
              if (U < up) U = up;
            }
          }
        }
      }
    }
  }
  setModuleTimeInterval(mo, TimeInterval(L, U));
  gatesCount[name] = gatesCounter;
  cd_indent-=2;
  Message("%*sdelay interval of module <%s>: [%d; %d]ps", cd_indent, "", name.c_str(), L, U);
}

//---------------------------------------------------------------------------
// LATCH FIX
bool isLatch(Instance *inst)
{
   string s = inst->getModuleName();
   int l = s.size();
   if (l>2 && (s[l-3]=='0' || s[l-3]=='1') && s[l-2] == 'd' && s[l-1] == 'r') return true;
   return false;
}

//---------------------------------------------------------------------------
bool placeCD(Module *mo)
{
  if (!mo || cdCount.count(mo))  // module has already been processed 
    return true; 
    
  string name=mo->getName();
  
  // no cd needed for library gates
  if (getLibLower(name)!=-1) // is library gate
  {
    cdCount[mo] = layersCount[mo] = 0;
    setModuleTimeInterval(mo, TimeInterval(getLibLower(name), getLibUpper(name)));
    return true;
  }

  // no cd needed for dual-rail library gates
  int l=name.size();
  if (name[l-4]=='_' && (name[l-3]=='p' || name[l-3]=='n') && name[l-2]=='d' && name[l-1]=='r')
  {
    string short_name=name;
    short_name.erase(l-4,4);
    if (getLibLower(short_name) != -1) // dual-rail library gate
    {
      cdCount[mo] = 0;
      layersCount[mo] = 0;
      calculateModuleTiming(mo);
      return true;
    }
  }
  Message("%*soptimising completion detection for module <%s>", cd_indent, "", name.c_str());
  cd_indent+=2;

  int n,m,i,j,k;
  Connection *conn;
  Instance   *inst;
  Instance   *next;
  Module     *modu;
  Port       *port;
  Net        *net;
  Vertex     v,nv;
  int gatesCounter = 0;
  int cd_count = 0;
  int pxCnt = 0;
  hash_set<Instance*> seen; // !!!! hash_set is NOT ANSI 

  n = mo->instances->num;
  PriorityQueue pq(n);

  // push all instances to PriorityQueue pq
  for(i=0; i<n; i++)
  {
    inst = (*(mo->instances))[i];
    if (isLatch(inst)) continue; 
    
    modu = getModule(inst);
    if (modu == NULL) continue; ///!!!
    if ( !placeCD(modu) )
    {
      cd_indent-=2;
      return false;
    }
    cd_count += cdCount[modu];

    int lo = getLower(modu);
    int up = getUpper(modu);

    gatesCounter += gatesCount[modu->getName()];
    m = inst->connections->num;
    seen.clear();

    v.inst = inst;
    v.f    = up;
    v.f_lo = lo;

    for(j=0; j<m; j++)
    {
      conn = (*(inst->connections))[j];
      if ( conn->testTag(TAG_PORT_OUTPUT) && conn->nets)
      {
        l = conn->nets->num;
        for(k=0; k<l; k++)
        {
           net = (*(conn->nets))[k];
           if (net) 
           {
             if (net->postset) 
             {
             	int nn = net->postset->num;
               for(int z=0; z<nn; z++) 
                 if (!isLatch((*(net->postset))[z]))  // LATCH FIX
                   seen.insert((*(net->postset))[z]);
             }
           }
        }
      }
    }
    v.cnt = seen.size(); // each instance is linked twice on dual rails
    v.delta = v.f; // it's layer 0 so g is ignored
    pq.push(v);
  }
  gatesCount[mo->getName()] = gatesCounter;

  // layer 0 construction
  int popped = 0;
  bool no_cd = true;
  int minStab = 0;
  pxCnt = 0;

  while(!pq.empty())
  {
    v = pq.top(); 
    if (v.delta > dC) { no_cd = false; break; }
    pxCnt--;
    pq.pop();
    popped++;
    inst = v.inst;
    if (v.cnt != 0)
    {
    	char* instance_full_name = v.inst->genFullName();
      Warning("%*sinstance <%s> dequeued with cnt=%d, f=%d, g=%d\n", 
        cd_indent, "", instance_full_name, v.cnt, v.f, v.f-v.delta);
      delete [] instance_full_name;
      pq.print();
    }
    n = inst->connections->num;
    seen.clear();
    for(i=0; i<n; i++)
    {
      conn = (*(inst->connections))[i];
      if (conn->testTag(TAG_PORT_INPUT))
      {
        m = conn->nets->num;
        for(j=0; j<m; j++)
        {
          net = (*(conn->nets))[j]; if (!net) continue;
          if (net->preset)
          { 
	          l = net->preset->num;
	          for(k=0; k<l; k++)
	          {
               next = (*(net->preset))[k];
               if (isLatch(next)) continue;  // LATCH FIX
	            if (seen.count(next)) continue;
	            seen.insert(next);
	            nv = pq.getVertex(next);
	            nv.cnt--;
	            nv.delta = nv.f = max(nv.f, v.f + getUpper(getModule(next)));
	            nv.f_lo = max(nv.f_lo, v.f_lo + getLower(getModule(next)));
	            if (minStab < v.f_lo) minStab = v.f_lo;
	            pq.update(nv);
	          }
          }
        }
      }
    }
  }
  Message("%*slayer #0 closed after %d instances added (minimal stabilisation time = %d)", 
    cd_indent, "", popped, minStab);

  int layer = 0;
  int no = 0; // number outputs of layer 1
  hash_map<Net*, int> outs; // !!!! hash_map is NOT ANSI 

  if (no_cd) // no cd needed: layer 0 is wider than the module
    goto finish;

  cd_count = pq.place_cd(); // place cd on outputs of layer 1

  for(i=1; i<=pq.count(); i++)
  {
    inst = pq.heap[i].inst;
    n = inst->connections->num;
    for(j=0; j<n; j++)
    {
      conn = (*(inst->connections))[j];
      if ( conn->testTag(TAG_PORT_OUTPUT) )
      {
        m = conn->nets->num;
        for(k=0; k<m; k++)
        {
          net = (*(conn->nets))[k]; if (!net) continue;
          l = 0;
          if (net->postset) l = net->postset->num;
          if (!l) { outs[net] = no++; continue;}
          bool external = false;
          // LATCH FIX not needed for pq as it does not contain latches
          for(int z=0; z<l; z++) if (!pq.contains((*(net->postset))[z])) { external = true; break;}
          if (external) outs[net] = no++;
        }
      }
    }
  }

  for(i=1; i<=pq.count(); i++)
  {
    v = pq.heap[i];
    v.g.resize(no);
    for(j=0; j<no; j++) v.g[j] = inf;
    inst = v.inst;
    n = inst->connections->num;
    l = getLower(getModule(inst));
    v.f = getUpper(getModule(inst));
    for(j=0; j<n; j++)
    {
      conn = (*(inst->connections))[j];
      if ( conn->testTag(TAG_PORT_OUTPUT) )
      {
        m = conn->nets->num;
        for(k=0; k<m; k++)
        {
          net = (*(conn->nets))[k]; if (!net) continue;
          if (outs.count(net)) v.g[outs[net]] = l;
        }
      }
    }
    int g = 0;
    for(j=0; j<no; j++) if (v.g[j]!=inf && v.g[j] > g) g = v.g[j];
    v.delta = v.f - g;
    pq.heap[i] = v;
  }
  pq.rebuildHeap();

  // process all the other layers
  layer = 1; // current layer
  popped = 0;

  pxCnt = 0;
  while(!pq.empty())
  {
    v = pq.top(); 
    if (v.delta <= dC) // fits to the current layer
    {
      pxCnt--;
      pq.pop();
      popped++;

      n = v.inst->connections->num;

      if (v.cnt != 0)
      {
        char* instance_full_name = v.inst->genFullName();
        Warning("%*sinstance <%s> dequeued with cnt=%d, f=%d, g=%d\n", 
          cd_indent, "", instance_full_name, v.cnt,v.f, v.f-v.delta);
        delete [] instance_full_name;
        pq.print();
      }
      seen.clear();

      for(i=0; i<n; i++)
      {
        conn = (*(v.inst->connections))[i];
        if ( conn->testTag(TAG_PORT_INPUT) )
        {
          m = conn->nets->num;
          for(j=0; j<m; j++)
          {
            net = (*(conn->nets))[j]; if (!net) continue;
            if (net->preset)
            {
	            l = net->preset->num;
	            for(k=0; k<l; k++)
	            {
                 inst = (*(net->preset))[k];
                 if (isLatch(inst)) continue; // LATCH FIX
	              if (seen.count(inst)) continue;
	              seen.insert(inst);
	              modu = getModule(inst);
	              int lo = getLower(modu), up = getUpper(modu);
	              nv = pq.getVertex(inst);
	              nv.f = max(nv.f, v.f + up);
	              int o,g = 0;
	              for(o=0; o<no; o++)  if (v.g[o] != inf) nv.g[o] = min(nv.g[o], v.g[o] + lo);
	              for(o=0; o<no; o++) if (nv.g[o] != inf && g < nv.g[o]) g = nv.g[o];
	              nv.delta = nv.f - g;
	              nv.cnt--;
	              pq.update(nv);
	            }
            }
          }
        }
      }
    }
    else // close the current layer
    {
      Message("%*slayer #%d closed after %d instances added", cd_indent, "", layer, popped);
      if (popped == 0)
      {
        Warning("C-element is way too fast");
        cd_indent-=2;
        return false;
      }
      popped=0;
      cd_count += pq.place_cd(); // place cd before the closed layer

      for(i=1; i<=pq.count(); i++)
      {
        int was_f = pq.heap[i].f;
        pq.heap[i].f = getUpper(getModule(pq.heap[i].inst));
        pq.heap[i].delta += pq.heap[i].f - was_f;
      }
      pq.rebuildHeap();
      layer++;
    }
  }

finish:
  cdCount[mo] = cd_count/2;
  layersCount[mo] = layer + 1;
  n = layersCount[mo];
  Message("%*smodule <%s> successfully processed (%d gates, %d layers, %d completions)", 
    cd_indent, "", name.c_str(), gatesCounter, layersCount[mo], cdCount[mo]);
  cd_indent-=2;
  return true;
}

//---------------------------------------------------------------------------
void setTimings(Circuit* circuit, float shrink)
{
  cd_circuit = circuit;
  libModuleTimeInterval.clear();
  moduleTimeInterval.clear();

  TimeInterval t;
  for (int i = 0; i < cd_circuit->lib->modules->num; i++)
  {
    Module* module_cur = cd_circuit->lib->modules->arr[i];
    if (module_cur->hasTimingInfo())
    {
      t.lower = int( module_cur->getMinDelay() * nanosecond+0.5 );
      t.upper = int( module_cur->getMaxDelay() * nanosecond+0.5 );
      t.upper = int( t.lower + (t.upper - t.lower)*shrink + 0.5 );
      libModuleTimeInterval[module_cur->getName()] = t;
      gatesCount[module_cur->getName()] = 1;
    }
  }
}

//---------------------------------------------------------------------------
void saveCD()
{
  hash_set<Net*>::iterator p,q;
  p=cds.begin(); q=cds.end();
  while (p!=q)
  {
    (*p++)->orTag(TAG_OBJ_CD);
  }
}

//---------------------------------------------------------------------------
int findCD(Module *module)
{
  cdCount.clear();
  layersCount.clear();
  cds.clear();
  itom.clear();
  if ( placeCD(module) )
    return cdCount[module];
  else
    return 0;
}
 
//---------------------------------------------------------------------------
bool optimiseCD(Module *module, float celement2_min_delay, float tree2_min_delay, float tree3_min_delay)
{
  calculateModuleTiming(module);
  celement2_min_delay_ps = int ( celement2_min_delay * nanosecond + 0.5 );
  tree2_min_delay_ps = int ( tree2_min_delay * nanosecond + 0.5 );
  tree3_min_delay_ps = int ( tree3_min_delay * nanosecond + 0.5 );
  cd_indent = 0;
  const int c_min = 1;
  const int c_max = 1024;
  
  int a = c_min;
  int b = c_max;
  int c;
  int res= c_max;
  int rh = -1;
  while(a != b-1)
  {
    c = (a+b)/2;
    int lev;
    int dtree = celement2_min_delay_ps + calcTree23Delay(c, lev);
    setCelementDelay(dtree);
    Message("%*strying %d-input C-element (%d-layer tree, %g ns minimum delay)", 
      cd_indent, "", c, lev, dtree/100.0);
    cd_indent += 2;
    int used = findCD(module) + 1; // + go signal
    cd_indent -= 2;
    Message("%*sneeded %d-input C-element", cd_indent, "", used); 
    if ( (used < c_min) || (used > c) ) 
    { 
      a = c;
      continue;
    }
    b = c;
    res = used; rh = dtree;
  }
  if ( (res > c_min) && (res < c_max) )
  {
    saveCD();
    return true;
  }
  else
    return false;
}
