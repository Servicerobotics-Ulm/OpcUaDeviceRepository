# OPC UA Traffic Light Server

This Device implementation provides an OPC UA server that runs on a PiXtend V2 device as the controller for a traffic light. The following diagram describes the traffic light setup.
![Alt text](OPCUATrafficlight.jpg?raw=true "OPC UA Trafficlight Setup")

## The OPC UA Information Model

The OPC UA information model for traffic light server contains 3 boolean nodes, one for each of the three color LEDs.
![Alt text](TrafficlightServer.png?raw=true "Traffic Light Server Information Model")
## Usage

For installation instructions, refer to [../README.md](../README.md).

To start the OPC UA Traffic Light Server follow the instructions below:

Step 1: Build OpcUaDeviceRepository Examples on PiXtend V2 device<br />
```sh
$ cd Path/To/OpcUaDeviceRepository
$ mkdir build
$ cd build
$ cmake ..
$ make
```
Step 2: Start OPC UA Traffic Light Server<br />
```sh
$ cd Path/To/OpcUaDeviceRepository/build/OPCUATrafficlight
$ ./TrafficlightServerTest
```

Step 3: The Server can now be accessed from any OPC UA Client.
