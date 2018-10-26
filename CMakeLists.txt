CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

# this is a lightweight C++ Wrapper around the open62541 library
ADD_SUBDIRECTORY(Open62541CppWrapper)

# specific OPC UA device servers
ADD_SUBDIRECTORY(OPCUAJoystickDevice)
