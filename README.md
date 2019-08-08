# OpcUaDeviceRepository

This repository consists of device driver implementations, each providing an OPC UA interface. The OPC UA interface is implemented based on the [Open62541CppWrapper](https://github.com/Servicerobotics-Ulm/Open62541CppWrapper) C++ library. The [Open62541CppWrapper](https://github.com/Servicerobotics-Ulm/Open62541CppWrapper) internally uses and encapsulates the [open62541](https://open62541.org/) C library. Individual devices might have additional, platform-specific dependencies related to the respectivelly used device library. 

This repository is maintained by Servicerobotik Ulm. For more information see:

* Big picture: relation of repositories: https://wiki.servicerobotik-ulm.de/download
* SRRC Technical Wiki on SmartSoft and SmartMDSD Toolchain: https://wiki.servicerobotik-ulm.de

## Dependencies

  * [**Open62541CppWrapper**](https://github.com/Servicerobotics-Ulm/Open62541CppWrapper)
  * [**CMake**](https://cmake.org/) min. version **3.5**
  * A C++ compiler supporting the **C++ 14** standard

Further dependencies and instructions are provided in the READMEs of the related device-subfolders.
