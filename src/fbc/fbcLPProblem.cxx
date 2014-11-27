#include "fbcLPProblem.hxx"

namespace fbc
{

/** \brief Constructor.
 *
 */
LPProblem::LPProblem()
{
  lpModel = new lprec;
}

/** \brief Destructor.
 *
 */
LPProblem::~LPProblem()
{
  delete_lp(lpModel);
}

/** \brief Getter.
 * @return lpModel
 */
lprec* LPProblem::getLpModel()
{
  return lpModel;
}

/** \brief Setter for "lpModel".
 * @param model Pointer to an lprec instance.
 */
void LPProblem::setLpModel(lprec* model)
{
  lpModel = model;
}

}
