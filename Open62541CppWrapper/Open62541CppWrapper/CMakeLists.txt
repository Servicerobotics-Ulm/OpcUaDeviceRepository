CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(Open62541CppWrapper VERSION 0.8)

# find open62541 as the main dependency
FIND_PACKAGE(open62541 PATHS /usr/local/lib/cmake)

# collect header files
FILE(GLOB HDRS ${PROJECT_SOURCE_DIR}/*.hh)

# setup server source files
SET(LIB_SRCS
	${PROJECT_SOURCE_DIR}/OpcUaValueType.cc
	${PROJECT_SOURCE_DIR}/OpcUaNodeId.cc
	${PROJECT_SOURCE_DIR}/OpcUaGenericClient.cc
	${PROJECT_SOURCE_DIR}/OpcUaGenericServer.cc
	${PROJECT_SOURCE_DIR}/MVC/AbstractModel.cc
	${PROJECT_SOURCE_DIR}/MVC/AbstractModelObserver.cc
)

# create server test executable
ADD_LIBRARY(${PROJECT_NAME} SHARED ${LIB_SRCS})

set_property(TARGET ${PROJECT_NAME} PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET ${PROJECT_NAME} PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})

# define include paths for the target
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>  # <prefix>/include/open62541CppWrapper
)

# add open62541 as library dependency and set further target properties
TARGET_LINK_LIBRARIES(${PROJECT_NAME} open62541)
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
)
TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} PUBLIC HAS_OPCUA)

# set the export-name used in the ${PROJECT_NAME}Config.cmake.in and for exporting and installing the target
SET(EXPORT_NAME ${PROJECT_NAME}Target)

# generate CMake package-config file
CONFIGURE_FILE(
  ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  @ONLY
)

# generate ConfigVersion file
INCLUDE(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  COMPATIBILITY AnyNewerVersion
)

# install library and target-exports
INSTALL(FILES ${HDRS} DESTINATION include/${PROJECT_NAME})
INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/MVC DESTINATION include/${PROJECT_NAME})
# install target and package-config files
INSTALL(TARGETS ${PROJECT_NAME} EXPORT ${EXPORT_NAME} LIBRARY DESTINATION lib)
INSTALL(EXPORT ${EXPORT_NAME} DESTINATION modules)
INSTALL(FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake DESTINATION modules)
INSTALL(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake" DESTINATION modules)
