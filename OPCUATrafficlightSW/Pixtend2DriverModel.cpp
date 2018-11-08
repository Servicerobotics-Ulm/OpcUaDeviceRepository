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

#include "Pixtend2DriverModel.h"

//  This is a Simulated variant of Pixtend2DriverModel

namespace Smart {

//PiXtend Simulation Usage related items
#define BY_MODEL 83
#define UPDATE_DELAY 30

Pixtend2DriverModel::Pixtend2DriverModel(const bool &startInternalThread)
:	OutputData(),	InputData(),	printAllLogs(false),	printDataStruct(true)
{}

Pixtend2DriverModel::~Pixtend2DriverModel() {}

void Pixtend2DriverModel::Sync()
{
	OutputData.byModelOut = BY_MODEL;
	if(printDataStruct)OutputData.Display();
}
void Pixtend2DriverModel::SyncIN()
{
	InputData.Display();
}
void Pixtend2DriverModel::SetNBit(uint8_t &i, const uint8_t &n, const bool &v)
{
	if(v)		i |= (1u << n);
	else		i &= ~(1u << n);
}
void Pixtend2DriverModel::setDigitalOutput(const uint8_t &number, const bool &value)
{	
	if(number < 4)
	{
		if(printAllLogs)std::cout<<"~~<<>>~~Pixtend2DriverModel||setDigitalOutput       ||"<<(int)number<<" | "<<(int)value<<std::endl;
		SetNBit(OutputData.byDigitalOut, number, value);
		Sync();
	}
}
void Pixtend2DriverModel::setDigitalOutput(const uint8_t &value)
{	
	if(value < 16)
	{
		if(printAllLogs)std::cout<<"~~<<>>~~Pixtend2DriverModel||setDigitalOutput       ||"<<(int)value<<std::endl;
		OutputData.byDigitalOut = value;
		Sync();
	}
}
bool Pixtend2DriverModel::getDigitalOutput(const uint8_t &number)
{	
	if(number < 4) {
		uint8_t value = OutputData.byDigitalOut & (1<<number);
		if(printAllLogs)std::cout<<"~~<<>>~~Pixtend2DriverModel||getDigitalOutput       ||"<<(int)number<<" | "<<(int)value<<std::endl;
		return value;
	}
	return false;
}
uint8_t Pixtend2DriverModel::getDigitalOutput()
{	
	if(printAllLogs)std::cout<<"~~<<>>~~Pixtend2DriverModel||getDigitalOutput       ||"<<(int)OutputData.byDigitalOut<<std::endl;
	return OutputData.byDigitalOut;
}

void Pixtend2DriverModel::setRelayOutput(const uint8_t &number, const bool &value)
{	
	if(number < 4)
	{
		if(printAllLogs)std::cout<<"~~<<>>~~Pixtend2DriverModel||setRelayOutput         ||"<<(int)number<<" | "<<(int)value<<std::endl;
		SetNBit(OutputData.byRelayOut, number, value);
		Sync();
	}
}
void Pixtend2DriverModel::setRelayOutput(const uint8_t &value)
{	
	if(value < 16)
	{
		if(printAllLogs)std::cout<<"~~<<>>~~Pixtend2DriverModel||setRelayOutput         ||"<<(int)value<<std::endl;
		OutputData.byRelayOut = value;
		Sync();
	}
}
bool Pixtend2DriverModel::getRelayOutput(const uint8_t &number)
{
	if(number < 4) {
		uint8_t value = OutputData.byRelayOut & (1<<number);
		if(printAllLogs)std::cout<<"~~<<>>~~Pixtend2DriverModel||getRelayOutput         ||"<<(int)number<<" | "<<(int)value<<std::endl;
		return value;
	}
	return false;
}
uint8_t Pixtend2DriverModel::getRelayOutput()
{	
	if(printAllLogs)std::cout<<"~~<<>>~~Pixtend2DriverModel||getRelayOutput         ||"<<(int)OutputData.byRelayOut<<std::endl;
	return OutputData.byRelayOut;
}

bool Pixtend2DriverModel::getDigitalInput(const uint8_t &number)
{	
	if(number < 4) {
		SyncIN();
		uint8_t value = InputData.byDigitalIn & (1<<number);
		if(printAllLogs)std::cout<<"~~<<>>~~Pixtend2DriverModel||getDigitalInput        ||"<<(int)number<<" | "<<(int)value<<std::endl;
		return value;
	}
	return false;
}
uint8_t Pixtend2DriverModel::getDigitalInput()
{	
	SyncIN();
	if(printAllLogs)std::cout<<"~~<<>>~~Pixtend2DriverModel||getDigitalInput        ||"<<(int)InputData.byDigitalIn<<std::endl;
	return InputData.byDigitalIn;
}
int Pixtend2DriverModel::waitOnDigitalInput(const uint8_t &number, const bool &value, const std::chrono::steady_clock::duration &timeout)
{
	int result = 0;
	std::chrono::time_point<std::chrono::system_clock> Start = std::chrono::system_clock::now();
	if(printAllLogs)std::cout<<"~~<<>>~~Pixtend2DriverModel||getDigitalInput        ||"<<(int)number<<" | "<<(int)value<<" | "
		<<std::chrono::duration_cast<std::chrono::seconds>(timeout).count()<<std::endl;
	while((getDigitalInput(number) != value) 
	  &&  (timeout > std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - Start)))
	{		
		std::this_thread::sleep_for(std::chrono::milliseconds(UPDATE_DELAY));
		if(printAllLogs)std::cout<<"~~<<>>~~Pixtend2DriverModel||getDigitalInput        ||"<<(int)number<<" | "<<(int)value <<std::endl;
		SyncIN();
	}
	return result;
}
int Pixtend2DriverModel::waitOnDigitalInput(const uint8_t &value, const std::chrono::steady_clock::duration &timeout)
{
	int result = 0;
	std::chrono::time_point<std::chrono::system_clock> Start = std::chrono::system_clock::now();
	if(printAllLogs)std::cout<<"~~<<>>~~Pixtend2DriverModel||getDigitalInput        ||"<<(int)value<<" | "
		<<std::chrono::duration_cast<std::chrono::seconds>(timeout).count()<<std::endl;
	while((getDigitalInput() != value)
	  &&  (timeout > std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - Start)))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(UPDATE_DELAY));
		if(printAllLogs)std::cout<<"~~<<>>~~Pixtend2DriverModel||getDigitalInput        ||"<<(int)value<<std::endl;
		SyncIN();
	}
	return result;
}
void Pixtend2DriverModel::setGPIOCtrl(const uint8_t &number, const bool &value)
{	
	if(number < 4)
	{
		if(printAllLogs)std::cout<<"~~<<>>~~Pixtend2DriverModel||setGPIOCtrl            ||"<<(int)number<<" | "<<(int)value<<std::endl;
		SetNBit(OutputData.byGPIOCtrl, number, value);
		Sync();
	}
}
void Pixtend2DriverModel::setGPIOCtrl(const uint8_t &value)
{	
	if(value < 16)
	{
		if(printAllLogs)std::cout<<"~~<<>>~~Pixtend2DriverModel||setGPIOCtrl            ||"<<(int)value<<std::endl;
		OutputData.byGPIOCtrl = value;
		Sync();
	}
}
bool Pixtend2DriverModel::getGPIOCtrl(const uint8_t &number)
{	
	if(number < 4) {
		uint8_t value = OutputData.byGPIOCtrl & (1<<number);
		if(printAllLogs)std::cout<<"~~<<>>~~Pixtend2DriverModel||getGPIOCtrl            ||"<<(int)number<<" | "<<(int)value<<std::endl;
		return value;
	}
	return false;
}
uint8_t Pixtend2DriverModel::getGPIOCtrl()
{	
	if(printAllLogs)std::cout<<"~~<<>>~~Pixtend2DriverModel||getGPIOCtrl            ||"<<(int)OutputData.byGPIOCtrl<<std::endl;
	return OutputData.byGPIOCtrl;
}
void Pixtend2DriverModel::setGPIO(const uint8_t &number, const bool &value)
{	
	if(number < 4)
	{
		if(printAllLogs)std::cout<<"~~<<>>~~Pixtend2DriverModel||setGPIO                ||"<<(int)number<<" | "<<(int)value<<std::endl;
		SetNBit(OutputData.byGPIOOut, number, value);
		Sync();
	}
}
void Pixtend2DriverModel::setGPIO(const uint8_t &value)
{	
	if(value < 16)
	{
		if(printAllLogs)std::cout<<"~~<<>>~~Pixtend2DriverModel||setGPIO                ||"<<(int)value<<std::endl;
		OutputData.byGPIOOut = value;
		Sync();
	}
}
bool Pixtend2DriverModel::getGPIO(const uint8_t &number)
{	
	if(number < 4) {
		uint8_t value = OutputData.byGPIOOut & (1<<number);
		if(printAllLogs)std::cout<<"~~<<>>~~Pixtend2DriverModel||getGPIO                ||"<<(int)number<<" | "<<(int)value<<std::endl;
		return value;
	}
	return false;
}
uint8_t Pixtend2DriverModel::getGPIO()
{	
	if(printAllLogs)std::cout<<"~~<<>>~~Pixtend2DriverModel||getGPIO                ||"<<(int)OutputData.byGPIOOut<<std::endl;
	return OutputData.byGPIOOut;
}
} /* namespace Smart */
