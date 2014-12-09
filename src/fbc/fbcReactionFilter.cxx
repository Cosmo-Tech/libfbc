#include "fbcReactionFilter.hxx"

#include "sbml/SBase.h"
#include "sbml/Reaction.h"

namespace fbc
{

/** Return true if the tested element is a Reaction instance; return false
 * otherwise.
 * @param element An SBase instance to be tested.
 */
bool ReactionFilter::filter(const SBase* element)
{
  const Reaction* rt = dynamic_cast<const Reaction*>(element);
  if (rt == NULL)
  { 
    return false;
  }
  else
  {
    return true;
  }
}

}
