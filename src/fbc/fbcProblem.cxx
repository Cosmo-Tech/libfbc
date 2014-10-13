#include "fbcProblem.hxx"

namespace fbc
{

Problem::Problem()
{
  //TODO
}

Problem::~Problem()
{
  //TODO
}

std::list<fbc::Constraint> Problem::getListOfConstraints()
{
  return listOfConstraints;
}

fbc::Solution Problem::getSolution()
{
  return solution;
}

fbc::StoichiometryMatrix Problem::getStoichiometryMatrix()
{
  return stoichiometryMatrix;
}

void Problem::initFromLPFile()
{
  //TODO
}

void Problem::initFromSBMLFile()
{
  //TODO
}

void Problem::initFromSBMLString()
{
  //TODO
}

void Problem::solve()
{
  //TODO
}

}
