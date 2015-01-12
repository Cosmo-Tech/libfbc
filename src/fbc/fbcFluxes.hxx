#ifndef __fbcFluxes_hxx
#define __fbcFluxes_hxx

#include "fbcFlux.hxx"

#include <map>
#include <string>
#include <iostream>
#include <vector>

class List;

namespace fbc
{

class LPProblem;

class Fluxes
{
  private:
    std::map<std::string,Flux*> fluxes;
    std::vector<std::string> keys;
  public:
    Fluxes();
    Fluxes(LPProblem* solved_model, List* r_lst, List* bc_lst);
    ~Fluxes();
    void add(Flux* flux);
    Flux* get(const char* key);
    std::string getKey(size_t index);
    std::vector<std::string> getKeys();
    int size();
};

}

#endif
