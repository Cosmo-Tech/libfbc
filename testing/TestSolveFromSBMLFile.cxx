#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "fbcFBAProblem.hxx"

/** \brief Test for solving LP formatted models.
 * Loads a simple LP model and solves it using lp_solve library.
 */
int main (int argc, char *argv[])
{
  fbc::FBAProblem pbm;
  pbm.initFromSBMLFile(argv[1]);
  pbm.solveProblem();
  assert(floor(100 * pbm.getSolution()->getObjectiveValue()) == 38);
  return 0;
}
