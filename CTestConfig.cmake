## This file should be placed in the root directory of your project.
## Then modify the CMakeLists.txt file in the root directory of your
## project to incorporate the testing dashboard.
## # The following are required to uses Dart and the Cdash dashboard
## enable_testing()
## include(CTest)

set(CTEST_PROJECT_NAME "libFBC")
set(CTEST_NIGHTLY_START_TIME "23:00:00 CEST")
set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "thecosmocompany.com")
set(CTEST_DROP_LOCATION "/CDash/submit.php?project=libFBC")
set(CTEST_DROP_SITE_CDASH TRUE)
