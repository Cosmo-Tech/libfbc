%module libfbc
%{
#include "../../fbc/fbcFBAProblem.hxx"
#include "../../fbc/fbcSolution.hxx"
#include "../../fbc/fbcFluxes.hxx"
%}
%include "std_vector.i"

namespace std {
  %template(vectord) vector<double>;
}

namespace fbc {
  class FBAProblem {
    public:
      FBAProblem();
      double getLowerFluxBound(const char* reaction);
      std::vector<double> getObjective();
      const char* getObjectiveSense();
      fbc::Solution* getSolution();
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

  class Solution {
    public:
      double getObjectiveValue();
      fbc::Fluxes* getFluxes();
  };

  class Fluxes {
    public:
      double get(const char* key);
  };
}
