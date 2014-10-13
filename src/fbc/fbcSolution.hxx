#ifndef __fbcSolution_hxx
#define __fbcSolution_hxx

#include <vector>

namespace fbc
{

class Solution
{
  private:
    double objectiveValue;
    std::vector<double> fluxes;
  public:
    Solution();
    ~Solution();
    double getObjectiveValue();
    std::vector<double> getFluxes();
};

}

#endif
