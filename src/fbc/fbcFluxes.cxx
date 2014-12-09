#include "fbcFluxes.hxx"
#include "fbcLPProblem.hxx"
#include "lp_lib.h"

#include "sbml/Reaction.h"
#include "sbml/util/List.h"

namespace fbc
{

/** \brief Constructor.
 *
 */
Fluxes::Fluxes()
{
}

/** \brief Constructor.
 *
 * Extract computed flux for each reaction implied in the input "solved_model".
 * This will be internally stored as a map with reaction identifier as
 * key and flux as value.
 * @param solved_model Pointer to a solved fbc::LPProblem model (i.e.
 * containing a solution).
 * @param r_lst Pointer to a List object containing Reaction instances.
 */
Fluxes::Fluxes(LPProblem* solved_model, List* r_lst)
{
  // dictionary of result is initialized based on the original problem
  for (int c = 0; c < r_lst->getSize(); c++)
  {
    Reaction* rt = (Reaction*) r_lst->get(c);
    fluxes[rt->getId()] = 0.0;
  }
  // extracting real flux values from solved model
  int nrows = get_Nrows(solved_model->getLpModel());
  int ncols = get_Ncolumns(solved_model->getLpModel());
  REAL pv[1+nrows+ncols];
  get_primal_solution(solved_model->getLpModel(), pv);
  for (int i = 1; i <= ncols; i++)
  {
    fluxes[get_origcol_name(solved_model->getLpModel(), i)] = pv[i+nrows];
  }
}

/** \brief Constructor.
 * 
 * Copy the content of the input "fl" object into "this"; only the identifier
 * and value of the Reaction objects listed in "er_lst" are considered.
 * @param fl Pointer to a Fluxes object.
 * @param er_lst Pointer to a List object containing Reaction instances.
 */
Fluxes::Fluxes(Fluxes* fl, List* er_lst)
{
  for (int i = 0; i < er_lst->getSize(); i++)
  {
    Reaction* rt = (Reaction*) er_lst->get(i);
    const char* id = rt->getId().c_str();
    fluxes[id] = fl->get(id);
  }
}

/* \brief Destructor.
 *
 */
Fluxes::~Fluxes()
{
}

/** \brief Access an element of the map.
 * @param key A string corresponding to the identifier of the reaction of 
 * interest. For example, "r_NNNN".
 * @return The value associated with the input key, i.e. the associated flux.
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

/** \brief Return the number of elements in "this".
 * @return An integer value.
 */
int Fluxes::size()
{
  return fluxes.size();
}

}
