#ifndef __fbcProblem_hxx
#define __fbcProblem_hxx

#include <list>
#include "fbcSolution.hxx"
#include "fbcConstraint.hxx"
#include "fbcStoichiometryMatrix.hxx"

namespace fbc
{

class Problem
{
  private:
    std::list<fbc::Constraint> listOfConstraints;
    fbc::StoichiometryMatrix stoichiometryMatrix;
    fbc::Solution solution;
  public:
    Problem();
    ~Problem();
    std::list<fbc::Constraint> getListOfConstraints();
    fbc::Solution getSolution();
    fbc::StoichiometryMatrix getStoichiometryMatrix();
    void initFromLPFile();
    void initFromSBMLFile();
    void initFromSBMLString();
    void solve();
};

}

#endif
