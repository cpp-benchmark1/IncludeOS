cmake_minimum_required(VERSION 3.5)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project (service)
include(os)

os_add_executable(net_router6 "Routing test ipv6" service.cpp)

os_add_drivers(net_router6 virtionet)
os_add_stdout(net_router6 default_stdout)

configure_file(test.py ${CMAKE_CURRENT_BINARY_DIR})
configure_file(setup.sh ${CMAKE_CURRENT_BINARY_DIR})
