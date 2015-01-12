#include "fbcExchangeReactionFilter.hxx"

#include "sbml/SBase.h"
#include "sbml/Reaction.h"
#include "sbml/Species.h"
#include "sbml/util/List.h"

namespace fbc
{

/** /brief Constructor.
 * @param sp_lst Pointer to a List of Species objects.
 */
ExchangeReactionFilter::ExchangeReactionFilter(List* sp_lst)
: ElementFilter()
{
  speciesList = sp_lst;
}

/** Return true if the tested element is a Reaction instance containing at
 * least one reactant or product which is a boundary condition; return
 * false otherwise.
 * @param element An SBase instance to be tested.
 */
bool ExchangeReactionFilter::filter(const SBase* element)
{
  const Reaction* rt = dynamic_cast<const Reaction*>(element);
  if ( ( rt == NULL ) | ( speciesList == NULL ) )
  { 
    return false;
  }
  else
  {
    for (size_t i = 0; i < speciesList->getSize(); i++)
    {
      Species* sp = (Species*) speciesList->get(i);
      if ( ( rt->getReactant(sp->getId()) != NULL ) |
        ( rt->getProduct(sp->getId()) != NULL ) )
      {
        return true;
      }
    }
    return false;
  }
}

}
