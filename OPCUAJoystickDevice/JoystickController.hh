//===================================================================================
//
//  Copyright (C) 2019 Alex Lotz, Vineet Nagrath
//
//        lotz@hs-ulm.de
//        nagrath@hs-ulm.de
//
//        Servicerobotik Ulm
//        Christian Schlegel
//        Ulm University of Applied Sciences
//        Prittwitzstr. 10
//        89075 Ulm
//        Germany
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
//===================================================================================


#ifndef JOYSTICKCONTROLLER_H_
#define JOYSTICKCONTROLLER_H_

#include <MVC/AbstractController.hh>

#include "JoystickView.hh"
#include "JoystickInterface.hh"
#include "OpcUaJoystick.hh"

namespace Smart {

/**
 * This class implements the Controller part of the Model-View-Controller (MVC)
 * design pattern. As a second responsibility, this class also implements
 * the generated interface which is used by the internally initialized OPC UA
 * server to interact with the actual model. The actual model can be internally
 * accessed over the given view pointer. Conceptually, this class decouples
 * the OPC UA server from the Model and handles the lifecycle of the OPC UA server.
 */
class JoystickController : public AbstractController, public JoystickInterface
{
private:
	OPCUA::Joystick server;
	JoystickView *view;

public:
	JoystickController(JoystickView *view);
	virtual ~JoystickController();

	/// implements AbstractModelObserver
	virtual void update() override;
	
	
	/** XML Specific Getter function for entity Xpos
	 *
	 *  This function gets Xpos  from the Server
	 *  When class Joystick is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *	
	 *  @param value	:output parameter, returns the new value if StatusCode is ALL_OK
	 *
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode getXpos(int &xpos) const override;
	
	/** XML Specific Getter function for entity Ypos
	 *
	 *  This function gets Ypos  from the Server
	 *  When class Joystick is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *	
	 *  @param value	:output parameter, returns the new value if StatusCode is ALL_OK
	 *
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode getYpos(int &ypos) const override;
	
	/** XML Specific Getter function for entity X2pos
	 *
	 *  This function gets X2pos  from the Server
	 *  When class Joystick is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *	
	 *  @param value	:output parameter, returns the new value if StatusCode is ALL_OK
	 *
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode getX2pos(int &x2pos) const override;
	
	/** XML Specific Getter function for entity Y2pos
	 *
	 *  This function gets Y2pos  from the Server
	 *  When class Joystick is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *	
	 *  @param value	:output parameter, returns the new value if StatusCode is ALL_OK
	 *
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode getY2pos(int &y2pos) const override;
	
	/** XML Specific Getter function for entity BUTTONS
	 *
	 *  This function gets BUTTONS  from the Server
	 *  When class Joystick is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *	
	 *  @param value	:output parameter, returns the new value if StatusCode is ALL_OK
	 *
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode getBUTTONS(int &bUTTONS) const override;
	
	/** XML Specific Getter function for entity BUTTON_0
	 *
	 *  This function gets BUTTON_0  from the Server
	 *  When class Joystick is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *	
	 *  @param value	:output parameter, returns the new value if StatusCode is ALL_OK
	 *
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode getBUTTON_0(bool &bUTTON_0) const override;
	
	/** XML Specific Getter function for entity BUTTON_1
	 *
	 *  This function gets BUTTON_1  from the Server
	 *  When class Joystick is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *	
	 *  @param value	:output parameter, returns the new value if StatusCode is ALL_OK
	 *
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode getBUTTON_1(bool &bUTTON_1) const override;
	
	/** XML Specific Getter function for entity BUTTON_2
	 *
	 *  This function gets BUTTON_2  from the Server
	 *  When class Joystick is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *	
	 *  @param value	:output parameter, returns the new value if StatusCode is ALL_OK
	 *
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode getBUTTON_2(bool &bUTTON_2) const override;
	
	/** XML Specific Getter function for entity BUTTON_3
	 *
	 *  This function gets BUTTON_3  from the Server
	 *  When class Joystick is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *	
	 *  @param value	:output parameter, returns the new value if StatusCode is ALL_OK
	 *
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode getBUTTON_3(bool &bUTTON_3) const override;
	
	/** XML Specific Getter function for entity BUTTON_4
	 *
	 *  This function gets BUTTON_4  from the Server
	 *  When class Joystick is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *	
	 *  @param value	:output parameter, returns the new value if StatusCode is ALL_OK
	 *
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode getBUTTON_4(bool &bUTTON_4) const override;
	
	/** XML Specific Getter function for entity BUTTON_5
	 *
	 *  This function gets BUTTON_5  from the Server
	 *  When class Joystick is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *	
	 *  @param value	:output parameter, returns the new value if StatusCode is ALL_OK
	 *
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode getBUTTON_5(bool &bUTTON_5) const override;
	
	/** XML Specific Getter function for entity BUTTON_6
	 *
	 *  This function gets BUTTON_6  from the Server
	 *  When class Joystick is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *	
	 *  @param value	:output parameter, returns the new value if StatusCode is ALL_OK
	 *
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode getBUTTON_6(bool &bUTTON_6) const override;
	
	/** XML Specific Getter function for entity BUTTON_7
	 *
	 *  This function gets BUTTON_7  from the Server
	 *  When class Joystick is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *	
	 *  @param value	:output parameter, returns the new value if StatusCode is ALL_OK
	 *
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode getBUTTON_7(bool &bUTTON_7) const override;
	
	
	/// call this method at the end of the main function
	virtual int run() override;
};

} /* namespace Smart */

#endif /* JOYSTICKCONTROLLER_H_ */
