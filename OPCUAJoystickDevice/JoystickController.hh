//===================================================================================
//
//  Copyright (C) 2018 Alex Lotz, Vineet Nagrath
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
//  Redistribution and use in source and binary forms, with or without modification,
//  are permitted provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//  2. Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//  3. Neither the name of the copyright holder nor the names of its contributors
//     may be used to endorse or promote products derived from this software
//     without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
//  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
//  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
//  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
//  OF THE POSSIBILITY OF SUCH DAMAGE.
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
