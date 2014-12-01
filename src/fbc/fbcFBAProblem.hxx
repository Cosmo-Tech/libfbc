#ifndef __fbcFBAProblem_hxx
#define __fbcFBAProblem_hxx

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include "fbcSolution.hxx"

class Model;
class FbcModelPlugin;

namespace fbc
{

class LPProblem;

class FBAProblem
{
  private:
    Solution solution;
    LPProblem* problem;
    std::map<std::string,int> colIndices;
    void initFromSBML(Model* sb_model);
    void populateMatrix(Model* sb_model, FbcModelPlugin* pl);
  public:
    FBAProblem();
    ~FBAProblem();
    double getLowerFluxBound(const char* reaction);
    std::vector<double> getObjective();
    const char* getObjectiveSense();
    Solution* getSolution();
    double getUpperFluxBound(const char* reaction);
    void initFromLPFile(const char* file);
    void initFromSBMLFile(const char* file);
    void initFromSBMLString(const char* string);
    void printProblem();
    void setFluxBound(const char* reaction, const char* type, double value);
    void setObjective(std::vector<double> objective);
    void setObjectiveSense(const char* sense);
    void solveProblem();
    void unsetFluxBound(const char* reaction);
    void unsetLowerFluxBound(const char* reaction);
    void unsetUpperFluxBound(const char* reaction);
};

}

#endif
