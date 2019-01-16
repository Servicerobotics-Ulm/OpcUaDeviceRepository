# OPC UA Traffic Light Server (Software Simulated)

This Device implementation provides an OPC UA server that runs on a simulated PiXtend V2 device as the controller for a traffic light (Software Simulated). The following describes the traffic light setup for simulated PiXtend V2 device.
```sh
Digital Output Pin 0 (DO 0): RED LED 
Digital Output Pin 1 (DO 1): YELLOW LED
Digital Output Pin 2 (DO 2): GREEN LED
```

## The OPC UA Information Model

The OPC UA information model for traffic light server contains 3 boolean nodes, one for each of the three color LEDs.
![Alt text](TrafficlightServerSW.png?raw=true "Traffic Light Server Information Model (Software Simulated)")
## Usage

For installation instructions, refer to [../README.md](../README.md).

To start the OPC UA Traffic Light Server follow the instructions below:

Step 1: Build OpcUaDeviceRepository Examples on any computer<br />
```sh
$ cd Path/To/OpcUaDeviceRepository
$ mkdir build
$ cd build
$ cmake ..
$ make
```
Step 2: Start OPC UA Traffic Light Server SW (Software Simulated)<br />
```sh
$ cd Path/To/OpcUaDeviceRepository/build/OPCUATrafficlightSW
$ ./TrafficlightServerSWTest
```

Step 3: The Server can now be accessed from any OPC UA Client. Updates can be seen at Server console. 
![Alt text](TrafficlightSWOUT.png?raw=true "Traffic Light Server Console")
