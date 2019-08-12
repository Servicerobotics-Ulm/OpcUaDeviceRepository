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
