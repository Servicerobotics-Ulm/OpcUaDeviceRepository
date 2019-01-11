# OPC UA Production Station

This Device implementation provides an OPC UA server that runs on a PiXtend V2 device as the controller for a production station. The following diagram describes the production station setup.
![Alt text](OPCUAProductionStation.jpg?raw=true "OPC UA Production Station Setup")

## The OPC UA Information Model

The OPC UA information model for Production Station contains 3 boolean nodes (One for each of the three color LEDs), one method to initiate loading of the box on to the production station and 2 methods to start/stop unloading of the box from the production station.
![Alt text](ProductionStation.png?raw=true "Production Station Server Information Model")
## Usage

For installation instructions, refer to [../README.md](../README.md).

To start the OPC UA Production Station follow the instructions below:

Step 1: Build OpcUaDeviceRepository Examples on PiXtend V2 device<br />
```sh
$ cd Path/To/OpcUaDeviceRepository
$ mkdir build
$ cd build
$ cmake ..
$ make
```
Step 2: Power On the conveyor motors<br />
Step 3: Start OPC UA Production Station<br />
```sh
$ cd Path/To/OpcUaDeviceRepository/build/OPCUAProductionStation
$ ./ProductionStationServer
```

Step 4: The Server can now be accessed from any OPC UA Client.
![Alt text](ProductionStationSW.png?raw=true "Production Station Server Method Call Usage")
