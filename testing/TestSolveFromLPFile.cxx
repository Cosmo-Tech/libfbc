#include <assert.h>
#include <math.h>
#include "fbcFBAProblem.hxx"

/** \brief Test for solving LP formatted models.
 * Loads a simple LP model and solves it using lp_solve library.
 */
int main (int argc, char *argv[])
{
  fbc::FBAProblem pbm;
  pbm.initFromLPFile(argv[1]);
  pbm.solveProblem();
  assert(floor(pbm.getSolution().getObjectiveValue()) == 6315.0);
  return 0;
}
