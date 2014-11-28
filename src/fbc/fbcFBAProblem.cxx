#include "fbcFBAProblem.hxx"
#include "fbcLPProblem.hxx"
#include "lp_lib.h"

#include "sbml/SBMLReader.h"
#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Reaction.h"
#include "sbml/Model.h"
#include "sbml/packages/fbc/extension/FbcModelPlugin.h"
#include "sbml/packages/fbc/sbml/Objective.h"
#include "sbml/packages/fbc/sbml/FluxObjective.h"

#include "fbcSolution.hxx"

namespace fbc
{

/** \brief Constructor.
 *
 */
FBAProblem::FBAProblem()
{
  problem = new LPProblem;
}

/** \brief Destructor.
 *
 */
FBAProblem::~FBAProblem()
{
  delete problem;
}

/**
 * @param reaction Identifier of the target reaction flux in the problem
 * matrix.
 * @return The value of the lower bound of the target reaction flux.
 */
double FBAProblem::getLowerFluxBound(const char* reaction)
{
  char* flux = const_cast<char*>(reaction);
  return get_lowbo(problem->getLpModel(), colIndices[flux]);
}

/** /brief Returns the objective function as a vector of double values.
 * The objective function is a linear combination of any reaction available in
 * the model; for instance, if [R0, R1, R2, R3] is a vector of reaction, the
 * objective vector [0, 2, 1, 0] defines the objective function 2*R1 + R2.
 * @return vec A vector of double values.
 */
std::vector<double> FBAProblem::getObjective()
{
  int num_reactions = get_Ncolumns(problem->getLpModel());
  double row[num_reactions + 1];
  get_row(problem->getLpModel(), 0, row);
  std::vector<double> vec(row, row + num_reactions + 1);
  vec.erase(vec.begin()); // remove first element
  return vec;
}

/** /brief Returns the objective function sense.
 * @return vec A string value representing the objective function sense
 * ('maximize' or 'minimize').
 */
const char* FBAProblem::getObjectiveSense()
{
  if (is_maxim(problem->getLpModel()))
  {
    return "maximize";
  }
  else
  {
    return "minimize";
  }
}

/** \brief Getter.
 * @return solution
 */
Solution* FBAProblem::getSolution()
{
  return &solution;
}

/**
 * @param reaction Identifier of the target reaction flux in the problem
 * matrix.
 * @return The value of the upper bound of the target reaction flux.
 */
double FBAProblem::getUpperFluxBound(const char* reaction)
{
  char* flux = const_cast<char*>(reaction);
  return get_upbo(problem->getLpModel(), colIndices[flux]);
}

/** \brief Initializes this with the content of a LP file.
 * The lp-format is a file format for describing linear programming problems in
 * lp_solve; its complete description can be found in the lp_solve reference
 * guide at http://lpsolve.sourceforge.net/.
 * @param file Address of a LP file.
 */
void FBAProblem::initFromLPFile(const char* file)
{
  problem->setLpModel(read_LP(const_cast<char*>(file), NORMAL, ""));
}

/** \brief Initializes this with the content of a SBML file.
 * The Systems Biology Markup Language (SBML) is an XML-based descriptive
 * language for systems biology. Specifications of its latest version can be
 * found at http://sbml.org.
 * @param file Address of a SBML file.
 */
void FBAProblem::initFromSBMLFile(const char* file)
{
  SBMLReader reader = SBMLReader();
  SBMLDocument* doc = reader.readSBMLFromFile(file);
  if (doc->getNumErrors() > 0)
  {
    std::cout << "Error " << doc->getError(0)->getErrorId() << " at line " <<
      doc->getError(0)->getLine() << " when opening file " << file << ": " <<
      doc->getError(0)->getMessage() << "\n";
    exit(EXIT_FAILURE);
  }
  else
  {
    Model* sb_model = doc->getModel();
    // acquire FBC plugin - mandatory
    FbcModelPlugin* pl =
      dynamic_cast<FbcModelPlugin*>(sb_model->getPlugin("fbc"));
    if (pl == NULL)
    {
      std::cout << "Error: no FBC plugin found in " << file;
      exit(EXIT_FAILURE);
    }
    populateMatrix(sb_model, pl);
  }
}

/** \brief Initializes this with a SBML string.
 * The Systems Biology Markup Language (SBML) is an XML-based descriptive
 * language for systems biology. Specifications of its latest version can be
 * found at http://sbml.org.
 * @param string A SBML string.
 */
void FBAProblem::initFromSBMLString(const char* string)
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
    Model* sb_model = doc->getModel();
    // acquire FBC plugin - mandatory
    FbcModelPlugin* pl =
      dynamic_cast<FbcModelPlugin*>(sb_model->getPlugin("fbc"));
    if (pl == NULL)
    {
      std::cout << "Error: no FBC plugin found.";
      exit(EXIT_FAILURE);
    }
    populateMatrix(sb_model, pl);
  }
}

