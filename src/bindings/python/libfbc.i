%module libfbc
%{
#include "../../fbc/fbcFBAProblem.hxx"
#include "../../fbc/fbcSolution.hxx"
%}
#include "../../fbc/fbcFBAProblem.hxx"
#include "../../fbc/fbcSolution.hxx"

namespace fbc {
  class FBAProblem {
    public:
      FBAProblem();
      lprec* getLpModel();
      fbc::Solution getSolution();
      void initFromLPFile(const char* file);
      void initFromSBMLFile(const char* file);
      void initFromSBMLString(const char* string);
      void printProblem();
      void solveProblem();
  };

  class Solution {
    public:
      Solution();
      double getObjectiveValue();
      std::vector<double> getFluxes();
  };
}
