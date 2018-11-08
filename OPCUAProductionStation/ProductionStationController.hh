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

#ifndef PRODUCTIONSTATIONCONTROLLER_H_
#define PRODUCTIONSTATIONCONTROLLER_H_

#include <MVC/AbstractController.hh>

#include "ProductionStationView.hh"
#include "ProductionStationInterface.hh"
#include "OpcUaProductionStation.hh"

namespace Smart {

/**
 * This class implements the Controller part of the Model-View-Controller (MVC)
 * design pattern. As a second responsibility, this class also implements
 * the generated interface which is used by the internally initialized OPC UA
 * server to interact with the actual model. The actual model can be internally
 * accessed over the given view pointer. Conceptually, this class decouples
 * the OPC UA server from the Model and handles the lifecycle of the OPC UA server.
 */
class ProductionStationController : public AbstractController, public ProductionStationInterface
{
private:
	OPCUA::ProductionStation server;
	ProductionStationView *view;

public:
	ProductionStationController(ProductionStationView *view);
	virtual ~ProductionStationController();

	/// implements AbstractModelObserver
	virtual void update() override;
	
	
	/** XML Specific Getter function for entity isBoxPresent
	 *
	 *  This function gets isBoxPresent  from the Server
	 *  When class ProductionStation is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *	
	 *  @param value	:output parameter, returns the new value if StatusCode is ALL_OK
	 *
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode getIsBoxPresent(bool &isBoxPresent) const override;
	
	/** XML Specific Getter function for entity LED_RED
	 *
	 *  This function gets LED_RED  from the Server
	 *  When class ProductionStation is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *	
	 *  @param value	:output parameter, returns the new value if StatusCode is ALL_OK
	 *
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode getLED_RED(bool &lED_RED) const override;
	
	/** XML Specific Setter function for entity LED_RED
	 *
	 *  This function sets LED_RED  at the Server
	 *  When class ProductionStation is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *
	 *  @param value			:Value to be set
	 * 
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode setLED_RED(const bool &value) override;
	
	/** XML Specific Getter function for entity LED_YELLOW
	 *
	 *  This function gets LED_YELLOW  from the Server
	 *  When class ProductionStation is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *	
	 *  @param value	:output parameter, returns the new value if StatusCode is ALL_OK
	 *
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode getLED_YELLOW(bool &lED_YELLOW) const override;
	
	/** XML Specific Setter function for entity LED_YELLOW
	 *
	 *  This function sets LED_YELLOW  at the Server
	 *  When class ProductionStation is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *
	 *  @param value			:Value to be set
	 * 
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode setLED_YELLOW(const bool &value) override;
	
	/** XML Specific Getter function for entity LED_GREEN
	 *
	 *  This function gets LED_GREEN  from the Server
	 *  When class ProductionStation is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *	
	 *  @param value	:output parameter, returns the new value if StatusCode is ALL_OK
	 *
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode getLED_GREEN(bool &lED_GREEN) const override;
	
	/** XML Specific Setter function for entity LED_GREEN
	 *
	 *  This function sets LED_GREEN  at the Server
	 *  When class ProductionStation is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *
	 *  @param value			:Value to be set
	 * 
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	virtual OPCUA::StatusCode setLED_GREEN(const bool &value) override;
	
	/** XML Specific Caller function for method loadbox
	 *
	 *  This function calls loadbox at the Server
	 *  When class ConveyorBelt is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *
	*  @param timeout			: Input | DataTypeIdentifier:6(int) ValueRank:-1 ArrayDimensions:0			 	
	*  @param result			: Output| DataTypeIdentifier:12(std::string) ValueRank:-1 ArrayDimensions:0			 	
	 * 
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	 virtual OPCUA::StatusCode callLoadbox(const int &timeout, std::string &result) override;
	 
	/** XML Specific Caller function for method start_unloading
	 *
	 *  This function calls start_unloading at the Server
	 *  When class ConveyorBelt is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *
	*  @param XtimeoutX			: Input | DataTypeIdentifier:6(int) ValueRank:-1 ArrayDimensions:0			 	
	*  @param result			: Output| DataTypeIdentifier:12(std::string) ValueRank:-1 ArrayDimensions:0			 	
	 * 
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	 virtual OPCUA::StatusCode callStart_unloading(const int &XtimeoutX, std::string &result) override;
	 
	/** XML Specific Caller function for method stop_unloading
	 *
	 *  This function calls stop_unloading at the Server
	 *  When class ConveyorBelt is used with a Specific XML file to connect to
	 *  SeRoNet Servers which implements the device information model.
	 *
	*  @param XtimeoutX			: Input | DataTypeIdentifier:6(int) ValueRank:-1 ArrayDimensions:0			 	
	*  @param result			: Output| DataTypeIdentifier:12(std::string) ValueRank:-1 ArrayDimensions:0			 	
	 * 
	 *  @return status code
	 *	- ALL_OK
	 *  - DISCONNECTED
	 *  - ERROR_COMMUNICATION
	 */
	 virtual OPCUA::StatusCode callStop_unloading(const int &XtimeoutX, std::string &result) override;
	 
	
	/// call this method at the end of the main function
	virtual int run() override;
};

} /* namespace Smart */

#endif /* PRODUCTIONSTATIONCONTROLLER_H_ */
