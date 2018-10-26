//===================================================================================
//
//  Copyright (C) 2018 Alex Lotz, Vineeth Nagrath
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

#include "JoystickController.hh"

namespace Smart {

JoystickController::JoystickController(JoystickView *view)
:	AbstractController(view)
,	server(this)
,	view(view)
{  }

JoystickController::~JoystickController()
{  }

void JoystickController::update()
{
	//Nothing to do in this example
}

//Getter methods for all OPCUA Variable nodes.
OPCUA::StatusCode JoystickController::getXpos(int &xpos) const
{
	xpos = view->getModel()->getXpos();
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode JoystickController::getYpos(int &ypos) const
{
	ypos = view->getModel()->getYpos();
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode JoystickController::getX2pos(int &x2pos) const
{
	x2pos = view->getModel()->getX2pos();
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode JoystickController::getY2pos(int &y2pos) const
{
	y2pos = view->getModel()->getY2pos();
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode JoystickController::getBUTTONS(int &bUTTONS) const
{
	bUTTONS = view->getModel()->getButtons();
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode JoystickController::getBUTTON_0(bool &bUTTON_0) const
{
	bUTTON_0 = view->getModel()->getButton(0);
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode JoystickController::getBUTTON_1(bool &bUTTON_1) const
{
	bUTTON_1 = view->getModel()->getButton(1);
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode JoystickController::getBUTTON_2(bool &bUTTON_2) const
{
	bUTTON_2 = view->getModel()->getButton(2);
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode JoystickController::getBUTTON_3(bool &bUTTON_3) const
{
	bUTTON_3 = view->getModel()->getButton(3);
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode JoystickController::getBUTTON_4(bool &bUTTON_4) const
{
	bUTTON_4 = view->getModel()->getButton(4);
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode JoystickController::getBUTTON_5(bool &bUTTON_5) const
{
	bUTTON_5 = view->getModel()->getButton(5);
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode JoystickController::getBUTTON_6(bool &bUTTON_6) const
{
	bUTTON_6 = view->getModel()->getButton(6);
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode JoystickController::getBUTTON_7(bool &bUTTON_7) const
{
	bUTTON_7 = view->getModel()->getButton(7);
	return OPCUA::StatusCode::ALL_OK;
}
//Setter methods for OPCUA Entity nodes with write access.

//Access methods for OPCUA Method nodes.

int JoystickController::run()
{
	// this call executes the OPCUA server (until it is killed)
	return server.run();
}

} /* namespace Smart */
