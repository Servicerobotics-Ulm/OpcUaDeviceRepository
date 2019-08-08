CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(OPCUAJoystickServer)

FIND_PACKAGE(Open62541CppWrapper 1.0)

# setup default include directoy
INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}
)

# setup server source files
SET(SERVER_SRCS
	${PROJECT_SOURCE_DIR}/LinuxJoystickDriverModel.cc
	${PROJECT_SOURCE_DIR}/JoystickView.cc
	${PROJECT_SOURCE_DIR}/JoystickController.cc
	${PROJECT_SOURCE_DIR}/JoystickServerMain.cc
	${PROJECT_SOURCE_DIR}/OpcUaJoystick.cc
)

# create server test executable
ADD_EXECUTABLE(${PROJECT_NAME} ${SERVER_SRCS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} Open62541CppWrapper pthread)
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
)
