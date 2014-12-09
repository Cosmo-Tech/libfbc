#ifndef __fbcExchangeReactionFilter_hxx
#define __fbcExchangeReactionFilter_hxx

#include "sbml/util/ElementFilter.h"

class SBase;
class List;

namespace fbc
{

class ExchangeReactionFilter: public ElementFilter
{
  private:
    List* speciesList;
  public:
    ExchangeReactionFilter(List* sp_lst);
    bool filter(const SBase* element);
};

}

#endif
