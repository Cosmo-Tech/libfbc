#include <assert.h>
#include <vector>
#include "fbcFBAProblem.hxx"

/** \brief Test for changing the objective function.
 * Loads a simple SBML model and changes its objective function.
 */
int main (int argc, char *argv[])
{
  fbc::FBAProblem pbm;
  pbm.initFromSBMLFile(argv[1]);
  std::vector<double> newObj;
  newObj.push_back(1.0);
  newObj.push_back(2.0);
  newObj.push_back(3.0);
  pbm.setObjective(newObj);
  assert(pbm.getObjective()[0] == 1.0);
  assert(pbm.getObjective()[1] == 2.0);
  assert(pbm.getObjective()[2] == 3.0);
  return 0;
}
