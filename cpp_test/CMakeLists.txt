cmake_minimum_required(VERSION 2.8)

project(genie_robot)

SET(CMAKE_USE_RELATIVE_PATHS "ON")
SET(NO_UNICODE "ON")
SET(CMAKE_CXX_FLAGS "-std=c++11")


SET(CPP_FILES  
    main.cpp
    robot.cpp
    util.cpp
)

SET(HDR_FILES  
    robot.h
    util.h
)

ADD_EXECUTABLE( ${PROJECT_NAME} ${CPP_FILES} ${HDR_FILES} )

INSTALL (TARGETS ${PROJECT_NAME} DESTINATION bin )
