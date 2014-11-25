#include <assert.h>
#include <math.h>
#include "fbcFBAProblem.hxx"

/** \brief Test for the flux bound editing API.
 * Loads a simple SBML model and unsets its flux bounds.
 */
int main (int argc, char *argv[])
{
  fbc::FBAProblem pbm;
  pbm.initFromSBMLFile(argv[1]);
  pbm.unsetLowerFluxBound("_J0");
  assert(pbm.getLowerFluxBound("_J0") == -1.0e30);
  pbm.unsetUpperFluxBound("_J1");
  assert(pbm.getUpperFluxBound("_J1") == 1.0e30);
  pbm.unsetFluxBound("_J2");
  assert(pbm.getUpperFluxBound("_J2") == 1.0e30);
  assert(pbm.getLowerFluxBound("_J2") == -1.0e30);
  return 0;
}
