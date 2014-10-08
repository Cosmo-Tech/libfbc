# - Find LIBSBML
# This module finds an installed SBML library.  It sets the following
# variables:
#  LIBSBML_FOUND - set to true if libSBML is found
#  LIBSBML_INCLUDE_DIR - libSBML include directory
#  LIBSBML_LIBRARY - libSBML library

SET(LIBSBML_FOUND 0)

find_path(LIBSBML_INCLUDE_DIR
  NAMES sbml/SBMLTypes.h
  PATHS /usr/include
        /usr/local/include
        /opt/local/include
  )

find_library(LIBSBML_LIBRARY
  NAMES libsbml.so libsbml.dll libsbml
  PATHS /usr/lib
        /usr/lib64
        /usr/local/lib
        /opt/local/lib
  )

IF(LIBSBML_LIBRARY)
  SET(LIBSBML_FOUND 1)
  MESSAGE(STATUS "Found libSBML: ${LIBSBML_LIBRARY}")
ENDIF()

IF(NOT LIBSBML_FOUND)
  MESSAGE(FATAL_ERROR "libSBML was not found on the system. Please specify the location of libSBML.")
ENDIF()
