#ifndef __fbcNonBoundaryConditionFilter_hxx
#define __fbcNonBoundaryConditionFilter_hxx

#include "sbml/util/ElementFilter.h"

class SBase;

namespace fbc
{

class NonBoundaryConditionFilter: public ElementFilter
{
  public:
    bool filter(const SBase* element);
};

}

#endif
