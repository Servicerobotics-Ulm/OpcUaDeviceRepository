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

#ifndef LinuxJoystickDriverModel_H_
#define LinuxJoystickDriverModel_H_

#include <MVC/AbstractModel.hh>

#include <set>
// C++11
#include <thread>
#include <atomic>

namespace Smart {

class LinuxJoystickDriverModel : public AbstractModel {
private:
	// internal thread handle
	std::thread thr;
	std::mutex thread_mutex;
	std::atomic<bool> cancel_thread;

	int Xpos;
	int Ypos;
	int X2pos;
	int Y2pos;
	int X3pos;
	int Y3pos;
	int Buttons;
	bool Button[10];

	int js_fd;

	void SetNBit(uint8_t &i, const uint8_t &n, const bool &v);

protected:
	// internal thread method
	void on_execute();

public:
	/// default constructor
	LinuxJoystickDriverModel(const std::string &devicePath="/dev/input/js0", const bool &startInternalThread=true);
	/// default destructor
	virtual ~LinuxJoystickDriverModel();

	/// start the internally used thread
	void startThread();
	/// stop the internally used thread
	void stopThread(const bool &waitTillStopped=true);


	/**
	 * JOYSTICK related methods from here
	 */
	int getXpos();
	int getYpos();
	int getX2pos();
	int getY2pos();
	int getX3pos();
	int getY3pos();
	int getButtons();
	bool getButton(const uint8_t &buttonNumber);
};

} /* namespace Smart */

#endif /* LinuxJoystickDriverModel_H_ */
