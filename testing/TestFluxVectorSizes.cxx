#include <stdio.h>
#include <assert.h>
#include "fbcFBAProblem.hxx"

/** \brief Test the size of the resulting vectors of fluxes after resolution.
 * Loads an SBML model, solves it and check the size of its resulting vector
 * of fluxes and exchange fluxes.
 */
int main (int argc, char *argv[])
{
  fbc::FBAProblem pbm;
  pbm.initFromSBMLFile(argv[1]);
  pbm.solveProblem();
  assert(pbm.getSolution()->getFluxes()->size() == 2546);
  assert(pbm.getSolution()->getExchangeFluxes()->size() == 345);
  return 0;
}
