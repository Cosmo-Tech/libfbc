set(
  FBC_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
  CACHE PATH "libFBC source directory" FORCE
  )

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
add_library(fbc SHARED ${SOURCES})
