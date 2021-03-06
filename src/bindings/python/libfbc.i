%module libfbc
%{
#include "../../fbc/fbcFBAProblem.hxx"
#include "../../fbc/fbcSolution.hxx"
#include "../../fbc/fbcFluxes.hxx"
#include "../../fbc/fbcFlux.hxx"
%}
%include "std_vector.i"
%include "std_string.i"

namespace std {
  %template(vectord) vector<double>;
  %template(vectorstr) vector<string>;
}

namespace fbc {
  class FBAProblem {
    public:
      FBAProblem();
      double getLowerFluxBound(const char* reaction);
      std::vector<double> getObjective();
      const char* getObjectiveSense();
      int getPreSolveSettings();
      fbc::Solution* getSolution();
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

  class Solution {
    public:
      double getObjectiveValue();
      fbc::Fluxes* getExchangeFluxes();
      fbc::Fluxes* getFluxes();
  };

  class Fluxes {
    public:
      fbc::Flux* get(const char* key);
      std::string getKey(size_t index);
      std::vector<std::string> getKeys();
      int size();
  };

  class Flux {
    public:
      bool isBCProduct();
      bool isBCReactant();
      bool isExchange();
      std::vector<std::string> getProductIds();
      std::vector<std::string> getReactantIds();
      std::string getId();
      double getValue();
  };
}
