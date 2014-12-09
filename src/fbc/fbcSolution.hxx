#ifndef __fbcSolution_hxx
#define __fbcSolution_hxx

#include <vector>
#include <iostream>
#include "fbcFluxes.hxx"

class List;

namespace fbc
{

class LPProblem;

class Solution
{
  private:
    double objectiveValue;
    Fluxes exchangeFluxes;
    Fluxes fluxes;
  public:
    Solution();
    Solution(LPProblem* solved_model, List* r_lst, List* er_list);
    ~Solution();
    double getObjectiveValue();
    Fluxes* getExchangeFluxes();
    Fluxes* getFluxes();
};

}

#endif
