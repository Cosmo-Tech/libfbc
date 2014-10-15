#ifndef __fbcProblem_hxx
#define __fbcProblem_hxx

#include <list>
#include <iostream>
#include "fbcSolution.hxx"
#include "fbcConstraint.hxx"
#include "fbcStoichiometryMatrix.hxx"
#include "sbml/SBMLReader.h"
#include "sbml/SBMLDocument.h"

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
    void initFromLPFile(const char* file);
    void initFromSBMLFile(const char* file);
    void initFromSBMLString(const char* string);
    void solve();
};

}

#endif
