#include <stdio.h>
#include <assert.h>
#include "fbcFBAProblem.hxx"
#include "fbcFlux.hxx"

/** \brief Tests the API of the fbc::Flux class.
 * Loads an SBML model, solves it and checks the output of various methods of
 * the fbc::Flux class public API.
 */
int main (int argc, char *argv[])
{
  fbc::FBAProblem pbm;
  pbm.initFromSBMLFile(argv[1]);
  pbm.solveProblem();
  fbc::Flux* flx = pbm.getSolution()->getFluxes()->get("R_14GLUCANabcpp");
  assert(flx->getProductIds().size() == 4);
  assert(flx->getReactantIds().size() == 3);
  assert(flx->isSink() == false);
  assert(flx->isSource() == false);
  assert(flx->isExchange() == false);
  assert(flx->isBCProduct() == false);
  assert(flx->isBCReactant() == false);
  return 0;
}
