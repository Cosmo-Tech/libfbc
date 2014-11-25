# Test macro
macro(fbcAddTest test_name executable args)
  add_test(
    NAME ${test_name}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${executable} ${args})
endmacro()

include_directories("${FBC_SOURCE_DIR}")
include_directories("${LPSOLVE_SOURCE_DIR}")

add_executable(TestSolveFromLPFile TestSolveFromLPFile.cxx)
target_link_libraries(TestSolveFromLPFile fbc)
fbcAddTest(SolveFromLPFile TestSolveFromLPFile "test.lp")

add_executable(TestSolveFromSBMLFile TestSolveFromSBMLFile.cxx)
target_link_libraries(TestSolveFromSBMLFile fbc)
fbcAddTest(SolveFromSBMLFile TestSolveFromSBMLFile "FEBS_antimony.xml")

add_executable(TestSolveFromSBMLString TestSolveFromSBMLString.cxx)
target_link_libraries(TestSolveFromSBMLString fbc ${LIBSBML_LIBRARY})
fbcAddTest(SolveFromSBMLString TestSolveFromSBMLString "FEBS_antimony.xml")

add_executable(TestSetFluxBound TestSetFluxBound.cxx)
target_link_libraries(TestSetFluxBound fbc)
fbcAddTest(SetFluxBound TestSetFluxBound "FEBS_antimony.xml")

add_executable(TestUnsetFluxBound TestUnsetFluxBound.cxx)
target_link_libraries(TestUnsetFluxBound fbc)
fbcAddTest(UnsetFluxBound TestUnsetFluxBound "FEBS_antimony.xml")
