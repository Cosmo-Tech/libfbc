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
class List;

namespace fbc
{

class LPProblem;

class FBAProblem
{
  private:
    List* bcList;
    List* fluxList;
    int preSolveSettings;
    LPProblem* problem;
    Solution solution;
    int timeOut;
    void initFromSBML(Model* sb_model);
    void populateMatrix(Model* sb_model, FbcModelPlugin* pl);
  public:
    FBAProblem();
    ~FBAProblem();
    double getLowerFluxBound(const char* reaction);
    std::vector<double> getObjective();
    const char* getObjectiveSense();
    int getPreSolveSettings();
    Solution* getSolution();
    int getTimeOut();
    double getUpperFluxBound(const char* reaction);
    void initFromSBMLFile(const char* file);
    void initFromSBMLString(const char* string);
    void initFromLPFile(const char* file);
    void printProblem();
    void setFluxBound(const char* reaction, const char* type, double value);
    void setObjective(std::vector<double> objective);
    void setObjectiveSense(const char* sense);
    void setPreSolveSettings(int settings);
    void setTimeOut(int timeout);
    void solveProblem();
    void unsetFluxBound(const char* reaction);
    void unsetLowerFluxBound(const char* reaction);
    void unsetUpperFluxBound(const char* reaction);
    void writeProblem(const char* file);
};

}

#endif
