#include "fbcFluxes.hxx"

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
 * @param solved_model A LP model solved (i.e. containing a solution).
 */
Fluxes::Fluxes(lprec* solved_model)
{
  int nrows = get_Nrows(solved_model);
  int ncols = get_Ncolumns(solved_model);
  REAL pv[1+nrows+ncols];
  get_primal_solution(solved_model, pv);
  // extracting fluxes
  for (int i = 1; i <= ncols; i++)
  {
    fluxes[get_col_name(solved_model, i)] = pv[i+nrows];
  }
}

/* \brief Destructor.
 *
 */
Fluxes::~Fluxes()
{
}

/** \brief Access an element of the map.
 * @param key An std::string.
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
