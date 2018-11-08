CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(TrafficlightServerSWTest)

# find Open62541CppWrapper as the main dependency
# FIND_PACKAGE(Open62541CppWrapper)

# setup default include directoy
INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}
)

# setup server source files
SET(SERVER_SRCS
	${PROJECT_SOURCE_DIR}/TrafficlightView.cc
	${PROJECT_SOURCE_DIR}/TrafficlightController.cc
	${PROJECT_SOURCE_DIR}/OpcUaTrafficlight.cc
	${PROJECT_SOURCE_DIR}/TrafficlightServerMain.cc
	${PROJECT_SOURCE_DIR}/Pixtend2DriverModel.cpp	
)

# create server test executable
ADD_EXECUTABLE(${PROJECT_NAME} ${SERVER_SRCS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} Open62541CppWrapper rt crypt pthread)
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
)
