# OPC UA Production Station

This Device implementation provides an OPC UA server that runs on a PiXtend V2 device as the controller for a production station. The following diagram illustrates the Pixtend controller wiring with the production station hardware components.

![Alt text](OPCUAProductionStation.jpg?raw=true "OPC UA Production Station Setup")

The production station consists of the following hardware components:<br />
 * PiXtend V2 S https://www.pixtend.de/downloads/pixtend-v2-downloads-english/
 * Miniature worm gear motor SFS Gr. 2 with DC-motor 24V i=59:3 idle speed 210 per min  https://www.maedler.de/Article/43047424
 * IBT-2 H-bridge module http://www.hessmer.org/blog/2013/12/28/ibt-2-h-bridge-with-arduino/
 * MDR-100-24 AC to DC converter https://eu.mouser.com/ProductDetail/MEAN-WELL/MDR-100-24?qs=TaOZSEYtRiUHDfSuqlnTDA==
 * K37 cable EM 24VAC/DC GN/YE/RD  https://www.werma.com/en/s_c900i2583/K37_cable_24VAC/DC_CL/GN/YE/RD/69814075.html
 * FESTO 165 326 SOEG-L-Q30-P-A-K-2L  https://www.festo.com/net/SupportPortal/Files/407497/SOEG-L-Q30-PA-K-2L_2007-07b_719262D6.pdf

## The OPC UA Information Model

The OPC UA information model for Production Station contains 3 boolean nodes (One for each of the three color LEDs), one method to initiate loading of the box on to the production station and 2 methods to start/stop unloading of the box from the production station.
![Alt text](ProductionStation.png?raw=true "Production Station Server Information Model")
## Usage

For installation instructions, refer to [../README.md](../README.md).

As an additional dependency, this programm requires the **pxdev** library that you can downlad from: FIXME add link

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
