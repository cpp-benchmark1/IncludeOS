cmake_minimum_required(VERSION 3.5)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project (service)
include(os)

os_add_executable(net_dhcpd_dhclient_linux "IncludeOS DHCP server test"  service.cpp)

os_add_plugins(net_dhcpd_dhclient_linux autoconf)
os_add_drivers(net_dhcpd_dhclient_linux virtionet)
os_add_stdout(net_dhcpd_dhclient_linux default_stdout)

configure_file(test.py ${CMAKE_CURRENT_BINARY_DIR})
