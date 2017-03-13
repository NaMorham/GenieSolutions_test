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

include(cmake_vars.log.cmake)

set(CMAKE_USE_RELATIVE_PATHS "ON")
set(NO_UNICODE "ON")
#set(CMAKE_CXX_FLAGS "-std=c++11")

if(CMAKE_COMPILER_IS_GNUCXX)
    #add_definitions(-Wall -ansi -Wno-deprecated -pthread -std=c++11)
    add_definitions(-Wall -ansi -Wno-deprecated -std=c++11)
endif()

if(MSVC)
    #vc 2012 fix for vararg templates
    set(MSVC_COMPILER_DEFS "-D_VARIADIC_MAX=10")
endif() 

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

# -------------------------------------------------------
enable_testing()
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

# -------------------------------------------------------
# Googletest projects
# Utils
set(GTEST_UTIL_PROJECT genie_util_test)

include_directories(
    include/
    ${GTEST_INCLUDE_DIRS}
)

add_executable(${GTEST_UTIL_PROJECT}
    test/util_test.cpp
    src/util.cpp
)

target_link_libraries(${GTEST_UTIL_PROJECT}
    ${GTEST_BOTH_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

install(TARGETS ${GTEST_UTIL_PROJECT} DESTINATION bin )

add_test(GTest-Utils ${GTEST_UTIL_PROJECT})

# Robot class
set(GTEST_ROBOT_PROJECT genie_robot_test)

include_directories(
    include/
    ${GTEST_INCLUDE_DIRS}
)

add_executable(${GTEST_ROBOT_PROJECT}
    test/robot_test.cpp
    src/util.cpp
    src/robot.cpp
)

target_link_libraries(${GTEST_ROBOT_PROJECT}
    ${GTEST_BOTH_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

install(TARGETS ${GTEST_ROBOT_PROJECT} DESTINATION bin )

add_test(GTest-Robot ${GTEST_ROBOT_PROJECT})

# -------------------------------------------------------
# Cram tests
set(TEST_FILES
    test/place_only.t
    test/back_to_start.t
    test/no_commands.t
    test/place_and_move.t
    test/place_move_turn.t
)

install(FILES ${TEST_FILES} DESTINATION test)

# TODO: Figure out how to add ${CMAKE_CURRENT_BINARY_DIR} to the test path env

add_test(PlaceOnly cram -v ${CMAKE_CACHEFILE_DIR}/dist/test/place_only.t)
add_test(PlaceAndMove cram -v ${CMAKE_CACHEFILE_DIR}/dist/test/place_and_move.t)
add_test(PlaceMoveTurn cram -v ${CMAKE_CACHEFILE_DIR}/dist/test/place_move_turn.t)
add_test(NoCommands cram -v ${CMAKE_CACHEFILE_DIR}/dist/test/no_commands.t)
add_test(BackToStart cram -v ${CMAKE_CACHEFILE_DIR}/dist/test/back_to_start.t)
