#ifndef __fbcSolution_hxx
#define __fbcSolution_hxx

#include <vector>
#include <iostream>
#include "lp_lib.h"

namespace fbc
{

class Solution
{
  private:
    double objectiveValue;
    std::vector<double> fluxes;
  public:
    Solution();
    Solution(lprec* solved_model);
    ~Solution();
    double getObjectiveValue();
    std::vector<double> getFluxes();
};

}

#endif
