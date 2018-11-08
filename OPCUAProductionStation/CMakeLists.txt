CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(ProductionStationServer)

# find Open62541CppWrapper as the main dependency
# FIND_PACKAGE(Open62541CppWrapper)

FIND_LIBRARY(PIXTEND_LIB NAMES pixtend)

# setup default include directoy
INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}
)

# setup server source files
SET(SERVER_SRCS
	${PROJECT_SOURCE_DIR}/ProductionStationView.cc
	${PROJECT_SOURCE_DIR}/ProductionStationController.cc
	${PROJECT_SOURCE_DIR}/OpcUaProductionStation.cc
	${PROJECT_SOURCE_DIR}/ProductionStationServerMain.cc
	${PROJECT_SOURCE_DIR}/Pixtend2DriverModel.cpp
)

IF(PIXTEND_LIB)
# create server test executable
ADD_EXECUTABLE(${PROJECT_NAME} ${SERVER_SRCS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} Open62541CppWrapper pixtend wiringPi rt crypt pthread)
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
)
ELSE()
MESSAGE("pixtend library not found -> skip building ${PROJECT_NAME}")
ENDIF()
