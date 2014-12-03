#include <assert.h>
#include <iostream>
#include <math.h>
#include "fbcFBAProblem.hxx"
#include "lp_lib.h"

/** \brief Test for the setPreSolveSettings method.
 * Loads an SBML model and solves it twice using different presolve levels.
 */
int main (int argc, char *argv[])
{
  fbc::FBAProblem pbm_none;
  pbm_none.initFromSBMLFile(argv[1]);
  pbm_none.setPreSolveSettings(PRESOLVE_NONE);
  pbm_none.solveProblem();
  double pre_none = pbm_none.getSolution()->getObjectiveValue();

  fbc::FBAProblem pbm_def;
  pbm_def.initFromSBMLFile(argv[1]);
  pbm_def.solveProblem();
  double pre_def = pbm_def.getSolution()->getObjectiveValue();

  assert(pre_def != pre_none);
  return 0;
}
