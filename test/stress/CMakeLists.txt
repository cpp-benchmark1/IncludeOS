cmake_minimum_required(VERSION 3.5)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(service)
include(os)

set(SOURCES
  service.cpp
)

os_add_executable(stress "Stress test" ${SOURCES})
os_add_stdout(stress default_stdout)
os_add_drivers(stress virtionet)
configure_file(test.py ${CMAKE_CURRENT_BINARY_DIR})
