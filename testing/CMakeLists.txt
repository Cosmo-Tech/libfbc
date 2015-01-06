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
fbcAddTest(fbcSolveFromLPFile TestSolveFromLPFile "test.lp")
set_tests_properties(fbcSolveFromLPFile PROPERTIES WILL_FAIL ON)

add_executable(TestSolveFromSBMLFile TestSolveFromSBMLFile.cxx)
target_link_libraries(TestSolveFromSBMLFile fbc)
fbcAddTest(fbcSolveFromSBMLFile TestSolveFromSBMLFile "salmonella_fbc.xml")

add_executable(TestSolveFromSBMLString TestSolveFromSBMLString.cxx)
target_link_libraries(TestSolveFromSBMLString fbc ${LIBSBML_LIBRARY})
fbcAddTest(fbcSolveFromSBMLString TestSolveFromSBMLString "salmonella_fbc.xml")

add_executable(TestSolveFromSBMLandLPFile TestSolveFromSBMLandLPFile.cxx) 	
target_link_libraries(TestSolveFromSBMLandLPFile fbc) 	
fbcAddTest(fbcSolveFromSBMLandLPFile TestSolveFromSBMLandLPFile "salmonella_fbc.xml")

add_executable(TestSetFluxBound TestSetFluxBound.cxx)
target_link_libraries(TestSetFluxBound fbc)
fbcAddTest(fbcSetFluxBound TestSetFluxBound "FEBS_antimony.xml")

add_executable(TestUnsetFluxBound TestUnsetFluxBound.cxx)
target_link_libraries(TestUnsetFluxBound fbc)
fbcAddTest(fbcUnsetFluxBound TestUnsetFluxBound "FEBS_antimony.xml")

add_executable(TestChangeObjectiveFunction TestChangeObjectiveFunction.cxx)
target_link_libraries(TestChangeObjectiveFunction fbc)
fbcAddTest(fbcChangeObjectiveFunction TestChangeObjectiveFunction "FEBS_antimony.xml")

add_executable(TestChangeObjectiveSense TestChangeObjectiveSense.cxx)
target_link_libraries(TestChangeObjectiveSense fbc)
fbcAddTest(fbcChangeObjectiveSense TestChangeObjectiveSense "FEBS_antimony.xml")

add_executable(TestSetPreSolveSettings TestSetPreSolveSettings.cxx)
target_link_libraries(TestSetPreSolveSettings fbc)
fbcAddTest(fbcSetPreSolveSettings TestSetPreSolveSettings "salmonella_fbc.xml")

add_executable(TestFluxVectorSizes TestFluxVectorSizes.cxx)
target_link_libraries(TestFluxVectorSizes fbc)
fbcAddTest(fbcFluxVectorSizes TestFluxVectorSizes "salmonella_fbc.xml")

add_executable(TestFluxAPI TestFluxAPI.cxx)
target_link_libraries(TestFluxAPI fbc)
fbcAddTest(fbcFluxAPI TestFluxAPI "salmonella_fbc.xml")

add_executable(TestExchangeFluxAPI TestExchangeFluxAPI.cxx)
target_link_libraries(TestExchangeFluxAPI fbc)
fbcAddTest(fbcExchangeFluxAPI TestExchangeFluxAPI "salmonella_fbc.xml")
