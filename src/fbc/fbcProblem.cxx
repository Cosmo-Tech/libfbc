#include "fbcProblem.hxx"

namespace fbc
{

/** \brief Constructor.
 *
 */
Problem::Problem()
{
  //TODO
}


/** \brief Destructor.
 *
 */
Problem::~Problem()
{
  //TODO
}

/** \brief Getter.
 * @return listOfConstraints
 */
std::list<fbc::Constraint> Problem::getListOfConstraints()
{
  return listOfConstraints;
}

/** \brief Getter.
 * @return solution
 */
fbc::Solution Problem::getSolution()
{
  return solution;
}

/** \brief Getter.
 * @return stoichiometryMatrix
 */
fbc::StoichiometryMatrix Problem::getStoichiometryMatrix()
{
  return stoichiometryMatrix;
}

/** \brief Initializes this with the content of a LP file.
 * The lp-format is a file format for describing linear programming problems in
 * lp_solve; its complete description can be found in the lp_solve reference
 * guide at http://lpsolve.sourceforge.net/.
 * @param file Address of a LP file.
 */
void Problem::initFromLPFile(const char* file)
{
  //TODO
}

/** \brief Initializes this with the content of a SBML file.
 * The Systems Biology Markup Language (SBML) is an XML-based descriptive
 * language for systems biology. Specifications of its latest version can be
 * found at http://sbml.org.
 * @param file Address of a SBML file.
 */
void Problem::initFromSBMLFile(const char* file)
{
  SBMLReader reader = SBMLReader();
  SBMLDocument* doc = reader.readSBMLFromFile(file);
  if (doc->getNumErrors() > 0)
  {
    std::cout << "Error " << doc->getError(0)->getErrorId() << " at line " <<
      doc->getError(0)->getLine() << " when opening file " << file;
  }
  else
  {
    //TODO
  }
}

/** \brief Initializes this with a SBML string.
 * The Systems Biology Markup Language (SBML) is an XML-based descriptive
 * language for systems biology. Specifications of its latest version can be
 * found at http://sbml.org.
 * @param string A SBML string.
 */
void Problem::initFromSBMLString(const char* string)
{
  SBMLReader reader = SBMLReader();
  SBMLDocument* doc = reader.readSBMLFromString(string);
  if (doc->getNumErrors() > 0)
  {
    std::cout << "Error " << doc->getError(0)->getErrorId() << " at line " <<
      doc->getError(0)->getLine() << " when opening input string";
  }
  else
  {
    //TODO
  }
}

/** \brief Solves the linear problem encoded by this.
 * Solution will be stored in this->solution.
 */
void Problem::solve()
{
  //TODO
}

}
