cmake_minimum_required(VERSION 2.8)

project(genie_robot)

#message(STATUS "DBG: CMAKE_CACHEFILE_DIR = " ${CMAKE_CACHEFILE_DIR})
#message(STATUS "DBG: CMAKE_BINARY_DIR = " ${CMAKE_BINARY_DIR})

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    if(NOT CMAKE_CACHEFILE_DIR)
        set(CMAKE_CACHEFILE_DIR ${CMAKE_BINARY_DIR})
    endif(NOT CMAKE_CACHEFILE_DIR)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_CACHEFILE_DIR}/dist/ CACHE PATH "default install dir" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

#message(STATUS "DBG: CMAKE_INSTALL_PREFIX = " ${CMAKE_INSTALL_PREFIX})

#include(cmake_vars.log.cmake)

set(CMAKE_USE_RELATIVE_PATHS "ON")
set(NO_UNICODE "ON")
set(CMAKE_CXX_FLAGS "-std=c++11")

set(CPP_FILES  
    src/main.cpp
    src/robot.cpp
    src/util.cpp
)

set(HDR_FILES  
    include/robot.h
    include/util.h
)

include_directories(
    include/
)

add_executable( ${PROJECT_NAME} ${CPP_FILES} ${HDR_FILES} )

install(TARGETS ${PROJECT_NAME} DESTINATION bin )

set(TEST_FILES
    test/place_only.t
    test/back_to_start.t
    test/no_commands.t
    test/place_and_move.t
    test/place_move_turn.t
)

install(FILES ${TEST_FILES} DESTINATION bin )

enable_testing()

add_test(PlaceOnly cram -v ${CMAKE_CACHEFILE_DIR}/dist/bin/place_only.t)
add_test(PlaceAndMove cram -v ${CMAKE_CACHEFILE_DIR}/dist/bin/place_and_move.t)
add_test(PlaceMoveTurn cram -v ${CMAKE_CACHEFILE_DIR}/dist/bin/place_move_turn.t)
add_test(NoCommands cram -v ${CMAKE_CACHEFILE_DIR}/dist/bin/no_commands.t)
add_test(BackToStart cram -v ${CMAKE_CACHEFILE_DIR}/dist/bin/back_to_start.t)

