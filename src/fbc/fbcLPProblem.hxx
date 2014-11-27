#ifndef __fbcLPProblem_hxx
#define __fbcLPProblem_hxx

#include "lp_lib.h"

namespace fbc
{

class LPProblem
{
  private:
    lprec* lpModel;
  public:
    LPProblem();
    ~LPProblem();
    lprec* getLpModel();
    void setLpModel(lprec* model);
};

}

#endif
