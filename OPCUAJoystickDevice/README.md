# OPC UA Joystick Device

This Device implementation probides an OPC UA server that uses the Linux Joystick library to access any Linux supported joystick device. The default hardware device path is "/dev/input/js0". See the Class LinuxJoystickDriverModel that allows changing this path as a constructor argument.

## The OPC UA Information Model

FIXME: shortly describe the information model with a Prosys screenshot 
![Alt text](Joystick.png?raw=true "Joystick Server Information Model")
## Usage

For installation instructions, refer to [../README.md](../README.md).

To start the OPC UA Joystick Device follow the instructions below:

Step 1: Build OpcUaDeviceRepository Examples
```sh
$ cd Path/To/OpcUaDeviceRepository
$ mkdir build
$ cd build
$ cmake ..
$ make
```
Step 2: Attach joystick to the computer
Step 3: Start OPC UA Joystick Device
```sh
$ cd Path/To/OpcUaDeviceRepository/build/OPCUAJoystickDevice
$ ./OPCUAJoystickServer
```
