#ifndef __fbcReactionFilter_hxx
#define __fbcReactionFilter_hxx

#include "sbml/util/ElementFilter.h"

class SBase;

namespace fbc
{

class ReactionFilter: public ElementFilter
{
  public:
    bool filter(const SBase* element);
};

}

#endif
