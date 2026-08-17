# CMake generated Testfile for 
# Source directory: /home/mariavittoria/hopfield_esame
# Build directory: /home/mariavittoria/hopfield_esame/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test([=[final.test]=] "/home/mariavittoria/hopfield_esame/build/Debug/final.test")
  set_tests_properties([=[final.test]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/mariavittoria/hopfield_esame/CMakeLists.txt;49;add_test;/home/mariavittoria/hopfield_esame/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test([=[final.test]=] "/home/mariavittoria/hopfield_esame/build/Release/final.test")
  set_tests_properties([=[final.test]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/mariavittoria/hopfield_esame/CMakeLists.txt;49;add_test;/home/mariavittoria/hopfield_esame/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test([=[final.test]=] "/home/mariavittoria/hopfield_esame/build/RelWithDebInfo/final.test")
  set_tests_properties([=[final.test]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/mariavittoria/hopfield_esame/CMakeLists.txt;49;add_test;/home/mariavittoria/hopfield_esame/CMakeLists.txt;0;")
else()
  add_test([=[final.test]=] NOT_AVAILABLE)
endif()
