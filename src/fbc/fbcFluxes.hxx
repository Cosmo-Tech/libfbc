#ifndef __fbcFluxes_hxx
#define __fbcFluxes_hxx

#include <map>
#include <string>
#include <iostream>

class List;

namespace fbc
{

class LPProblem;

class Fluxes
{
  private:
    std::map<std::string,double> fluxes;
  public:
    Fluxes();
    Fluxes(LPProblem* solved_model, List* r_lst);
    Fluxes(Fluxes* fl, List* er_lst);
    ~Fluxes();
    double get(const char* key);
    int size();
};

}

#endif
