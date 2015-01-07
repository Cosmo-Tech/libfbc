#include <stdio.h>
#include <assert.h>
#include "fbcFBAProblem.hxx"
#include "fbcFlux.hxx"

/** \brief Tests the API of the fbc::Flux class for an exchange flux.
 * Loads an SBML model, solves it and checks the output of various methods of
 * the fbc::Flux class public API in the case of an exchange flux.
 */
int main (int argc, char *argv[])
{
  fbc::FBAProblem pbm;
  pbm.initFromSBMLFile(argv[1]);
  pbm.solveProblem();
  fbc::Flux* flx = pbm.getSolution()->getFluxes()->get("R_EX_ac_e");
  assert(flx->getProductIds().size() == 1);
  assert(flx->getReactantIds().size() == 1);
  assert(flx->isExchange() == true);
  assert(flx->isBCProduct() == true);
  assert(flx->isBCReactant() == false);
  return 0;
}