/** \brief Fill the matrix of the linear problem.
 * @param sb_model A Model object describing the problem to be solved.
 * @param pl A FbcModelPlugin object corresponding to sb_model.
 */
void FBAProblem::populateMatrix(Model* sb_model, FbcModelPlugin* pl)
{
  const Objective* obj = pl->getActiveObjective();
  const int num_species = sb_model->getNumSpecies();
  problem->setLpModel(make_lp(num_species, 0));
  // set the objective sense
  setObjectiveSense(const_cast<Objective*>(obj)->getType().c_str());
  // names rows after the species ids - row 0 is the objective function
  for (int i = 0; i < num_species; i++)
  {
    const std::string id = sb_model->getSpecies(i)->getId();
    set_row_name(problem->getLpModel(), i+1, const_cast<char*>(id.c_str()));
  }
  // populate problem matrix
  for (int r = 0; r < sb_model->getNumReactions(); r++)
  {
    REAL col[num_species + 1];
    Reaction* rt = sb_model->getReaction(r);
    // objective function
    for (int o = 0; o < obj->getNumFluxObjectives(); o++)
    {
      FluxObjective* fl_obj =
        const_cast<FluxObjective*>(obj->getFluxObjective(o));
      if (strcmp(rt->getId().c_str(), fl_obj->getReaction().c_str()) == 0)
      {
        col[0] = fl_obj->getCoefficient();
      }
      else
      {
        col[0] = 0.0;
      }
    }
    // stoichiometry matrix
    for (int s = 1; s <= num_species; s++)
    {
      char* current = get_row_name(problem->getLpModel(), s);
      if (rt->getReactant(current) != NULL)
      {
        col[s] = - rt->getReactant(current)->getStoichiometry();
      }
      else if (rt->getProduct(current) != NULL)
      {
        col[s] = rt->getProduct(current)->getStoichiometry();
      }
      else
      {
        col[s] = 0.0;
      }
    }
    add_column(problem->getLpModel(), col);
    // name column after reaction id
    const std::string r_id = rt->getId();
    set_col_name(problem->getLpModel(), r+1, const_cast<char*>(r_id.c_str()));
    // populate map of column indices
    colIndices[const_cast<char*>(r_id.c_str())] = r+1;
  }
  // edit reaction bounds
  for (int b = 0; b < pl->getNumFluxBounds(); b++)
  {
    FluxBound* fb = pl->getFluxBound(b);
    setFluxBound(fb->getReaction().c_str(), fb->getOperation().c_str(),
      fb->getValue());
  }
}

/** \brief Displays "problem".
 */
void FBAProblem::printProblem()
{
  print_lp(problem->getLpModel());
}

/** \brief Change the value of a flux bound.
 * @param reaction Identifier of the reaction flux to be constrained.
 * @param type Type of bound to be applied; can be 'lessEqual', 'greaterEqual'
 * or 'equal'.
 * @param value Value of the bound.
 */
