#include "fbcSolution.hxx"
#include "fbcLPProblem.hxx"
#include "lp_lib.h"

#include "fbcFluxes.hxx"
#include "sbml/util/List.h"

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
 * @param r_lst Pointer to the list of original flux Reaction objects.
 * @param er_lst Pointer to the list of exchange flux Reaction objects.
 */
Solution::Solution(LPProblem* solved_model, List* r_lst, List* er_lst)
{ 
  int nrows = get_Nrows(solved_model->getLpModel());
  int ncols = get_Ncolumns(solved_model->getLpModel());
  REAL pv[1+nrows+ncols];
  get_primal_solution(solved_model->getLpModel(), pv);
  objectiveValue = pv[0];
  fluxes = Fluxes(solved_model, &*r_lst);
  exchangeFluxes = Fluxes(&fluxes, &*er_lst);
}

/* \brief Destructor.
 *
 */
Solution::~Solution()
{
}

/** \brief Getter.
 * @return exchangeFluxes
 */
Fluxes* Solution::getExchangeFluxes()
{
  return &exchangeFluxes;
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
