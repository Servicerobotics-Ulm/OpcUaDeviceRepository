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

#include "ProductionStationController.hh"

namespace Smart {

#define MOTOR_CLOCKWISE_GPIO_PIN 0
#define MOTOR_ANTICLOCKWISE_GPIO_PIN 1
#define BOX_SENSOR_PIN 1
#define BOX_SENSOR_CUTOFF_PIN 3
#define LED_RED_PIN 0
#define LED_YELLOW_PIN 1
#define LED_GREEN_PIN 2

ProductionStationController::ProductionStationController(ProductionStationView *view)
:	AbstractController(view)
,	server(this)
,	view(view)
{
	view->getModel()->setDigitalOutput(0);
	view->getModel()->setDigitalOutput(BOX_SENSOR_CUTOFF_PIN, true);   // Setting ON the proximity sensor
	view->getModel()->setDigitalOutput(LED_GREEN_PIN, true);
}

ProductionStationController::~ProductionStationController()
{
	view->getModel()->setDigitalOutput(LED_GREEN_PIN, false);
	view->getModel()->setDigitalOutput(LED_YELLOW_PIN, false);
	view->getModel()->setDigitalOutput(LED_RED_PIN, false);
	view->getModel()->setGPIO(MOTOR_CLOCKWISE_GPIO_PIN, false);
	view->getModel()->setGPIO(MOTOR_ANTICLOCKWISE_GPIO_PIN, false);
}

void ProductionStationController::update()
{
	//Nothing to do in this example
}

//Getter methods for all OPCUA Variable nodes.
OPCUA::StatusCode ProductionStationController::getIsBoxPresent(bool &isBoxPresent) const
{
	isBoxPresent = view->getModel()->getDigitalInput(BOX_SENSOR_PIN);
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode ProductionStationController::getLED_RED(bool &lED_RED) const
{
	lED_RED = view->getModel()->getDigitalOutput(LED_RED_PIN);
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode ProductionStationController::getLED_YELLOW(bool &lED_YELLOW) const
{
	lED_YELLOW = view->getModel()->getDigitalOutput(LED_YELLOW_PIN);
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode ProductionStationController::getLED_GREEN(bool &lED_GREEN) const
{
	lED_GREEN = view->getModel()->getDigitalOutput(LED_GREEN_PIN);
	return OPCUA::StatusCode::ALL_OK;
}
//Setter methods for OPCUA Entity nodes with write access.
OPCUA::StatusCode ProductionStationController::setLED_RED(const bool &value)
{
	view->getModel()->setDigitalOutput(LED_RED_PIN, value);
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode ProductionStationController::setLED_YELLOW(const bool &value)
{
	view->getModel()->setDigitalOutput(LED_YELLOW_PIN, value);
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode ProductionStationController::setLED_GREEN(const bool &value)
{
	view->getModel()->setDigitalOutput(LED_GREEN_PIN, value);
	return OPCUA::StatusCode::ALL_OK;
}

//Access methods for OPCUA Method nodes.
OPCUA::StatusCode ProductionStationController::callLoadbox(const int &Timeout,std::string &Result)
{
	printf("Loadbox()  IN\n");
	std::string status = "ERROR";
	view->getModel()->setDigitalOutput(LED_YELLOW_PIN, true);
	bool isBoxPresent = false;
	getIsBoxPresent(isBoxPresent);
	if(isBoxPresent == false) 
	{
		// setting up GPIO Mode
		view->getModel()->setGPIOCtrl(MOTOR_CLOCKWISE_GPIO_PIN, true);
		view->getModel()->setGPIOCtrl(MOTOR_ANTICLOCKWISE_GPIO_PIN, true);
		// activate motor clockwise
		view->getModel()->setGPIO(MOTOR_ANTICLOCKWISE_GPIO_PIN, false);
		view->getModel()->setGPIO(MOTOR_CLOCKWISE_GPIO_PIN, true);
		// wait till box arrives (or timeout occurs)
		int result = view->getModel()->waitOnDigitalInput(BOX_SENSOR_PIN, true, std::chrono::seconds(Timeout));
		// stop motor
		view->getModel()->setGPIO(MOTOR_CLOCKWISE_GPIO_PIN, false);
		view->getModel()->setGPIO(MOTOR_ANTICLOCKWISE_GPIO_PIN, false);
		// check for timeout
		if(result == -1) {
			status = "TIMEOUT";
		} else {
			status = "SUCCESS";
		}
	}

	view->getModel()->setDigitalOutput(LED_YELLOW_PIN, false);
	printf("Loadbox()  OUT\n");
	Result = status;
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode ProductionStationController::callStart_unloading(const int &XtimeoutX,std::string &Result)
{
	printf("Start_unloadbox()  IN\n");
	view->getModel()->setDigitalOutput(LED_RED_PIN, true);
	std::string status = "ERROR";
	bool isBoxPresent = false;
	getIsBoxPresent(isBoxPresent);
	if(isBoxPresent == true) 
	{
		view->getModel()->setDigitalOutput(LED_YELLOW_PIN, true);
		// setting up GPIO Mode
		view->getModel()->setGPIOCtrl(MOTOR_CLOCKWISE_GPIO_PIN, true);
		view->getModel()->setGPIOCtrl(MOTOR_ANTICLOCKWISE_GPIO_PIN, true);
		// activate motor anti-clockwise
		view->getModel()->setGPIO(MOTOR_CLOCKWISE_GPIO_PIN, false);
		view->getModel()->setGPIO(MOTOR_ANTICLOCKWISE_GPIO_PIN, true);
		status = "UNLOADING_STARTED";
	}
	printf("Start_unloadbox()  OUT\n");
	view->getModel()->setDigitalOutput(LED_RED_PIN, false);
	Result = status;
	return OPCUA::StatusCode::ALL_OK;
}
OPCUA::StatusCode ProductionStationController::callStop_unloading(const int &XtimeoutX,std::string &Result)
{
	printf("Stop_unloadbox()  IN\n");
	view->getModel()->setDigitalOutput(LED_RED_PIN, true);
	std::string status = "ERROR";
	// setting up GPIO Mode
	view->getModel()->setGPIOCtrl(MOTOR_CLOCKWISE_GPIO_PIN, true);
	view->getModel()->setGPIOCtrl(MOTOR_ANTICLOCKWISE_GPIO_PIN, true);
	// stop motor
	view->getModel()->setGPIO(MOTOR_CLOCKWISE_GPIO_PIN, false);
	view->getModel()->setGPIO(MOTOR_ANTICLOCKWISE_GPIO_PIN, false);
	status = "UNLOADING_STOPPED";
	printf("Stop_unloadbox()  OUT\n");
	view->getModel()->setDigitalOutput(LED_RED_PIN, false);
	view->getModel()->setDigitalOutput(LED_YELLOW_PIN, false);
	Result = status;
	return OPCUA::StatusCode::ALL_OK;
}

int ProductionStationController::run()
{
	// this call executes the OPCUA server (until it is killed)
	return server.run();
}

} /* namespace Smart */
