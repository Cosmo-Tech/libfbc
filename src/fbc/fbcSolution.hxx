#ifndef __fbcSolution_hxx
#define __fbcSolution_hxx

#include <vector>
#include <iostream>
#include "fbcFluxes.hxx"

namespace fbc
{

class LPProblem;

class Solution
{
  private:
    double objectiveValue;
    Fluxes fluxes;
  public:
    Solution();
    Solution(LPProblem* solved_model);
    ~Solution();
    double getObjectiveValue();
    Fluxes* getFluxes();
};

}

#endif
