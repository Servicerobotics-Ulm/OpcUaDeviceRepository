# OpcUaDeviceRepository

This repository consists of device driver implementations, each providing an OPC UA interface. The OPC UA interface is implemented using the [open62541](https://open62541.org/) C library which is encapsulated within the leightweight C++ Wrapper (see subfolder Open62541CppWrapper). Individual devices might have additional, platform-specific dependencies related to the respectivelly used device library. 

## Installation instructions

Installation requirements:

  * [**open62541**](https://open62541.org/) using the [github repository](https://github.com/open62541/open62541)
  * [**CMake**](https://cmake.org/) min. version **3.0**
  * A C++ compiler supporting the **C++ 11** standard

For more detailed installation instructions for the open62541 library, please see the Readme within the subfolder Open62541CppWrapper. After satisfying the installation requirements, you can build the projects as follows:

```
> mkdir build
> cd build
> cmake ..
> make 
> sudo make install # optional
```

