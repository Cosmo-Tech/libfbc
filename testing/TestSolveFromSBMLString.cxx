#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "fbcFBAProblem.hxx"
#include "sbml/SBMLReader.h"
#include "sbml/SBMLDocument.h"

/** \brief Test for solving LP formatted models.
 * Loads a simple LP model and solves it using lp_solve library.
 */
int main (int argc, char *argv[])
{
  SBMLReader reader = SBMLReader();
  SBMLDocument* doc = reader.readSBMLFromFile(argv[1]);
  fbc::FBAProblem pbm;
  pbm.initFromSBMLString(doc->toSBML());
  pbm.solveProblem();
  assert(floor(100 * pbm.getSolution()->getObjectiveValue()) == 38);
  return 0;
}
