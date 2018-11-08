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

#ifndef PIXTEND2DRIVERMODEL_H_
#define PIXTEND2DRIVERMODEL_H_

#include "MVC/AbstractModel.hh"

#include <chrono>
#include <thread>
#include <string>
#include <iostream>

//  This is a Simulated variant of Pixtend2DriverModel

namespace Smart {

class OutputDataStruct
{
public:
	uint8_t byModelOut;
	uint8_t byDigitalOut;
	uint8_t byRelayOut;
	uint8_t byGPIOCtrl;
	uint8_t byGPIOOut;

	uint8_t byModelOut_old;
	uint8_t byDigitalOut_old;
	uint8_t byRelayOut_old;
	uint8_t byGPIOCtrl_old;
	uint8_t byGPIOOut_old;

	unsigned long count;

	bool ValueChanged()
	{
		if(byModelOut != byModelOut_old) return true;
		if(byDigitalOut != byDigitalOut_old) return true;
		if(byRelayOut != byRelayOut_old) return true;
		if(byGPIOCtrl != byGPIOCtrl_old) return true;
		if(byModelOut != byModelOut_old) return true;
		return false;
	}

	std::string byBit(uint8_t in)
	{
		std::string out = "";
		out = out + "[" + std::to_string((int) (in & (1<<3))>>3);
		out = out + " " + std::to_string((int) (in & (1<<2))>>2);
		out = out + " " + std::to_string((int) (in & (1<<1))>>1);
		out = out + " " + std::to_string((int) (in & (1<<0))>>0);
		out = out + "]";
		return out;
	}
	void Display()
	{
		if(ValueChanged())
		{
			std::cout<<"------------------------------------------------------------------------"<<count++<<std::endl;		
			std::cout<<"Pixtend2Simulated"<<std::endl;
			std::cout<<"byModelOut       :"<<(int)byModelOut<<std::endl;
			std::cout<<"byDigitalOut     :"<<(int)byDigitalOut<<byBit(byDigitalOut)<<std::endl;
			std::cout<<"byRelayOut       :"<<(int)byRelayOut<<byBit(byRelayOut)<<std::endl;
			std::cout<<"byGPIOCtrl       :"<<(int)byGPIOCtrl<<byBit(byGPIOCtrl)<<std::endl;
			std::cout<<"byGPIOOut        :"<<(int)byGPIOOut<<byBit(byGPIOOut)<<std::endl;
			byModelOut_old = byModelOut;
			byDigitalOut_old = byDigitalOut;
			byRelayOut_old = byRelayOut;
			byGPIOCtrl_old = byGPIOCtrl;
			byModelOut_old = byModelOut;
		}
	}
};
class InputDataStruct
{
public:
	uint8_t byDigitalIn;
	std::string byBit(uint8_t in)
	{
		std::string out = "";
		out = out + "[" + std::to_string((int) (in & (1<<3))>>3);
		out = out + " " + std::to_string((int) (in & (1<<2))>>2);
		out = out + " " + std::to_string((int) (in & (1<<1))>>1);
		out = out + " " + std::to_string((int) (in & (1<<0))>>0);
		out = out + "]";
		return out;
	}
	void Display()
	{
		int val;
		std::cout<<"------------------------------------------------------------------------New Input Request"<<std::endl;		
		std::cout<<"Pixtend2Simulated"<<std::endl;
		std::cout<<"byDigitalIn      :"<<(int)byDigitalIn<<byBit(byDigitalIn)<<std::endl;
		std::cout<<"Provide New Value for byDigitalIn   (0-15)or(-1 to retain old value)"<<std::endl;
		std::cin>>val;
		if(val >=0 && val<=15)
			byDigitalIn = (uint8_t)val;
		std::cout<<"------------------------------------------------------------------------"<<std::endl;		
		std::cout<<"Pixtend2Simulated"<<std::endl;
		std::cout<<"byDigitalIn      :"<<(int)byDigitalIn<<byBit(byDigitalIn)<<std::endl;
	}
};
class Pixtend2DriverModel : public AbstractModel {
private:
	OutputDataStruct	OutputData;
	InputDataStruct		InputData;
	//Utility Method to set nth bit of an integer i to a boolean value v
	void SetNBit(uint8_t &i, const uint8_t &n, const bool &v);
	void Sync();
	void SyncIN();
	bool printAllLogs;
	bool printDataStruct;
public:
	Pixtend2DriverModel(const bool &startInternalThread=false);
	virtual ~Pixtend2DriverModel();

	void setDigitalOutput(const uint8_t &number, const bool &value);
	void setDigitalOutput(const uint8_t &value);
	bool getDigitalOutput(const uint8_t &number);
	uint8_t getDigitalOutput();

	void setRelayOutput(const uint8_t &number, const bool &value);
	void setRelayOutput(const uint8_t &value);
	bool getRelayOutput(const uint8_t &number);
	uint8_t getRelayOutput();

	bool getDigitalInput(const uint8_t &number);
	uint8_t getDigitalInput();
	int waitOnDigitalInput(const uint8_t &number, const bool &value, const std::chrono::steady_clock::duration &timeout=std::chrono::steady_clock::duration::zero());
	int waitOnDigitalInput(const uint8_t &value, const std::chrono::steady_clock::duration &timeout=std::chrono::steady_clock::duration::zero());

	void setGPIOCtrl(const uint8_t &number, const bool &value);
	void setGPIOCtrl(const uint8_t &value);
	bool getGPIOCtrl(const uint8_t &number);
	uint8_t getGPIOCtrl();

	void setGPIO(const uint8_t &number, const bool &value);
	void setGPIO(const uint8_t &value);
	bool getGPIO(const uint8_t &number);
	uint8_t getGPIO();
};

} /* namespace Smart */

#endif /* PIXTEND2DRIVERMODEL_H_ */
