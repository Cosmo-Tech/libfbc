#ifndef __fbcBoundaryConditionFilter_hxx
#define __fbcBoundaryConditionFilter_hxx

#include "sbml/util/ElementFilter.h"

class SBase;

namespace fbc
{

class BoundaryConditionFilter: public ElementFilter
{
  public:
    bool filter(const SBase* element);
};

}

#endif
