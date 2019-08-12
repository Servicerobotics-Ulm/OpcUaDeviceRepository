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
