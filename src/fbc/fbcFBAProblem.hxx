#ifndef __fbcFBAProblem_hxx
#define __fbcFBAProblem_hxx

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include "fbcSolution.hxx"
#include "sbml/SBMLReader.h"
#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Reaction.h"
#include "sbml/Model.h"
#include "sbml/packages/fbc/extension/FbcModelPlugin.h"
#include "sbml/packages/fbc/sbml/Objective.h"
#include "sbml/packages/fbc/sbml/FluxObjective.h"
#include "lp_lib.h"

namespace fbc
{

class FBAProblem
{
  private:
    fbc::Solution solution;
    lprec* lpModel;
    std::map<std::string,int> colIndices;
    void populateMatrix(Model* sb_model, FbcModelPlugin* pl);
  public:
    FBAProblem();
    ~FBAProblem();
    lprec* getLpModel();
    fbc::Solution getSolution();
    void initFromLPFile(const char* file);
    void initFromSBMLFile(const char* file);
    void initFromSBMLString(const char* string);
    void printProblem();
    void solveProblem();
};

}

#endif
