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
 * Extract computed flux for each reaction in the input "solved_model".
 * This will be internally stored as a map with reaction identifier as
 * key and flux as value.
 * @param solved_model Pointer to a solved fbc::LPProblem model (i.e.
 * containing a solution).
 * @param r_lst Pointer to a List object containing Reaction instances.
 * @param bc_lst Pointer to a List object containing Species instances.
 */
Fluxes::Fluxes(LPProblem* solved_model, List* r_lst, List* bc_lst)
{
  // dictionary of result is initialized based on the original problem
  for (int c = 0; c < r_lst->getSize(); c++)
  {
    Reaction* rt = (Reaction*) r_lst->get(c);
    Flux* flx = new Flux(rt, 0.0, &*bc_lst);
    fluxes[const_cast<char*>(rt->getId().c_str())] = flx;
    keys.push_back(const_cast<char*>(rt->getId().c_str()));
  }
  // extracting real flux values from solved model
  int nrows = get_Nrows(solved_model->getLpModel());
  int ncols = get_Ncolumns(solved_model->getLpModel());
  REAL pv[1+nrows+ncols];
  get_primal_solution(solved_model->getLpModel(), pv);
  for (int i = 1; i <= ncols; i++)
  {
    fluxes[get_origcol_name(solved_model->getLpModel(), i)]->setValue(
      pv[i+nrows]);
  }
}

/* \brief Destructor.
 *
 */
Fluxes::~Fluxes()
{
}

/** \brief Add an item to the "fluxes" map.
 * The value of the added item is the input "flux" object, while its
 * associated key is the "id" attribute of this same "flux" object.
 * @param flux Pointer to a fbc::Flux object.
 */
void Fluxes::add(Flux* flux)
{
  std::string flx_id = flux->getId();
  if (fluxes.count(flx_id) != 0)
  {
    // key already exists in "fluxes"
    std::cout << "Error: key " << flx_id << " already exists.\n";
    exit(EXIT_FAILURE);
  }
  else
  {
    fluxes[const_cast<char*>(flx_id.c_str())] = flux;
    keys.push_back(const_cast<char*>(flx_id.c_str()));
  }
}

/** \brief Access an element of the map.
 * @param key A string corresponding to the identifier of the reaction of 
 * interest. For example, "r_NNNN".
 * @return The value associated with the input key, i.e. the associated flux.
 */
Flux* Fluxes::get(const char* key)
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

/* /brief Return the element at "index" in "keys".
 * @param index An integer value.
 * @return A string.
 */
std::string Fluxes::getKey(int index)
{
  if ( index < keys.size() )
  {
    return keys[index];
  }
  else
  {
    std::cout << "Error: index " << index << " out of range.\n";
    exit(EXIT_FAILURE);
  }
}

/* /brief Return "keys".
 * @return The list of keys of "fluxes" map.
 */
std::vector<std::string> Fluxes::getKeys()
{
  return keys;
}

/** \brief Return the number of elements in "this".
 * @return An integer value.
 */
int Fluxes::size()
{
  return fluxes.size();
}

}
