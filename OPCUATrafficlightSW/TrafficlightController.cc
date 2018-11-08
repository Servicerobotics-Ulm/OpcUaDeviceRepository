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

#include "TrafficlightController.hh"

namespace Smart {

#define LED_RED_PIN 0
#define LED_YELLOW_PIN 1
#define LED_GREEN_PIN 2

TrafficlightController::TrafficlightController(TrafficlightView *view)
:	AbstractController(view)
,	server(this)
,	view(view)
{
	view->getModel()->setDigitalOutput(LED_GREEN_PIN, false);
	view->getModel()->setDigitalOutput(LED_YELLOW_PIN, false);
	view->getModel()->setDigitalOutput(LED_RED_PIN, false);
}

TrafficlightController::~TrafficlightController()
{
	view->getModel()->setDigitalOutput(LED_GREEN_PIN, false);
	view->getModel()->setDigitalOutput(LED_YELLOW_PIN, false);
	view->getModel()->setDigitalOutput(LED_RED_PIN, false);
}

void TrafficlightController::update()
{
	//Nothing to do in this example
}

//Getter methods for all OPCUA Variable nodes.
OPCUA::StatusCode TrafficlightController::getLED_RED(bool &lED_RED) const
{
	lED_RED = view->getModel()->getDigitalOutput(LED_RED_PIN);
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode TrafficlightController::getLED_YELLOW(bool &lED_YELLOW) const
{
	lED_YELLOW = view->getModel()->getDigitalOutput(LED_YELLOW_PIN);
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode TrafficlightController::getLED_GREEN(bool &lED_GREEN) const
{
	lED_GREEN = view->getModel()->getDigitalOutput(LED_GREEN_PIN);
	return OPCUA::StatusCode::ALL_OK;
}
//Setter methods for OPCUA Entity nodes with write access.
OPCUA::StatusCode TrafficlightController::setLED_RED(const bool &value)
{
	view->getModel()->setDigitalOutput(LED_RED_PIN, value);
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode TrafficlightController::setLED_YELLOW(const bool &value)
{
	view->getModel()->setDigitalOutput(LED_YELLOW_PIN, value);
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode TrafficlightController::setLED_GREEN(const bool &value)
{
	view->getModel()->setDigitalOutput(LED_GREEN_PIN, value);
	return OPCUA::StatusCode::ALL_OK;
}

//Access methods for OPCUA Method nodes.

int TrafficlightController::run()
{
	// this call executes the OPCUA server (until it is killed)
	return server.run();
}

} /* namespace Smart */
