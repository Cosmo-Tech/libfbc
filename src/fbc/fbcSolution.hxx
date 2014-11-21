#ifndef __fbcSolution_hxx
#define __fbcSolution_hxx

#include <vector>
#include <iostream>
#include "lp_lib.h"
#include "fbcFluxes.hxx"

namespace fbc
{

class Solution
{
  private:
    double objectiveValue;
    fbc::Fluxes fluxes;
  public:
    Solution();
    Solution(lprec* solved_model);
    ~Solution();
    double getObjectiveValue();
    fbc::Fluxes getFluxes();
};

}

#endif
