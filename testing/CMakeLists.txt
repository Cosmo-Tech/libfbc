# Test macro
macro(fbcAddTest test_name executable args)
  add_test(
    NAME ${test_name}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${executable} ${args})
endmacro()

include_directories("${LPSOLVE_SOURCE_DIR}")

add_executable(TestSolveFromLPFile TestSolveFromLPFile.cxx)
target_link_libraries(TestSolveFromLPFile lpsolve55)
fbcAddTest(SolveFromLPFile TestSolveFromLPFile "test.lp")
