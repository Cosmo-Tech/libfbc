#include <assert.h>
#include <math.h>
#include "fbcFBAProblem.hxx"

/** \brief Test for the flux bound editing API.
 * Loads a simple SBML model and modifies its flux bounds.
 */
int main (int argc, char *argv[])
{
  fbc::FBAProblem pbm;
  pbm.initFromSBMLFile(argv[1]);
  pbm.setFluxBound("_J0", "greaterEqual", 2.35);
  assert(pbm.getLowerFluxBound("_J0") == 2.35);
  pbm.setFluxBound("_J1", "lessEqual", 4.37);
  assert(pbm.getUpperFluxBound("_J1") == 4.37);
  pbm.setFluxBound("_J2", "equal", 6.53);
  assert(pbm.getUpperFluxBound("_J2") == 6.53);
  assert(pbm.getLowerFluxBound("_J2") == 6.53);
  return 0;
}