void FBAProblem::setFluxBound(
  const char* reaction, const char* type, double value)
{
  char* op = const_cast<char*>(type);
  char* flux = const_cast<char*>(reaction);
  if (strcmp(op, "lessEqual") == 0)
  {
    set_upbo(problem->getLpModel(), colIndices[flux], value);
  }
  else if (strcmp(op, "greaterEqual") == 0)
  {
    set_lowbo(problem->getLpModel(), colIndices[flux], value);
  }
  else if (strcmp(op, "equal") == 0)
  {
    set_upbo(problem->getLpModel(), colIndices[flux], value);
    set_lowbo(problem->getLpModel(), colIndices[flux], value);
  }
  else
  {
    std::cout << "Error: " << op << " is not a valid flux bound type.\n";
    exit(EXIT_FAILURE);
  }
}

/** /brief Set the value of the objective function in the problem matrix.
 * The objective function is a linear combination of any reaction available in
 * the model; for instance, if [R0, R1, R2, R3] is a vector of reaction, the
 * objective vector [0, 2, 1, 0] defines the objective function 2*R1 + R2.
 * @param objective A vector of double values.
 */
void FBAProblem::setObjective(std::vector<double> objective)
{
  // input vector must contain as many elements as the number of reactions in
  // LP model
  int num_reactions = get_Ncolumns(problem->getLpModel());
  if (num_reactions == objective.size())
  {
    objective.insert(objective.begin(), 0.0);
    double obj[objective.size()];
    std::copy(objective.begin(), objective.end(), obj);
    set_row(problem->getLpModel(), 0, obj);
  }
  else
  {
    std::cout << "Error: input vector size is " << objective.size() <<
      "; expected size: " << num_reactions << ".\n";
    exit(EXIT_FAILURE);
  }
}

/** /brief Set the optimization sense for the objective function.
 * @param sense A string indicating the sense of the objective function (
 * can be either 'maximize' or 'minimize').
 */
void FBAProblem::setObjectiveSense(const char* sense)
{
  char* sns = const_cast<char*>(sense);
  if (strcmp(sns, "maximize") == 0)
  {
    set_maxim(problem->getLpModel());
  }
  else if (strcmp(sns, "minimize") == 0)
  {
    set_minim(problem->getLpModel());
  }
  else
  {
    std::cout << "Error: " << sns << " is not a valid objective sense. " <<
      "Valid values are 'maximize' or 'minimize'.\n";
    exit(EXIT_FAILURE);
  }
}

/** \brief Solves the linear problem encoded by this.
 * Solution will be stored in this->solution.
 */
void FBAProblem::solveProblem()
{
    solve(problem->getLpModel());
    solution = Solution(problem);
}

/** \brief Set the target reaction flux free.
 * Lower and upper bound for the target flux are respectively set to -Infinite
 * and +Infinite.
 * @param reaction Identifier of the target reaction flux in the problem
 * matrix.
 */
void FBAProblem::unsetFluxBound(const char* reaction)
{
  char* flux = const_cast<char*>(reaction);
  set_unbounded(problem->getLpModel(), colIndices[flux]);
}

/** \brief Set the lower bound of the target reaction flux free.
 * Lower flux bound is set to -Infinite.
 * @param reaction Identifier of the target reaction flux in the problem
 * matrix.
 */
void FBAProblem::unsetLowerFluxBound(const char* reaction)
{
  char* flux = const_cast<char*>(reaction);
  set_lowbo(problem->getLpModel(), colIndices[flux],
    -get_infinite(problem->getLpModel()));
}

/** \brief Set the upper bound of the target reaction flux free.
 * Lower flux bound is set to +Infinite.
 * @param reaction Identifier of the target reaction flux in the problem
 * matrix.
 */
void FBAProblem::unsetUpperFluxBound(const char* reaction)
{
  char* flux = const_cast<char*>(reaction);
  set_upbo(problem->getLpModel(), colIndices[flux],
    get_infinite(problem->getLpModel()));
}

}
