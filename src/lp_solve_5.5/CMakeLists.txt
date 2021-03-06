set(
  LPSOLVE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
  CACHE PATH "lp_solve source directory" FORCE
  )

set(SOURCES
  ${LPSOLVE_SOURCE_DIR}/lp_MDO.c
  ${LPSOLVE_SOURCE_DIR}/lp_MDO.h
  ${LPSOLVE_SOURCE_DIR}/ini.c
  ${LPSOLVE_SOURCE_DIR}/ini.h
  ${LPSOLVE_SOURCE_DIR}/fortify.c
  ${LPSOLVE_SOURCE_DIR}/fortify.h
  ${LPSOLVE_SOURCE_DIR}/lp_rlp.c
  ${LPSOLVE_SOURCE_DIR}/lp_rlp.h
  ${LPSOLVE_SOURCE_DIR}/lp_crash.c
  ${LPSOLVE_SOURCE_DIR}/lp_crash.h
  ${LPSOLVE_SOURCE_DIR}/lp_Hash.c
  ${LPSOLVE_SOURCE_DIR}/lp_Hash.h
  ${LPSOLVE_SOURCE_DIR}/lp_lib.c
  ${LPSOLVE_SOURCE_DIR}/lp_lib.h
  ${LPSOLVE_SOURCE_DIR}/lp_wlp.c
  ${LPSOLVE_SOURCE_DIR}/lp_wlp.h
  ${LPSOLVE_SOURCE_DIR}/lp_matrix.c
  ${LPSOLVE_SOURCE_DIR}/lp_matrix.h
  ${LPSOLVE_SOURCE_DIR}/lp_mipbb.c
  ${LPSOLVE_SOURCE_DIR}/lp_mipbb.h
  ${LPSOLVE_SOURCE_DIR}/lp_MPS.c
  ${LPSOLVE_SOURCE_DIR}/lp_MPS.h
  ${LPSOLVE_SOURCE_DIR}/lp_params.c
  ${LPSOLVE_SOURCE_DIR}/lp_presolve.c
  ${LPSOLVE_SOURCE_DIR}/lp_presolve.h
  ${LPSOLVE_SOURCE_DIR}/lp_price.c
  ${LPSOLVE_SOURCE_DIR}/lp_price.h
  ${LPSOLVE_SOURCE_DIR}/lp_pricePSE.c
  ${LPSOLVE_SOURCE_DIR}/lp_pricePSE
  ${LPSOLVE_SOURCE_DIR}/lp_report.c
  ${LPSOLVE_SOURCE_DIR}/lp_report.h
  ${LPSOLVE_SOURCE_DIR}/lp_scale.c
  ${LPSOLVE_SOURCE_DIR}/lp_scale.h
  ${LPSOLVE_SOURCE_DIR}/lp_simplex.c
  ${LPSOLVE_SOURCE_DIR}/lp_simplex.h
  ${LPSOLVE_SOURCE_DIR}/lp_SOS.c
  ${LPSOLVE_SOURCE_DIR}/lp_SOS.h
  ${LPSOLVE_SOURCE_DIR}/lp_utils.c
  ${LPSOLVE_SOURCE_DIR}/lp_utils.h
  ${LPSOLVE_SOURCE_DIR}/yacc_read.c
  ${LPSOLVE_SOURCE_DIR}/yacc_read.h
  ${LPSOLVE_SOURCE_DIR}/bfp/bfp_LUSOL/lp_LUSOL.c
  ${LPSOLVE_SOURCE_DIR}/bfp/bfp_LUSOL/lp_LUSOL.h
  ${LPSOLVE_SOURCE_DIR}/bfp/bfp_LUSOL/LUSOL/lusol.c
  ${LPSOLVE_SOURCE_DIR}/bfp/bfp_LUSOL/LUSOL/lusol.h
  ${LPSOLVE_SOURCE_DIR}/shared/commonlib.c
  ${LPSOLVE_SOURCE_DIR}/shared/commonlib.h
  ${LPSOLVE_SOURCE_DIR}/shared/mmio.c
  ${LPSOLVE_SOURCE_DIR}/shared/mmio.h
  ${LPSOLVE_SOURCE_DIR}/shared/myblas.c
  ${LPSOLVE_SOURCE_DIR}/shared/myblas.h
  ${LPSOLVE_SOURCE_DIR}/colamd/colamd.c
  ${LPSOLVE_SOURCE_DIR}/colamd/colamd.h
  )

include_directories(${LPSOLVE_SOURCE_DIR})
include_directories(${LPSOLVE_SOURCE_DIR}/shared)
include_directories(${LPSOLVE_SOURCE_DIR}/bfp)
include_directories(${LPSOLVE_SOURCE_DIR}/bfp/bfp_LUSOL)
include_directories(${LPSOLVE_SOURCE_DIR}/bfp/bfp_LUSOL/LUSOL)
include_directories(${LPSOLVE_SOURCE_DIR}/colamd)

add_definitions(-DINVERSE_ACTIVE=INVERSE_LUSOL)
add_definitions(-DYY_NEVER_INTERACTIVE)
add_definitions(-DPARSER_LP)
add_definitions(-DRoleIsExternalInvEngine)

set(M_LIB)
IF(NOT WIN32)
  set(M_LIB m)
ENDIF()

add_library(lpsolve55-static STATIC ${SOURCES})
target_link_libraries(lpsolve55-static ${CMAKE_DL_LIBS} ${M_LIB})

add_library(lpsolve55 SHARED ${SOURCES})
target_link_libraries(lpsolve55 ${CMAKE_DL_LIBS} ${M_LIB})

# libfbc patch - install files
INSTALL(TARGETS lpsolve55 lpsolve55-static 
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )

FILE(GLOB_RECURSE lp_solve_include_files "${LPSOLVE_SOURCE_DIR}/*.h")
INSTALL(FILES ${lp_solve_include_files} DESTINATION include/lpsolve55)
# Install documents
set (LPSOLVE_INSTALL_DOCS)
set (LPSOLVE_INSTALL_DOCS ${LPSOLVE_INSTALL_DOCS} ${LPSOLVE_SOURCE_DIR}/README.txt)
INSTALL(FILES ${LPSOLVE_INSTALL_DOCS} DESTINATION share/lpsolve55)
