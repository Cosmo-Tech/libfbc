#include <assert.h>
#include <string.h>
#include "fbcFBAProblem.hxx"

/** \brief Test for changing the objective sense.
 * Loads a simple SBML model and changes its objective sense.
 */
int main (int argc, char *argv[])
{
  fbc::FBAProblem pbm;
  pbm.initFromSBMLFile(argv[1]);
  pbm.setObjectiveSense("minimize");
  assert(strcmp(pbm.getObjectiveSense(), "minimize") == 0);
  return 0;
}
