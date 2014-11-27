#include "fbcSolution.hxx"
#include "fbcLPProblem.hxx"
#include "lp_lib.h"

#include "fbcFluxes.hxx"

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
 * @param solved_model Pointer to a solved fbc::LPProblem (i.e. containing a
 * solution).
 */
Solution::Solution(LPProblem* solved_model)
{ 
  int nrows = get_Nrows(solved_model->getLpModel());
  int ncols = get_Ncolumns(solved_model->getLpModel());
  REAL pv[1+nrows+ncols];
  get_primal_solution(solved_model->getLpModel(), pv);
  objectiveValue = pv[0];
  fluxes = Fluxes(solved_model);
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
Fluxes* Solution::getFluxes()
{
  return &fluxes;
}

/** \brief Getter.
 * @return objectiveValue
 */
double Solution::getObjectiveValue()
{
  return objectiveValue;
}

}
