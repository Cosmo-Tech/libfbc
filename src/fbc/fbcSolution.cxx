#include "fbcSolution.hxx"

namespace fbc
{

Solution::Solution()
{
  //TODO
}

Solution::~Solution()
{
  //TODO
}

std::vector<double> Solution::getFluxes()
{
  return fluxes;
}

double Solution::getObjectiveValue()
{
  return objectiveValue;
}

}
