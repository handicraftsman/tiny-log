cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(TinyLog VERSION 0.1.0 LANGUAGES C)

IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  SET(CMAKE_INSTALL_PREFIX /usr/ CACHE PATH "Default install prefix" FORCE)
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig)

add_library(libtiny-log SHARED tiny-log.c)
set_target_properties(libtiny-log PROPERTIES OUTPUT_NAME tiny-log)

add_executable(tltest test.c)
target_link_libraries(tltest libtiny-log)

configure_file(${CMAKE_SOURCE_DIR}/tiny-log.pc.in ${CMAKE_BINARY_DIR}/tiny-log.pc)
install(FILES ${CMAKE_BINARY_DIR}/tiny-log.pc DESTINATION lib/pkgconfig)

install(
  TARGETS libtiny-log
  LIBRARY DESTINATION lib
)

install(FILES tiny-log.h DESTINATION include)
