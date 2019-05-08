# OpcUaDeviceRepository

This repository consists of device driver implementations, each providing an OPC UA interface. The OPC UA interface is implemented using the [open62541](https://open62541.org/) C library which is encapsulated within the leightweight C++ Wrapper (see subfolder Open62541CppWrapper). Individual devices might have additional, platform-specific dependencies related to the respectivelly used device library. 

This repository is maintained by Servicerobotik Ulm. For more information see:

* Big picture: relation of repositories: https://wiki.servicerobotik-ulm.de/download
* SRRC Technical Wiki on SmartSoft and SmartMDSD Toolchain: https://wiki.servicerobotik-ulm.de

## Installation dependencies

  * [**open62541**](https://open62541.org/) using the [github repository](https://github.com/open62541/open62541) (install as described below)
  ** tested with commit in master branch 755abcfc54f5c7f438d0e1dee91370df28e6c02e
  * [**CMake**](https://cmake.org/) min. version **3.0**
  * A C++ compiler supporting the **C++ 11** standard

## Compile instructions for the open62541 library 

### Arranging prerequisites
```sh
$ sudo apt-get install git build-essential gcc pkg-config cmake python python-six
```
### Cloning open62541
```sh
$ git clone https://github.com/open62541/open62541.git
$ cd open62541
$ git submodule init
$ git submodule update
```
![IMG01](images/IMG01_Cloning_open62541.png)

### Building open62541
```sh
$ mkdir build
$ cd build
$ cmake -DUA_ENABLE_AMALGAMATION=ON -DUA_ENABLE_METHODCALLS=ON -DUA_ENABLE_SUBSCRIPTIONS=ON -DUA_ENABLE_DISCOVERY_MULTICAST=ON ..
$ make
$ sudo make install
```
![IMG02](images/IMG02_Building_open62541.png)
### Building and running OPCUA examples using single-file release open62541.h
```sh
$ cd examples
$ gcc -std=c99 -I../build/ ../build/open62541.c tutorial_server_variable.c -o server
$ ./server
```
![IMG03](images/IMG03_Running_Examples.png) 

### Open a Prosys OPC UA client to view/edit server nodes
**Address**: opc.tcp://<*IP address of server* / *localhost*>:4840
![IMG04](images/IMG04_View_in_OPCUA_client.png)


## Compile instructions for this repository

The following instructions will build the Open62541CppWrapper and all the OPC UA enabled Devices:

```
> mkdir build
> cd build
> cmake ..
> make 
> sudo make install # optional
```

