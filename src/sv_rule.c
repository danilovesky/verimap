#include "sv_rule.h"
#include "hash.h"

//---------------------------------------------------------------------------
Rule::Rule(int tag, char* name, char* prefix_dr, char* prefix_pd, char* prefix_pc, char* prefix_nd, char* prefix_nc, char* polarity) : VerilogObject(tag, name)
{
  this->prefix_dr = prefix_dr;
  this->prefix_pd = prefix_pd;
  this->prefix_pc = prefix_pc;
  this->prefix_nd = prefix_nd;
  this->prefix_nc = prefix_nc;
  this->polarity = polarity;
}

//---------------------------------------------------------------------------
Rule::Rule(const Rule &rule) : VerilogObject(rule)
{
  this->prefix_dr = namecopy(rule.prefix_dr);
  this->prefix_pd = namecopy(rule.prefix_pd);
  this->prefix_pc = namecopy(rule.prefix_pc);
  this->prefix_nd = namecopy(rule.prefix_nd);
  this->prefix_nc = namecopy(rule.prefix_nc);
  this->polarity = namecopy(rule.polarity);
}

//---------------------------------------------------------------------------
Rule::~Rule()
{
  delete [] prefix_dr;
  delete [] prefix_pd;
  delete [] prefix_pc;
  delete [] prefix_nd;
  delete [] prefix_nc;
  delete [] polarity;
}

