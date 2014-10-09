#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "lp_lib.h"

/** \brief Test for solving LP formatted models.
 * Loads a simple LP model and solves it using lp_solve library.
 */
int main (int argc, char *argv[])
{
  lprec *lp;
  int ret;
  REAL pv[6];
  lp = read_LP(argv[1], NORMAL, "test");
  ret = solve(lp);
  get_primal_solution(lp, pv);
  assert(floor(pv[0]) == 6315.0);
  delete_lp(lp);
  return ret;
}
