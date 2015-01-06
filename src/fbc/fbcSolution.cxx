#include "fbcSolution.hxx"
#include "fbcLPProblem.hxx"
#include "lp_lib.h"

#include "fbcFluxes.hxx"
#include "fbcFlux.hxx"
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
 * @param bc_lst Pointer to the list of boundary condition Species objects.
 */
Solution::Solution(LPProblem* solved_model, List* r_lst, List* bc_lst)
{ 
  int nrows = get_Nrows(solved_model->getLpModel());
  int ncols = get_Ncolumns(solved_model->getLpModel());
  REAL pv[1+nrows+ncols];
  get_primal_solution(solved_model->getLpModel(), pv);
  objectiveValue = pv[0];
  fluxes = Fluxes(solved_model, &*r_lst, &*bc_lst);
}

/* \brief Destructor.
 *
 */
Solution::~Solution()
{
}

/** \brief Getter.
 * 
 * @return A pointer to a Fluxes object containing only exchange Flux objects.
 */
Fluxes* Solution::getExchangeFluxes()
{
  Fluxes ex_fl;
  for (int i = 0; i < fluxes.getKeys().size(); i++)
  {
    Flux* flx = fluxes.get(fluxes.getKey(i).c_str());
    if (flx->isExchange())
    {
      ex_fl.add(flx);
    }
  }
  return &ex_fl;
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
