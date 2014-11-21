set(
  FBC_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
  CACHE PATH "libFBC source directory" FORCE
  )

find_package(LIBSBML REQUIRED)

set(LIBFBC_SOURCES
  ${FBC_SOURCE_DIR}/fbcFBAProblem.cxx
  ${FBC_SOURCE_DIR}/fbcFBAProblem.hxx
  ${FBC_SOURCE_DIR}/fbcSolution.cxx
  ${FBC_SOURCE_DIR}/fbcSolution.hxx
  ${FBC_SOURCE_DIR}/fbcFluxes.cxx
  ${FBC_SOURCE_DIR}/fbcFluxes.hxx
  CACHE PATH "libFBC source files" FORCE
)

include_directories(${FBC_SOURCE_DIR})
include_directories(${LPSOLVE_SOURCE_DIR})

add_library(fbc-static STATIC ${LIBFBC_SOURCES})
target_link_libraries(fbc-static ${LIBSBML_LIBRARY} lpsolve55-static)
add_library(fbc SHARED ${LIBFBC_SOURCES})
target_link_libraries(fbc ${LIBSBML_LIBRARY} lpsolve55)
