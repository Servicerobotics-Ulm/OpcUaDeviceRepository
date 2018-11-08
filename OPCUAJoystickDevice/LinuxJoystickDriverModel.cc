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

#include "LinuxJoystickDriverModel.hh"

#include <chrono>
#include <iostream>
#include <thread>

#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>

namespace Smart {

LinuxJoystickDriverModel::LinuxJoystickDriverModel(const std::string &devicePath, const bool &startInternalThread)
:	cancel_thread(false)
{
	js_fd = open(devicePath.c_str(), O_RDONLY);
	if(js_fd < 0)
	{
		printf("Error: Unable to open %s for reading\n", devicePath.c_str());
	}

	changed_values = false;

	if(startInternalThread == true) {
		startThread();
	}
	Xpos = 0;
	Ypos = 0;
	X2pos = 0;
	Y2pos = 0;
	X3pos = 0;
	Y3pos = 0;
	Buttons = 0;
	Button[0] = false;
	Button[1] = false;
	Button[2] = false;
	Button[3] = false;
	Button[4] = false;
	Button[5] = false;
	Button[6] = false;
	Button[7] = false;
	Button[8] = false;
	Button[9] = false;
}

LinuxJoystickDriverModel::~LinuxJoystickDriverModel()
{
	// stop thread in any case (save to use even if thread is not started)
	stopThread();
	close(js_fd);
}

void LinuxJoystickDriverModel::startThread()
{
	cancel_thread = false;
	thr = std::thread(&LinuxJoystickDriverModel::on_execute, this);
}

void LinuxJoystickDriverModel::stopThread(const bool &waitTillStopped)
{
	cancel_thread = true;
	if(waitTillStopped == true && thr.joinable() == true) {
		// wait till thread stops by itself
		thr.join();
	}
}

void LinuxJoystickDriverModel::SetNBit(uint8_t &i, const uint8_t &n, const bool &v)
{
	if(v)		i |= (1u << n);
	else		i &= ~(1u << n);
}

void LinuxJoystickDriverModel::on_execute()
{
	// set nonblocking mode
	fcntl( js_fd, F_SETFL, O_NONBLOCK );

	while(!cancel_thread)
	{
		// read serial device
		js_event e;
		int num_bytes = read(js_fd, &e, sizeof(js_event));
		if(num_bytes > 0)
		{
			//printf("%d %d %d %d\n", e.time, e.value, e.type, e.number);
			changed_values = true;
			switch (e.type)
			{
				case JS_EVENT_BUTTON: 	{	  Button[e.number] = (bool) e.value;  break; }
				case JS_EVENT_AXIS: 	
				{
					switch(e.number)
					{
						case 0:	{	Xpos = 	e.value;	break;}
						case 1:	{	Ypos = 	e.value;	break;}
						case 2:	{	X2pos = e.value;	break;}
						case 3:	{	Y2pos = e.value;	break;}
						case 4:	{	X3pos = e.value;	break;}
						case 5:	{	Y3pos = e.value;	break;}
					}
					break;
				}
				default: changed_values = false;
			}
			if (changed_values)
			{
				  Buttons = 0;
				  int po2[] = {1,2,4,8,16,32,64,128,256,512};
				  for(int i=0; i<10; i++)
					  Buttons += po2[i] * Button[i];
				  printf(" Buttons: %d %d %d %d %d %d %d %d %d %d || Xpos:%d Ypos:%d X2pos:%d Y2pos:%d X3pos:%d Y3pos:%d\n",
					  Button[9],Button[8],Button[7],Button[6],Button[5],Button[4],Button[3],Button[2],Button[1],Button[0],
					  Xpos,Ypos,X2pos,Y2pos,X3pos,Y3pos);
			}
		}
		// sleep for 20 ms
		std::this_thread::sleep_for (std::chrono::milliseconds(20));
	}
}

int LinuxJoystickDriverModel::getXpos(){return Xpos;}
int LinuxJoystickDriverModel::getYpos(){return Ypos;}
int LinuxJoystickDriverModel::getX2pos(){return X2pos;}
int LinuxJoystickDriverModel::getY2pos(){return Y2pos;}
int LinuxJoystickDriverModel::getX3pos(){return X3pos;}
int LinuxJoystickDriverModel::getY3pos(){return Y3pos;}
int LinuxJoystickDriverModel::getButtons(){return Buttons;}
bool LinuxJoystickDriverModel::getButton(const uint8_t &buttonNumber)
{
	if (buttonNumber < 8)
		return Button[buttonNumber];
	return bool();
}

} /* namespace Smart */
