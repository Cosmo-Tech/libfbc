#ifndef __fbcFluxes_hxx
#define __fbcFluxes_hxx

#include <map>
#include <string>
#include <iostream>
#include "lp_lib.h"

namespace fbc
{

class Fluxes
{
  private:
    std::map<std::string,double> fluxes;
  public:
    Fluxes();
    Fluxes(lprec* solved_model);
    ~Fluxes();
    double get(const char* key);
};

}

#endif
