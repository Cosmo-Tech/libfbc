#include "fbcFluxes.hxx"
#include "fbcLPProblem.hxx"
#include "lp_lib.h"

namespace fbc
{

/** \brief Constructor.
 *
 */
Fluxes::Fluxes()
{
}

/** \brief Constructor.
 * Extract flux keys and values from input "solved_model".
 * @param solved_model Pointer to a solved fbc::LPProblem model (i.e.
 * containing a solution).
 */
Fluxes::Fluxes(LPProblem* solved_model)
{
  int nrows = get_Nrows(solved_model->getLpModel());
  int ncols = get_Ncolumns(solved_model->getLpModel());
  REAL pv[1+nrows+ncols];
  get_primal_solution(solved_model->getLpModel(), pv);
  // extracting fluxes
  for (int i = 1; i <= ncols; i++)
  {
    fluxes[get_col_name(solved_model->getLpModel(), i)] = pv[i+nrows];
  }
}

/* \brief Destructor.
 *
 */
Fluxes::~Fluxes()
{
}

/** \brief Access an element of the map.
 * @param key A string.
 * @return The value associated with the input key.
 */
double Fluxes::get(const char* key)
{
  if (fluxes.find(key) == fluxes.end())
  {
    // key does not exist in fluxes
    std::cout << "Error: key " << key << " not found.\n";
    exit(EXIT_FAILURE);
  }
  else
  {
    return fluxes[key];
  }
}

}
