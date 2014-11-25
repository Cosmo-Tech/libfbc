#include "fbcFBAProblem.hxx"

namespace fbc
{

/** \brief Constructor.
 *
 */
FBAProblem::FBAProblem()
{
}

/** \brief Destructor.
 *
 */
FBAProblem::~FBAProblem()
{
  delete_lp(lpModel);
}

/**
 * @param reaction Identifier of the target reaction flux in the problem
 * matrix.
 * @return The value of the lower bound of the target reaction flux.
 */
double FBAProblem::getLowerFluxBound(const char* reaction)
{
  char* flux = const_cast<char*>(reaction);
  return get_lowbo(lpModel, colIndices[flux]);
}

/** \brief Getter.
 * @return lpModel
 */
lprec* FBAProblem::getLpModel()
{
  return lpModel;
}

/** \brief Getter.
 * @return solution
 */
fbc::Solution FBAProblem::getSolution()
{
  return solution;
}

/**
 * @param reaction Identifier of the target reaction flux in the problem
 * matrix.
 * @return The value of the upper bound of the target reaction flux.
 */
double FBAProblem::getUpperFluxBound(const char* reaction)
{
  char* flux = const_cast<char*>(reaction);
  return get_upbo(lpModel, colIndices[flux]);
}

/** \brief Initializes this with the content of a LP file.
 * The lp-format is a file format for describing linear programming problems in
 * lp_solve; its complete description can be found in the lp_solve reference
 * guide at http://lpsolve.sourceforge.net/.
 * @param file Address of a LP file.
 */
void FBAProblem::initFromLPFile(const char* file)
{
  lpModel = read_LP(const_cast<char*>(file), NORMAL, "");
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

/** \brief Fill the matrix of lpModel.
 * @param sb_model A Model object describing the problem to be solved.
 * @param pl A FbcModelPlugin object corresponding to sb_model.
 */
void FBAProblem::populateMatrix(Model* sb_model, FbcModelPlugin* pl)
{
  const Objective* obj = pl->getActiveObjective();
  const int num_species = sb_model->getNumSpecies();
  lpModel = make_lp(num_species, 0);
  // set the objective direction
  if (
    strcmp(const_cast<Objective*>(obj)->getType().c_str(), "maximize") == 0)
  {
    set_maxim(lpModel);
  }
  else
  {
    set_minim(lpModel);
  }
  // names rows after the species ids - row 0 is the objective function
  for (int i = 0; i < num_species; i++)
  {
    const std::string id = sb_model->getSpecies(i)->getId();
    set_row_name(lpModel, i+1, const_cast<char*>(id.c_str()));
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
      char* current = get_row_name(lpModel, s);
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
    add_column(lpModel, col);
    // name column after reaction id
    const std::string r_id = rt->getId();
    set_col_name(lpModel, r+1, const_cast<char*>(r_id.c_str()));
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

/** \brief Displays the problem encoded in lpModel.
 */
void FBAProblem::printProblem()
{
  print_lp(lpModel);
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
    set_upbo(lpModel, colIndices[flux], value);
  }
  else if (strcmp(op, "greaterEqual") == 0)
  {
    set_lowbo(lpModel, colIndices[flux], value);
  }
  else if (strcmp(op, "equal") == 0)
  {
    set_upbo(lpModel, colIndices[flux], value);
    set_lowbo(lpModel, colIndices[flux], value);
  }
  else
  {
    std::cout << "Error: " << op << " is not a valid flux bound type.\n";
    exit(EXIT_FAILURE);
  }
}

/** \brief Solves the linear problem encoded by this.
 * Solution will be stored in this->solution.
 */
void FBAProblem::solveProblem()
{
    solve(lpModel);
    solution = fbc::Solution(lpModel);
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
  set_unbounded(lpModel, colIndices[flux]);
}

/** \brief Set the lower bound of the target reaction flux free.
 * Lower flux bound is set to -Infinite.
 * @param reaction Identifier of the target reaction flux in the problem
 * matrix.
 */
void FBAProblem::unsetLowerFluxBound(const char* reaction)
{
  char* flux = const_cast<char*>(reaction);
  set_lowbo(lpModel, colIndices[flux], -get_infinite(lpModel));
}

/** \brief Set the upper bound of the target reaction flux free.
 * Lower flux bound is set to +Infinite.
 * @param reaction Identifier of the target reaction flux in the problem
 * matrix.
 */
void FBAProblem::unsetUpperFluxBound(const char* reaction)
{
  char* flux = const_cast<char*>(reaction);
  set_upbo(lpModel, colIndices[flux], get_infinite(lpModel));
}

}
