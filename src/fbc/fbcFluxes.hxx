#ifndef __fbcFluxes_hxx
#define __fbcFluxes_hxx

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
    std::map<std::string,double> fluxes;
    std::vector<std::string> keys;
  public:
    Fluxes();
    Fluxes(LPProblem* solved_model, List* r_lst);
    Fluxes(Fluxes* fl, List* er_lst);
    ~Fluxes();
    double get(const char* key);
    std::string getKey(int index);
    std::vector<std::string> getKeys();
    int size();
};

}

#endif
