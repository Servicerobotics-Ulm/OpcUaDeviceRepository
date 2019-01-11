# OPC UA Joystick Device

This Device implementation probides an OPC UA server that uses the Linux Joystick library to access any Linux supported joystick device. The default hardware device path is "/dev/input/js0". See the Class LinuxJoystickDriverModel that allows changing this path as a constructor argument.

## The OPC UA Information Model

The OPC UA information model for Joystick Server contains 8 boolean nodes (One for every button on the Joystick), one integer node that combines 8 bits of boolean buttons as one integer and 4 integer nodes that contain the X and Y positions for the two joysticks.
![Alt text](Joystick.png?raw=true "Joystick Server Information Model")
## Usage

For installation instructions, refer to [../README.md](../README.md).

To start the OPC UA Joystick Device follow the instructions below:

Step 1: Build OpcUaDeviceRepository Examples<br />
```sh
$ cd Path/To/OpcUaDeviceRepository
$ mkdir build
$ cd build
$ cmake ..
$ make
```
Step 2: Attach joystick to the computer<br />
Step 3: Start OPC UA Joystick Device<br />
```sh
$ cd Path/To/OpcUaDeviceRepository/build/OPCUAJoystickDevice
$ ./OPCUAJoystickServer
```
