#include "fbcFBAProblem.hxx"
#include "fbcLPProblem.hxx"
#include "lp_lib.h"

#include "sbml/SBMLReader.h"
#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Reaction.h"
#include "sbml/Model.h"
#include "sbml/util/List.h"
#include "sbml/packages/fbc/extension/FbcModelPlugin.h"
#include "sbml/packages/fbc/sbml/Objective.h"
#include "sbml/packages/fbc/sbml/FluxObjective.h"

#include "fbcSolution.hxx"
#include "fbcBoundaryConditionFilter.hxx"
#include "fbcNonBoundaryConditionFilter.hxx"
#include "fbcExchangeReactionFilter.hxx"
#include "fbcReactionFilter.hxx"

namespace fbc
{

/** \brief Constructor.
 *
 */
FBAProblem::FBAProblem()
{
  problem = new LPProblem;
  timeOut = 60;
  preSolveSettings = PRESOLVE_ROWS | PRESOLVE_COLS;
  // Ensure that lists are initialized to empty lists when creating a FBAProblem
  fluxList = NULL;
  bcList = NULL;
}

/** \brief Destructor.
 *
 */
FBAProblem::~FBAProblem()
{
  if(fluxList != NULL)
  {
    delete fluxList;
  }
  if(bcList != NULL)
  {
    delete bcList; 
  }
  delete problem;
}

/** \brief Returns the value of the lower bound of the target reaction flux.
 * @param reaction Identifier of the target reaction flux in the problem
 * matrix.
 * @return The flux bound value as a double.
 */
double FBAProblem::getLowerFluxBound(const char* reaction)
{
  char* flux = const_cast<char*>(reaction);
  return get_lowbo(problem->getLpModel(),
    get_nameindex(problem->getLpModel(), flux, 0));
}

/** \brief Returns the objective function as a vector of double values.
 *
 * The objective function is a linear combination of any reaction available in
 * the model; for instance, if [R0, R1, R2, R3] is a vector of reaction, the
 * objective vector [0, 2, 1, 0] defines the objective function 2*R1 + R2.
 * @return vec A vector of double values.
 */
std::vector<double> FBAProblem::getObjective()
{
  const int size = get_Ncolumns(problem->getLpModel()) + 1;
  double* row = new double[size];
  get_row(problem->getLpModel(), 0, row);
  std::vector<double> vec(row, row + size);
  vec.erase(vec.begin()); // remove first element
  return vec;
}

/** \brief Returns the objective function sense.
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

/** \brief Returns the presolve level to be applied before solving the problem.
 * @return An integer value representing the presolve level in lp_solve.
 */
int FBAProblem::getPreSolveSettings()
{
  return preSolveSettings;
}

/** \brief Getter.
 * @return solution
 */
Solution* FBAProblem::getSolution()
{
  return &solution;
}

/** \brief Getter.
 * @return timeOut
 */
int FBAProblem::getTimeOut()
{
  return timeOut;
}

/** \brief Returns the value of the upper bound of the target reaction flux.
 * @param reaction Identifier of the target reaction flux in the problem
 * matrix.
 * @return The flux bound value as a double.
 */
double FBAProblem::getUpperFluxBound(const char* reaction)
{
  char* flux = const_cast<char*>(reaction);
  return get_upbo(problem->getLpModel(),
    get_nameindex(problem->getLpModel(), flux, 0));
}

/** \brief Acquire mandatory FBC plugin before populating matrix.
 * @param sb_model Pointer to an SBML Model instance.
 */
void FBAProblem::initFromSBML(Model* sb_model)
{
  // acquire FBC plugin - mandatory
  FbcModelPlugin* pl =
    dynamic_cast<FbcModelPlugin*>(sb_model->getPlugin("fbc"));
  if (pl == NULL)
  {
    std::cout << "Error: no FBC plugin found.\n";
    exit(EXIT_FAILURE);
  }
  populateMatrix(sb_model, pl);
}

/** \brief Initializes this with the content of a SBML file.
 *
 * The Systems Biology Markup Language (SBML) is an XML-based descriptive
 * language for systems biology. Specifications of its latest version can be
 * found at http://sbml.org.
 * @param file Address of a SBML file.
 */
void FBAProblem::initFromSBMLFile(const char* file)
{
  SBMLReader reader = SBMLReader();
  SBMLDocument* doc = reader.readSBMLFromFile(file);
  if (doc->getNumErrors(2) > 0 || doc->getNumErrors(3) > 0)
  {
    std::cout << "Error " << doc->getError(0)->getErrorId() << " at line " <<
      doc->getError(0)->getLine() << " when opening file " << file << ": " <<
      doc->getError(0)->getMessage() << "\n";
    exit(EXIT_FAILURE);
  }
  else if (doc->getNumErrors(0) > 0 || doc->getNumErrors(1) > 0)
  {
    std::cout << doc->getNumErrors(0) + doc->getNumErrors(1) << " warnings" <<
      " returned when opening file " << file << ".\n";
    initFromSBML(doc->getModel());
  }
  else
  {
    initFromSBML(doc->getModel());
  }
}

/** \brief Initializes this with a SBML string.
 *
 * The Systems Biology Markup Language (SBML) is an XML-based descriptive
 * language for systems biology. Specifications of its latest version can be
 * found at http://sbml.org.
 * @param string A SBML string.
 */
void FBAProblem::initFromSBMLString(const char* string)
{
  SBMLReader reader = SBMLReader();
  SBMLDocument* doc = reader.readSBMLFromString(string);
  if (doc->getNumErrors(2) > 0 || doc->getNumErrors(3) > 0)
  {
    std::cout << "Error " << doc->getError(0)->getErrorId() << " at line " <<
      doc->getError(0)->getLine() << " when opening input string: " <<
      doc->getError(0)->getMessage() << "\n";
    exit(EXIT_FAILURE);
  }
  else if (doc->getNumErrors(0) > 0 || doc->getNumErrors(1) > 0)
  {
    std::cout << doc->getNumErrors(0) + doc->getNumErrors(1) << " warnings" <<
      " returned when opening input string.\n";
    initFromSBML(doc->getModel());
  }
  else
  {
    initFromSBML(doc->getModel());
  }
}

/** \brief Initializes this with the content of a LP file. This method was
 *         designed to be used after a first initialization based on an SBML
 *         file. LP model should be consistent with the model of this first SBML
 *         file.
 *
 * This method aims at allowing a user which needs to launch FBA calculation
 * several times to save computing time. The solving of a FBA problem will
 * indeed possibly modify the associated LP problem by doing simplifications in
 * order to solve the problem, especially when using pre-solve functions. The
 * proposed solution to avoid successive opening of SBML files, very time
 * consuming, is to firstly init FBA problem based on a SBML file
 * (FBAProblem::initFromSBMLFile or FBAProblem::initFromSBMLString), then
 * write the associated LP problem in a file (FBAProblem::writeProblem)
 * and reopen it each time a new FBA computation
 * is required. Opening the SBML file triggers the initialization of
 * meta-information such as the list of fluxes and the list of exchange fluxes.
 * 	
 * The lp-format is a file format for describing linear programming problems in 	
 * lp_solve; its complete description can be found in the lp_solve reference 	
 * guide at http://lpsolve.sourceforge.net/. 	
 * @param file Address of a LP file. 	
 */
void FBAProblem::initFromLPFile(const char* file) 	
{
  if(fluxList == NULL)
  {
    std::cout << " Error: fluxList is empty. Please note that the loading "
    << "of the associated SBML file should have been scheduled as it is the "
    << " expected use's context of this method. For more "
    << "information, please refer to the documentation.";
    exit(EXIT_FAILURE);
  }
  else if(bcList == NULL)
  {
    std::cout << " Error: bcList is empty. Please check the "
    << "metabolic network: it is strange that the network is not empty but "
    << "that all the metabolites consumed are produced too and vice-versa "
    << "within the network, implying a total independancy towards the "
    << "external world.";
    exit(EXIT_FAILURE);
  }
  problem->setLpModel(read_LP(const_cast<char*>(file), NORMAL, ""));
}

/** \brief Fill the matrix of the linear problem.
 *
 * @param sb_model A Model object describing the problem to be solved.
 * @param pl A FbcModelPlugin object corresponding to sb_model.
 */
void FBAProblem::populateMatrix(Model* sb_model, FbcModelPlugin* pl)
{
  // declaring filters, create lists of boundary / non-boundary species
  NonBoundaryConditionFilter non_bc_flt;
  BoundaryConditionFilter bc_flt;
  ReactionFilter r_flt;
  List* non_bc = sb_model->getListOfSpecies()->getAllElements(&non_bc_flt);
  // initialize "bcList" and "fluxList" attributes
  fluxList = sb_model->getListOfReactions()->getAllElements(&r_flt);
  bcList = sb_model->getListOfSpecies()->getAllElements(&bc_flt);
  // build "problem"
  const Objective* obj = pl->getActiveObjective();
  int num_species = non_bc->getSize();
  problem->setLpModel(make_lp(num_species, 0));
  // set the objective sense
  setObjectiveSense(const_cast<Objective*>(obj)->getType().c_str());
  // names rows after the species ids - row 0 is the objective function
  for (int i = 0; i < num_species; i++)
  {  
    Species* sp = (Species*) non_bc->get(i);
    const std::string id = sp->getId();
    set_row_name(problem->getLpModel(), i+1, const_cast<char*>(id.c_str()));
    set_constr_type(problem->getLpModel(), i+1, EQ);
  }
  // populate problem matrix
  for (int r = 0; r < sb_model->getNumReactions(); r++)
  {
    double* col = new double[num_species + 1];
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
    // if reaction is reversible, flux is unbounded
    if (rt->getReversible())
    {
      set_unbounded(problem->getLpModel(), r+1);
    }
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
  int colIndex = get_nameindex(problem->getLpModel(), flux, 0);
  if (strcmp(op, "lessEqual") == 0)
  {
    set_upbo(problem->getLpModel(), colIndex, value);
  }
  else if (strcmp(op, "greaterEqual") == 0)
  {
    set_lowbo(problem->getLpModel(), colIndex, value);
  }
  else if (strcmp(op, "equal") == 0)
  {
    set_upbo(problem->getLpModel(), colIndex, value);
    set_lowbo(problem->getLpModel(), colIndex, value);
  }
  else
  {
    std::cout << "Error: " << op << " is not a valid flux bound type.\n";
    exit(EXIT_FAILURE);
  }
}

/** \brief Set the value of the objective function in the problem matrix.
 *
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
    double* obj = new double[objective.size()];
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

/** \brief Set the optimization sense for the objective function.
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

/** \brief Sets the value of preSolveSettings.
 * @param settings Value of the settings to be applied.
 */
void FBAProblem::setPreSolveSettings(int settings)
{
  preSolveSettings = settings;
}

/** \brief Set the value of lp_solve time out.
 * @param timeout An integer value.
 */
void FBAProblem::setTimeOut(int timeout)
{
  timeOut = timeout;
}

/** \brief Solves the linear problem encoded by this.
 *
 * Solution will be stored in this->solution.
 */
void FBAProblem::solveProblem()
{ // TODO - copy the problem before presolving it and delete it after resolution
  set_presolve(problem->getLpModel(), preSolveSettings,
    get_presolveloops(problem->getLpModel()));
  set_timeout(problem->getLpModel(), timeOut);
  solve(problem->getLpModel());
  solution = Solution(problem, fluxList, bcList);
}

/** \brief Set the target reaction flux free.
 *
 * Lower and upper bound for the target flux are respectively set to -Infinite
 * and +Infinite.
 * @param reaction Identifier of the target reaction flux in the problem
 * matrix.
 */
void FBAProblem::unsetFluxBound(const char* reaction)
{
  char* flux = const_cast<char*>(reaction);
  set_unbounded(problem->getLpModel(),
    get_nameindex(problem->getLpModel(), flux, 0));
}

/** \brief Set the lower bound of the target reaction flux free.
 *
 * Lower flux bound is set to -Infinite.
 * @param reaction Identifier of the target reaction flux in the problem
 * matrix.
 */
void FBAProblem::unsetLowerFluxBound(const char* reaction)
{
  char* flux = const_cast<char*>(reaction);
  set_lowbo(problem->getLpModel(),
    get_nameindex(problem->getLpModel(), flux, 0),
    -get_infinite(problem->getLpModel()));
}

/** \brief Set the upper bound of the target reaction flux free.
 *
 * Lower flux bound is set to +Infinite.
 * @param reaction Identifier of the target reaction flux in the problem
 * matrix.
 */
void FBAProblem::unsetUpperFluxBound(const char* reaction)
{
  char* flux = const_cast<char*>(reaction);
  set_upbo(problem->getLpModel(),
    get_nameindex(problem->getLpModel(), flux, 0),
    get_infinite(problem->getLpModel()));
}

/** \brief Write the LP problem in the input file.
 * @param file Address of the file where the problem should be written.
 */
void FBAProblem::writeProblem(const char* file)
{
  write_lp(problem->getLpModel(), const_cast<char*>(file));
}

}
