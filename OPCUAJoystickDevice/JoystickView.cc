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

#include "JoystickView.hh"

namespace Smart {

JoystickView::JoystickView(LinuxJoystickDriverModel *model)
:	AbstractView(model)
{  }

JoystickView::~JoystickView()
{  }

void JoystickView::update()
{
	//FIXME: implement this method
}

LinuxJoystickDriverModel* JoystickView::getModel() const {
	return dynamic_cast<LinuxJoystickDriverModel*>(model);
}

} /* namespace Smart */
