#include "fbcSolution.hxx"

namespace fbc
{

/** \brief Constructor.
 *
 */
Solution::Solution()
{
}

/** \brief Constructor.
 * Extract objective value and fluxes from input "solved_model".
 * @param solved_model A LP model solved (i.e. containing a solution).
 */
Solution::Solution(lprec* solved_model)
{
  int nrows = get_Nrows(solved_model);
  int ncols = get_Ncolumns(solved_model);
  REAL pv[1+nrows+ncols];
  get_primal_solution(solved_model, pv);
  objectiveValue = pv[0];
  // extracting fluxes
  for (int i = nrows +1; i <= nrows + ncols; i++)
  {
    fluxes.push_back(pv[i]);
  }
}

/* \brief Destructor.
 *
 */
Solution::~Solution()
{
}

/** \brief Getter.
 * @return fluxes
 */
std::vector<double> Solution::getFluxes()
{
  return fluxes;
}

/** \brief Getter.
 * @return objectiveValue
 */
double Solution::getObjectiveValue()
{
  return objectiveValue;
}

}
