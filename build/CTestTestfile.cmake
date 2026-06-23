# CMake generated Testfile for 
# Source directory: F:/SelfJob/CPlusPlusDesignModeDemo
# Build directory: F:/SelfJob/CPlusPlusDesignModeDemo/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(smoke "F:/SelfJob/CPlusPlusDesignModeDemo/build/bin/Debug/DesignPatternDemoTests.exe")
  set_tests_properties(smoke PROPERTIES  _BACKTRACE_TRIPLES "F:/SelfJob/CPlusPlusDesignModeDemo/CMakeLists.txt;99;add_test;F:/SelfJob/CPlusPlusDesignModeDemo/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(smoke "F:/SelfJob/CPlusPlusDesignModeDemo/build/bin/Release/DesignPatternDemoTests.exe")
  set_tests_properties(smoke PROPERTIES  _BACKTRACE_TRIPLES "F:/SelfJob/CPlusPlusDesignModeDemo/CMakeLists.txt;99;add_test;F:/SelfJob/CPlusPlusDesignModeDemo/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(smoke "F:/SelfJob/CPlusPlusDesignModeDemo/build/bin/MinSizeRel/DesignPatternDemoTests.exe")
  set_tests_properties(smoke PROPERTIES  _BACKTRACE_TRIPLES "F:/SelfJob/CPlusPlusDesignModeDemo/CMakeLists.txt;99;add_test;F:/SelfJob/CPlusPlusDesignModeDemo/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(smoke "F:/SelfJob/CPlusPlusDesignModeDemo/build/bin/RelWithDebInfo/DesignPatternDemoTests.exe")
  set_tests_properties(smoke PROPERTIES  _BACKTRACE_TRIPLES "F:/SelfJob/CPlusPlusDesignModeDemo/CMakeLists.txt;99;add_test;F:/SelfJob/CPlusPlusDesignModeDemo/CMakeLists.txt;0;")
else()
  add_test(smoke NOT_AVAILABLE)
endif()
