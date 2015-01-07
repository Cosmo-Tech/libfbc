#ifndef __fbcFlux_hxx
#define __fbcFlux_hxx

#include <vector>
#include <string>
#include <iostream>

class Reaction;
class List;

namespace fbc
{

class Flux
{
  private:
    bool bcProduct;
    bool bcReactant;
    bool exchange;
    std::string id;
    std::vector<std::string> products;
    std::vector<std::string> reactants;
    double value;
  public:
    Flux();
    Flux(Reaction* rt, double flx, List* bc);
    ~Flux();
    bool isBCProduct();
    bool isBCReactant();
    bool isExchange();
    std::vector<std::string> getProductIds();
    std::vector<std::string> getReactantIds();
    std::string getId();
    double getValue();
    void setValue(double flx);
};

}

#endif
