#ifndef __fbcFluxes_hxx
#define __fbcFluxes_hxx

#include <map>
#include <string>
#include <iostream>

namespace fbc
{

class LPProblem;

class Fluxes
{
  private:
    std::map<std::string,double> fluxes;
  public:
    Fluxes();
    Fluxes(LPProblem* solved_model);
    ~Fluxes();
    double get(const char* key);
};

}

#endif
