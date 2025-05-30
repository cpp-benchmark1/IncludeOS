cmake_minimum_required(VERSION 3.6.0)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(includeos C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
  include
  ../../src/include
)



if (NOT ARCH)
  set(ARCH CMAKE_SYSTEM_PROCESSOR)
endif()

#do we need all of this*?
add_definitions(-DARCH_${ARCH})
add_definitions(-DARCH="${ARCH}")
add_definitions(-DPLATFORM_${PLATFORM})

set(TRIPLE "${ARCH}-pc-linux-elf")
set(CMAKE_CXX_COMPILER_TARGET ${TRIPLE})
set(CMAKE_C_COMPILER_TARGET ${TRIPLE})

add_custom_command(
  PRE_BUILD
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/hotswap64.bin
	COMMAND ${CMAKE_ASM_NASM_COMPILER} -f bin -o ${CMAKE_CURRENT_BINARY_DIR}/hotswap64.bin ${CMAKE_CURRENT_SOURCE_DIR}/src/hotswap64.asm
  COMMENT "Building hotswap binary"
  DEPENDS src/hotswap64.asm
)
add_custom_target(hotswap64 DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/hotswap64.bin)


set(SRCS
  src/storage.cpp
  src/partition.cpp
  src/update.cpp
  src/resume.cpp
  src/rollback.cpp
  src/elfscan.cpp
  src/serialize_tcp.cpp
)
if (NOT CMAKE_TESTING_ENABLED)
  list(APPEND SRCS
    src/hotswap.cpp
    src/hotswap64_blob.asm
  )
  if (${ARCH} STREQUAL "x86_64")
    list(APPEND SRCS src/serialize_s2n.cpp)
  endif()
endif()


# LiveUpdate static library
add_library(liveupdate STATIC ${SRCS} )
if (NOT CMAKE_TESTING_ENABLED)
  add_dependencies(liveupdate hotswap64)
endif()
set_target_properties(liveupdate PROPERTIES PUBLIC_HEADER "include/liveupdate;include/liveupdate.hpp")

INSTALL(TARGETS liveupdate
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include
)
