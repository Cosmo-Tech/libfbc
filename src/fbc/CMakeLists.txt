set(
  FBC_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
  CACHE PATH "libFBC source directory" FORCE
  )

find_package(LIBSBML REQUIRED)

set(SOURCES
  ${FBC_SOURCE_DIR}/fbcConstraint.cxx
  ${FBC_SOURCE_DIR}/fbcConstraint.hxx
  ${FBC_SOURCE_DIR}/fbcProblem.cxx
  ${FBC_SOURCE_DIR}/fbcProblem.hxx
  ${FBC_SOURCE_DIR}/fbcSolution.cxx
  ${FBC_SOURCE_DIR}/fbcSolution.hxx
  ${FBC_SOURCE_DIR}/fbcStoichiometryMatrix.cxx
  ${FBC_SOURCE_DIR}/fbcStoichiometryMatrix.hxx
)

include_directories(${FBC_SOURCE_DIR})

add_library(fbc-static STATIC ${SOURCES})
target_link_libraries(fbc-static ${LIBSBML_LIBRARY})
add_library(fbc SHARED ${SOURCES})
target_link_libraries(fbc ${LIBSBML_LIBRARY})
